// CTabParentBase.cpp : implementation file
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "CTabParentBase.h"

// CTabParentBase dialog

IMPLEMENT_DYNAMIC(CTabParentBase, CDialog)

CTabParentBase::CTabParentBase(INT IDD,CWnd* pParent /*=NULL*/)
	: CDialog( IDD, pParent)
{

}

CTabParentBase::~CTabParentBase()
{
}

void CTabParentBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabParentBase, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTabParentBase message handlers

void CTabParentBase::OnDestroy()
{
	CDialog::OnDestroy();

	for(DWORD dwPos = 0; dwPos < m_dwListCount; dwPos++)
	{
		m_ppTabList[dwPos]->DestroyWindow();
		delete m_ppTabList[dwPos];
	}
	m_dwListCount = 0;	
}