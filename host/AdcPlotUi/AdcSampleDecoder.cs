namespace AdcPlotUi;

internal readonly record struct DecodedSample(byte Channel, byte Ofa, ushort Value);

internal static class AdcSampleDecoder
{
  public static DecodedSample[] Decode(byte[] rawBytes)
  {
    if (rawBytes.Length % AdcStreamFormat.SampleBytes != 0)
      throw new ArgumentException($"raw buffer length {rawBytes.Length} is not a multiple of 2");

    var count = rawBytes.Length / AdcStreamFormat.SampleBytes;
    var samples = new DecodedSample[count];
    for (var i = 0; i < count; i++)
    {
      var word = BitConverter.ToUInt16(rawBytes, i * AdcStreamFormat.SampleBytes);
      samples[i] = new DecodedSample(
        Channel: (byte)((word & AdcStreamFormat.ChannelIdMask) >> 15),
        Ofa: (byte)((word & AdcStreamFormat.OfaMask) >> 14),
        Value: (ushort)(word & AdcStreamFormat.SampleMask));
    }

    return samples;
  }

  public static IEnumerable<ushort> FilterValues(
    IEnumerable<DecodedSample> samples,
    int channelId)
  {
    foreach (var sample in samples)
    {
      if (sample.Channel == channelId)
        yield return sample.Value;
    }
  }
}
