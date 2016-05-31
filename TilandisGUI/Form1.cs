using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using Newtonsoft.Json.Linq;

namespace TilandisGUI {
    public partial class frm_tilandisgui : Form {
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);

        public frm_tilandisgui() {
            InitializeComponent();
        }

        JObject json_links;

        private void Form1_Load(object sender, EventArgs e) {
            // TODO: fix this crap
            //Bitmap img_shield = new Bitmap(SystemIcons.Shield.ToBitmap(), new Size(12, 16));
            //cbx_asadmin.Image = img_shield;

            func_reloadjson();

            lst_links.SelectedIndexChanged += clbk_linksel;
        }

        private void clbk_linksel(object sender, EventArgs e) {
            if (lst_links.SelectedItems.Count <= 0) { // none selected
                return; // do nothing
            }

            ListViewItem lvi_curitem = lst_links.SelectedItems[0];

            JObject prop_linksettings = (JObject) json_links.Value<JObject>(lvi_curitem.Text);

            edt_linkname.Text = lvi_curitem.Text;
            edt_pathname.Text = prop_linksettings.Value<string>("path");
            edt_workdir.Text = prop_linksettings.Value<string>("workdir");
            edt_args.Text = prop_linksettings.Value<string>("args");
            cbx_asadmin.Checked = prop_linksettings.Value<bool>("asadmin");
        }

        private void func_reloadjson() {
            StreamReader r = new StreamReader("links.json");
            string str_linksjson = r.ReadToEnd();
            json_links = JObject.Parse(str_linksjson);
            r.Close();

            foreach (JProperty prop_curitem in json_links.Properties()) {
                ListViewItem lvi_curitem = new ListViewItem(prop_curitem.Name);
                JObject prop_linksettings = (JObject) prop_curitem.Value;

                lvi_curitem.SubItems.Add(prop_linksettings.Value<string>("path"));

                lst_links.Items.Add(lvi_curitem);
            }
        }
    }
}
