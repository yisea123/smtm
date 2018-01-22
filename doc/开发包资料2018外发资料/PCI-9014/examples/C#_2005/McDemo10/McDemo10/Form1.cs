using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using Pci9014;

namespace McDemo10
{
    public partial class Form1 : Form
    {
        //CPci9014 m_MC;
        int axis;
        int m_axis;
        String str;
        int m_type;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            int rc;
            int card_count = 0;
            int[] card_id=new int[16];
 
            rc = CPci9014.p9014_initial(ref card_count, card_id);
            if (rc != 0)
            {
                MessageBox.Show("Initialize PCI-9014 fail");
            }
            if (card_count < 1)
            {
                MessageBox.Show("Find No PCI-9014 device");
            }
            else
            {
                for (int i = 0; i < card_count; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        axis = card_id[i] * 4 + j;
                        CPci9014.p9014_set_pos(axis , 0, 0);
                        str = Convert.ToString(axis);
                        m_ctlAxisSel.Items.Add(str); 
                    }
                }
            }
            textBox1.Text = "1000";
            textBox2.Text = "10000";
            textBox3.Text = "50000";
            textBox4.Text = "50000";
            textBox5.Text =" 10000";
            m_ctlAxisSel.Text =Convert .ToString( card_id[0] * 4 );
            m_axis = card_id[0] * 4;
            radioButton1.Checked = true;
            m_type = 0;
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            CPci9014.p9014_close();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            double start_vel, max_vel, acc, dec;
            int dist;
            int rc = 0;
            start_vel = Convert.ToDouble(textBox1.Text);
            max_vel = Convert.ToDouble(textBox2.Text);
            acc = Convert.ToDouble(textBox3.Text);
            dec = Convert.ToDouble(textBox4.Text);
            dist = Convert.ToInt32(textBox5.Text);
            CPci9014.p9014_set_t_profile(m_axis ,start_vel ,max_vel , acc, dec);

            switch (m_type)
            {
                case 0:
               {
                CPci9014.p9014_pmove(m_axis, dist, 0, 2);
                   break;
               }
                case 1:
               {
                CPci9014.p9014_vmove(m_axis, 1, 2);
                   break;
               }
                case 2:
               {
                CPci9014.p9014_vmove(m_axis, 0, 2);
                   break ;
               }
            }

            if (rc != 0)
                MessageBox.Show("Stop Axis fail,return code:" + Convert.ToString(rc));
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            int cmd_pos = 0,enc_pos=0;
            uint motion_status = 0,io_status=0;
            double cur_vel = 0.0f;

            CPci9014.p9014_get_motion_status(m_axis, ref motion_status);
            CPci9014.p9014_get_io_status(m_axis, ref io_status);
            CPci9014.p9014_get_current_speed(m_axis,ref cur_vel);
            CPci9014.p9014_get_pos(m_axis, 0, ref cmd_pos);
            CPci9014.p9014_get_pos(m_axis, 1, ref enc_pos);

            textBox6.Text=Convert.ToString(cur_vel);
            textBox7.Text=Convert.ToString (motion_status);
            textBox8.Text = Convert.ToString(cmd_pos);
            textBox9.Text = Convert.ToString(enc_pos);

            //PEL
            if ((io_status % 2)==1)
            {
                textBox10.Text = "ON";
            }
            else
            {
                textBox10.Text = "OFF";
            }

            //MEL
            if (((io_status>>1)%2)==1)
            {
                textBox11.Text = "ON";
            }
            else
            {
                textBox11.Text = "OFF";
            }

            //EMG
            if (((io_status>>4)%2)==1)
            {
                textBox12.Text = "OFF";
            }
            else
            {
                textBox12.Text = "ON";
            }
        }

        private void m_ctlAxisSel_SelectedIndexChanged(object sender, EventArgs e)
        {
            int sel;
            sel = Convert.ToInt32(m_ctlAxisSel.Text);
            if (sel >= 0)
            {
                m_axis = sel;
            }
            else
            {
                m_ctlAxisSel.SelectedIndex = 0;
                m_axis = Convert.ToInt32(m_ctlAxisSel.Text);
            }
        }

        private void SdStop_Click(object sender, EventArgs e)
        {
            int rc = 0;
            rc = CPci9014.p9014_stop(m_axis, 0);
            if (rc != 0)
            {
                MessageBox.Show("Stop Axis fail,return code:" + Convert.ToString(rc));
            }
        }

        private void EmgStop_Click(object sender, EventArgs e)
        {
            int rc = 0;
            rc = CPci9014.p9014_stop(m_axis, 1);
            if (rc != 0)
            {
                MessageBox.Show("Stop Axis fail,return code:" + Convert.ToString(rc));
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                m_type = 0;
            }
            else if (radioButton2.Checked == true)
            {
               m_type = 1;
            }
            else if (radioButton3.Checked == true)
            {
               m_type = 2;
            }

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                m_type = 0;
            }
            else if (radioButton2.Checked == true)
            {
                m_type = 1;
            }
            else if (radioButton3.Checked == true)
            {
                m_type = 2;
            }
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                m_type = 0;
            }
            else if (radioButton2.Checked == true)
            {
                m_type = 1;
            }
            else if (radioButton3.Checked == true)
            {
                m_type = 2;
            }
        }
    }
}