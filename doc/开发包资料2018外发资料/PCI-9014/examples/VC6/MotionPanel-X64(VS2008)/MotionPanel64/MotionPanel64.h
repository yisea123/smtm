// MotionPanel64.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMotionPanel64App:
// �йش����ʵ�֣������ MotionPanel64.cpp
//

class CMotionPanel64App : public CWinApp
{
public:
	CMotionPanel64App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMotionPanel64App theApp;