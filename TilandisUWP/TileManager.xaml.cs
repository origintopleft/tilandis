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

        List<Tile> tiles;

        public TileManager()
        {
            this.InitializeComponent();
            tiles = new List<Tile>();

            foreach (KeyValuePair<string, Dictionary<string, string>> kvp_tile in App.tiles) {
                string str_tilename = kvp_tile.Key;
                var dict_tile = kvp_tile.Value;

                Tile tile_current = new Tile();
                tile_current.str_largepath = dict_tile["str_largepath"];
                tile_current.str_widepath = dict_tile["str_widepath"];
                tile_current.str_medpath = dict_tile["str_medpath"];
                tile_current.str_smallpath = dict_tile["str_smallpath"];
                tile_current.str_name = str_tilename;
                tiles.Add(tile_current);
            }

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
