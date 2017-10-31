using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace MainProject
{
    /// <summary>
    /// Interaction logic for SearchWindow.xaml
    /// </summary>
    public partial class SearchWindow : Window
    {
        private List<string> NameList { get; set; }
        public bool IfConnected { get; set; }

        public SearchWindow()
        {
            InitializeComponent();
            IfConnected = false;
        }

        private void AvailableDevicesListBox_Loaded(object sender, RoutedEventArgs e)
        {
            MainWindow.MainController.MainExecuter.ELMClient.DiscoverBTHDevices();
            NameList = MainWindow.MainController.MainExecuter.ELMClient.DeviceNameList;

            InfoTextBlock.Text = "Znaleziono następujące urządzenia Bluetooth. Proszę wybrać odpowiednie urządzenie, a następnie nacisnąć przycisk \"Połącz\"";

            AvailableDevicesListBox.ItemsSource = NameList;
        }

        private void ConnectButton_Click(object sender, RoutedEventArgs e)
        {
            string DevicePin = string.Empty;

            if (!MainWindow.MainController.MainExecuter.ELMClient.CheckIfAuthenticated(AvailableDevicesListBox.SelectedItem.ToString()))
            {
                PinInput PIN = new PinInput();
                PIN.ShowDialog();

                if (!PIN.IfEntered)
                    return;

                DevicePin = PIN.EnteredPin;
            }

            MainWindow.MainController.MainExecuter.SetTheServer(AvailableDevicesListBox.SelectedItem.ToString(), DevicePin);

            try
            {
                MainWindow.MainController.MainExecuter.StartThread();
                IfConnected = true;
                string CheckResponse = MainWindow.MainController.MainExecuter.ExecuteCommand("ATI\r", false);
                CheckResponse = MainWindow.MainController.MainExecuter.ExecuteCommand("ATI\r", false);

                if (!CheckResponse.Contains("ELM327"))
                    throw new BTHLibrary.BTHException("Wybrane urządzenie to nie ELM327");

                Close();
            }
            catch(Exception exc)
            {
                MessageBox.Show(this, exc.Message, "Błąd", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void AvailableDevicesListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ConnectButton.IsEnabled = true;
        }
    }
}
