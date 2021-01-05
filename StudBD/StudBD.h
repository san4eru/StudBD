
// StudBD.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CStudBDApp:
// Сведения о реализации этого класса: StudBD.cpp
//

class CStudBDApp : public CWinApp
{
public:
	CStudBDApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CStudBDApp theApp;
