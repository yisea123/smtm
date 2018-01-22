#pragma once


// Axis dialog
#include "TabChildBase.h"
class Axis : public CTabChildBase
{
	DECLARE_DYNAMIC(Axis)

public:
	Axis(CWnd* pParent = NULL);   // standard constructor
	virtual ~Axis();

// Dialog Data
	enum { IDD = IDD_AIXS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
