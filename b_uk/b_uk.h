
// b_uk.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// Cb_ukApp:
// � ���������� ������� ������ ��. b_uk.cpp
//

class Cb_ukApp : public CWinApp
{
public:
	Cb_ukApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern Cb_ukApp theApp;