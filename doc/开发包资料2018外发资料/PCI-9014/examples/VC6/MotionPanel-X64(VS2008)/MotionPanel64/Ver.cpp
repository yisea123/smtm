// Ver.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "Ver.h"


// Ver dialog

IMPLEMENT_DYNAMIC(Ver, CDialog)

Ver::Ver(CWnd* pParent /*=NULL*/)
	: CTabChildBase(Ver::IDD, pParent)
{
	m_szTabName = _T("∞Ê±æ–≈œ¢");

	m_SliderCtrlCount = 0;
	m_pSliderCtrlID = NULL;

	//EditCtrl
	m_EditCtrlCount = 0;
	m_pEditCtrlID = NULL;

	//ComboBoxCtrl
	m_ComboBoxCtrlCount = 0;
	m_pComboBoxCtrlID = NULL;

	//StaticCtrl
	m_StaticCtrlCount = 4;
	m_pStaticCtrlID = new UINT[ m_StaticCtrlCount ];
	m_pStaticCtrlID[ 0 ] = IDC_APP_VER;
	m_pStaticCtrlID[ 1 ] = IDC_API_VER;
	m_pStaticCtrlID[ 2 ] = IDC_DRV_VER;
	m_pStaticCtrlID[ 3 ] = IDC_LOGIC_VER;


	//ButtonCtrl
	m_ButtonCtrlCount = 0;
	m_pButtonCtrlID = NULL;//new UINT[ m_ButtonCtrlCount ];
}

Ver::~Ver()
{
}

void Ver::DoDataExchange(CDataExchange* pDX)
{
	CTabChildBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Ver, CTabChildBase)
END_MESSAGE_MAP()


// Ver message handlers
