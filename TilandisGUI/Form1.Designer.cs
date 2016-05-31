namespace TilandisGUI {
    partial class frm_tilandisgui {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.lst_links = new System.Windows.Forms.ListView();
            this.linkname = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.path = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.grp_linksettings = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.cbx_asadmin = new System.Windows.Forms.CheckBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btn_browseworkdir = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_newlink = new System.Windows.Forms.Button();
            this.btn_dellink = new System.Windows.Forms.Button();
            this.grp_linksettings.SuspendLayout();
            this.SuspendLayout();
            // 
            // lst_links
            // 
            this.lst_links.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.linkname,
            this.path});
            this.lst_links.FullRowSelect = true;
            this.lst_links.Location = new System.Drawing.Point(13, 13);
            this.lst_links.Name = "lst_links";
            this.lst_links.Size = new System.Drawing.Size(246, 390);
            this.lst_links.Sorting = System.Windows.Forms.SortOrder.Ascending;
            this.lst_links.TabIndex = 0;
            this.lst_links.UseCompatibleStateImageBehavior = false;
            this.lst_links.View = System.Windows.Forms.View.Details;
            // 
            // linkname
            // 
            this.linkname.Text = "Link Name";
            this.linkname.Width = 63;
            // 
            // path
            // 
            this.path.Text = "File Path";
            this.path.Width = 176;
            // 
            // grp_linksettings
            // 
            this.grp_linksettings.Controls.Add(this.label5);
            this.grp_linksettings.Controls.Add(this.button2);
            this.grp_linksettings.Controls.Add(this.cbx_asadmin);
            this.grp_linksettings.Controls.Add(this.textBox4);
            this.grp_linksettings.Controls.Add(this.label4);
            this.grp_linksettings.Controls.Add(this.textBox3);
            this.grp_linksettings.Controls.Add(this.label3);
            this.grp_linksettings.Controls.Add(this.button1);
            this.grp_linksettings.Controls.Add(this.textBox2);
            this.grp_linksettings.Controls.Add(this.label2);
            this.grp_linksettings.Controls.Add(this.btn_browseworkdir);
            this.grp_linksettings.Controls.Add(this.textBox1);
            this.grp_linksettings.Controls.Add(this.label1);
            this.grp_linksettings.Location = new System.Drawing.Point(266, 13);
            this.grp_linksettings.Name = "grp_linksettings";
            this.grp_linksettings.Size = new System.Drawing.Size(578, 244);
            this.grp_linksettings.TabIndex = 1;
            this.grp_linksettings.TabStop = false;
            this.grp_linksettings.Text = "Link Settings";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(455, 220);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(117, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Bold fields are required.";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(9, 215);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 12;
            this.button2.Text = "Save";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // cbx_asadmin
            // 
            this.cbx_asadmin.AutoSize = true;
            this.cbx_asadmin.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.cbx_asadmin.Location = new System.Drawing.Point(100, 155);
            this.cbx_asadmin.Name = "cbx_asadmin";
            this.cbx_asadmin.Size = new System.Drawing.Size(123, 17);
            this.cbx_asadmin.TabIndex = 11;
            this.cbx_asadmin.Text = "Run as Administrator";
            this.cbx_asadmin.UseVisualStyleBackColor = true;
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(100, 128);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(391, 20);
            this.textBox4.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(40, 131);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "Arguments";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBox3
            // 
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.Location = new System.Drawing.Point(100, 16);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(391, 20);
            this.textBox3.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(30, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Link Name";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(497, 76);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 20);
            this.button1.TabIndex = 5;
            this.button1.Text = "Browse";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.Location = new System.Drawing.Point(100, 76);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(391, 20);
            this.textBox2.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(40, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "File Path";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btn_browseworkdir
            // 
            this.btn_browseworkdir.Location = new System.Drawing.Point(497, 102);
            this.btn_browseworkdir.Name = "btn_browseworkdir";
            this.btn_browseworkdir.Size = new System.Drawing.Size(75, 20);
            this.btn_browseworkdir.TabIndex = 2;
            this.btn_browseworkdir.Text = "Browse";
            this.btn_browseworkdir.UseVisualStyleBackColor = true;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(100, 102);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(391, 20);
            this.textBox1.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 105);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Working Directory";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btn_newlink
            // 
            this.btn_newlink.Location = new System.Drawing.Point(275, 264);
            this.btn_newlink.Name = "btn_newlink";
            this.btn_newlink.Size = new System.Drawing.Size(75, 23);
            this.btn_newlink.TabIndex = 2;
            this.btn_newlink.Text = "New";
            this.btn_newlink.UseVisualStyleBackColor = true;
            // 
            // btn_dellink
            // 
            this.btn_dellink.Location = new System.Drawing.Point(275, 294);
            this.btn_dellink.Name = "btn_dellink";
            this.btn_dellink.Size = new System.Drawing.Size(75, 23);
            this.btn_dellink.TabIndex = 3;
            this.btn_dellink.Text = "Delete";
            this.btn_dellink.UseVisualStyleBackColor = true;
            // 
            // frm_tilandisgui
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(856, 415);
            this.Controls.Add(this.btn_dellink);
            this.Controls.Add(this.btn_newlink);
            this.Controls.Add(this.grp_linksettings);
            this.Controls.Add(this.lst_links);
            this.Name = "frm_tilandisgui";
            this.Text = "Tilandis Control GUI";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.grp_linksettings.ResumeLayout(false);
            this.grp_linksettings.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView lst_links;
        private System.Windows.Forms.ColumnHeader linkname;
        private System.Windows.Forms.ColumnHeader path;
        private System.Windows.Forms.GroupBox grp_linksettings;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.CheckBox cbx_asadmin;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btn_browseworkdir;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_newlink;
        private System.Windows.Forms.Button btn_dellink;
        private System.Windows.Forms.Label label5;
    }
}

