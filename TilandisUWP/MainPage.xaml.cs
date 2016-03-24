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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TilandisUWP
{
    /// <summary>
    /// Main page.
    /// </summary>
    public sealed partial class MainPage : Page {
        TileManager tm;
        public MainPage() {
            this.InitializeComponent();

            tm = new TileManager();
            tm.RequestTileEditor += clbk_open_tile_editor;

            SplitViewREF.Content = tm;
        }

        private void clbk_open_tile_editor(object sender, EventArgs e) {
            SplitViewREF.Content = new TileEditor();
        }

        private void clk_nav_flyout(object sender, PointerRoutedEventArgs e) {
            SplitViewREF.IsPaneOpen = !SplitViewREF.IsPaneOpen;
        }

        private void clk_nav_tiles(object sender, PointerRoutedEventArgs e) {
            SplitViewREF.IsPaneOpen = false;
            SplitViewREF.Content = tm;
        }

        private void clk_nav_settings(object sender, PointerRoutedEventArgs e) {
            SplitViewREF.IsPaneOpen = false;
            SplitViewREF.Content = new Settings();
        }

        public void request_navigation<T>() where T : Page, new() {
            SplitViewREF.Content = new T();
        }
    }
}
