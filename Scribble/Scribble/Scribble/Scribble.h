// Scribble.h : Scribble ���ε{�����D���Y��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"       // �D�n�Ÿ�


// CScribbleApp:
// �аѾ\��@�����O�� Scribble.cpp
//

class CScribbleApp : public CWinApp
{
public:
	CScribbleApp();


// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@
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