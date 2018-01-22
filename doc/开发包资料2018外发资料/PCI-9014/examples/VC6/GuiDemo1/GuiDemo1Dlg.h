// GuiDemo1Dlg.h : header file
//

#if !defined(AFX_GUIDEMO1DLG_H__02645527_3652_4685_8F32_CE8863A825FE__INCLUDED_)
#define AFX_GUIDEMO1DLG_H__02645527_3652_4685_8F32_CE8863A825FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGuiDemo1Dlg dialog

class CGuiDemo1Dlg : public CDialog
{
// Construction
public:
	CGuiDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGuiDemo1Dlg)
	enum { IDD = IDD_GUIDEMO1_DIALOG };
	CComboBox	m_ctlAxisSel;
	int		m_Type;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGuiDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonEmgStop();
	afx_msg void OnButtonSdStop();
	afx_msg void OnButtonRun();
	afx_msg void OnEditchangeComboAxis();
	afx_msg void OnSelchangeComboAxis();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_axis;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDEMO1DLG_H__02645527_3652_4685_8F32_CE8863A825FE__INCLUDED_)
