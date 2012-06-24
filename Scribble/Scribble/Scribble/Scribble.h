// Scribble.h : Scribble 應用程式的主標頭檔
//
#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"       // 主要符號


// CScribbleApp:
// 請參閱實作此類別的 Scribble.cpp
//

class CScribbleApp : public CWinApp
{
public:
	CScribbleApp();


// 覆寫
public:
	virtual BOOL InitInstance();

// 程式碼實作
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	LPCTSTR const m_pszUserSettingSection;
	LPCTSTR const m_pszThickPenWidth;
	LPCTSTR const m_pszThinPenWidth;
	LPCTSTR const m_pszRestrictCanvasWidth;
	LPCTSTR const m_pszRestrictCanvasHeight;
	LPCTSTR const m_pszCanvasBkgColor;
};

extern CScribbleApp theApp;