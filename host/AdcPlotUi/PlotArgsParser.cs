namespace AdcPlotUi;

internal static class PlotArgsParser
{
  private static readonly HashSet<int> ValidAdcChannels = [0, 1];

  public static PlotSettings Parse(string[] args)
  {
    var settings = new PlotSettings();

    for (var i = 0; i < args.Length; i++)
    {
      switch (args[i])
      {
        case "--xdma-index":
          settings = settings with { XdmaIndex = ReadInt(args, ref i, "--xdma-index") };
          break;
        case "--c2h":
          settings = settings with { C2hPath = ReadString(args, ref i, "--c2h") };
          break;
        case "--packet-bytes":
          settings = settings with { PacketBytes = ReadInt(args, ref i, "--packet-bytes") };
          break;
        case "--window-samples":
          settings = settings with { WindowSamples = ReadInt(args, ref i, "--window-samples") };
          break;
        case "--refresh-ms":
          settings = settings with { RefreshMs = ReadInt(args, ref i, "--refresh-ms") };
          break;
        case "--adc-ch-list":
          settings = settings with { AdcChannels = ParseAdcChannelList(ReadString(args, ref i, "--adc-ch-list")) };
          break;
        case "-h":
        case "--help":
          PrintHelp();
          Environment.Exit(0);
          break;
        default:
          throw new ArgumentException($"unknown argument: {args[i]}");
      }
    }

    Validate(settings);
    return settings;
  }

  private static void Validate(PlotSettings settings)
  {
    if (settings.PacketBytes <= 0)
      throw new ArgumentException("packet-bytes must be > 0");
    if (settings.WindowSamples <= 0)
      throw new ArgumentException("window-samples must be > 0");
    if (settings.RefreshMs <= 0)
      throw new ArgumentException("refresh-ms must be > 0");
    if (settings.AdcChannels.Count == 0)
      throw new ArgumentException("adc-ch-list must list at least one channel");
    foreach (var ch in settings.AdcChannels)
    {
      if (!ValidAdcChannels.Contains(ch))
        throw new ArgumentException($"invalid adc channel id {ch}; valid values are 0 (A) and 1 (B)");
    }
  }

  private static IReadOnlyList<int> ParseAdcChannelList(string value)
  {
    var parts = value.Split(',', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries);
    if (parts.Length == 0)
      throw new ArgumentException("adc-ch-list must list at least one channel");
    return parts.Select(int.Parse).ToArray();
  }

  private static int ReadInt(string[] args, ref int index, string name)
  {
    if (index + 1 >= args.Length)
      throw new ArgumentException($"missing value for {name}");
    if (!int.TryParse(args[++index], out var value))
      throw new ArgumentException($"invalid integer for {name}: {args[index]}");
    return value;
  }

  private static string ReadString(string[] args, ref int index, string name)
  {
    if (index + 1 >= args.Length)
      throw new ArgumentException($"missing value for {name}");
    return args[++index];
  }

  private static void PrintHelp()
  {
    Console.WriteLine("""
      Live ADC plot UI (equivalent to read_adc_stream.py plot).

      Usage:
        dotnet run -- [options]

      Options:
        --xdma-index N        XDMA device index (default: 0)
        --c2h PATH            Override C2H channel-1 device path
        --packet-bytes N      Bytes per read() call (default: 8192)
        --window-samples N    Rolling window per channel (default: 4096)
        --refresh-ms N        Plot refresh interval in ms (default: 100)
        --adc-ch-list IDS     Comma-separated channel ids: 0=A, 1=B (default: 0,1)
        -h, --help            Show this help
      """);
  }
}
