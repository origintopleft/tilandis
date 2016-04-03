using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
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

        private string _str_tilename;

        public string str_tilename {
            get { return _str_tilename; }
            set {
                _str_tilename = value;
                edt_linkname.Text = value;
            }
        }


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

            str_tilename = "";
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
        }

        private async Task<StorageFile> get_tile_image() {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();
            picker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
            picker.ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail;
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".jpeg");
            picker.FileTypeFilter.Add(".png");

            return await picker.PickSingleFileAsync();
        }

        private async void clk_pick_large_tile(object sender, TappedRoutedEventArgs e) {
            StorageFile file_user = await get_tile_image();
            string str_tilename = edt_linkname.Text;
            StorageFolder dir_tiledir = await App.dir_local.CreateFolderAsync("tile_assets\\" + str_tilename, CreationCollisionOption.OpenIfExists);
            StorageFile file_copiedin = await file_user.CopyAsync(dir_tiledir, "large", NameCollisionOption.ReplaceExisting);

            bmi_largetile.UriSource = new Uri(file_copiedin.Path);
        }

        private async void clk_pick_wide_tile(object sender, TappedRoutedEventArgs e) {
            StorageFile file_user = await get_tile_image();
            string str_tilename = edt_linkname.Text;
            StorageFolder dir_tiledir = await App.dir_local.CreateFolderAsync("tile_assets\\" + str_tilename, CreationCollisionOption.OpenIfExists);
            StorageFile file_copiedin = await file_user.CopyAsync(dir_tiledir, "wide", NameCollisionOption.ReplaceExisting);

            bmi_widetile.UriSource = new Uri(file_copiedin.Path);
        }

        private async void clk_pick_med_tile(object sender, TappedRoutedEventArgs e) {
            StorageFile file_user = await get_tile_image();
            string str_tilename = edt_linkname.Text;
            StorageFolder dir_tiledir = await App.dir_local.CreateFolderAsync("tile_assets\\" + str_tilename, CreationCollisionOption.OpenIfExists);
            StorageFile file_copiedin = await file_user.CopyAsync(dir_tiledir, "med", NameCollisionOption.ReplaceExisting);

            bmi_medtile.UriSource = new Uri(file_copiedin.Path);
        }

        private async void clk_pick_small_tile(object sender, TappedRoutedEventArgs e) {
            StorageFile file_user = await get_tile_image();
            StorageFolder dir_tiledir = await App.dir_local.CreateFolderAsync("tile_assets\\" + str_tilename, CreationCollisionOption.OpenIfExists);
            StorageFile file_copiedin = await file_user.CopyAsync(dir_tiledir, "small", NameCollisionOption.ReplaceExisting);

            bmi_smalltile.UriSource = new Uri(file_copiedin.Path);
        }

        private void clk_delete(object sender, RoutedEventArgs e) {
            App.tiles.Remove(str_tilename);

            if (str_tilename != "") {
                
                try { Directory.Delete(App.dir_local.Path + "\\tile_assets\\" + str_tilename, true); }
                catch (DirectoryNotFoundException) { /* pass */ }
            }
        }

        private async void clbk_change_link_name(object sender, TextChangedEventArgs e) {
            string tilepath = "";
            try {
                // for tilefile in ["large", "wide", "med", "small"]:
                foreach (string tilefile in new List<string> { "large", "wide", "med", "small" }) {
                    // End result: tilepath = LocalState\tile_assets
                    tilepath  = "tile_assets\\";
                    tilepath += str_tilename + "\\";
                    tilepath += tilefile;

                    if (await App.dir_local.TryGetItemAsync(tilepath) != null) {
                        // We do it this way instead of just using bmi_imagefile's data so we don't accidentally
                        // delete editor assets or something silly like that
                        StorageFile file_old = await App.dir_local.GetFileAsync(tilepath);
                        StorageFolder dir_new = await App.dir_local.CreateFolderAsync("tile_assets\\" + edt_linkname.Text, CreationCollisionOption.OpenIfExists);
                        await file_old.MoveAsync(dir_new);
                    }
                }
                str_tilename = edt_linkname.Text;
            }
            catch (Exception exc) {
                var dialog = new Windows.UI.Popups.MessageDialog(tilepath);
                await dialog.ShowAsync();
                throw exc;
            }
        }
    }
}
