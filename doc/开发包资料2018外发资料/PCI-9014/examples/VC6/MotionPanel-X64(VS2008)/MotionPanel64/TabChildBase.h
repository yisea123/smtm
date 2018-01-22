// TabChildBase.h

#pragma once

class CTabChildBase : public CDialog
{
public:
	CTabChildBase(INT IDD,CWnd* pParent = NULL);
	virtual ~CTabChildBase();
	void UpdateDisplay( bool bShowType = true );

	LPCTSTR m_szTabName;
	int	m_DlgID;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void *pExtra, AFX_CMDHANDLERINFO *pHandlerInfo);
	
private:
	CWnd *GetTabParent()
	{
		return(GetParent()->GetParent());
	};
protected:
	//SliderCtrl
	int m_SliderCtrlCount;
	PUINT m_pSliderCtrlID;

	//EditCtrl
	int m_EditCtrlCount;
	PUINT m_pEditCtrlID;

	//ComboBoxCtrl
	int m_ComboBoxCtrlCount;
	PUINT m_pComboBoxCtrlID;

	//StaticCtrl
	int m_StaticCtrlCount;
	PUINT m_pStaticCtrlID;

	//ButtonCtrl
	int	m_ButtonCtrlCount;
	PUINT m_pButtonCtrlID;

	virtual void OnOK(){DestroyWindow();};
	virtual void OnCancel(){DestroyWindow();};
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()
};