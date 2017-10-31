using System.Collections.Generic;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using ParserBridge;
using BTHLibrary;

namespace MainProject
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static RequestController MainController { get; }
        private Dictionary<MultipleReadData, Label> AllLabels;
        private Dictionary<MultipleReadData, double> RealTimeData;
        private Thread ConstantReadThread;

        public delegate void UpdateUIControls();

        static MainWindow()
        {
            MainController = new RequestController();
        }

        public MainWindow() 
        {
            InitializeComponent();

            AllLabels = new Dictionary<MultipleReadData, Label>
            {
                { MultipleReadData.VehicleSpeed, SpeedLabel },
                { MultipleReadData.EngineLoad, EngineLoadLabel },
                { MultipleReadData.EngineCoolantTemperature, CoolantTemperatureLabel },
                { MultipleReadData.EngineOilTemperature, EngineOilTemperatureLabel },
                { MultipleReadData.FuelPressure, FuelPressureLabel },
                { MultipleReadData.IntakeManifoldAbsolutePressure, IntakeManifoldAbsolutePressureLabel },
                { MultipleReadData.IntakeAirTemperature, IntakeAirTemperatureLabel },
                { MultipleReadData.ThrottlePosition, ThrottlePositionLabel },
                { MultipleReadData.RelativeAcceleratorPedalPosition, RelativeAcceleratorPedalPositionLabel }
            };
        }

        private void RequestRealTimeDataAndPresentToUser()
        {
            MainController.RequestRealTimeData();

            RealTimeData = MainController.ResponseInterpreter.GetInterpretedRealTimeParameters();

            foreach (MultipleReadData NextKey in RealTimeData.Keys)
                AllLabels[NextKey].Content = RealTimeData[NextKey];
        }

        private void ConstantRead()
        {
            bool? IsConstantReadChecked = true;
            while (IsConstantReadChecked == true)
            {
                ConstantReadCheckBox.Dispatcher.Invoke((() => IsConstantReadChecked = ConstantReadCheckBox.IsChecked));

                Thread.Sleep(1000);

                Dispatcher.Invoke(new UpdateUIControls(RequestRealTimeDataAndPresentToUser), null);
            }
        }

        private void SearchButton_Click(object sender, RoutedEventArgs e)
        {
            SearchWindow Searcher = new SearchWindow();
            Searcher.ShowDialog();

            if (!Searcher.IfConnected)
                return;

            SearchButton.IsEnabled = false;
            RefreshButton.IsEnabled = true;
            ConstantReadCheckBox.IsEnabled = true;

            MainController.InitializeELM();

            MainController.RequestVehicleInformation();

            Dictionary<SingleReadData, string> VehicleInformation = MainController.ResponseInterpreter.GetInterpretedVehicleInformation();

            RetrievedProtocolTextBlock.Text = VehicleInformation[SingleReadData.Protocol];
            RetrievedStandardTextBlock.Text = VehicleInformation[SingleReadData.OBDStandard];
            RetrievedFuelTypeTextBlock.Text = VehicleInformation[SingleReadData.FuelType];

            VehicleInformation.Clear();
        }

        private void RefreshButton_Click(object sender, RoutedEventArgs e)
        {
            RequestRealTimeDataAndPresentToUser();
        }

        private void ConstantReadCheckBox_Checked(object sender, RoutedEventArgs e)
        {

            ConstantReadThread = new Thread(new ThreadStart(ConstantRead));
            ConstantReadThread.Start();

            RefreshButton.IsEnabled = false;
        }

        private void ConstantReadCheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            //ConstantReadThread.Join();
            ConstantReadThread.Abort();

            RefreshButton.IsEnabled = true;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (MainController.MainExecuter.ELMClient.IfConnected)
            {
                MainController.MainExecuter.ExecuteCommand("ATZ\r", true);
                MainController.MainExecuter.JoinThread();
            }

            if (ConstantReadCheckBox.IsChecked == true)
                ConstantReadThread.Abort();
        }
    }
}
