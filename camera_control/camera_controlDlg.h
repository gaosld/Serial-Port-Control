
// camera_controlDlg.h : 头文件
//

#pragma once

#include "CamCtrlInterface.h"
#define LEFTTIMERID	1
#define RIGHTTIMERID	2
#define UPTIMERID	3
#define DOWNTIMERID	4

// Ccamera_controlDlg 对话框
class Ccamera_controlDlg : public CDialogEx
{
// 构造
public:
	Ccamera_controlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CAMERA_CONTROL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CamCtrlInterface m_CamCtrl;
	BYTE m_iPreset;
	int m_iPanSpeed;
	int m_iTiltSpeed;
	CComboBox m_CBProtocl;
	CComboBox m_CBCom;
	CComboBox m_CBBaud;
	int m_iProto;
	int m_iAddr;
	int m_iCom;
	int m_iBaut;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnpreset0();
	afx_msg void OnBnClickedBtnpreset1();
	afx_msg void OnBnClickedBtnpreset2();
	afx_msg void OnBnClickedBtnpreset3();
	afx_msg void OnBnClickedBtnpreset4();
	afx_msg void OnBnClickedBtnpreset5();
	afx_msg void OnBnClickedBtnpreset6();
	afx_msg void OnBnClickedBtnpreset7();
	afx_msg void OnBnClickedBtnpreset8();
	afx_msg void OnBnClickedBtnpreset9();
	afx_msg void OnBnClickedBtnpreset10();
	afx_msg void OnBnClickedBtnpreset11();
	afx_msg void OnBnClickedBtnpreset12();
	afx_msg void OnBnClickedBtnpreset13();
	afx_msg void OnBnClickedBtnpreset14();
	afx_msg void OnBnClickedBtnpreset15();
	afx_msg void OnBnClickedBtnpreset16();
	afx_msg void OnBnClickedBtnpreset17();
	afx_msg void OnBnClickedBtnpreset18();
	afx_msg void OnBnClickedBtnpreset19();
	afx_msg void OnBnClickedBtnpreset20();
	afx_msg void OnBnClickedBtnpreset21();
	afx_msg void OnBnClickedBtnpreset22();
	afx_msg void OnBnClickedBtnpreset23();
	afx_msg void OnBnClickedBtnpreset24();
	afx_msg void OnEnChangeEditpreset();
	afx_msg void OnBnClickedBtnsetpreset();
	afx_msg void OnBnClickedBtngotopreset();
	afx_msg void OnBnClickedBtnclearpreset();
	afx_msg void OnEnChangeEditpanspeed();
	afx_msg void OnEnChangeEdittiltspeed();
	afx_msg void OnEnChangeEditaddress();
	afx_msg void OnCbnSelchangeComboprotocol();
	afx_msg void OnCbnSelchangeCombocom();
	afx_msg void OnCbnSelchangeCombobaud();
};
