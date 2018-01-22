//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "pci9014.h"
#include "TypeDef.h"

//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *One;
    TTabSheet *Three;
    TTabSheet *Four;
    TStatusBar *StatusBar1;
        TTabSheet *TabSheet1;
        TStringGrid *StringGridFreeMode;
        TGroupBox *GroupBox1;
    TRadioGroup *RadioGroupFreeModeDriveType;
        TLabel *Label1;
        TEdit *EditFreeModeDist;
        TButton *ButtonFreeModeRun;
        TButton *ButtonFreeModeStop;
        TTimer *Timer1;
	TGroupBox *GroupBoxDI;
	TGroupBox *GroupBoxDO1;
	TCheckBox *CheckBoxDO0;
	TCheckBox *CheckBoxDO1;
        TCheckBox *CheckBoxDO2;
        TCheckBox *CheckBoxDO3;
        TCheckBox *CheckBoxDO4;
        TCheckBox *CheckBoxDO5;
        TCheckBox *CheckBoxDO6;
	TCheckBox *CheckBoxDO7;
	TCheckBox *CheckBoxDO15;
	TCheckBox *CheckBoxDO14;
        TCheckBox *CheckBoxDO13;
	TCheckBox *CheckBoxDO12;
	TCheckBox *CheckBoxDO11;
	TCheckBox *CheckBoxDO10;
	TCheckBox *CheckBoxDO9;
	TCheckBox *CheckBoxDO8;
	TCheckBox *CheckBoxDI15;
	TCheckBox *CheckBoxDI14;
	TCheckBox *CheckBoxDI13;
	TCheckBox *CheckBoxDI12;
	TCheckBox *CheckBoxDI11;
	TCheckBox *CheckBoxDI10;
	TCheckBox *CheckBoxDI9;
	TCheckBox *CheckBoxDI8;
	TCheckBox *CheckBoxDI0;
	TCheckBox *CheckBoxDI1;
	TCheckBox *CheckBoxDI2;
	TCheckBox *CheckBoxDI3;
	TCheckBox *CheckBoxDI4;
	TCheckBox *CheckBoxDI5;
	TCheckBox *CheckBoxDI6;
	TCheckBox *CheckBoxDI7;
	TGroupBox *GroupBox2;
	TLabel *Label2;
	TEdit *EditLogicVer;
	TEdit *EditDriverVer;
	TEdit *EditApiVer;
	TEdit *EditAppVer;
	TLabel *Label4;
	TLabel *Label7;
	TLabel *Label8;
    TLabel *LabelDioNote;
    TButton *ButtonCfgApply;
    TRadioGroup *RadioGroupOutputPulseMode;
    TRadioGroup *RadioGroupInputPulseMode;
    TGroupBox *GroupBox3;
    TEdit *EditStartVel;
    TEdit *EditMaxVel;
    TEdit *EditAccel;
    TEdit *EditDecel;
    TRadioGroup *RadioGroupVelProfile;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label9;
    TLabel *Label10;
    TButton *ButtonClearPos;
    TRadioGroup *RadioGroupParamAxisSel;
    TGroupBox *GroupBoxHomeConfig;
    TRadioGroup *RadioGroupHomeMode;
    TRadioGroup *RadioGroupOrgLevel;
    TRadioGroup *RadioGroupEzLevel;
        TRadioGroup *RadioGroupVelMode;
        TLabel *Label11;
    TEdit *EditJerkPercent;
        TLabel *Label12;
        TRadioGroup *RadioGroupELLevel;
    TComboBox *ComboBoxCardNo;
    TLabel *Label3;
    TRadioGroup *RadioGroupDriveAxis;
        TEdit *EditLogicRev;
        TLabel *Label13;
    void __fastcall PageControl1Change(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ButtonFreeModeRunClick(TObject *Sender);
        void __fastcall ButtonFreeModeStopClick(TObject *Sender);
    void __fastcall ButtonCfgApplyClick(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ButtonClearPosClick(TObject *Sender);
    void __fastcall ComboBoxCardNoChages(TObject *Sender);
    void __fastcall RadioGroupParamAxisSelClick(TObject *Sender);

protected:
    enum {AXIS_MAX = 64};
    enum {AXIS_PER_CARD = 4};

private:	// User declarations
public:		// User declarations
    virtual __fastcall TFormMain(TComponent* Owner);
protected:
     void UpdateDIO(unsigned int di);
        AXIS_PARAM_T          m_sAxisParam[AXIS_MAX];
        int m_currCardNo;
        int m_CardNoArray[16];
        int m_CardCount;
        int ConfigReadFromFile(int axis);
    int ConfigSaveFile(int axis);
    int ConfigAxis(int axis);
    int ConfigUpdateUi(int axis);


};
//---------------------------------------------------------------------------
extern TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
