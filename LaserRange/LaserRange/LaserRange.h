
// LaserRange.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLaserRangeApp: 
// �йش����ʵ�֣������ LaserRange.cpp
//

class CLaserRangeApp : public CWinApp
{
public:
	CLaserRangeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLaserRangeApp theApp;