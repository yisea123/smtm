// MotionPanel64Dlg.h : 头文件
//

#pragma once

#include "CTabParentBase.h"
#include "TabChildBase.h"

typedef struct __AXIS_PARAM_T{
	int output_pulse_mode;
	int	input_pulse_mode;
	int	home_mode;
	int	org_level;
	int	ez_level;
	int el_level;

	int vel_profile;
	int vel_mode;
	double start_vel;
	double max_vel;
	double accel;
	double decel;
	double jp;
}AXIS_PARAM_T;


typedef struct _IOBit_tag
{
	unsigned short _bit0:1;
	unsigned short _bit1:1;
	unsigned short _bit2:1;
	unsigned short _bit3:1;
	unsigned short _bit4:1;
	unsigned short _bit5:1;
	unsigned short _bit6:1;
	unsigned short _bit7:1;
	unsigned short _bit8:1;
	unsigned short _bit9:1;
	unsigned short _bit10:1;
	unsigned short _bit11:1;
	unsigned short _bit12:1;
	unsigned short _bit13:1;
	unsigned short _bit14:1;
	unsigned short _bit15:1;
	unsigned short _bit16:16;
}IOBit;

typedef union _IOWORD_tag
{
	IOBit IOBIT;
	unsigned int IOW;
}IOWORD;

typedef struct HardAxisStatusBit_tag
{
	unsigned short _pel:1;
	unsigned short _mel:1;
	unsigned short _org:1;
	unsigned short _ez:1;
	unsigned short _emg:1;
	unsigned short _reserv0;
	unsigned int _reserv1:26;
}HardAxisStatusBit;

typedef union _AxisStatus_tag {
	HardAxisStatusBit ASBIT;
	unsigned int AS;
}HardAxisStatus;

enum{ OFF = 0,ON };
// CMotionPanel64Dlg 对话框
class CMotionPanel64Dlg : public CTabParentBase
{
private:
	int m_nPageID;
	int m_nlanguage;
	int m_nConfigAxisNo;
	int m_nCurCardIndex;
	// 构造
public:
	CMotionPanel64Dlg(CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
	enum { IDD = IDD_MOTIONPANEL64_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void CreateTabs(void);
	void ShowTab(DWORD dwTabNo, int nCmdShow);	

	BOOL DisplaySlider(HWND hWnd);
	BOOL DisplayStatic(HWND hWnd);
	BOOL DisplayEdit(HWND hWnd,bool bShowType = true );
	BOOL DisplayCombo(HWND hWnd);
	BOOL DisplayButton(HWND hWnd);

	BOOL UpdateByEdit(HWND hWnd);
	BOOL UpdateBySlider(HWND hWnd);
	BOOL UpdateByCombo(HWND hWnd);
	BOOL UpdateByButton(HWND hWnd);
	void UppdateTabs( bool bShowType = true );

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangingTabMain(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	enum {AXIS_MAX = 64};
	enum { AXIS_X = 0,AXIS_Y,AXIS_Z,AXIS_U,AXIS_PER_CARD };
private:
	AXIS_PARAM_T  m_sAxisParam[AXIS_MAX];
	int m_CardNoArray[16];
	int m_CardCount;
	int ConfigReadFromFile(int axis);
	int ConfigSaveFile(int axis);
	int ConfigAxis(int axis);

	double m_dCurrentVel[ AXIS_PER_CARD ];
	int m_nDestPos[ AXIS_PER_CARD ];
	int m_nCMDPos[ AXIS_PER_CARD ];
	int m_nCurrentPos[ AXIS_PER_CARD ];
	IOWORD m_wordInput;
	IOWORD m_wordOutput;
	HardAxisStatus m_pAxisStatus[AXIS_PER_CARD];
	bool m_bStatues[ AXIS_PER_CARD ];
	bool m_bToSetCMD[ AXIS_PER_CARD ];
	int m_nCMDType;
	int m_nVelModel;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int WritePrivateProfileInt(LPCTSTR lpAppName, LPCTSTR lpKeyName, INT nValue, LPCTSTR lpFileName);

};
