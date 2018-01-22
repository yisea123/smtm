#pragma once


// Ver dialog
#include "TabChildBase.h"
class Ver : public CTabChildBase
{
	DECLARE_DYNAMIC(Ver)

public:
	Ver(CWnd* pParent = NULL);   // standard constructor
	virtual ~Ver();

// Dialog Data
	enum { IDD = IDD_VER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
