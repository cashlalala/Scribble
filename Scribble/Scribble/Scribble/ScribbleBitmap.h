#pragma once
#include "afxwin.h"

class CScribbleBitmap :
	public CBitmap
{
protected: // 僅從序列化建立	
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
