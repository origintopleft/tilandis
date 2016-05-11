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
using Newtonsoft.Json;

namespace TilandisGUI {
    public partial class frm_tilandisgui : Form {
        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);

        public frm_tilandisgui() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            // TODO: fix this crap
            //Bitmap img_shield = new Bitmap(SystemIcons.Shield.ToBitmap(), new Size(12, 16));
            //cbx_asadmin.Image = img_shield;

            using (StreamReader r = new StreamReader("links.json")) {
                string str_linksjson = r.ReadToEnd();
                dynamic json_links = JsonConvert.DeserializeObject(str_linksjson);
            }
        }
    }
}
