namespace AdcPlotUi;

public sealed record PlotSettings
{
  public int XdmaIndex { get; init; } = 0;
  public string? C2hPath { get; init; }
  public int PacketBytes { get; init; } = AdcStreamFormat.PacketBytes;
  public int WindowSamples { get; init; } = 128; // changed from AdcStreamFormat.SamplesPerPacket;
  public int RefreshMs { get; init; } = 100;
  public IReadOnlyList<int> AdcChannels { get; init; } = AdcStreamFormat.DefaultAdcChannels;

  public string ResolvedC2hPath =>
    C2hPath ?? AdcStreamFormat.DefaultC2hDevice(XdmaIndex);
}
