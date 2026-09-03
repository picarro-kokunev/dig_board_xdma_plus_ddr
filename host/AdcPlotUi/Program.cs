using System;
using Avalonia;

namespace AdcPlotUi;

internal static class Program
{
  [STAThread]
  public static int Main(string[] args)
  {
    PlotSettings settings;
    try
    {
      settings = PlotArgsParser.Parse(args);
    }
    catch (Exception ex)
    {
      Console.Error.WriteLine($"error: {ex.Message}");
      Console.Error.WriteLine("Use --help for usage.");
      return 1;
    }

    App.StartupSettings = settings;
    BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
    return 0;
  }

  public static AppBuilder BuildAvaloniaApp()
    => AppBuilder.Configure<App>()
      .UsePlatformDetect()
#if DEBUG
      .WithDeveloperTools()
#endif
      .WithInterFont()
      .LogToTrace();
}
