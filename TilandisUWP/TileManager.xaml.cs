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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace TilandisUWP {
    public class Tile {
        string str_largepath, str_medpath, str_widepath, str_smallpath;
        public Tile() {
            str_largepath = "";
            str_medpath = "";
            str_widepath = "";
            str_smallpath = "";
        }

        public void set_large(string path) {
            str_largepath = path;
            if (str_medpath == "") { str_medpath = path; } // required to provide a medium tile
        }
    }

    /// <summary>
    /// Tile management page. Displays all tiles.
    /// </summary>
    public sealed partial class TileManager : Page {
        public delegate void eventhandler(object source, EventArgs e);
        public event eventhandler RequestTileEditor;

        List<string> tiles;

        public TileManager()
        {
            this.InitializeComponent();
            tiles = new List<string>();

            // TEMP: add the Dota 2 tile image
            tiles.Add("Assets/dev_temp/as2tile.png");
            tiles.Add("Assets/dev_temp/bj3tile.png");
            tiles.Add("Assets/dev_temp/citskytile.png");
            tiles.Add("Assets/dev_temp/dotatile.png");
            cvs_tilehub.Source = tiles;
        }

        private void clk_opentileeditor(object sender, TappedRoutedEventArgs e) {
            RequestTileEditor(this, null);
        }
    }
}
