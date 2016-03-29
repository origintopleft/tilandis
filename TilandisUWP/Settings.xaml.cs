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
            edt_resport.Text = ((int) App.adc_local.Values["int_port"]).ToString();

            cbx_darkui.IsChecked = (bool) App.adc_local.Values["bool_darkui"];
        }

        private void clbk_launchprotocol_edited(object sender, TextChangedEventArgs args) {
            App.adc_local.Values["str_launchprotocol"] = edt_launchprotocol.Text;
        }
        private void clbk_ctlprotocol_edited(object sender, TextChangedEventArgs args) {
            App.adc_local.Values["str_controlprotocol"] = edt_ctlprotocol.Text;
        }

        private void clk_darkuibox(object sender, RoutedEventArgs e) {
            App.adc_local.Values["bool_darkui"] = cbx_darkui.IsChecked;
        }

        private void clbk_port_edited(object sender, TextChangedEventArgs e) {
            int result;
            if (int.TryParse(edt_resport.Text, out result)) {
                edt_resport.Text = result.ToString(); // Just in case there were letters and we just stripped them

                if (result > 65535) {
                    // Invalid port number
                    Random rng = new Random();
                    result = rng.Next(50000, 60000);
                    edt_resport.Text = result.ToString();
                }
            } else {
                // Bad text
                Random rng = new Random();
                result = rng.Next(50000, 60000);
                edt_resport.Text = result.ToString();
            }

            App.adc_local.Values["int_port"] = result;
        }
    }
}
