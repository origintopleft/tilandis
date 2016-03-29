using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace TilandisUWP
{
    /// <summary>
    /// Settings Page
    /// </summary>
    public sealed partial class Settings : Page
    {
        public Settings()
        {
            this.InitializeComponent();

            edt_launchprotocol.Text = (string) App.adc_local.Values["str_launchprotocol"];
            edt_ctlprotocol.Text = (string) App.adc_local.Values["str_controlprotocol"];

            cbx_darkui.IsChecked = (bool) App.adc_local.Values["bool_darkui"];
        }

        private void clbk_launchprotocol_edited(TextBox sender, TextCompositionEndedEventArgs args) {
            App.adc_local.Values["str_launchprotocol"] = edt_launchprotocol.Text;
        }
        private void clbk_ctlprotocol_edited(TextBox sender, TextCompositionEndedEventArgs args) {
            App.adc_local.Values["str_controlprotocol"] = edt_ctlprotocol.Text;
        }

        private void clk_darkuibox(object sender, RoutedEventArgs e) {
            App.adc_local.Values["bool_darkui"] = cbx_darkui.IsChecked;
        }
    }
}
