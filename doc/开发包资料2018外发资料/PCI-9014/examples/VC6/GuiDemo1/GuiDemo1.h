// GuiDemo1.h : main header file for the GUIDEMO1 application
//

#if !defined(AFX_GUIDEMO1_H__7E7EFD1F_F49B_492A_B043_4046CBC5AECF__INCLUDED_)
#define AFX_GUIDEMO1_H__7E7EFD1F_F49B_492A_B043_4046CBC5AECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGuiDemo1App:
// See GuiDemo1.cpp for the implementation of this class
//

class CGuiDemo1App : public CWinApp
{
public:
	CGuiDemo1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuiDemo1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGuiDemo1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDEMO1_H__7E7EFD1F_F49B_492A_B043_4046CBC5AECF__INCLUDED_)
