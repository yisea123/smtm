// GuiDemo1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GuiDemo1.h"
#include "GuiDemo1Dlg.h"
#include "pci9014.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiDemo1Dlg dialog

CGuiDemo1Dlg::CGuiDemo1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuiDemo1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuiDemo1Dlg)
	m_Type = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGuiDemo1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuiDemo1Dlg)
	DDX_Control(pDX, IDC_COMBO_AXIS, m_ctlAxisSel);
	DDX_Radio(pDX, IDC_RADIO1, m_Type);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGuiDemo1Dlg, CDialog)
	//{{AFX_MSG_MAP(CGuiDemo1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_EMG_STOP, OnButtonEmgStop)
	ON_BN_CLICKED(IDC_BUTTON_SD_STOP, OnButtonSdStop)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_CBN_EDITCHANGE(IDC_COMBO_AXIS, OnEditchangeComboAxis)
	ON_CBN_SELCHANGE(IDC_COMBO_AXIS, OnSelchangeComboAxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuiDemo1Dlg message handlers

BOOL CGuiDemo1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int board_count = 0, board_id[16];
	int rc = 0, axis ;
	CString str;

	SetTimer(1, 50, NULL);
	rc = p9014_initial(&board_count, board_id);
	if(0 != rc)
	{
		AfxMessageBox("Initialize PCI-9014 fail");
		OnOK();
	}

	if(board_count < 1)
	{
		AfxMessageBox("Find No PCI-9014 device");
		OnOK();
	}
	else
	{
		for(int i = 0; i < board_count; i ++)
		{
			for(int j = 0; j <4 ; j++)
			{
				axis = board_id[i] * 4 + j;
				str.Format("%d", axis);
				m_ctlAxisSel.AddString((LPCSTR)str);

				//设置位置计数器默认值
				p9014_set_pos(axis, 0, 0);
				p9014_set_pos(axis, 1, 0);
				
				//设置运动参数
				p9014_set_t_profile(axis, 1000, 10000, 50000, 50000);
			}
		}
		m_ctlAxisSel.SetCurSel(0);
		
	}
	
	GetDlgItem(IDC_EDIT1)->SetWindowText("1000");
	GetDlgItem(IDC_EDIT2)->SetWindowText("10000");
	GetDlgItem(IDC_EDIT3)->SetWindowText("50000");
	GetDlgItem(IDC_EDIT4)->SetWindowText("50000");

	GetDlgItem(IDC_EDIT11)->SetWindowText("10000");	//distance
	
	m_axis = board_id[0]*4 + 0;	//设置默认的卡号
	m_Type = 0;		//设置默认值为点位运动

	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGuiDemo1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGuiDemo1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGuiDemo1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGuiDemo1Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	//release resource
	p9014_close();

	CDialog::OnClose();
}

//
//	定时器回调函数，用于查询运动卡中控制轴的位置、状态等信息
//
void CGuiDemo1Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	unsigned int motion_status = 0, io_status = 0;
	int cmd_pos = 0, enc_pos = 0;
	double cur_vel = 0.0f;
	CString str;

	if(1 == nIDEvent)
	{
		p9014_get_motion_status(m_axis, &motion_status);
		p9014_get_current_speed(m_axis, &cur_vel);
		p9014_get_pos(m_axis, 0, &cmd_pos);
		p9014_get_pos(m_axis, 1, &enc_pos);
		p9014_get_io_status(m_axis, &io_status);

		str.Format("%d", motion_status);
		GetDlgItem(IDC_EDIT6)->SetWindowText(str);

		str.Format("%.1f", cur_vel);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);

		str.Format("%d", cmd_pos);
		GetDlgItem(IDC_EDIT7)->SetWindowText(str);

		str.Format("%d", enc_pos);
		GetDlgItem(IDC_EDIT8)->SetWindowText(str);
		
		//PEL
		if(io_status & 0x1)
		{
			GetDlgItem(IDC_EDIT9)->SetWindowText("ON");
		}
		else
		{
			GetDlgItem(IDC_EDIT9)->SetWindowText("OFF");
		}
		
		//mel
		if(io_status & 0x2)
		{
			GetDlgItem(IDC_EDIT10)->SetWindowText("ON");
		}
		else
		{
			GetDlgItem(IDC_EDIT10)->SetWindowText("OFF");
		}

		//EMG
		if(io_status & 0x10)
		{
			GetDlgItem(IDC_EDIT12)->SetWindowText("1");
		}
		else
		{
			GetDlgItem(IDC_EDIT12)->SetWindowText("0");
		}
	}
	CDialog::OnTimer(nIDEvent);
}

//立即停止，没有减速过程
void CGuiDemo1Dlg::OnButtonEmgStop() 
{
	// TODO: Add your control notification handler code here
	int rc = 0;
	CString str;

	rc = p9014_stop(m_axis, 1);
	if(rc)
	{
		str.Format("Stop axis fail, return code: %d", rc);
		AfxMessageBox(str);
	}
	
}

//减速停止，有减速过程
void CGuiDemo1Dlg::OnButtonSdStop() 
{
	// TODO: Add your control notification handler code here
	int rc = 0;
	CString str;

	rc = p9014_stop(m_axis, 0);
	if(rc)
	{
		str.Format("Stop axis fail, return code: %d", rc);
		AfxMessageBox(str);
	}
}

//运行指令
void CGuiDemo1Dlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	CString str;
	double  start_vel, max_vel, acc, dec;
	int dist;
	int rc = 0;

	UpdateData(TRUE);

	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	start_vel = atof((LPCSTR) str);

	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	max_vel = atof((LPCSTR) str);

	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	acc  = atof((LPCSTR) str);

	GetDlgItem(IDC_EDIT4)->GetWindowText(str);
	dec  = atof((LPCSTR) str);

	GetDlgItem(IDC_EDIT11)->GetWindowText(str);	//distance
	dist  = atoi((LPCSTR) str);
	
	//设置运动参数
	p9014_set_t_profile(m_axis, start_vel, max_vel, acc, dec);

	switch(m_Type)
	{
	case 0:		//点位运动, 相对坐标，带加速、减速
		{
			rc = p9014_pmove(m_axis, dist, 0, 2);	//incremental  coordinate, with acc/dec
		}
		break;


	case 1:	//正向连续驱动(速度模式)
		{
			rc = p9014_vmove(m_axis, 1, 2);		//velecity mode driving, CW
		}

		break;

	case 2:	//反向连续驱动(速度模式)
		{
			rc = p9014_vmove(m_axis, 0, 2);		//velecity mode driving, CCW
		}
		break;

	default:
		{
		}
		break;
	}
	
	if(rc)
	{
		str.Format("Drive axis fail, return code: %d", rc);
		AfxMessageBox(str);
	}
}

void CGuiDemo1Dlg::OnEditchangeComboAxis() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int sel ;
	sel = m_ctlAxisSel.GetCurSel();
	if( sel >= 0)
	{
		m_ctlAxisSel.GetLBText(sel, str);
	}
	else
	{
		m_ctlAxisSel.SetCurSel(0);
		m_ctlAxisSel.GetLBText(0, str);
	}

	m_axis = atoi((LPCSTR)str);	
}

void CGuiDemo1Dlg::OnSelchangeComboAxis() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int sel ;
	sel = m_ctlAxisSel.GetCurSel();
	if( sel >= 0)
	{
		m_ctlAxisSel.GetLBText(sel, str);
	}
	else
	{
		m_ctlAxisSel.SetCurSel(0);
		m_ctlAxisSel.GetLBText(0, str);
	}

	m_axis = atoi((LPCSTR)str);		
}
