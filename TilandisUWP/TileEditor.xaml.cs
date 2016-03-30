﻿using System;
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
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace TilandisUWP {
    /// <summary>
    /// Tile editor screen. Users can configure tile images and launch settings here.
    /// </summary>
    public sealed partial class TileEditor : Page {
        public BitmapImage bmi_largetile = new BitmapImage();
        public BitmapImage bmi_widetile = new BitmapImage();
        public BitmapImage bmi_medtile = new BitmapImage();
        public BitmapImage bmi_smalltile = new BitmapImage();

        public TileEditor() {
            this.InitializeComponent();

            if (App.is_dark) {
                bmi_largetile.UriSource = new Uri(BaseUri, "/Assets/editor/310x310d.png");
                bmi_widetile.UriSource = new Uri(BaseUri, "/Assets/editor/310x150d.png");
                bmi_medtile.UriSource = new Uri(BaseUri, "/Assets/editor/150x150d.png");
                bmi_smalltile.UriSource = new Uri(BaseUri, "/Assets/editor/71x71d.png");
            } else {
                bmi_largetile.UriSource = new Uri(BaseUri, "/Assets/editor/310x310.png");
                bmi_widetile.UriSource = new Uri(BaseUri, "/Assets/editor/310x150.png");
                bmi_medtile.UriSource = new Uri(BaseUri, "/Assets/editor/150x150.png");
                bmi_smalltile.UriSource = new Uri(BaseUri, "/Assets/editor/71x71.png");
            }

            img_large.Source = bmi_largetile;
            img_wide.Source = bmi_widetile;
            img_med.Source = bmi_medtile;
            img_small.Source = bmi_smalltile;
        }

        private void clk_savetile(object sender, RoutedEventArgs e) {
            if (App.tiles.ContainsKey(edt_linkname.Text)) {
                // TODO: figure out what happens if the tile's already pinned

                App.tiles.Remove(edt_linkname.Text);
            }

            var this_tile = new Dictionary<string, string>();
            this_tile["str_largepath"] = bmi_largetile.UriSource.ToString();
            this_tile["str_widepath"] = bmi_widetile.UriSource.ToString();
            this_tile["str_medpath"] = bmi_medtile.UriSource.ToString();
            this_tile["str_smallpath"] = bmi_smalltile.UriSource.ToString();

            App.tiles.Add(edt_linkname.Text, this_tile);

            var dialog = new Windows.UI.Popups.MessageDialog(edt_linkname.Text);
            System.Threading.Tasks.Task.Run(() => dialog.ShowAsync());
        }
    }
}
