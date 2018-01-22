#pragma once


// Config dialog
#include "TabChildBase.h"
class Config : public CTabChildBase
{
	DECLARE_DYNAMIC(Config)

public:
	Config(CWnd* pParent = NULL);   // standard constructor
	virtual ~Config();

// Dialog Data
	enum { IDD = IDD_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
