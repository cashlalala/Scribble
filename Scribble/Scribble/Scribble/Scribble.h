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
};

extern CScribbleApp theApp;