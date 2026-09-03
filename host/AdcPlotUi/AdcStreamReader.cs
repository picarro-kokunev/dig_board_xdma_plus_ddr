namespace AdcPlotUi;

internal sealed class AdcStreamReader : IDisposable
{
  private readonly string _path;
  private readonly int _packetBytes;
  private readonly int _maxQueue;
  private readonly object _queueLock = new();
  private readonly Queue<DecodedSample[]> _queue = new();
  private readonly CancellationTokenSource _cts = new();
  private Thread? _thread;
  private Exception? _error;

  public AdcStreamReader(string path, int packetBytes, int maxQueue = 8)
  {
    _path = path;
    _packetBytes = packetBytes;
    _maxQueue = maxQueue;
  }

  public Exception? Error => Volatile.Read(ref _error);

  public void Start()
  {
    if (_thread is not null)
      return;

    _thread = new Thread(ReadLoop)
    {
      IsBackground = true,
      Name = "adc-c2h-reader",
    };
    _thread.Start();
  }

  public void Stop()
  {
    _cts.Cancel();
    _thread?.Join(TimeSpan.FromSeconds(2));
  }

  public IReadOnlyList<DecodedSample[]> PopAll()
  {
    lock (_queueLock)
    {
      if (_queue.Count == 0)
        return Array.Empty<DecodedSample[]>();

      var items = _queue.ToArray();
      _queue.Clear();
      return items;
    }
  }

  private void ReadLoop()
  {
    try
    {
      using var stream = new FileStream(
        _path,
        FileMode.Open,
        FileAccess.Read,
        FileShare.ReadWrite,
        bufferSize: _packetBytes,
        options: FileOptions.SequentialScan);

      var buffer = new byte[_packetBytes];
      while (!_cts.IsCancellationRequested)
      {
        ReadExact(stream, buffer);
        var decoded = AdcSampleDecoder.Decode(buffer);
        lock (_queueLock)
        {
          while (_queue.Count >= _maxQueue)
            _queue.Dequeue();
          _queue.Enqueue(decoded);
        }
      }
    }
    catch (Exception ex) when (ex is not OperationCanceledException)
    {
      Volatile.Write(ref _error, ex);
    }
  }

  private static void ReadExact(Stream stream, byte[] buffer)
  {
    var offset = 0;
    while (offset < buffer.Length)
    {
      var read = stream.Read(buffer, offset, buffer.Length - offset);
      if (read == 0)
      {
        throw new EndOfStreamException(
          $"device closed/EOF after {offset}/{buffer.Length} bytes " +
          "(is the FPGA programmed and streaming?)");
      }

      offset += read;
    }
  }

  public void Dispose()
  {
    Stop();
    _cts.Dispose();
  }
}
