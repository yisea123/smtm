//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PageControl1Change(TObject *Sender)
{
    char buf[3];

    //StatusBar1->SimpleText = "Page index: " +
    //           AnsiString(itoa(PageControl1->ActivePage->PageIndex, buf, 10));
}
//---------------------------------------------------------------------------
// initializa form
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    int rc;
    int i, j, axis;
    AnsiString str;
    
    StringGridFreeMode->Cells[0][1] = "X";
    StringGridFreeMode->Cells[0][2] = "Y";
    StringGridFreeMode->Cells[0][3] = "Z";
    StringGridFreeMode->Cells[0][4] = "A";

    StringGridFreeMode->Cells[1][0] = "Cur. Vel.";
    StringGridFreeMode->Cells[2][0] = "Status";
    StringGridFreeMode->Cells[3][0] = "Cmd. Pos.";
    StringGridFreeMode->Cells[4][0] = "Enc. Pos.";
    StringGridFreeMode->Cells[5][0] = "PEL";
    StringGridFreeMode->Cells[6][0] = "MEL";
    StringGridFreeMode->Cells[7][0] = "ORG";
    StringGridFreeMode->Cells[8][0] = "EMG";
    StringGridFreeMode->Cells[9][0] = "Alarm";

    //set col width
    StringGridFreeMode->ColWidths[5] = 40;
    StringGridFreeMode->ColWidths[6] = 40;
    StringGridFreeMode->ColWidths[7] = 40;
    StringGridFreeMode->ColWidths[8] = 40;

    EditFreeModeDist->Text = "1000";
    RadioGroupFreeModeDriveType->ItemIndex = 0;
    RadioGroupVelMode->ItemIndex = 2;   //high speed with A/D

    EditStartVel->Text = "1000";
    EditMaxVel->Text = "10000";
    EditAccel->Text = "500000";
    EditDecel->Text = "500000";
    EditJerkPercent->Text = "1.00";
    
    RadioGroupOutputPulseMode->ItemIndex = 0;
    RadioGroupInputPulseMode->ItemIndex = 0;

    //configuration page default
    RadioGroupVelProfile->ItemIndex = 0;
    RadioGroupHomeMode->ItemIndex = 0;
    RadioGroupParamAxisSel->ItemIndex = 0;
        
    RadioGroupOrgLevel->ItemIndex = 0;
    RadioGroupEzLevel->ItemIndex = 1;
    RadioGroupELLevel->ItemIndex = 0;

    rc = p9014_initial(&m_CardCount, m_CardNoArray);
    if(rc)
    {
        MessageDlg("Initialize card fail!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        PostQuitMessage(0);
    }
    if(m_CardCount < 1)
    {
        MessageDlg("Find no card!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        PostQuitMessage(0);
    }

    for(i = 0; i < m_CardCount; i ++)
    {
        str.sprintf("%d", m_CardNoArray[i]);
        ComboBoxCardNo->Items->Add(str);
        for(j = 0; j < AXIS_PER_CARD; j ++)
        {
            axis = m_CardNoArray[i] * AXIS_PER_CARD + j;
            ConfigReadFromFile(axis);
            ConfigAxis(axis);
        }
    }
    ComboBoxCardNo->ItemIndex = 0;
    m_currCardNo = m_CardNoArray[0];
    RadioGroupParamAxisSel->ItemIndex = 0;   //param. sheet, select x by default
    ConfigUpdateUi(m_currCardNo * AXIS_PER_CARD + 0);

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
    int row, col;
    AnsiString str;
    int rc;
    double curr_vel;
    int cmd_pos, enc_pos;
    int pel, mel, org, emg;
    int axis;
    unsigned int status, io_status;
    switch ( PageControl1->ActivePageIndex )
    {
        //free mode
    case 0:
    {
        for (row = 0; row < AXIS_PER_CARD; row++)
        {
            axis = m_currCardNo * AXIS_PER_CARD + row;

            //current vel
            p9014_get_current_speed(axis, &curr_vel);
             str.sprintf("%.2lf", curr_vel);
            StringGridFreeMode->Cells[1][row + 1] = str;

            //status
            p9014_get_motion_status(axis, &status);
            str.sprintf("%d", status);
            StringGridFreeMode->Cells[2][row + 1] = str;

            //command pos
            p9014_get_pos(axis, 0, &cmd_pos);
            str.sprintf("%d", cmd_pos);
            StringGridFreeMode->Cells[3][row + 1] = str;

            //feedback pos
            p9014_get_pos(axis, 1, &enc_pos);
            str.sprintf("%d", enc_pos);
            StringGridFreeMode->Cells[4][row + 1] = str;

            //PEL
            io_status = 0;
            p9014_get_io_status(axis, &io_status);
            
            str.sprintf("%d", (io_status & 0x1)? 1 : 0);
            StringGridFreeMode->Cells[5][row + 1] = str;

            //MEL
            str.sprintf("%d", (io_status & 0x2)? 1 : 0);
            StringGridFreeMode->Cells[6][row + 1] = str;

            //ORG
            str.sprintf("%d", (io_status & 0x4)? 1 : 0);
            StringGridFreeMode->Cells[7][row + 1] = str;

            //EMG
            str.sprintf("%d", (io_status & 0x10)? 1 : 0);
            StringGridFreeMode->Cells[8][row + 1] = str;

            //alarm
            str.sprintf("%d", (io_status & 0x100)? 1 : 0);
            StringGridFreeMode->Cells[9][row + 1] = str;
        }
    }
    break;

    //DI/DO
    case 1:
    {
        UpdateDIO(0);
    }
    break;

	//param. config
    case 2:
    {
    }
    break;

    case 3:
    {
	    unsigned int ver[ ] = {0, 0, 0, 0};
	    unsigned int rev = 0;
		p9014_get_version(m_currCardNo, ver +0, ver + 1, ver + 2);
	    
	    //logic version
	    str.sprintf("0x%x", ver[2]);
	    EditLogicVer->Text = str;
		
		//logic revision
		p9014_get_revision(m_currCardNo, &rev);
		str.sprintf("0x%x", rev);
		EditLogicRev->Text = str;
		
	    str.sprintf("0x%x", ver[1]);
	    EditDriverVer->Text = str;
	
	    str.sprintf("0x%x", ver[0]);
	    EditApiVer->Text = str;
	
	    EditAppVer->Text ="1.03";
    }
    break;

    default:
        break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonFreeModeRunClick(TObject *Sender)
{
    double dist, vel, acc;
    int axis, index;
    int vel_mode;
	int rc = 0;
    AnsiString str;

    dist = atof(EditFreeModeDist->Text.c_str());

    vel_mode = RadioGroupVelMode->ItemIndex;
    if(vel_mode < 0)
        vel_mode = 2;

    if(RadioGroupDriveAxis->ItemIndex < 0)
    {
        axis = m_currCardNo * AXIS_PER_CARD + 0;
    }
    else
    {
        axis = m_currCardNo * AXIS_PER_CARD +  RadioGroupDriveAxis->ItemIndex;
    }

    index = RadioGroupFreeModeDriveType->ItemIndex;
    if(index < 0)
    {
        return;
    }

    switch(index)
    {
        case 0:  //positioning jog with  absolute coordinate
        {
            rc = p9014_pmove(axis, dist, 1, vel_mode);
        }
        break;

        case 1:  //positioning jog with  incremental coordinate
        {

            rc = p9014_pmove(axis, dist, 0, vel_mode);

        }
        break;

        case 2:  //continuous jog(+)
        {
             rc = p9014_vmove(axis, 1, vel_mode);

        }
        break;

        case 3:      //continuous jog(-)
        {
            rc = p9014_vmove(axis, 0, vel_mode);
        }
        break;

        case 4:  //homing(+)
        {
            rc = p9014_home_move(axis, 1);
        }
        break;

        case 5:  //homing(-)
        {
            rc = p9014_home_move(axis, 0);
        }
        break;

        default:
        break;
    }
    if(rc)
    {
        str.sprintf("Drive Axis fail, return code: %d", rc);
        MessageDlg(str, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonFreeModeStopClick(TObject *Sender)
{
    int axis;
    int rc = 0;
    AnsiString str;
    
    if(RadioGroupDriveAxis->ItemIndex < 0)
    {
        axis = m_currCardNo * AXIS_PER_CARD + 0;
    }
    else
    {
        axis = m_currCardNo * AXIS_PER_CARD +  RadioGroupDriveAxis->ItemIndex;
    }

    rc = p9014_stop(axis, 0);
    if(rc)
    {
        str.sprintf("Stop Axis fail, return code: %d", rc);
        MessageDlg(str, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}

//update DI/DO status
void TFormMain::UpdateDIO(unsigned int di)
{
    //TODO: Add your source code here
    int bit;

    p9014_get_di(m_currCardNo, &di);
    
    CheckBoxDI0->Checked = (di & (0x1 << 0))? true: false;
    CheckBoxDI1->Checked = (di & (0x1 << 1))? true: false;
    CheckBoxDI2->Checked = (di & (0x1 << 2))? true: false;
    CheckBoxDI3->Checked = (di & (0x1 << 3))? true: false;
    CheckBoxDI4->Checked = (di & (0x1 << 4))? true: false;
    CheckBoxDI5->Checked = (di & (0x1 << 5))? true: false;
    CheckBoxDI6->Checked = (di & (0x1 << 6))? true: false;
    CheckBoxDI7->Checked = (di & (0x1 << 7))? true: false;
    CheckBoxDI8->Checked = (di & (0x1 << 8))? true: false;
    CheckBoxDI9->Checked = (di & (0x1 << 9))? true: false;
    CheckBoxDI10->Checked = (di & (0x1 << 10))? true: false;
    CheckBoxDI11->Checked = (di & (0x1 << 11))? true: false;
    CheckBoxDI12->Checked = (di & (0x1 << 12))? true: false;
    CheckBoxDI13->Checked = (di & (0x1 << 13))? true: false;
    CheckBoxDI14->Checked = (di & (0x1 << 14))? true: false;
    CheckBoxDI15->Checked = (di & (0x1 << 15))? true: false;

    p9014_set_do_bit(m_currCardNo, 0, CheckBoxDO0->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 1, CheckBoxDO1->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 2, CheckBoxDO2->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 3, CheckBoxDO3->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 4, CheckBoxDO4->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 5, CheckBoxDO5->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 6, CheckBoxDO6->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 7, CheckBoxDO7->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 8, CheckBoxDO8->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 9, CheckBoxDO9->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 10, CheckBoxDO10->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 11, CheckBoxDO11->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 12, CheckBoxDO12->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 13, CheckBoxDO13->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 14, CheckBoxDO14->Checked? 1  : 0);
    p9014_set_do_bit(m_currCardNo, 15, CheckBoxDO15->Checked? 1  : 0);
}

//---------------------------------------------------------------------------
//if it is in free mode, enter coordinated mode
//all axes should be in position before switching operatio mode
//  change driving parameter
//  Note:
//  Before chaning parameter, be sure that all axes is in position
//
void __fastcall TFormMain::ButtonCfgApplyClick(TObject *Sender)
{
    int i, axis;

    i = RadioGroupParamAxisSel->ItemIndex;
    if(i < 0)
    {
        MessageDlg("please select an axis", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }
    axis = m_currCardNo * AXIS_PER_CARD + i;

    //output pulse mode
    if(0 == RadioGroupOutputPulseMode->ItemIndex)
    {
         m_sAxisParam[axis].output_pulse_mode = 0;
    }
    else if(1 == RadioGroupOutputPulseMode->ItemIndex)
    {
        m_sAxisParam[axis].output_pulse_mode = 1;
    }

    //input pulse mode
    if(0 == RadioGroupInputPulseMode->ItemIndex)
    {
        m_sAxisParam[axis].input_pulse_mode = 0;
    }
    else if(1 == RadioGroupInputPulseMode->ItemIndex)
    {
        m_sAxisParam[axis].input_pulse_mode = 1;
    }

    //home mode
    int home_mode = 0, org_level = 0, ez_level = 1;
    if(0 == RadioGroupHomeMode->ItemIndex)
    {
        home_mode = 0;
    }
    else
    {
        home_mode = 1;
    }

    if(0 == RadioGroupOrgLevel->ItemIndex)
    {
        org_level = 0;
    }
    else
    {
        org_level = 1;
    }

    if( 0 == RadioGroupEzLevel->ItemIndex)
    {
        ez_level = 0;
    }
    else
    {
        ez_level = 1;

    }
    m_sAxisParam[axis].home_mode = home_mode;
    m_sAxisParam[axis].org_level = org_level;
    m_sAxisParam[axis].ez_level = ez_level;

    //end limit active level
    if( 0 == RadioGroupELLevel->ItemIndex)
    {
         m_sAxisParam[axis].el_level = 0;
    }
    else
    {
        m_sAxisParam[axis].el_level = 1;
    }
    
	if(0 == RadioGroupVelProfile->ItemIndex)
		m_sAxisParam[axis].vel_profile = 0;
	else
		m_sAxisParam[axis].vel_profile = 1;
		
    m_sAxisParam[axis].start_vel = EditStartVel->Text.ToDouble();
    m_sAxisParam[axis].max_vel = EditMaxVel->Text.ToDouble();
    m_sAxisParam[axis].accel = EditAccel->Text.ToDouble();
    m_sAxisParam[axis].decel = EditDecel->Text.ToDouble();
    m_sAxisParam[axis].jp =  EditJerkPercent->Text.ToDouble();
	
    ConfigAxis(axis);
    ConfigSaveFile(axis);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


int TFormMain::ConfigReadFromFile(int axis)
{
        //TODO: Add your source code here
   TIniFile *ini;
   AnsiString strAxis;
   AnsiString appPath;

   appPath = ExtractFilePath(Application-> ExeName);
   appPath.cat_sprintf("\\config.ini");
   ini = new TIniFile(appPath);

   strAxis.sprintf("AXIS_%d", axis);
   m_sAxisParam[axis].output_pulse_mode = ini->ReadInteger( strAxis, "OUTPUT_PULSE_MODE", 0 );
   m_sAxisParam[axis].input_pulse_mode = ini->ReadInteger( strAxis, "INPUT_PULSE_MODE", 0 );
   m_sAxisParam[axis].home_mode = ini->ReadInteger( strAxis, "HOME_MODE", 0 );
   m_sAxisParam[axis].org_level = ini->ReadInteger( strAxis, "ORG_LEVEL", 0 );
   m_sAxisParam[axis].el_level = ini->ReadInteger( strAxis, "EL_LEVEL", 0 );
   m_sAxisParam[axis].ez_level = ini->ReadInteger( strAxis, "EZ_LEVEL", 0 );

   m_sAxisParam[axis].vel_profile = ini->ReadInteger( strAxis, "VEL_PROFILE", 0 );

   m_sAxisParam[axis].start_vel = ini->ReadFloat( strAxis, "START_VEL", 1000.0 );
   m_sAxisParam[axis].max_vel = ini->ReadFloat( strAxis, "MAX_VEL", 1000.0 );
   m_sAxisParam[axis].accel = ini->ReadFloat( strAxis, "ACCELERATION", 500000.0 );
   m_sAxisParam[axis].decel = ini->ReadFloat( strAxis, "DECELERATION", 500000.0 );
   m_sAxisParam[axis].jp = ini->ReadFloat( strAxis, "JERK_PERCENT", 0.3 );

   delete ini;
   return 0;
}

int TFormMain::ConfigSaveFile(int axis)
{
        //TODO: Add your source code here
   TIniFile *ini;
   AnsiString strAxis;
   AnsiString appPath;

   appPath = ExtractFilePath(Application-> ExeName);
   appPath.cat_sprintf("\\config.ini");
   ini = new TIniFile(appPath);

   strAxis.sprintf("AXIS_%d", axis);
   ini->WriteInteger( strAxis, "OUTPUT_PULSE_MODE", m_sAxisParam[axis].output_pulse_mode );
   ini->WriteInteger( strAxis, "INPUT_PULSE_MODE", m_sAxisParam[axis].input_pulse_mode );
   ini->WriteInteger( strAxis, "HOME_MODE", m_sAxisParam[axis].home_mode );
   ini->WriteInteger( strAxis, "ORG_LEVEL", m_sAxisParam[axis].org_level );
   ini->WriteInteger( strAxis, "EL_LEVEL", m_sAxisParam[axis].el_level );
   ini->WriteInteger( strAxis, "EZ_LEVEL", m_sAxisParam[axis].ez_level );

   ini->WriteInteger( strAxis, "VEL_PROFILE", m_sAxisParam[axis].vel_profile );

   ini->WriteFloat( strAxis, "START_VEL", m_sAxisParam[axis].start_vel );
   ini->WriteFloat( strAxis, "MAX_VEL", m_sAxisParam[axis].max_vel );
   ini->WriteFloat( strAxis, "ACCELERATION", m_sAxisParam[axis].accel );
   ini->WriteFloat( strAxis, "DECELERATION", m_sAxisParam[axis].decel );
   ini->WriteFloat( strAxis, "JERK_PERCENT", m_sAxisParam[axis].jp );
   
   delete ini;
   return 0;
}
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    int axis, i,j;
    for(i = 0; i < m_CardCount; i ++)
    {
        for(j = 0; j < AXIS_PER_CARD; j ++)
        {
            axis = m_CardNoArray[i] * AXIS_PER_CARD + j;
            ConfigSaveFile(axis);
        }
    }
    p9014_close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ButtonClearPosClick(TObject *Sender)
{
    int axis;
    int rc;
    AnsiString str;
    
    if(RadioGroupDriveAxis->ItemIndex < 0)
    {
        axis = m_currCardNo * AXIS_PER_CARD + 0;
    }
    else
    {
        axis = m_currCardNo * AXIS_PER_CARD +  RadioGroupDriveAxis->ItemIndex;
    }

    rc = p9014_set_pos(axis, 0, 0);
    rc = p9014_set_pos(axis, 1, 0);
    if(rc)
    {
        str.sprintf("Stop Axis fail, return code: %d", rc);
        MessageDlg(str, mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ComboBoxCardNoChages(TObject *Sender)
{
    if(ComboBoxCardNo->ItemIndex < 0)
        return;

    //card no. changes, select x by default and then display param.
    m_currCardNo =   m_CardNoArray[ComboBoxCardNo->ItemIndex];
    RadioGroupParamAxisSel->ItemIndex = 0;
    RadioGroupDriveAxis->ItemIndex = 0;
    ConfigUpdateUi(m_currCardNo * AXIS_PER_CARD + 0);
}
//---------------------------------------------------------------------------
//config axis according to parameter stored in m_sAxisParam
int TFormMain::ConfigAxis(int axis)
{
    //TODO: Add your source code here
    int rc = 0;

    rc = p9014_set_pls_outmode(axis,
        m_sAxisParam[axis].output_pulse_mode? 1 : 0);

    rc += p9014_set_pls_iptmode(axis,
        m_sAxisParam[axis].input_pulse_mode? 1 : 0);

    rc += p9014_set_el_level(axis,
        m_sAxisParam[axis].el_level? 1 : 0);

    rc += p9014_home_config(axis,
        (m_sAxisParam[axis].home_mode? 2 : 0), //home_mode,
        (m_sAxisParam[axis].org_level? 1 : 0), //org_level,
        (m_sAxisParam[axis].ez_level? 1 : 0)//ez_level);
        );
    
    if(0 == m_sAxisParam[axis].vel_profile)
    {
    rc += p9014_set_t_profile(axis,
        m_sAxisParam[axis].start_vel,
        m_sAxisParam[axis].max_vel,
        m_sAxisParam[axis].accel,
        m_sAxisParam[axis].decel);
    }
    else
    {
    rc += p9014_set_s_profile(axis,
        m_sAxisParam[axis].start_vel,
        m_sAxisParam[axis].max_vel,
        m_sAxisParam[axis].accel,
        m_sAxisParam[axis].decel,
        m_sAxisParam[axis].jp
        );
    }
    return rc;
}
//---------------------------------------------------------------------------
//display axis's parameter on dialog
int TFormMain::ConfigUpdateUi(int axis)
{
    //TODO: Add your source code here
    AnsiString str;
    unsigned int d;
    RadioGroupOutputPulseMode->ItemIndex =   m_sAxisParam[axis].output_pulse_mode ? 1 : 0;
    RadioGroupInputPulseMode->ItemIndex =  m_sAxisParam[axis].input_pulse_mode? 1 : 0;
    RadioGroupHomeMode->ItemIndex =  m_sAxisParam[axis].home_mode? 1 : 0;
    RadioGroupOrgLevel->ItemIndex =  m_sAxisParam[axis].org_level? 1 : 0;
    RadioGroupEzLevel->ItemIndex =   m_sAxisParam[axis].ez_level? 1 : 0;
    RadioGroupELLevel->ItemIndex = m_sAxisParam[axis].el_level? 1 : 0;
    RadioGroupVelProfile->ItemIndex = m_sAxisParam[axis].vel_profile? 1: 0;
	
    str.sprintf("%.2f", m_sAxisParam[axis].start_vel);
    EditStartVel->Text = str;
    str.sprintf("%.2f", m_sAxisParam[axis].max_vel);
    EditMaxVel->Text = str;
    str.sprintf("%.2f", m_sAxisParam[axis].accel);
    EditAccel->Text = str;
    str.sprintf("%.2f", m_sAxisParam[axis].decel);
    EditDecel->Text = str;	
    str.sprintf("%.2f", m_sAxisParam[axis].jp);
    EditJerkPercent->Text = str;
	
    //update DO display on dialog
    d = 0;
    p9014_get_do(m_currCardNo, &d);

	 CheckBoxDO0->Checked = (d & (0x1 << 0 ))? true : false;
	 CheckBoxDO1->Checked = (d & (0x1 << 1 ))? true : false;
	 CheckBoxDO2->Checked = (d & (0x1 << 2 ))? true : false;
	 CheckBoxDO3->Checked = (d & (0x1 << 3 ))? true : false;
	 CheckBoxDO4->Checked = (d & (0x1 << 4 ))? true : false;
	 CheckBoxDO5->Checked = (d & (0x1 << 5 ))? true : false;
	 CheckBoxDO6->Checked = (d & (0x1 << 6 ))? true : false;
	 CheckBoxDO7->Checked = (d & (0x1 << 7 ))? true : false;
	 CheckBoxDO8->Checked = (d & (0x1 << 8 ))? true : false;
	 CheckBoxDO9->Checked = (d & (0x1 << 9 ))? true : false;
	CheckBoxDO10->Checked = (d & (0x1 << 10))? true : false;
	CheckBoxDO11->Checked = (d & (0x1 << 11))? true : false;
	CheckBoxDO12->Checked = (d & (0x1 << 12))? true : false;
	CheckBoxDO13->Checked = (d & (0x1 << 13))? true : false;
	CheckBoxDO14->Checked = (d & (0x1 << 14))? true : false;
	CheckBoxDO15->Checked = (d & (0x1 << 15))? true : false;

    return 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RadioGroupParamAxisSelClick(TObject *Sender)
{
    int sel = RadioGroupParamAxisSel->ItemIndex;
    if( sel < 0)
        return;

    ConfigUpdateUi(m_currCardNo * AXIS_PER_CARD + sel);
}
//---------------------------------------------------------------------------

