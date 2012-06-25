#pragma once
#include "afxwin.h"

class CScribbleBitmap :
	public CBitmap
{
protected: // �ȱq�ǦC�ƫإ�	
	DECLARE_SERIAL(CScribbleBitmap)
public:
	CScribbleBitmap();
	~CScribbleBitmap(void);
	virtual void Serialize(CArchive& ar);
	CString m_szFilePath;
	int GetWidthPixel(void);
	int GetHeightPixel(void);
	void LoadBitMapFromFile(CString szfilePath = NULL);
};
