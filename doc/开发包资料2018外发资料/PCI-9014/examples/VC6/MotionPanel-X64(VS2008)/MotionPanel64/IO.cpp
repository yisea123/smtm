// IO.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "IO.h"


// IO dialog

IMPLEMENT_DYNAMIC(IO, CDialog)

IO::IO(CWnd* pParent /*=NULL*/)
	: CTabChildBase(IO::IDD, pParent)
{
	m_szTabName = _T("通用输入/输出");

	m_SliderCtrlCount = 0;
	m_pSliderCtrlID = NULL;

	//EditCtrl
	m_EditCtrlCount = 0;
	m_pEditCtrlID = NULL;

	//ComboBoxCtrl
	m_ComboBoxCtrlCount = 0;
	m_pComboBoxCtrlID = NULL;

	//StaticCtrl
	m_StaticCtrlCount = 0;
	m_pStaticCtrlID = NULL;//new UINT[ m_StaticCtrlCount ];

	//ButtonCtrl
	m_ButtonCtrlCount = 32;
	m_pButtonCtrlID = new UINT[ m_ButtonCtrlCount ];
	m_pButtonCtrlID[ 0 ] = IDC_IN0;
	m_pButtonCtrlID[ 1 ] = IDC_IN1;
	m_pButtonCtrlID[ 2 ] = IDC_IN2;
	m_pButtonCtrlID[ 3 ] = IDC_IN3;
	m_pButtonCtrlID[ 4 ] = IDC_IN4;
	m_pButtonCtrlID[ 5 ] = IDC_IN5;
	m_pButtonCtrlID[ 6 ] = IDC_IN6;
	m_pButtonCtrlID[ 7 ] = IDC_IN7;
	m_pButtonCtrlID[ 8 ] = IDC_IN8;
	m_pButtonCtrlID[ 9 ] = IDC_IN9;
	m_pButtonCtrlID[ 10 ] = IDC_IN10;
	m_pButtonCtrlID[ 11 ] = IDC_IN11;
	m_pButtonCtrlID[ 12 ] = IDC_IN12;
	m_pButtonCtrlID[ 13 ] = IDC_IN13;
	m_pButtonCtrlID[ 14 ] = IDC_IN14;
	m_pButtonCtrlID[ 15 ] = IDC_IN15;

	m_pButtonCtrlID[ 16 ] = IDC_OUT0;
	m_pButtonCtrlID[ 17 ] = IDC_OUT1;
	m_pButtonCtrlID[ 18 ] = IDC_OUT2;
	m_pButtonCtrlID[ 19 ] = IDC_OUT3;
	m_pButtonCtrlID[ 20 ] = IDC_OUT4;
	m_pButtonCtrlID[ 21 ] = IDC_OUT5;
	m_pButtonCtrlID[ 22 ] = IDC_OUT6;
	m_pButtonCtrlID[ 23 ] = IDC_OUT7;
	m_pButtonCtrlID[ 24 ] = IDC_OUT8;
	m_pButtonCtrlID[ 25 ] = IDC_OUT9;
	m_pButtonCtrlID[ 26 ] = IDC_OUT10;
	m_pButtonCtrlID[ 27 ] = IDC_OUT11;
	m_pButtonCtrlID[ 28 ] = IDC_OUT12;
	m_pButtonCtrlID[ 29 ] = IDC_OUT13;
	m_pButtonCtrlID[ 30 ] = IDC_OUT14;
	m_pButtonCtrlID[ 31 ] = IDC_OUT15;
}

IO::~IO()
{
}

void IO::DoDataExchange(CDataExchange* pDX)
{
	CTabChildBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IO, CTabChildBase)
END_MESSAGE_MAP()


// IO message handlers
