// onfig.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "onfig.h"


// Config dialog

IMPLEMENT_DYNAMIC(Config, CDialog)

Config::Config(CWnd* pParent /*=NULL*/)
	: CTabChildBase(Config::IDD, pParent)
{
	m_szTabName = _T("≤Œ ˝…Ë÷√");

	m_SliderCtrlCount = 0;
	m_pSliderCtrlID = NULL;

	//EditCtrl
	m_EditCtrlCount = 5;
	m_pEditCtrlID = new UINT[ m_EditCtrlCount ];
	m_pEditCtrlID[ 0 ] = IDC_VEL_START;
	m_pEditCtrlID[ 1 ] = IDC_VEL_MAX;
	m_pEditCtrlID[ 2 ] = IDC_ACC;
	m_pEditCtrlID[ 3 ] = IDC_DEC;
	m_pEditCtrlID[ 4 ] = IDC_JERK;

	//ComboBoxCtrl
	m_ComboBoxCtrlCount = 0;
	m_pComboBoxCtrlID = NULL;

	//StaticCtrl
	m_StaticCtrlCount = 0;
	m_pStaticCtrlID = NULL;//new UINT[ m_StaticCtrlCount ];

	//ButtonCtrl
	m_ButtonCtrlCount = 17;
	m_pButtonCtrlID = new UINT[ m_ButtonCtrlCount ];
	m_pButtonCtrlID[ 0 ] = IDC_MODEL_PULSE;
	m_pButtonCtrlID[ 1 ] = IDC_MODEL_CWCCW;	
	m_pButtonCtrlID[ 2 ] = IDC_BACK_PULSE;
	m_pButtonCtrlID[ 3 ] = IDC_BACK_AB;
	m_pButtonCtrlID[ 4 ] = IDC_ORG;
	m_pButtonCtrlID[ 5 ] = IDC_ORG_EZ;
	m_pButtonCtrlID[ 6 ] = IDC_EZ_LOW;
	m_pButtonCtrlID[ 7 ] = IDC_EZ_HIGH;
	m_pButtonCtrlID[ 8 ] = IDC_T_TYPE;
	m_pButtonCtrlID[ 9 ] = IDC_S_TYPE;
	m_pButtonCtrlID[ 10 ] = IDC_LIMIT_LOW;
	m_pButtonCtrlID[ 11 ] = IDC_LIMIT_HIGH;
	m_pButtonCtrlID[ 12 ] = IDC_SET_X;
	m_pButtonCtrlID[ 13 ] = IDC_SET_Y;
	m_pButtonCtrlID[ 14 ] = IDC_SET_Z;
	m_pButtonCtrlID[ 15 ] = IDC_SET_U;
	m_pButtonCtrlID[ 16 ] = IDC_APPLY;
}

Config::~Config()
{
}

void Config::DoDataExchange(CDataExchange* pDX)
{
	CTabChildBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Config, CTabChildBase)
END_MESSAGE_MAP()


// Config message handlers
