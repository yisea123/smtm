// Axis.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "Axis.h"


// Axis dialog

IMPLEMENT_DYNAMIC(Axis, CDialog)

Axis::Axis(CWnd* pParent /*=NULL*/)
: CTabChildBase(Axis::IDD, pParent)
{
	m_szTabName = _T("Öá");

	m_SliderCtrlCount = 0;
	m_pSliderCtrlID = NULL;

	//EditCtrl
	m_EditCtrlCount = 32;
	m_pEditCtrlID = new UINT[ m_EditCtrlCount ];
	m_pEditCtrlID[ 0 ] = IDC_DEST_POS_X;
	m_pEditCtrlID[ 1 ] = IDC_DEST_POS_Y;
	m_pEditCtrlID[ 2 ] = IDC_DEST_POS_Z;
	m_pEditCtrlID[ 3 ] = IDC_DEST_POS_U;

	m_pEditCtrlID[ 4 ] = IDC_SPEED_X;
	m_pEditCtrlID[ 5 ] = IDC_SPEED_Y;
	m_pEditCtrlID[ 6 ] = IDC_SPEED_Z;
	m_pEditCtrlID[ 7 ] = IDC_SPEED_U;

	m_pEditCtrlID[ 8 ] = IDC_STATUS_X;
	m_pEditCtrlID[ 9 ] = IDC_STATUS_Y;
	m_pEditCtrlID[ 10 ] = IDC_STATUS_Z;
	m_pEditCtrlID[ 11 ] = IDC_STATUS_U;

	m_pEditCtrlID[ 12 ] = IDC_CMDPOS_X;
	m_pEditCtrlID[ 13 ] = IDC_CMDPOS_Y;
	m_pEditCtrlID[ 14 ] = IDC_CMDPOS_Z;
	m_pEditCtrlID[ 15 ] = IDC_CMDPOS_U;

	m_pEditCtrlID[ 16 ] = IDC_ENCPOS_X;
	m_pEditCtrlID[ 17 ] = IDC_ENCPOS_Y;
	m_pEditCtrlID[ 18 ] = IDC_ENCPOS_Z;
	m_pEditCtrlID[ 19 ] = IDC_ENCPOS_U;

	m_pEditCtrlID[ 20 ] = IDC_PEL_X;
	m_pEditCtrlID[ 21 ] = IDC_PEL_Y;
	m_pEditCtrlID[ 22 ] = IDC_PEL_Z;
	m_pEditCtrlID[ 23 ] = IDC_PEL_U;

	m_pEditCtrlID[ 24 ] = IDC_MEL_X;
	m_pEditCtrlID[ 25 ] = IDC_MEL_Y;
	m_pEditCtrlID[ 26 ] = IDC_MEL_Z;
	m_pEditCtrlID[ 27 ] = IDC_MEL_U;

	m_pEditCtrlID[ 28 ] = IDC_ORG_X;
	m_pEditCtrlID[ 29 ] = IDC_ORG_Y;
	m_pEditCtrlID[ 30 ] = IDC_ORG_Z;
	m_pEditCtrlID[ 31 ] = IDC_ORG_U;

	//ComboBoxCtrl
	m_ComboBoxCtrlCount = 0;
	m_pComboBoxCtrlID = NULL;

	//StaticCtrl
	m_StaticCtrlCount = 0;
	m_pStaticCtrlID = NULL;//new UINT[ m_StaticCtrlCount ];

	//ButtonCtrl
	m_ButtonCtrlCount = 21;
	m_pButtonCtrlID = new UINT[ m_ButtonCtrlCount ];
	m_pButtonCtrlID[ 0 ] = IDC_P_RUN;
	m_pButtonCtrlID[ 1 ] = IDC_INC_RUN;
	m_pButtonCtrlID[ 2 ] = IDC_V_RUN_P;
	m_pButtonCtrlID[ 3 ] = IDC_V_RUN_N;
	m_pButtonCtrlID[ 4 ] = IDC_HOME_P;
	m_pButtonCtrlID[ 5 ] = IDC_HOME_N;

	m_pButtonCtrlID[ 6 ] = IDC_X;
	m_pButtonCtrlID[ 7 ] = IDC_Y;
	m_pButtonCtrlID[ 8 ] = IDC_Z;
	m_pButtonCtrlID[ 9 ] = IDC_U;

	m_pButtonCtrlID[ 10 ] = IDC_CMD_RUN;
	m_pButtonCtrlID[ 11 ] = IDC_CMD_ESTOP;
	m_pButtonCtrlID[ 12 ] = IDC_CMD_STOP;
	m_pButtonCtrlID[ 13 ] = IDC_CLEAR_POS;

	m_pButtonCtrlID[ 14 ] = IDC_SPEED_LOW;
	m_pButtonCtrlID[ 15 ] = IDC_SPEED_HIGH;
	m_pButtonCtrlID[ 16 ] = IDC_SPEED_INCREASE;

	m_pButtonCtrlID[ 17 ] = IDC_DER_CHANGE_X;
	m_pButtonCtrlID[ 18 ] = IDC_DER_CHANGE_Y;
	m_pButtonCtrlID[ 19 ] = IDC_DER_CHANGE_Z;
	m_pButtonCtrlID[ 20 ] = IDC_DER_CHANGE_U;
	
}

Axis::~Axis()
{
}

void Axis::DoDataExchange(CDataExchange* pDX)
{
	CTabChildBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Axis, CTabChildBase)
END_MESSAGE_MAP()


// Axis message handlers
