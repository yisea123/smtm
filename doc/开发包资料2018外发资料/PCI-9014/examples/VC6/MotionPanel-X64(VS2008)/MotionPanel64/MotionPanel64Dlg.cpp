// MotionPanel64Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MotionPanel64.h"
#include "MotionPanel64Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Axis.h"
#include "IO.h"
#include "onfig.h"
#include "Ver.h"

#include "pci9014.h"
#pragma comment( lib,"Pci9014.lib")

enum LANGUAGE{ CN = 0,EN };
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMotionPanel64Dlg 对话框




CMotionPanel64Dlg::CMotionPanel64Dlg(CWnd* pParent /*=NULL*/)
: CTabParentBase(CMotionPanel64Dlg::IDD, pParent)
, m_nCurCardIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nlanguage = CN;
	m_nPageID = 0;
	m_nConfigAxisNo = 0;

	memset( m_sAxisParam,0,sizeof( AXIS_PARAM_T ) * AXIS_MAX);
	memset( m_CardNoArray,0,sizeof( int ) * 16);
	m_CardCount = 0;

	memset( m_dCurrentVel,0,sizeof( double ) * AXIS_PER_CARD );
	memset( m_nCMDPos,0,sizeof( int ) * AXIS_PER_CARD );
	memset( m_nCurrentPos,0,sizeof( int ) * AXIS_PER_CARD );

	m_wordInput.IOW = 0;
	m_wordOutput.IOW = 0;
	memset( m_pAxisStatus,0,sizeof( HardAxisStatus ) * AXIS_PER_CARD);

	m_nDestPos[ 0 ] = 2000;
	m_nDestPos[ 1 ] = 2000;
	m_nDestPos[ 2 ] = 2000;
	m_nDestPos[ 3 ] = 2000;

	memset( m_bStatues,0,sizeof( bool ) * AXIS_PER_CARD);
	memset( m_bToSetCMD,0,sizeof( bool ) * AXIS_PER_CARD);

	m_nCMDType = 0;
	m_nVelModel = 2;
}

void CMotionPanel64Dlg::DoDataExchange(CDataExchange* pDX)
{
	CTabParentBase::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_CARD, m_nCurCardIndex);
}

BEGIN_MESSAGE_MAP(CMotionPanel64Dlg, CTabParentBase)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CMotionPanel64Dlg::OnTcnSelchangeTabMain)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_MAIN, &CMotionPanel64Dlg::OnTcnSelchangingTabMain)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMotionPanel64Dlg 消息处理程序

BOOL CMotionPanel64Dlg::OnInitDialog()
{
	CTabParentBase::OnInitDialog();

	int rc = 0;
	int i = 0, j = 0, axis = 0;
	CString str;

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	rc = p9014_initial(&m_CardCount, m_CardNoArray);
	if(rc)
	{
		AfxMessageBox(_T("Initialize card fail!"));
	}
	if(m_CardCount < 1)
	{
		AfxMessageBox(_T("Find no card!"));
	}

	do
	{
		for(j = 0; j < AXIS_PER_CARD; j ++)
		{
			axis = j;//m_CardNoArray[i] * AXIS_PER_CARD + j;
			ConfigReadFromFile(axis);
			ConfigAxis(axis);
		}
		i ++;
	}while( i < m_CardCount );

	for(i = 0; i < m_CardCount; i ++)
	{
		str.Format(_T("%d"), m_CardNoArray[i]);
		((CComboBox*)GetDlgItem( IDC_CARD ))->AddString( str );
	}

	CreateTabs();
	SetTimer( 100,100,NULL );
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMotionPanel64Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMotionPanel64Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CTabParentBase::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMotionPanel64Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMotionPanel64Dlg::DisplaySlider(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	return bReval;
}
BOOL CMotionPanel64Dlg::DisplayStatic(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	TCHAR	szTmp[1024];
	_tcscpy_s(szTmp, TEXT(""));
	switch(nID)
	{
	case IDC_APP_VER:
		{
			_stprintf_s(szTmp, _T("1.03"));
		}
		break;
	case IDC_API_VER:
		{
			unsigned int ver[ ] = {0, 0, 0, 0};
			p9014_get_version(m_CardNoArray[ m_nCurCardIndex ], ver +0, ver + 1, ver + 2);
			_stprintf_s(szTmp, _T("%d.%02d"), ver[0] >> 8, ver[0] & 0xff);
		}
		break;
	case IDC_DRV_VER:
		{
			unsigned int ver[ ] = {0, 0, 0, 0};
			p9014_get_version(m_CardNoArray[ m_nCurCardIndex ], ver +0, ver + 1, ver + 2);
			_stprintf_s(szTmp, _T("%d.%02d"), ver[1] >> 8, ver[1] & 0xff);
		}
		break;
	case IDC_LOGIC_VER:
		{
			unsigned int ver[ ] = {0, 0, 0, 0};
			p9014_get_version(m_CardNoArray[ m_nCurCardIndex ], ver +0, ver + 1, ver + 2);
			_stprintf_s(szTmp, _T("%d.%02d"), ver[2] >> 8, ver[2] & 0xff);
		}
		break;
	}
	::SetWindowText(hWnd, szTmp);	
	return(bReval);
}
BOOL CMotionPanel64Dlg::DisplayEdit(HWND hWnd,bool bShowType )
{
	BOOL bReval = TRUE;
	TCHAR	szTmp[1024];
	_tcscpy_s(szTmp, TEXT(""));
	int nID = ::GetDlgCtrlID(hWnd);
	switch(nID)
	{
	case IDC_VEL_START:
		{
			_stprintf_s(szTmp, _T("%f"),m_sAxisParam[ m_nConfigAxisNo ].start_vel);
		}
		break;
	case IDC_VEL_MAX:
		{
			_stprintf_s(szTmp, _T("%f"),m_sAxisParam[ m_nConfigAxisNo ].max_vel);
		}
		break;
	case IDC_ACC:
		{
			_stprintf_s(szTmp, _T("%f"),m_sAxisParam[ m_nConfigAxisNo ].accel);
		}
		break;
	case IDC_DEC:
		{
			_stprintf_s(szTmp, _T("%f"),m_sAxisParam[ m_nConfigAxisNo ].decel);
		}
		break;
	case IDC_JERK:
		{
			_stprintf_s(szTmp, _T("%f"),m_sAxisParam[ m_nConfigAxisNo ].jp);
		}
		break;

	case IDC_DEST_POS_X:
		{
			_stprintf_s(szTmp, _T("%d"),m_nDestPos[ AXIS_X ]);
		}
		break;
	case IDC_DEST_POS_Y:
		{
			_stprintf_s(szTmp, _T("%d"),m_nDestPos[ AXIS_Y ]);
		}
		break;
	case IDC_DEST_POS_Z:
		{
			_stprintf_s(szTmp, _T("%d"),m_nDestPos[ AXIS_Z ]);
		}
		break;
	case IDC_DEST_POS_U:
		{
			_stprintf_s(szTmp, _T("%d"),m_nDestPos[ AXIS_U ]);
		}
		break;

	case IDC_SPEED_X:
		{
			_stprintf_s(szTmp, _T("%f"),m_dCurrentVel[ AXIS_X ]);
		}
		break;
	case IDC_SPEED_Y:
		{
			_stprintf_s(szTmp, _T("%f"),m_dCurrentVel[ AXIS_Y ]);
		}
		break;
	case IDC_SPEED_Z:
		{
			_stprintf_s(szTmp, _T("%f"),m_dCurrentVel[ AXIS_Z ]);
		}
		break;
	case IDC_SPEED_U:
		{
			_stprintf_s(szTmp, _T("%f"),m_dCurrentVel[ AXIS_U ]);
		}
		break;
	case IDC_STATUS_X:
		{
			if( m_bStatues[ AXIS_X ] )
			{
				_stprintf_s(szTmp, _T("Run") );
			}
			else
			{
				_stprintf_s(szTmp, _T("Stop") );
			}
		}
		break;
	case IDC_STATUS_Y:
		{
			if( m_bStatues[ AXIS_Y ] )
			{
				_stprintf_s(szTmp, _T("Run") );
			}
			else
			{
				_stprintf_s(szTmp, _T("Stop") );
			}
		}
		break;
	case IDC_STATUS_Z:
		{
			if( m_bStatues[ AXIS_Z ] )
			{
				_stprintf_s(szTmp, _T("Run") );
			}
			else
			{
				_stprintf_s(szTmp, _T("Stop") );
			}
		}
		break;
	case IDC_STATUS_U:
		{
			if( m_bStatues[ AXIS_U ] )
			{
				_stprintf_s(szTmp, _T("Run") );
			}
			else
			{
				_stprintf_s(szTmp, _T("Stop") );
			}
		}
		break;

	case IDC_CMDPOS_X:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCMDPos[ AXIS_X ]);
		}
		break;
	case IDC_CMDPOS_Y:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCMDPos[ AXIS_Y ]);
		}
		break;
	case IDC_CMDPOS_Z:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCMDPos[ AXIS_Z ]);
		}
		break;
	case IDC_CMDPOS_U:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCMDPos[ AXIS_U ]);
		}
		break;

	case IDC_ENCPOS_X:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCurrentPos[ AXIS_X ]);
		}
		break;
	case IDC_ENCPOS_Y:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCurrentPos[ AXIS_Y ]);
		}
		break;
	case IDC_ENCPOS_Z:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCurrentPos[ AXIS_Z ]);
		}
		break;
	case IDC_ENCPOS_U:
		{
			_stprintf_s(szTmp, _T("%d"),m_nCurrentPos[ AXIS_U ]);
		}
		break;

	case IDC_PEL_X:
		{
			if( m_pAxisStatus[ AXIS_X ].ASBIT._pel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_PEL_Y:
		{
			if( m_pAxisStatus[ AXIS_Y ].ASBIT._pel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_PEL_Z:
		{
			if( m_pAxisStatus[ AXIS_Z ].ASBIT._pel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_PEL_U:
		{
			if( m_pAxisStatus[ AXIS_U ].ASBIT._pel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_MEL_X:
		{
			if( m_pAxisStatus[ AXIS_X ].ASBIT._mel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_MEL_Y:
		{
			if( m_pAxisStatus[ AXIS_Y ].ASBIT._mel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_MEL_Z:
		{
			if( m_pAxisStatus[ AXIS_Z ].ASBIT._mel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_MEL_U:
		{
			if( m_pAxisStatus[ AXIS_U ].ASBIT._mel == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_ORG_X:
		{
			if( m_pAxisStatus[ AXIS_X ].ASBIT._org == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_ORG_Y:
		{
			if( m_pAxisStatus[ AXIS_Y ].ASBIT._org == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_ORG_Z:
		{
			if( m_pAxisStatus[ AXIS_U ].ASBIT._org == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	case IDC_ORG_U:
		{
			if( m_pAxisStatus[ AXIS_U ].ASBIT._org == 1 )
			{
				_stprintf_s(szTmp, _T("ON") );
			}
			else
			{
				_stprintf_s(szTmp, _T("OFF") );
			}
		}
		break;
	}
	
	if( (IDC_DEST_POS_X != nID 
		&&IDC_DEST_POS_Y != nID
		&&IDC_DEST_POS_Z != nID
		&&IDC_DEST_POS_U != nID) 
		)
	{
	::SetWindowText(hWnd, szTmp);
	}
	else
	{
		if( bShowType )
		{
			::SetWindowText(hWnd, szTmp);
		}
	}
	return bReval;
}
BOOL CMotionPanel64Dlg::DisplayCombo(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	return bReval;
}
BOOL CMotionPanel64Dlg::DisplayButton(HWND hWnd)
{
	BOOL bReval = TRUE;
	TCHAR	szTmp[1024];
	_tcscpy_s(szTmp, TEXT(""));
	int nID = ::GetDlgCtrlID(hWnd);
	if( m_nlanguage == CN )
	{
		switch(nID)
		{
		case IDC_MODEL_PULSE:
			{				
				_stprintf_s(szTmp, _T("脉冲\\方向"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].output_pulse_mode == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_MODEL_CWCCW:
			{				
				_stprintf_s(szTmp, _T("正/负脉冲(CW\\CCW"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].output_pulse_mode == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_BACK_PULSE:
			{				
				_stprintf_s(szTmp, _T("脉冲\\方向"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].input_pulse_mode == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_BACK_AB:
			{				
				_stprintf_s(szTmp, _T("4xAB"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].input_pulse_mode == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_ORG:
			{				
				_stprintf_s(szTmp, _T("原点开关"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].home_mode == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_ORG_EZ:
			{				
				_stprintf_s(szTmp, _T("原点+EZ"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].home_mode == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_EZ_LOW:
			{				
				_stprintf_s(szTmp, _T("低电平"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].ez_level == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_EZ_HIGH:
			{				
				_stprintf_s(szTmp, _T("高电平"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].ez_level == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_T_TYPE:
			{				
				_stprintf_s(szTmp, _T("T型曲线"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].vel_profile == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_S_TYPE:
			{				
				_stprintf_s(szTmp, _T("S型曲线"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].vel_profile == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_LIMIT_LOW:
			{				
				_stprintf_s(szTmp, _T("低电平"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].el_level == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_LIMIT_HIGH:
			{				
				_stprintf_s(szTmp, _T("高电平"));
				::SendMessage(hWnd, BM_SETCHECK, m_sAxisParam[ m_nConfigAxisNo ].el_level == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_SET_X:
			{				
				_stprintf_s(szTmp, _T("X"));
				::SendMessage(hWnd, BM_SETCHECK, m_nConfigAxisNo == 0?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;	
		case IDC_SET_Y:
			{				
				_stprintf_s(szTmp, _T("Y"));
				::SendMessage(hWnd, BM_SETCHECK, m_nConfigAxisNo == 1?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_SET_Z:
			{				
				_stprintf_s(szTmp, _T("Z"));
				::SendMessage(hWnd, BM_SETCHECK, m_nConfigAxisNo == 2?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_SET_U:
			{				
				_stprintf_s(szTmp, _T("U"));
				::SendMessage(hWnd, BM_SETCHECK, m_nConfigAxisNo == 3?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_APPLY:
			{				
				_stprintf_s(szTmp, _T("应用"));
			}
			break;
		case IDC_IN0:
			{				
				_stprintf_s(szTmp, _T("DI0"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit0 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN1:
			{				
				_stprintf_s(szTmp, _T("DI1"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit1 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN2:
			{				
				_stprintf_s(szTmp, _T("DI2"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit2 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN3:
			{				
				_stprintf_s(szTmp, _T("DI3"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit3 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN4:
			{				
				_stprintf_s(szTmp, _T("DI4"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit4 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN5:
			{				
				_stprintf_s(szTmp, _T("DI5"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit5 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN6:
			{				
				_stprintf_s(szTmp, _T("DI6"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit6 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN7:
			{				
				_stprintf_s(szTmp, _T("DI7"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit7 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN8:
			{				
				_stprintf_s(szTmp, _T("DI8"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit8 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN9:
			{				
				_stprintf_s(szTmp, _T("DI9"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit9 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN10:
			{				
				_stprintf_s(szTmp, _T("DI10"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit10 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN11:
			{				
				_stprintf_s(szTmp, _T("DI11"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit11 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN12:
			{				
				_stprintf_s(szTmp, _T("DI12"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit12 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN13:
			{				
				_stprintf_s(szTmp, _T("DI13"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit13 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN14:
			{				
				_stprintf_s(szTmp, _T("DI14"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit14 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_IN15:
			{				
				_stprintf_s(szTmp, _T("DI15"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordInput.IOBIT._bit15 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT0:
			{				
				_stprintf_s(szTmp, _T("DO0"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit0 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT1:
			{				
				_stprintf_s(szTmp, _T("DO1"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit1 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT2:
			{				
				_stprintf_s(szTmp, _T("DO2"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit2 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT3:
			{				
				_stprintf_s(szTmp, _T("DO3"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit3 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT4:
			{				
				_stprintf_s(szTmp, _T("DO4"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit4 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT5:
			{				
				_stprintf_s(szTmp, _T("DO5"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit5 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT6:
			{				
				_stprintf_s(szTmp, _T("DO6"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit6 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT7:
			{				
				_stprintf_s(szTmp, _T("DO7"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit7 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT8:
			{				
				_stprintf_s(szTmp, _T("DO8"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit8 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT9:
			{				
				_stprintf_s(szTmp, _T("DO9"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit9 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT10:
			{				
				_stprintf_s(szTmp, _T("DO10"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit10 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT11:
			{				
				_stprintf_s(szTmp, _T("DO11"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit11 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT12:
			{				
				_stprintf_s(szTmp, _T("DO12"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit12 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT13:
			{				
				_stprintf_s(szTmp, _T("DO13"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit13 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT14:
			{				
				_stprintf_s(szTmp, _T("DO14"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit14 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case  IDC_OUT15:
			{				
				_stprintf_s(szTmp, _T("DO15"));
				::SendMessage(hWnd, BM_SETCHECK, m_wordOutput.IOBIT._bit15 == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_P_RUN:
			{				
				_stprintf_s(szTmp, _T("绝对位置"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_INC_RUN:
			{
				_stprintf_s(szTmp, _T("增量运动"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_V_RUN_P:
			{				
				_stprintf_s(szTmp, _T("速度模式+"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 2 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_V_RUN_N:
			{				
				_stprintf_s(szTmp, _T("速度模式-"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 3 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_HOME_P:
			{				
				_stprintf_s(szTmp, _T("回原点+"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 4 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_HOME_N:
			{				
				_stprintf_s(szTmp, _T("回原点-"));
				::SendMessage(hWnd, BM_SETCHECK, m_nCMDType == 5 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;

		case IDC_X:
			{				
				_stprintf_s(szTmp, _T("X"));
				::SendMessage(hWnd, BM_SETCHECK, m_bToSetCMD[ AXIS_X ] ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_Y:
			{				
				_stprintf_s(szTmp, _T("Y"));
				::SendMessage(hWnd, BM_SETCHECK, m_bToSetCMD[ AXIS_Y ] ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_Z:
			{				
				_stprintf_s(szTmp, _T("Z"));
				::SendMessage(hWnd, BM_SETCHECK, m_bToSetCMD[ AXIS_Z ] ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_U:
			{				
				_stprintf_s(szTmp, _T("U"));
				::SendMessage(hWnd, BM_SETCHECK, m_bToSetCMD[ AXIS_U ] ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;

		case IDC_CMD_RUN:
			{				
				_stprintf_s(szTmp, _T("运行"));
			}
			break;
		case IDC_CMD_ESTOP:
			{				
				_stprintf_s(szTmp, _T("急停"));
			}
			break;
		case IDC_CMD_STOP:
			{				
				_stprintf_s(szTmp, _T("减速停止"));
			}
			break;
		case IDC_CLEAR_POS:
			{				
				_stprintf_s(szTmp, _T("位置清零"));
			}
			break;
		case IDC_SPEED_LOW:
			{
				_stprintf_s(szTmp, _T("低速运行"));
				::SendMessage(hWnd, BM_SETCHECK, m_nVelModel == 0 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_SPEED_HIGH:
			{
				_stprintf_s(szTmp, _T("高速运行"));
				::SendMessage(hWnd, BM_SETCHECK, m_nVelModel == 1 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_SPEED_INCREASE:
			{
				_stprintf_s(szTmp, _T("加减速运行"));
				::SendMessage(hWnd, BM_SETCHECK, m_nVelModel == 2 ?BST_CHECKED:BST_UNCHECKED, 0);
			}
			break;
		case IDC_DER_CHANGE_X:
			{
				_stprintf_s(szTmp, _T("换向"));
			}
			break;
		case IDC_DER_CHANGE_Y:
			{
				_stprintf_s(szTmp, _T("换向"));
			}
			break;
		case IDC_DER_CHANGE_Z:
			{
				_stprintf_s(szTmp, _T("换向"));
			}
			break;
		case IDC_DER_CHANGE_U:
			{
				_stprintf_s(szTmp, _T("换向"));
			}
			break;
		}
	}
	::SetWindowText(hWnd, szTmp);

	return(bReval);
}
BOOL CMotionPanel64Dlg::UpdateByEdit(HWND hWnd)
{

	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	CEdit objEdit;
	objEdit.Attach(hWnd);
	TCHAR szTmp[MAX_PATH];
	objEdit.GetWindowText(szTmp, MAX_PATH);
	objEdit.Detach();

	char tmp[ MAX_PATH ];
	memset( tmp,0,MAX_PATH );
	WideCharToMultiByte( CP_ACP, 0,szTmp, -1, tmp, MAX_PATH,NULL,NULL ) ;
	float iNewValue = (float)(atof( tmp ));

	if(bReval)
	{
		switch(nID)
		{
		case IDC_VEL_START:
			{
				//int iNewValue = _ttol(szTmp);				
				if( iNewValue > 0 )
				{
					m_sAxisParam[ m_nConfigAxisNo ].start_vel = iNewValue;
				}
			}
			break;
		case IDC_VEL_MAX:
			{
				if( iNewValue > 0 )
				{
					m_sAxisParam[ m_nConfigAxisNo ].max_vel = iNewValue;
				}
			}
			break;
		case IDC_ACC:
			{
				if( iNewValue > 0 )
				{
					m_sAxisParam[ m_nConfigAxisNo ].accel = iNewValue;
				}
			}
			break;
		case IDC_DEC:
			{
				if( iNewValue > 0 )
				{
					m_sAxisParam[ m_nConfigAxisNo ].decel = iNewValue;
				}
			}
			break;
		case IDC_JERK:
			{
				if( iNewValue > 0 )
				{
					m_sAxisParam[ m_nConfigAxisNo ].jp = iNewValue;
				}
			}
			break;

		case IDC_DEST_POS_X:
			{
				m_nDestPos[ AXIS_X ] = (int)iNewValue;
			}
			break;
		case IDC_DEST_POS_Y:
			{
				m_nDestPos[ AXIS_Y ] = (int)iNewValue;
			}
			break;
		case IDC_DEST_POS_Z:
			{
				m_nDestPos[ AXIS_Z ] = (int)iNewValue;
			}
			break;
		case IDC_DEST_POS_U:
			{
				m_nDestPos[ AXIS_U ] = (int)iNewValue;
			}
			break;
		}
	}
	return bReval;
}
BOOL CMotionPanel64Dlg::UpdateBySlider(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	return bReval;
}
BOOL CMotionPanel64Dlg::UpdateByCombo(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);
	return bReval;
}
BOOL CMotionPanel64Dlg::UpdateByButton(HWND hWnd)
{
	BOOL bReval = TRUE;
	int nID = ::GetDlgCtrlID(hWnd);

	switch(nID)
	{
	case IDC_MODEL_PULSE:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].output_pulse_mode = 0;
		}
		break;
	case IDC_MODEL_CWCCW:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].output_pulse_mode = 1;
		}
		break;
	case IDC_BACK_PULSE:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].input_pulse_mode = 0;
		}
		break;
	case IDC_BACK_AB:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].input_pulse_mode = 1;
		}
		break;
	case IDC_ORG:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].home_mode = 0;
		}
		break;
	case IDC_ORG_EZ:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].home_mode = 1;
		}
		break;
	case IDC_EZ_LOW:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].ez_level = 0;
		}
		break;
	case IDC_EZ_HIGH:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].ez_level = 1;
		}
		break;
	case IDC_T_TYPE:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].vel_profile = 0;
		}
		break;
	case IDC_S_TYPE:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].vel_profile = 1;
		}
		break;
	case IDC_LIMIT_LOW:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].el_level = 0;
		}
		break;
	case IDC_LIMIT_HIGH:
		{				
			m_sAxisParam[ m_nConfigAxisNo ].el_level = 1;
		}
		break;
	case IDC_SET_X:
		{				
			m_nConfigAxisNo = 0;
		}
		break;	
	case IDC_SET_Y:
		{				
			m_nConfigAxisNo = 1;
		}
		break;
	case  IDC_SET_Z:
		{				
			m_nConfigAxisNo = 2;
		}
		break;
	case  IDC_SET_U:
		{				
			m_nConfigAxisNo = 3;
		}
		break;
	case IDC_APPLY:
		{
			ConfigSaveFile( m_nConfigAxisNo );
			ConfigAxis( m_nConfigAxisNo + m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD );
		}
		break;

	case  IDC_OUT0:
		{				
			if( m_wordOutput.IOBIT._bit0 == OFF )
			{
				m_wordOutput.IOBIT._bit0 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit0 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT1:
		{				
			if( m_wordOutput.IOBIT._bit1 == OFF )
			{
				m_wordOutput.IOBIT._bit1 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit1 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT2:
		{				
			if( m_wordOutput.IOBIT._bit2 == OFF )
			{
				m_wordOutput.IOBIT._bit2 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit2 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT3:
		{				
			if( m_wordOutput.IOBIT._bit3 == OFF )
			{
				m_wordOutput.IOBIT._bit3 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit3 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT4:
		{				
			if( m_wordOutput.IOBIT._bit4 == OFF )
			{
				m_wordOutput.IOBIT._bit4 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit4 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT5:
		{				
			if( m_wordOutput.IOBIT._bit5 == OFF )
			{
				m_wordOutput.IOBIT._bit5 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit5 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT6:
		{				
			if( m_wordOutput.IOBIT._bit6 == OFF )
			{
				m_wordOutput.IOBIT._bit6 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit6 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT7:
		{				
			if( m_wordOutput.IOBIT._bit7 == OFF )
			{
				m_wordOutput.IOBIT._bit7 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit7 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT8:
		{				
			if( m_wordOutput.IOBIT._bit8 == OFF )
			{
				m_wordOutput.IOBIT._bit8 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit8 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT9:
		{				
			if( m_wordOutput.IOBIT._bit9 == OFF )
			{
				m_wordOutput.IOBIT._bit9 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit9 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT10:
		{				
			if( m_wordOutput.IOBIT._bit10 == OFF )
			{
				m_wordOutput.IOBIT._bit10 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit10 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT11:
		{				
			if( m_wordOutput.IOBIT._bit11 == OFF )
			{
				m_wordOutput.IOBIT._bit11 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit11 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT12:
		{				
			if( m_wordOutput.IOBIT._bit12 == OFF )
			{
				m_wordOutput.IOBIT._bit12 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit12 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT13:
		{				
			if( m_wordOutput.IOBIT._bit13 == OFF )
			{
				m_wordOutput.IOBIT._bit13 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit13 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT14:
		{				
			if( m_wordOutput.IOBIT._bit14 == OFF )
			{
				m_wordOutput.IOBIT._bit14 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit14 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case  IDC_OUT15:
		{				
			if( m_wordOutput.IOBIT._bit15 == OFF )
			{
				m_wordOutput.IOBIT._bit15 = ON;
			}
			else
			{
				m_wordOutput.IOBIT._bit15 = OFF;
			}
			p9014_set_do( m_nCurCardIndex,m_wordOutput.IOW );
		}
		break;
	case IDC_P_RUN:
		{
			m_nCMDType = 0;
		}
		break;
	case IDC_INC_RUN:
		{
			m_nCMDType = 1;
		}
		break;
	case IDC_V_RUN_P:
		{				
			m_nCMDType = 2;
		}
		break;
	case IDC_V_RUN_N:
		{				
			m_nCMDType = 3;
		}
		break;
	case IDC_HOME_P:
		{				
			m_nCMDType = 4;
		}
		break;
	case IDC_HOME_N:
		{				
			m_nCMDType = 5;
		}
		break;

	case IDC_X:
		{				
			m_bToSetCMD[ AXIS_X ] = !m_bToSetCMD[ AXIS_X ];
		}
		break;
	case IDC_Y:
		{				
			m_bToSetCMD[ AXIS_Y ] = !m_bToSetCMD[ AXIS_Y ];
		}
		break;
	case IDC_Z:
		{				
			m_bToSetCMD[ AXIS_Z ] = !m_bToSetCMD[ AXIS_Z ];
		}
		break;
	case IDC_U:
		{				
			m_bToSetCMD[ AXIS_U ] = !m_bToSetCMD[ AXIS_U ];
		}
		break;

	case IDC_CMD_RUN:
		{				
			for( int nAxisNo = 0; nAxisNo < AXIS_PER_CARD;nAxisNo ++ )
			{
				if( m_bToSetCMD[ nAxisNo ] )
				{
					int nAxis = m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD + nAxisNo;
					switch( m_nCMDType )
					{
					case 0:
						{
							int rc = p9014_pmove( nAxis, m_nDestPos[ nAxisNo ], 1, m_nVelModel);
							if(rc)
							{
								CString str;
								str.Format(_T("发送绝对位置运行失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					case 1:
						{
							int rc = p9014_pmove( nAxis, m_nDestPos[ nAxisNo ], 0, m_nVelModel);
							if(rc)
							{
								CString str;
								str.Format(_T("发送相对位置运行失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					case 2:
						{
							int rc = p9014_vmove( nAxis, 1, m_nVelModel );
							if(rc)
							{
								CString str;
								str.Format(_T("发送速度运行模式正向失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					case 3:
						{
							int rc = p9014_vmove( nAxis, 0, m_nVelModel );
							if(rc)
							{
								CString str;
								str.Format(_T("发送速度运行模式负向失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					case 4:
						{
							int rc = p9014_home_move( nAxis, 1 );
							if(rc)
							{
								CString str;
								str.Format(_T("正向回零失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					case 5:
						{
							int rc = p9014_home_move( nAxis, 0 );
							if(rc)
							{
								CString str;
								str.Format(_T("正向回零失败，返回值: %d"), rc);
								AfxMessageBox( str );
							}
						}
						break;
					}
				}
			}
		}
		break;
	case IDC_CMD_ESTOP:
		{				
			for( int nAxisNo = 0; nAxisNo < AXIS_PER_CARD;nAxisNo ++ )
			{
				int nAxis = m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD + nAxisNo;
				if( m_bToSetCMD[ nAxisNo ] )
				{
					int rc = p9014_stop(nAxis, 1);
					if(rc)
					{
						CString str;
						str.Format(_T("急停轴失败，返回值: %d"), rc);
						AfxMessageBox( str );
					}
				}
			}
		}
		break;
	case IDC_CMD_STOP:
		{				
			for( int nAxisNo = 0; nAxisNo < AXIS_PER_CARD;nAxisNo ++ )
			{
				int nAxis = m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD + nAxisNo;
				if( m_bToSetCMD[ nAxisNo ] )
				{
					int rc = p9014_stop(nAxis, 0);
					if(rc)
					{
						CString str;
						str.Format(_T("停止轴失败，返回值: %d"), rc);
						AfxMessageBox( str );
					}
				}
			}
		}
		break;
	case IDC_CLEAR_POS:
		{				
			for( int nAxisNo = 0; nAxisNo < AXIS_PER_CARD;nAxisNo ++ )
			{
				int nAxis = m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD + nAxisNo;
				if( m_bToSetCMD[ nAxisNo ] )
				{
					int rc = p9014_set_pos(nAxis, 0, 0);
					rc = p9014_set_pos(nAxis, 1, 0);
					if(rc)
					{
						CString str;
						str.Format(_T("清除位置失败，返回值: %d"), rc);
						AfxMessageBox( str );
					}
				}
			}
		}
		break;
	case IDC_SPEED_LOW:
		{
			m_nVelModel = 0;
		}
		break;
	case IDC_SPEED_HIGH:
		{
			m_nVelModel = 1;
		}
		break;
	case IDC_SPEED_INCREASE:
		{
			m_nVelModel = 2;
		}
		break;
	case IDC_DER_CHANGE_X:
			{
				m_nDestPos[ AXIS_X ] = -m_nDestPos[ AXIS_X ];
			}
			break;
		case IDC_DER_CHANGE_Y:
			{
				m_nDestPos[ AXIS_Y ] = -m_nDestPos[ AXIS_Y ];
			}
			break;
		case IDC_DER_CHANGE_Z:
			{
				m_nDestPos[ AXIS_Z ] = -m_nDestPos[ AXIS_Z ];
			}
			break;
		case IDC_DER_CHANGE_U:
			{
				m_nDestPos[ AXIS_U ] = -m_nDestPos[ AXIS_U ];
			}
			break;
	}
	return(bReval);
}

void CMotionPanel64Dlg::UppdateTabs( bool bShowType )
{
	for(DWORD dwPos = 0; dwPos < m_dwListCount; dwPos++)
	{
		m_ppTabList[dwPos]->UpdateDisplay( bShowType );
	}
}
void CMotionPanel64Dlg::CreateTabs(void)
{
	m_dwListCount = 4;
	m_ppTabList[0] = new Axis();
	m_ppTabList[1] = new IO();
	m_ppTabList[2] = new Config();
	m_ppTabList[3] = new Ver();

	CTabCtrl	objTabCtrl;
	objTabCtrl.Attach(GetDlgItem( IDC_TAB_MAIN )->GetSafeHwnd());

	for(DWORD dwPos = 0; dwPos < m_dwListCount; dwPos++)
	{
		m_ppTabList[dwPos]->Create(m_ppTabList[dwPos]->m_DlgID, &objTabCtrl);
		m_ppTabList[dwPos]->ShowWindow( SW_HIDE );

		TC_ITEM	TabCtrlItem = {0};
		TabCtrlItem.pszText = const_cast<LPTSTR>(m_ppTabList[dwPos]->m_szTabName);
		TabCtrlItem.mask = TCIF_TEXT;
		objTabCtrl.InsertItem(dwPos, &TabCtrlItem);
	}
	objTabCtrl.Detach();

	ShowTab(0, SW_SHOW);
}
void CMotionPanel64Dlg::ShowTab(DWORD dwTabNo, int nCmdShow)
{
	if(SW_SHOW == nCmdShow)
	{
		CTabCtrl	objTabCtrl;
		CRect	rectTabClient;

		objTabCtrl.Attach(GetDlgItem( IDC_TAB_MAIN )->GetSafeHwnd());
		objTabCtrl.GetClientRect(&rectTabClient);
		objTabCtrl.AdjustRect(FALSE, &rectTabClient);
		objTabCtrl.Detach();
		m_ppTabList[dwTabNo]->MoveWindow(rectTabClient.left, rectTabClient.top, rectTabClient.Width(), rectTabClient.Height());

		m_ppTabList[dwTabNo]->ShowWindow(SW_SHOW);
		m_ppTabList[dwTabNo]->UpdateWindow();
		m_ppTabList[dwTabNo]->UpdateDisplay();
	}
	else
	{
		m_ppTabList[dwTabNo]->ShowWindow(nCmdShow);
	}
}

void CMotionPanel64Dlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl	objTabCtrl;
	objTabCtrl.Attach(GetDlgItem(IDC_TAB_MAIN)->GetSafeHwnd());
	int iCurSel = objTabCtrl.GetCurSel();
	m_nPageID = iCurSel;

	objTabCtrl.Detach();

	if(0 <= iCurSel)
	{
		ShowTab(iCurSel, SW_SHOW);
	}
	*pResult = 0;
}

void CMotionPanel64Dlg::OnTcnSelchangingTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl	objTabCtrl;
	objTabCtrl.Attach(GetDlgItem(IDC_TAB_MAIN)->GetSafeHwnd());
	int iCurSel = objTabCtrl.GetCurSel();
	objTabCtrl.Detach();


	if(0 <= iCurSel)
	{
		ShowTab(iCurSel, SW_HIDE);
	}
	*pResult = 0;
}

void CMotionPanel64Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if( nIDEvent == 100 )
	{
		KillTimer( nIDEvent );
		for( int nAxisNo = 0; nAxisNo < AXIS_PER_CARD;nAxisNo ++ )
		{
			if( m_CardCount > 0 )
			{
				int nAxis = m_CardNoArray[ m_nCurCardIndex ] * AXIS_PER_CARD + nAxisNo;
				p9014_get_current_speed( nAxis , &m_dCurrentVel[ nAxisNo ] );

				unsigned int status;
				p9014_get_motion_status( nAxis, &status);
				m_bStatues[ nAxisNo ] = status == 1?true:false;

				p9014_get_pos( nAxis, 0, &m_nCMDPos[ nAxisNo ] );

				p9014_get_pos( nAxis, 1, &m_nCurrentPos[ nAxisNo ] );

				p9014_get_io_status( nAxis,&m_pAxisStatus[ nAxisNo ].AS );

				p9014_get_di( m_CardNoArray[ m_nCurCardIndex ],&(m_wordInput.IOW) );
				p9014_get_do(m_CardNoArray[m_nCurCardIndex], &(m_wordOutput.IOW));
			}

		}
		if( m_nPageID == 0 || m_nPageID == 1 )
		{
			UppdateTabs( false );

		}
		SetTimer( 100,100,NULL );
	}
	CTabParentBase::OnTimer(nIDEvent);
}


int CMotionPanel64Dlg::ConfigAxis(int axis)
{
	//TODO: Add your source code here
	int rc = 0;

	rc = p9014_set_pls_outmode(axis,
		m_sAxisParam[axis].output_pulse_mode? 1 : 0);

	rc += p9014_set_pls_iptmode(axis,
		m_sAxisParam[axis].input_pulse_mode? 1 : 0);

	rc += p9014_set_el_level(axis,
		m_sAxisParam[axis].el_level? 1 : 0);

	rc += p9014_home_config(axis,
		(m_sAxisParam[axis].home_mode? 2 : 0), //home_mode,
		(m_sAxisParam[axis].org_level? 1 : 0), //org_level,
		(m_sAxisParam[axis].ez_level? 1 : 0)//ez_level);
		);
	rc += p9014_set_t_profile(axis,
		m_sAxisParam[axis].start_vel,
		m_sAxisParam[axis].max_vel,
		m_sAxisParam[axis].accel,
		m_sAxisParam[axis].decel);
	return rc;
}

int CMotionPanel64Dlg::ConfigReadFromFile(int axis)
{
	wchar_t strAxis[ 20 ];
	memset( strAxis,0,sizeof( wchar_t )*20 );
	swprintf_s( strAxis,20,_T("[AXIS_%d]"),axis%AXIS_PER_CARD );
	m_sAxisParam[axis].output_pulse_mode = ::GetPrivateProfileInt( strAxis,_T("OUTPUT_PULSE_MODE"),0,_T("Config.ini"));
	m_sAxisParam[axis].input_pulse_mode = ::GetPrivateProfileInt( strAxis,_T("INPUT_PULSE_MODE"),0,_T("Config.ini"));
	m_sAxisParam[axis].home_mode = ::GetPrivateProfileInt( strAxis,_T("HOME_MODE"),0,_T("Config.ini"));
	m_sAxisParam[axis].org_level =  ::GetPrivateProfileInt(strAxis, _T("ORG_LEVEL"), 0, _T("Config.ini"));
	m_sAxisParam[axis].el_level = 1;//::GetPrivateProfileInt( strAxis,_T("EL_LEVEL"),0,_T("Config.ini"));
	m_sAxisParam[axis].ez_level = ::GetPrivateProfileInt( strAxis,_T("EZ_LEVEL"),0,_T("Config.ini"));

	m_sAxisParam[axis].vel_profile = ::GetPrivateProfileInt( strAxis,_T("VEL_PROFILE"),0,_T("Config.ini"));

	m_sAxisParam[axis].start_vel = ::GetPrivateProfileInt( strAxis,_T("START_VEL"),1000,_T("Config.ini"));
	m_sAxisParam[axis].max_vel = ::GetPrivateProfileInt( strAxis,_T("MAX_VEL"),10000,_T("Config.ini"));
	m_sAxisParam[axis].accel = ::GetPrivateProfileInt( strAxis,_T("ACCELERATION"),50000,_T("Config.ini"));
	m_sAxisParam[axis].decel = ::GetPrivateProfileInt( strAxis,_T("DECELERATION"),50000,_T("Config.ini"));
	m_sAxisParam[axis].jp = 1;
	return 0;
}

int CMotionPanel64Dlg::ConfigSaveFile(int axis)
{
	wchar_t strAxis[ 20 ];
	memset( strAxis,0,sizeof( wchar_t )*20 );
	swprintf_s( strAxis,20,_T("[AXIS_%d]"),axis%AXIS_PER_CARD );

	WritePrivateProfileInt( strAxis,_T("OUTPUT_PULSE_MODE"),m_sAxisParam[axis].output_pulse_mode,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("INPUT_PULSE_MODE"),m_sAxisParam[axis].input_pulse_mode,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("HOME_MODE"),m_sAxisParam[axis].home_mode,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("ORG_LEVEL"),m_sAxisParam[axis].org_level,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("EL_LEVEL"),m_sAxisParam[axis].el_level,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("EZ_LEVEL"),m_sAxisParam[axis].ez_level,_T("Config.ini"));

	WritePrivateProfileInt( strAxis,_T("VEL_PROFILE"),m_sAxisParam[axis].vel_profile,_T("Config.ini"));

	WritePrivateProfileInt( strAxis,_T("START_VEL"),(int)m_sAxisParam[axis].start_vel,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("MAX_VEL"),(int)m_sAxisParam[axis].max_vel,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("ACCELERATION"),(int)m_sAxisParam[axis].accel,_T("Config.ini"));
	WritePrivateProfileInt( strAxis,_T("DECELERATION"),(int)m_sAxisParam[axis].decel,_T("Config.ini"));
	//m_sAxisParam[axis].jp = 1;
	return 0;
}
int CMotionPanel64Dlg::WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue, LPCTSTR lpFileName)
{
	int nRt = 0;
	int nErr = 0;
	CString str;

	str.Format(_T("%d"),nValue);
	nRt = ::WritePrivateProfileString(lpAppName, lpKeyName, str, lpFileName); 
	if( nRt == 0 )
	{
		nErr = GetLastError();
	}

	return nRt;
}
