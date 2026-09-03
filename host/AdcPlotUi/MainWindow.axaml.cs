using Avalonia.Controls;
using Avalonia.Interactivity;
using Avalonia.Threading;
using ScottPlot;

namespace AdcPlotUi;

public partial class MainWindow : Window
{
  private static readonly int[] AllAdcChannels = [0, 1];

  private static readonly ScottPlot.Color[] ChannelColors =
  [
    ScottPlot.Color.FromHex("#1f77b4"),
    ScottPlot.Color.FromHex("#ff7f0e"),
  ];

  private readonly PlotSettings _settings;
  private readonly Dictionary<int, RollingSampleBuffer> _buffers = new();
  private AdcStreamReader? _reader;
  private DispatcherTimer? _refreshTimer;
  private bool _controlsReady;

  public MainWindow() : this(new PlotSettings())
  {
  }

  public MainWindow(PlotSettings settings)
  {
    _settings = settings;
    InitializeComponent();
    InitializeControls();
    InitializeBuffers(settings.WindowSamples);

    ConfigurePlot();
    UpdateStatusText();
    Opened += OnOpened;
    Closed += OnClosed;
    _controlsReady = true;
  }

  private void InitializeControls()
  {
    ChannelACheckBox.IsChecked = _settings.AdcChannels.Contains(0);
    ChannelBCheckBox.IsChecked = _settings.AdcChannels.Contains(1);
    ChannelACheckBox.IsCheckedChanged += OnChannelToggled;
    ChannelBCheckBox.IsCheckedChanged += OnChannelToggled;
    WindowSamplesInput.Value = _settings.WindowSamples;
    RefreshMsInput.Value = _settings.RefreshMs;
  }

  private void InitializeBuffers(int windowSamples)
  {
    _buffers.Clear();
    foreach (var ch in AllAdcChannels)
      _buffers[ch] = new RollingSampleBuffer(windowSamples);
  }

  private IReadOnlyList<int> GetEnabledChannels()
  {
    var channels = new List<int>(2);
    if (ChannelACheckBox.IsChecked == true)
      channels.Add(0);
    if (ChannelBCheckBox.IsChecked == true)
      channels.Add(1);
    return channels;
  }

  private void UpdateStatusText()
  {
    var channelNames = string.Join(
      ",",
      GetEnabledChannels().Select(AdcStreamFormat.ChannelName));
    if (channelNames.Length == 0)
      channelNames = "(none)";

    var windowSamples = (int)(WindowSamplesInput.Value ?? _settings.WindowSamples);
    var refreshMs = (int)(RefreshMsInput.Value ?? _settings.RefreshMs);
    StatusText.Text =
      $"Plotting ADC samples from {_settings.ResolvedC2hPath} " +
      $"(rolling window: {windowSamples} samples/channel, " +
      $"refresh: {refreshMs} ms, channels={channelNames})";
  }

  private void ConfigurePlot()
  {
    var plot = PlotView.Plot;
    plot.Title($"Live ADC stream: {_settings.ResolvedC2hPath}");
    plot.XLabel("Sample index (rolling window)");
    plot.YLabel("ADC code (unsigned)");
    plot.ShowLegend(Alignment.UpperRight);
    plot.Grid.MajorLineColor = ScottPlot.Color.FromHex("#000000").WithAlpha(0.15);
  }

  private void OnChannelToggled(object? sender, RoutedEventArgs e)
  {
    if (!_controlsReady)
      return;

    if (GetEnabledChannels().Count == 0)
    {
      _controlsReady = false;
      if (sender == ChannelACheckBox)
        ChannelACheckBox.IsChecked = true;
      else
        ChannelBCheckBox.IsChecked = true;
      _controlsReady = true;
      ErrorText.Text = "At least one ADC channel must remain enabled.";
      return;
    }

    ErrorText.Text = string.Empty;
    UpdateStatusText();
    UpdatePlot();
  }

  private void OnWindowSamplesChanged(object? sender, NumericUpDownValueChangedEventArgs e)
  {
    if (!_controlsReady || e.NewValue is not decimal newValue)
      return;

    var windowSamples = (int)newValue;
    if (windowSamples <= 0)
      return;

    foreach (var buffer in _buffers.Values)
      buffer.Resize(windowSamples);

    UpdateStatusText();
  }

  private void OnRefreshMsChanged(object? sender, NumericUpDownValueChangedEventArgs e)
  {
    if (!_controlsReady || e.NewValue is not decimal newValue)
      return;

    var refreshMs = (int)newValue;
    if (refreshMs <= 0)
      return;

    if (_refreshTimer is not null)
      _refreshTimer.Interval = TimeSpan.FromMilliseconds(refreshMs);

    UpdateStatusText();
  }

  private void OnOpened(object? sender, EventArgs e)
  {
    _reader = new AdcStreamReader(_settings.ResolvedC2hPath, _settings.PacketBytes);
    _reader.Start();

    var startupTimer = new DispatcherTimer
    {
      Interval = TimeSpan.FromMilliseconds(200),
    };
    startupTimer.Tick += (_, _) =>
    {
      startupTimer.Stop();
      if (_reader.Error is Exception ex)
      {
        ErrorText.Text = $"Failed to open/read {_settings.ResolvedC2hPath}: {ex.Message}";
        return;
      }

      var refreshMs = (int)(RefreshMsInput.Value ?? _settings.RefreshMs);
      _refreshTimer = new DispatcherTimer
      {
        Interval = TimeSpan.FromMilliseconds(refreshMs),
      };
      _refreshTimer.Tick += (_, _) => UpdatePlot();
      _refreshTimer.Start();
    };
    startupTimer.Start();
  }

  private void OnClosed(object? sender, EventArgs e)
  {
    _refreshTimer?.Stop();
    _reader?.Dispose();
  }

  private void UpdatePlot()
  {
    if (_reader is null)
      return;

    var enabledChannels = GetEnabledChannels();

    foreach (var packet in _reader.PopAll())
    {
      foreach (var ch in enabledChannels)
        _buffers[ch].AddRange(AdcSampleDecoder.FilterValues(packet, ch));
    }

    if (_reader.Error is Exception ex)
    {
      ErrorText.Text = $"Stream ended: {ex.Message}";
      _refreshTimer?.Stop();
      Close();
      return;
    }

    var plot = PlotView.Plot;
    plot.Clear();
    ConfigurePlot();

    var allValues = new List<ushort>();
    var maxLen = 1;

    foreach (var ch in enabledChannels)
    {
      var values = _buffers[ch].Snapshot();
      if (values.Length == 0)
        continue;

      var ys = values.Select(v => (double)v).ToArray();
      var signal = plot.Add.Signal(ys);
      signal.LegendText = $"Channel {AdcStreamFormat.ChannelName(ch)}";
      signal.Color = ChannelColors[ch % ChannelColors.Length];
      signal.LineWidth = 0.8f;
      signal.LineStyle.Pattern = LinePattern.Dashed;
      allValues.AddRange(values);
      maxLen = Math.Max(maxLen, values.Length);
    }

    if (allValues.Count > 0)
    {
      var lo = allValues.Min();
      var hi = allValues.Max();
      var pad = Math.Max(1, (int)(0.05 * (hi - lo + 1)));
      plot.Axes.SetLimitsX(0, maxLen);
      plot.Axes.SetLimitsY(lo - pad, hi + pad);
    }

    PlotView.Refresh();
  }
}
