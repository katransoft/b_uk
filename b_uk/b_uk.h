
// b_uk.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// Cb_ukApp:
// О реализации данного класса см. b_uk.cpp
//

class Cb_ukApp : public CWinApp
{
public:
	Cb_ukApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern Cb_ukApp theApp;