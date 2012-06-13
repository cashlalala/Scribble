// ScribbleDoc.cpp : CScribbleDoc 類別的實作
//

#include "stdafx.h"
#include "Scribble.h"

#include "ScribbleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScribbleDoc

IMPLEMENT_DYNCREATE(CScribbleDoc, CDocument)

BEGIN_MESSAGE_MAP(CScribbleDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CScribbleDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CScribbleDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CScribbleDoc 建構/解構

CScribbleDoc::CScribbleDoc()
: m_nPenWidth(0)
{
	// TODO: 在此加入一次建構程式碼

}

CScribbleDoc::~CScribbleDoc()
{
}

BOOL CScribbleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	InitDocument();
	return TRUE;
}




BOOL CScribbleDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	InitDocument();
	return TRUE;
}

// Called on File/Close

void CScribbleDoc::DeleteContents()
{
	while( !m_strokeList.IsEmpty( ) )
	{
		delete m_strokeList.RemoveHead( );
	}

	CDocument::DeleteContents();
}

// CScribbleDoc 序列化

void CScribbleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此加入儲存程式碼
	}
	else
	{
		// TODO: 在此加入載入程式碼
	}
	m_strokeList.Serialize( ar );
}


CPen* CScribbleDoc::GetCurrentPen()
{
	return &m_penCur;
}


// CScribbleDoc 診斷

#ifdef _DEBUG
void CScribbleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CScribbleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}


#endif //_DEBUG


// CScribbleDoc 命令

void CScribbleDoc::InitDocument(void)
{
	m_nPenWidth = 2;  // Default 2-pixel pen width
	// Solid black pen
	m_penCur.CreatePen( PS_SOLID, m_nPenWidth, RGB(0,0,0) );
}

CStroke* CScribbleDoc::NewStroke(void)
{
	CStroke* pStrokeItem = new CStroke(m_nPenWidth);
	m_strokeList.AddTail( pStrokeItem );
	SetModifiedFlag( );    // Mark document as modified
	// to confirm File Close.
	return pStrokeItem;
}
