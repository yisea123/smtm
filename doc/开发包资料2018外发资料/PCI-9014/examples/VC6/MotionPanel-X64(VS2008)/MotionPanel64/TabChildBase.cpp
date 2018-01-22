// TabChildBase.cpp
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TabChildBase.h"
//#include "SetMainPad.h"
#include "CTabParentBase.h"


//////////////////////////////////////////////////////////////////////
CTabChildBase::CTabChildBase(INT IDD,CWnd* pParent)
	: CDialog(IDD, pParent)
{
	m_szTabName = NULL;
	m_DlgID = IDD;

	//SliderCtrl
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
	m_pStaticCtrlID = NULL;
	
	//ButtonCtrl
	m_ButtonCtrlCount = 0;
	m_pButtonCtrlID = NULL;
}

CTabChildBase::~CTabChildBase()
{
	//SliderCtrl
	if(NULL != m_pSliderCtrlID)
	{
		delete[] m_pSliderCtrlID;
		m_pSliderCtrlID = NULL;
		m_SliderCtrlCount = 0;
	}

	//EditCtrl
	if(NULL != m_pEditCtrlID)
	{
		delete[] m_pEditCtrlID;
		m_pEditCtrlID = NULL;
		m_EditCtrlCount = 0;
	}
	
	//ComboBoxCtrl
	if(NULL != m_pComboBoxCtrlID)
	{
		delete[] m_pComboBoxCtrlID;
		m_pComboBoxCtrlID = NULL;
		m_ComboBoxCtrlCount = 0;
	}

	//StaticCtrl
	if(NULL != m_pStaticCtrlID)
	{
		delete[] m_pStaticCtrlID;
		m_pStaticCtrlID = NULL;
		m_StaticCtrlCount = 0;
	}

	//ButtonCtrl
	if(NULL != m_pButtonCtrlID)
	{
		delete[] m_pButtonCtrlID;
		m_pButtonCtrlID = NULL;
		m_ButtonCtrlCount = 0;
	}
}

BEGIN_MESSAGE_MAP(CTabChildBase, CDialog)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL CTabChildBase::PreTranslateMessage(MSG* pMsg) 
{	
	switch(pMsg->message)
	{
		case(WM_KEYDOWN ):
			switch( pMsg->wParam )
			{
				case VK_RETURN:
					{
						UINT nID = ::GetDlgCtrlID(pMsg->hwnd);
						for(int i = 0; i < m_EditCtrlCount; i++)
						{
							if(nID == m_pEditCtrlID[i])
							{
								CTabParentBase *pTabParent = (CTabParentBase*)GetTabParent();
								pTabParent->UpdateByEdit(pMsg->hwnd);
								UpdateDisplay();
								break;
							}
						}
					}
					return TRUE;
				case VK_ESCAPE:
					return TRUE;
				default:
					break;
			}
			break;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void CTabChildBase::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CTabParentBase *pTabParent = (CTabParentBase*)GetTabParent();
	BOOL bExist = FALSE;

	UINT nID = ::GetDlgCtrlID(pScrollBar->GetSafeHwnd());
	for(int i=0; i < m_SliderCtrlCount; i++)
	{
		if(m_pSliderCtrlID[i] == nID)
		{
			pTabParent->UpdateBySlider(pScrollBar->GetSafeHwnd());
			bExist = TRUE;
			break;
		}
	}
	if(bExist)
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
	UpdateDisplay();
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL CTabChildBase::OnCmdMsg(UINT nID, int nCode, void *pExtra, AFX_CMDHANDLERINFO *pHandlerInfo)
{
	if(pHandlerInfo == NULL)
	{
		if(CBN_SELCHANGE == nCode)
		{
			for(int i = 0; i < m_ComboBoxCtrlCount; i++)
			{
				if(nID == m_pComboBoxCtrlID[i])
				{
					CTabParentBase *pTabParent = (CTabParentBase*)GetTabParent();
					pTabParent->UpdateByCombo(GetDlgItem(nID)->GetSafeHwnd());

					UpdateDisplay();
					return(TRUE);
				}
			}
		}
		else if(CN_COMMAND == nCode)
		{
			for(int i = 0; i < m_ButtonCtrlCount; i++)
			{
				if(nID == m_pButtonCtrlID[i])
				{
					CTabParentBase *pTabParent = (CTabParentBase*)GetTabParent();
					pTabParent->UpdateByButton(GetDlgItem(nID)->GetSafeHwnd());
					UpdateDisplay();
					return(TRUE);
				}
			}
		}
	}

	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void CTabChildBase::UpdateDisplay( bool bShowType )
{
	CTabParentBase *pTabParent = (CTabParentBase*)GetTabParent();
	int i;

	//SliderCtrl
	for(i = 0; i < m_SliderCtrlCount; i++)
	{
		pTabParent->DisplaySlider(GetDlgItem(m_pSliderCtrlID[i])->GetSafeHwnd());
	}
	 
	//EditCtrl
	for(i = 0; i < m_EditCtrlCount; i++)
	{
		pTabParent->DisplayEdit(GetDlgItem(m_pEditCtrlID[i])->GetSafeHwnd(),bShowType);
	}

	//ComboBoxCtrl
	for(i = 0; i < m_ComboBoxCtrlCount; i++)
	{
		pTabParent->DisplayCombo(GetDlgItem(m_pComboBoxCtrlID[i])->GetSafeHwnd());
	}

	//ButtonCtrl
	for(i = 0; i < m_ButtonCtrlCount; i++)
	{
		pTabParent->DisplayButton(GetDlgItem(m_pButtonCtrlID[i])->GetSafeHwnd());
	}

	//StaticCtrl
	for(i = 0; i < m_StaticCtrlCount; i++)
	{
		pTabParent->DisplayStatic(GetDlgItem(m_pStaticCtrlID[i])->GetSafeHwnd());
	}
}










