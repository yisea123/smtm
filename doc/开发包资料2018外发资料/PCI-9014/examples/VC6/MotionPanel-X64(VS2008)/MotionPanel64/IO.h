#pragma once


// IO dialog
#include "TabChildBase.h"
class IO : public CTabChildBase
{
	DECLARE_DYNAMIC(IO)

public:
	IO(CWnd* pParent = NULL);   // standard constructor
	virtual ~IO();

// Dialog Data
	enum { IDD = IDD_IO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
