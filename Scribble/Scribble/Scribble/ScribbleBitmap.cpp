#include "StdAfx.h"
#include "ScribbleBitmap.h"

IMPLEMENT_SERIAL(CScribbleBitmap, CBitmap, 2)


CScribbleBitmap::CScribbleBitmap(void)
: m_szFilePath(_T(""))
{
}

CScribbleBitmap::~CScribbleBitmap(void)
{
}

void CScribbleBitmap::Serialize(CArchive& ar)
{
	BITMAP bmp;

	if (ar.IsStoring())
	{	// storing code
		//bitmap serialize
		GetBitmap(&bmp);
		ar << bmp.bmType;
		ar << bmp.bmWidth;
		ar << bmp.bmHeight;
		ar << bmp.bmWidthBytes;
		ar << bmp.bmPlanes;
		ar << bmp.bmBitsPixel;

		BYTE* bits = (BYTE*)bmp.bmBits;
		for (int i = 0; i < bmp.bmHeight; ++i) {
			for (int j = 0; j < bmp.bmWidthBytes; ++j) {
				ar << *bits;
				bits++;
			}
		}
	}
	else
	{	// loading code

		//bitmap deserialize
		ar >> bmp.bmType;
		ar >> bmp.bmWidth;
		ar >> bmp.bmHeight;
		ar >> bmp.bmWidthBytes;
		ar >> bmp.bmPlanes;
		ar >> bmp.bmBitsPixel;
		
		bmp.bmBits = malloc(bmp.bmHeight * bmp.bmWidthBytes);
		BYTE* bits = (BYTE*)bmp.bmBits;
		for (int i = 0; i < bmp.bmHeight; ++i) {
			for (int j = 0; j < bmp.bmWidthBytes; ++j) {
				ar >> *bits;
				bits++;
			}
		}

		if (CreateBitmap(bmp.bmWidth,bmp.bmHeight,bmp.bmPlanes,bmp.bmBitsPixel,bmp.bmBits))
		{
			if (SetBitmapBits(bmp.bmHeight * bmp.bmWidthBytes, (const void*)bits))
				TRACE("pass");
			SetBitmapDimension(bmp.bmWidth, bmp.bmHeight);
		}

	}
}

int CScribbleBitmap::GetWidthPixel(void)
{
	BITMAP tmpBmp;
	this->GetBitmap(&tmpBmp);
	return tmpBmp.bmWidth;
}

int CScribbleBitmap::GetHeightPixel(void)
{
	BITMAP tmpBmp;
	this->GetBitmap(&tmpBmp);
	return tmpBmp.bmHeight;
}

void CScribbleBitmap::LoadBitMapFromFile(CString szFilePath)
{
	m_szFilePath = (!szFilePath.IsEmpty())?		szFilePath:
				   (!m_szFilePath.IsEmpty())?	m_szFilePath:
					NULL;
	if (m_szFilePath.IsEmpty())
		return;
	
	Detach();
	HBITMAP hBmp = (HBITMAP)::LoadImage(NULL,m_szFilePath,
										IMAGE_BITMAP,0,0,
										LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	Attach(hBmp);
}
