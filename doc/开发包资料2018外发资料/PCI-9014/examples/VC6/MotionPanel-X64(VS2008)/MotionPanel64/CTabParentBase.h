#pragma once
#include "TabChildBase.h"
#define MAX_TAB_COUNT 10

// CTabParentBase dialog

class CTabParentBase : public CDialog
{
	DECLARE_DYNAMIC(CTabParentBase)

public:
	CTabParentBase(INT IDD,CWnd* pParent = NULL);   // standard constructor	
	virtual ~CTabParentBase();
	virtual BOOL  UpdateByEdit(HWND hWnd) = 0;
	virtual BOOL  UpdateBySlider(HWND hWnd) = 0;
	virtual BOOL  UpdateByCombo(HWND hWnd) = 0;
	virtual BOOL  UpdateByButton(HWND hWnd) = 0;

	virtual BOOL  DisplaySlider(HWND hWnd) = 0;
	virtual BOOL  DisplayEdit(HWND hWnd,bool bShowType = true ) = 0;
	virtual BOOL  DisplayCombo(HWND hWnd) = 0;
	virtual BOOL  DisplayButton(HWND hWnd) = 0;
	virtual BOOL  DisplayStatic(HWND hWnd) = 0;	
protected :
	CTabChildBase	*m_ppTabList[MAX_TAB_COUNT];
	DWORD	m_dwListCount;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
