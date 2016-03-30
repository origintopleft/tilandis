﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
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

            clk_nav_tiles(null, null);
        }

        private void clbk_open_tile_editor(object sender, TileEditorEventArgs e) {
            TileEditor TileEditorREF = new TileEditor();

            if (e.is_editing) {
                TileEditorREF.edt_linkname.Text = e.target_tile;

                TileEditorREF.bmi_largetile.UriSource = new Uri(App.tiles[e.target_tile]["str_largepath"]);
                TileEditorREF.bmi_widetile.UriSource = new Uri(App.tiles[e.target_tile]["str_widepath"]);
                TileEditorREF.bmi_medtile.UriSource = new Uri(App.tiles[e.target_tile]["str_medpath"]);
                TileEditorREF.bmi_smalltile.UriSource = new Uri(App.tiles[e.target_tile]["str_smallpath"]);
            }

            SplitViewREF.Content = TileEditorREF;
        }

        private void clk_nav_flyout(object sender, PointerRoutedEventArgs e) {
            SplitViewREF.IsPaneOpen = !SplitViewREF.IsPaneOpen;
        }

        private void clk_nav_tiles(object sender, PointerRoutedEventArgs e) {
            SplitViewREF.IsPaneOpen = false;
            tm = new TileManager();
            tm.RequestTileEditor += clbk_open_tile_editor;

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
