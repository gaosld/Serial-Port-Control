
// camera_control.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Ccamera_controlApp:
// 有关此类的实现，请参阅 camera_control.cpp
//

class Ccamera_controlApp : public CWinApp
{
public:
	Ccamera_controlApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Ccamera_controlApp theApp;