
// camera_controlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "camera_control.h"
#include "camera_controlDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccamera_controlDlg 对话框




Ccamera_controlDlg::Ccamera_controlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccamera_controlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iProto = 0;
	m_iAddr = 1;
	m_iCom = 7;
	m_iBaut = 0;
	m_iPanSpeed = 40;
	m_iTiltSpeed = 40;
}

void Ccamera_controlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOPROTOCOL, m_CBProtocl);
	DDX_Control(pDX, IDC_COMBOCOM, m_CBCom);
	DDX_Control(pDX, IDC_COMBOBAUD, m_CBBaud);
}

BEGIN_MESSAGE_MAP(Ccamera_controlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNPRESET0, &Ccamera_controlDlg::OnBnClickedBtnpreset0)
	ON_BN_CLICKED(IDC_BTNPRESET1, &Ccamera_controlDlg::OnBnClickedBtnpreset1)
	ON_BN_CLICKED(IDC_BTNPRESET2, &Ccamera_controlDlg::OnBnClickedBtnpreset2)
	ON_BN_CLICKED(IDC_BTNPRESET3, &Ccamera_controlDlg::OnBnClickedBtnpreset3)
	ON_BN_CLICKED(IDC_BTNPRESET4, &Ccamera_controlDlg::OnBnClickedBtnpreset4)
	ON_BN_CLICKED(IDC_BTNPRESET5, &Ccamera_controlDlg::OnBnClickedBtnpreset5)
	ON_BN_CLICKED(IDC_BTNPRESET6, &Ccamera_controlDlg::OnBnClickedBtnpreset6)
	ON_BN_CLICKED(IDC_BTNPRESET7, &Ccamera_controlDlg::OnBnClickedBtnpreset7)
	ON_BN_CLICKED(IDC_BTNPRESET8, &Ccamera_controlDlg::OnBnClickedBtnpreset8)
	ON_BN_CLICKED(IDC_BTNPRESET9, &Ccamera_controlDlg::OnBnClickedBtnpreset9)
	ON_BN_CLICKED(IDC_BTNPRESET10, &Ccamera_controlDlg::OnBnClickedBtnpreset10)
	ON_BN_CLICKED(IDC_BTNPRESET11, &Ccamera_controlDlg::OnBnClickedBtnpreset11)
	ON_BN_CLICKED(IDC_BTNPRESET12, &Ccamera_controlDlg::OnBnClickedBtnpreset12)
	ON_BN_CLICKED(IDC_BTNPRESET13, &Ccamera_controlDlg::OnBnClickedBtnpreset13)
	ON_BN_CLICKED(IDC_BTNPRESET14, &Ccamera_controlDlg::OnBnClickedBtnpreset14)
	ON_BN_CLICKED(IDC_BTNPRESET15, &Ccamera_controlDlg::OnBnClickedBtnpreset15)
	ON_BN_CLICKED(IDC_BTNPRESET16, &Ccamera_controlDlg::OnBnClickedBtnpreset16)
	ON_BN_CLICKED(IDC_BTNPRESET17, &Ccamera_controlDlg::OnBnClickedBtnpreset17)
	ON_BN_CLICKED(IDC_BTNPRESET18, &Ccamera_controlDlg::OnBnClickedBtnpreset18)
	ON_BN_CLICKED(IDC_BTNPRESET19, &Ccamera_controlDlg::OnBnClickedBtnpreset19)
	ON_BN_CLICKED(IDC_BTNPRESET20, &Ccamera_controlDlg::OnBnClickedBtnpreset20)
	ON_BN_CLICKED(IDC_BTNPRESET21, &Ccamera_controlDlg::OnBnClickedBtnpreset21)
	ON_BN_CLICKED(IDC_BTNPRESET22, &Ccamera_controlDlg::OnBnClickedBtnpreset22)
	ON_BN_CLICKED(IDC_BTNPRESET23, &Ccamera_controlDlg::OnBnClickedBtnpreset23)
	ON_BN_CLICKED(IDC_BTNPRESET24, &Ccamera_controlDlg::OnBnClickedBtnpreset24)
	ON_EN_CHANGE(IDC_EDITPRESET, &Ccamera_controlDlg::OnEnChangeEditpreset)
	ON_BN_CLICKED(IDC_BTNSETPRESET, &Ccamera_controlDlg::OnBnClickedBtnsetpreset)
	ON_BN_CLICKED(IDC_BTNGOTOPRESET, &Ccamera_controlDlg::OnBnClickedBtngotopreset)
	ON_BN_CLICKED(IDC_BTNCLEARPRESET, &Ccamera_controlDlg::OnBnClickedBtnclearpreset)
	ON_EN_CHANGE(IDC_EDITPANSPEED, &Ccamera_controlDlg::OnEnChangeEditpanspeed)
	ON_EN_CHANGE(IDC_EDITTILTSPEED, &Ccamera_controlDlg::OnEnChangeEdittiltspeed)
	ON_EN_CHANGE(IDC_EDITADDRESS, &Ccamera_controlDlg::OnEnChangeEditaddress)
	ON_CBN_SELCHANGE(IDC_COMBOPROTOCOL, &Ccamera_controlDlg::OnCbnSelchangeComboprotocol)
	ON_CBN_SELCHANGE(IDC_COMBOCOM, &Ccamera_controlDlg::OnCbnSelchangeCombocom)
	ON_CBN_SELCHANGE(IDC_COMBOBAUD, &Ccamera_controlDlg::OnCbnSelchangeCombobaud)
END_MESSAGE_MAP()


// Ccamera_controlDlg 消息处理程序

BOOL Ccamera_controlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	fstream fConfig;
	fConfig.open("CamConfig.sys");
	if(!fConfig)
	{
		fConfig.open("CamConfig.sys", ofstream::out);
		fConfig<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
		fConfig.close();
	}
	fConfig.close();
	fConfig.open("CamConfig.sys");
	string temp;
	if(getline(fConfig, temp))
	{
		m_iProto = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	if(getline(fConfig,temp))
	{
		m_iAddr = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	if(getline(fConfig,temp))
	{
		m_iCom = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	if(getline(fConfig, temp))
	{
		m_iBaut = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	if(getline(fConfig,temp))
	{
		m_iPanSpeed = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	if(getline(fConfig, temp))
	{
		m_iTiltSpeed = atoi(temp.c_str());
	}
	else
	{
		AfxMessageBox(TEXT("摄像头配置文件读取失败！"));
	}
	fConfig.close();

	CString strTemp;
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("1"));
	strTemp.Format(TEXT("%d"), m_iPanSpeed);
	GetDlgItem(IDC_EDITPANSPEED)->SetWindowText(strTemp);
	strTemp.Format(TEXT("%d"), m_iTiltSpeed);
	GetDlgItem(IDC_EDITTILTSPEED)->SetWindowText(strTemp);
	strTemp.Format(TEXT("%d"),m_iAddr);
	GetDlgItem(IDC_EDITADDRESS)->SetWindowText(strTemp);

	m_CBProtocl.AddString(TEXT("Pelco-D"));
	m_CBProtocl.SetCurSel(m_iProto);

	m_CBCom.AddString(TEXT("Com1"));
	m_CBCom.AddString(TEXT("Com2"));
	m_CBCom.AddString(TEXT("Com3"));
	m_CBCom.AddString(TEXT("Com4"));
	m_CBCom.AddString(TEXT("Com5"));
	m_CBCom.AddString(TEXT("Com6"));
	m_CBCom.AddString(TEXT("Com7"));
	m_CBCom.AddString(TEXT("Com8"));
	for(int i = 0; i < 4; i++)
	{
		m_CBCom.SetItemData(i, i+1);
	}
	m_CBCom.SetCurSel(m_iCom);

	m_CBBaud.AddString(TEXT("2400"));
	m_CBBaud.AddString(TEXT("4800"));
	m_CBBaud.AddString(TEXT("9600"));
	m_CBBaud.SetItemData(0, 2400);
	m_CBBaud.SetItemData(1, 4800);
	m_CBBaud.SetItemData(2, 9600);
	m_CBBaud.SetCurSel(m_iBaut);
	m_CamCtrl.SetAllInstructionsOfPELCOD();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Ccamera_controlDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ccamera_controlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL Ccamera_controlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BTNLEFT)->m_hWnd)
		{
			m_CamCtrl.PanSpeed(GetDlgItemInt(IDC_EDITPANSPEED));
			m_CamCtrl.PanLeft();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNRIGHT)->m_hWnd)
		{
			m_CamCtrl.PanSpeed(GetDlgItemInt(IDC_EDITPANSPEED));
			m_CamCtrl.PanRight();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNUP)->m_hWnd)
		{
			m_CamCtrl.TiltSpeed(GetDlgItemInt(IDC_EDITTILTSPEED));
			m_CamCtrl.TiltUp();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNDOWN)->m_hWnd)
		{
			m_CamCtrl.TiltSpeed(GetDlgItemInt(IDC_EDITTILTSPEED));
			m_CamCtrl.TiltDown();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNOPENIRIS)->m_hWnd)
		{
			m_CamCtrl.OpenIris();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNCLOSEIRIS)->m_hWnd)
		{
			m_CamCtrl.CloseIris();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNFOCUSFAR)->m_hWnd)
		{
			m_CamCtrl.FocusFar();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNFOCUSNEAR)->m_hWnd)
		{
			m_CamCtrl.FocusNear();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNZOOMWIDE)->m_hWnd)
		{
			m_CamCtrl.ZoomWide();
		}
		if (pMsg->hwnd == GetDlgItem(IDC_BTNZOOMTELE)->m_hWnd)
		{
			m_CamCtrl.ZoomTele();
		}
	}

	if (pMsg->message==WM_LBUTTONUP)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BTNLEFT)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNRIGHT)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNUP)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNDOWN)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNOPENIRIS)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNCLOSEIRIS)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNFOCUSFAR)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNFOCUSNEAR)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNZOOMWIDE)->m_hWnd ||
			pMsg->hwnd == GetDlgItem(IDC_BTNZOOMTELE)->m_hWnd)
		{
			m_CamCtrl.StopMov();
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void Ccamera_controlDlg::OnBnClickedBtnpreset0()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("127"));
	m_CamCtrl.GotoPreset(127);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("1"));
	m_CamCtrl.GotoPreset(1);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("2"));
	m_CamCtrl.GotoPreset(2);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset3()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("3"));
	m_CamCtrl.GotoPreset(3);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset4()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("4"));
	m_CamCtrl.GotoPreset(4);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset5()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("5"));
	m_CamCtrl.GotoPreset(5);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset6()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("6"));
	m_CamCtrl.GotoPreset(6);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset7()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("7"));
	m_CamCtrl.GotoPreset(7);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset8()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("8"));
	m_CamCtrl.GotoPreset(8);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset9()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("9"));
	m_CamCtrl.GotoPreset(9);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset10()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("10"));
	m_CamCtrl.GotoPreset(10);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset11()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("11"));
	m_CamCtrl.GotoPreset(11);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset12()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("12"));
	m_CamCtrl.GotoPreset(12);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset13()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("13"));
	m_CamCtrl.GotoPreset(13);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset14()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("14"));
	m_CamCtrl.GotoPreset(14);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset15()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("15"));
	m_CamCtrl.GotoPreset(15);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset16()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("16"));
	m_CamCtrl.GotoPreset(16);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset17()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("17"));
	m_CamCtrl.GotoPreset(17);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset18()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("18"));
	m_CamCtrl.GotoPreset(18);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset19()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("19"));
	m_CamCtrl.GotoPreset(19);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset20()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("20"));
	m_CamCtrl.GotoPreset(20);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset21()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("21"));
	m_CamCtrl.GotoPreset(21);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset22()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("22"));
	m_CamCtrl.GotoPreset(22);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset23()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("23"));
	m_CamCtrl.GotoPreset(23);
}


void Ccamera_controlDlg::OnBnClickedBtnpreset24()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("24"));
	m_CamCtrl.GotoPreset(24);
}


void Ccamera_controlDlg::OnEnChangeEditpreset()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(GetDlgItemInt(IDC_EDITPRESET) > 127)
	{
		GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("127"));
	}
	if(GetDlgItemInt(IDC_EDITPRESET) < 1)
	{
		GetDlgItem(IDC_EDITPRESET)->SetWindowText(TEXT("1"));
	}
}


void Ccamera_controlDlg::OnBnClickedBtnsetpreset()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT iPreset = GetDlgItemInt(IDC_EDITPRESET);
	if(iPreset < 128)
	{
		m_CamCtrl.SetPreset(iPreset);
	}
}


void Ccamera_controlDlg::OnBnClickedBtngotopreset()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT iPreset = GetDlgItemInt(IDC_EDITPRESET);
	if(iPreset < 128)
	{
		m_CamCtrl.GotoPreset(iPreset);
	}
}


void Ccamera_controlDlg::OnBnClickedBtnclearpreset()
{
	// TODO: 在此添加控件通知处理程序代码
	UINT iPreset = GetDlgItemInt(IDC_EDITPRESET);
	if(iPreset < 128)
	{
		m_CamCtrl.ClearPreset(iPreset);
	}
}


void Ccamera_controlDlg::OnEnChangeEditpanspeed()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(GetDlgItemInt(IDC_EDITPANSPEED) > 63)
	{
		GetDlgItem(IDC_EDITPANSPEED)->SetWindowText(TEXT("63"));
	}
	m_iPanSpeed = GetDlgItemInt(IDC_EDITPANSPEED);
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}


void Ccamera_controlDlg::OnEnChangeEdittiltspeed()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(GetDlgItemInt(IDC_EDITTILTSPEED) > 63)
	{
		GetDlgItem(IDC_EDITTILTSPEED)->SetWindowText(TEXT("63"));
	}
	m_iTiltSpeed = GetDlgItemInt(IDC_EDITTILTSPEED);
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}


void Ccamera_controlDlg::OnEnChangeEditaddress()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(GetDlgItemInt(IDC_EDITADDRESS) > 255)
	{
		GetDlgItem(IDC_EDITADDRESS)->SetWindowText(TEXT("255"));
	}
	m_iAddr = GetDlgItemInt(IDC_EDITADDRESS);
	m_CamCtrl.SetAddrOfInstruction(m_iAddr);
	m_CamCtrl.StopMov();
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}


void Ccamera_controlDlg::OnCbnSelchangeComboprotocol()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iProto = m_CBProtocl.GetCurSel();
	m_CamCtrl.SetComProtocol(m_iProto);
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}


void Ccamera_controlDlg::OnCbnSelchangeCombocom()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_CamCtrl.GetComState())
	{
		m_CamCtrl.CloseCam();
	}
	m_iCom = m_CBCom.GetCurSel();
	m_CamCtrl.OpenCam(m_CBCom.GetItemData(m_iCom),
		m_CBBaud.GetItemData(m_iBaut));
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}


void Ccamera_controlDlg::OnCbnSelchangeCombobaud()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_CamCtrl.GetComState())
	{
		m_CamCtrl.CloseCam();
	}
	m_iBaut = m_CBBaud.GetCurSel();
	m_CamCtrl.OpenCam(m_CBCom.GetItemData(m_iCom),
		m_CBBaud.GetItemData(m_iBaut));
	ofstream of("CamConfig.sys");
	of<<m_iProto<<endl<<m_iAddr<<endl<<m_iCom<<endl<<m_iBaut<<endl<<m_iPanSpeed<<endl<<m_iTiltSpeed;
	of.close();
}
