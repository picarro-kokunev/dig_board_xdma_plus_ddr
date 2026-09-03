using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;

namespace AdcPlotUi;

public partial class App : Application
{
  internal static PlotSettings StartupSettings { get; set; } = new();

  public override void Initialize()
  {
    AvaloniaXamlLoader.Load(this);
  }

  public override void OnFrameworkInitializationCompleted()
  {
    if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
    {
      desktop.MainWindow = new MainWindow(StartupSettings);
    }

    base.OnFrameworkInitializationCompleted();
  }
}
