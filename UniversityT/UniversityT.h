
// UniversityT.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CUniApp:
// О реализации данного класса см. UniversityT.cpp
//

class CUniApp : public CWinApp
{
public:
	CUniApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CUniApp theApp;