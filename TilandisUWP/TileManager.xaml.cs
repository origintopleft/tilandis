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
        public string str_largepath, str_medpath, str_widepath, str_smallpath;
        public Tile() {
            str_largepath = "";
            str_medpath = "";
            str_widepath = "";
            str_smallpath = "";
        }
    }

    /// <summary>
    /// For passing arguments to launching the tile editor (like which tile to edit)
    /// </summary>
    public sealed partial class TileEditorEventArgs : EventArgs {
        public bool is_editing;
        public string target_tile;
        public TileEditorEventArgs(bool is_editing, string target_tile) {
            this.is_editing = is_editing;
            this.target_tile = target_tile;
        }
    }

    /// <summary>
    /// Tile management page. Displays all tiles.
    /// </summary>
    public sealed partial class TileManager : Page {
        public delegate void eventhandler(object source, TileEditorEventArgs e);
        public event eventhandler RequestTileEditor;

        bool tedt_editing;
        string tedt_target;

        List<Tile> tiles;

        public TileManager()
        {
            this.InitializeComponent();
            tiles = new List<Tile>();

            // TEMP
            Tile tile_as2 = new Tile();
            tile_as2.str_largepath = "Assets/dev_temp/as2tile.png";
            tiles.Add(tile_as2);

            Tile tile_bj3 = new Tile();
            tile_bj3.str_largepath = "Assets/dev_temp/bj3tile.png";
            tiles.Add(tile_bj3);

            Tile tile_citsky = new Tile();
            tile_citsky.str_largepath = "Assets/dev_temp/citskytile.png";
            tiles.Add(tile_citsky);

            Tile tile_dota2 = new Tile();
            tile_dota2.str_largepath = "Assets/dev_temp/dotatile.png";
            tiles.Add(tile_dota2);

            cvs_tilehub.Source = tiles;
        }

        private void clk_opentileeditor(object sender, TappedRoutedEventArgs e) {
            RequestTileEditor(this, null);
        }
    }
}
