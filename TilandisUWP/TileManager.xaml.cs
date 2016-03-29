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
        public string str_largepath, str_medpath, str_widepath, str_smallpath, str_name;
        public Tile() {
            str_largepath = "";
            str_medpath = "";
            str_widepath = "";
            str_smallpath = "";
            str_name = "";
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
            tile_dota2.str_name = "dota2";
            tiles.Add(tile_dota2);

            Tile stile_newtile = new Tile();
            stile_newtile.str_name = "_new";
            if (App.is_dark) { stile_newtile.str_largepath = "Assets/editor/newtiled.png"; }
            else { stile_newtile.str_largepath = "Assets/editor/newtile.png"; }
            tiles.Add(stile_newtile);

            cvs_tilehub.Source = tiles;
        }

        private void clk_opentileeditor(object sender, TappedRoutedEventArgs e) {
            Image img_sender = (Image) sender;
            TileEditorEventArgs teev;
            if (((string) img_sender.Tag) == "_new") {
                teev = new TileEditorEventArgs(false, "");
            } else {
                teev = new TileEditorEventArgs(true, (string) img_sender.Tag);
            }
            RequestTileEditor(this, teev);
        }
    }
}
