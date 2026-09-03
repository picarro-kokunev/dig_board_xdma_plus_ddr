namespace AdcPlotUi;

internal sealed class RollingSampleBuffer
{
  private int _capacity;
  private readonly List<ushort> _items;

  public RollingSampleBuffer(int capacity)
  {
    if (capacity <= 0)
      throw new ArgumentOutOfRangeException(nameof(capacity));
    _capacity = capacity;
    _items = new List<ushort>(Math.Min(capacity, 1024));
  }

  public int Capacity => _capacity;

  public void Resize(int capacity)
  {
    if (capacity <= 0)
      throw new ArgumentOutOfRangeException(nameof(capacity));

    _capacity = capacity;
    while (_items.Count > _capacity)
      _items.RemoveAt(0);
  }

  public void Clear() => _items.Clear();

  public void AddRange(IEnumerable<ushort> values)
  {
    foreach (var value in values)
    {
      if (_items.Count >= _capacity)
        _items.RemoveAt(0);
      _items.Add(value);
    }
  }

  public ushort[] Snapshot() => _items.ToArray();

  public int Count => _items.Count;
}
