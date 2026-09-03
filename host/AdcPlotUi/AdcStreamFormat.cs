namespace AdcPlotUi;

/// <summary>
/// Stream/sample constants matching adc_c2h_axis_bridge.v and read_adc_stream.py.
/// </summary>
internal static class AdcStreamFormat
{
    public const int SampleBytes = 2;
    public const int SamplesPerBeat = 8;
    public const int PacketBeats = 512;
    public const int PacketBytes = PacketBeats * SamplesPerBeat * SampleBytes;
    public const int SamplesPerPacket = PacketBytes / SampleBytes;

    public const ushort ChannelIdMask = 0x8000;
    public const ushort OfaMask = 0x4000;
    public const ushort SampleMask = 0x3FFF;

    public static readonly int[] DefaultAdcChannels = [0, 1];

    public static string DefaultC2hDevice(int xdmaIndex) =>
        $"/dev/xdma{xdmaIndex}_c2h_1";

    public static string ChannelName(int channelId) =>
        channelId == 0 ? "A" : "B";
}
