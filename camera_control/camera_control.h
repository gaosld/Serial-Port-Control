
// camera_control.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccamera_controlApp:
// �йش����ʵ�֣������ camera_control.cpp
//

class Ccamera_controlApp : public CWinApp
{
public:
	Ccamera_controlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccamera_controlApp theApp;