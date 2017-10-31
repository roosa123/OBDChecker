using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MainProject
{
    /// <summary>
    /// Interaction logic for PinInput.xaml
    /// </summary>
    public partial class PinInput : Window
    {
        public string EnteredPin { get; set; }
        public bool IfEntered { get; set; }

        public PinInput()
        {
            InitializeComponent();
            IfEntered = false;
        }

        private void PINTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (PINTextBox.Text != string.Empty)
                ConfirmButton.IsEnabled = true;
            else
                ConfirmButton.IsEnabled = false;
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void ConfirmButton_Click(object sender, RoutedEventArgs e)
        {
            IfEntered = true;
            EnteredPin = PINTextBox.Text;
            Close();
        }
    }
}
