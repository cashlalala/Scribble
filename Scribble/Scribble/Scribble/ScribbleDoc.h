// ScribbleDoc.h : CScribbleDoc ���O������
//


#pragma once


class CScribbleDoc : public CDocument
{
protected: // �ȱq�ǦC�ƫإ�
	CScribbleDoc();
	DECLARE_DYNCREATE(CScribbleDoc)

// �ݩ�
public:

// �@�~
public:

// �мg
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// �{���X��@
public:
	virtual ~CScribbleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
};


