
// Lab3-BitmapeView.h : interface of the CLab3BitmapeView class
//

#pragma once
#define toRad 0.01745329;
#include <math.h>
class CLab3BitmapeView : public CView
{
protected: // create from serialization only
	CLab3BitmapeView();
	DECLARE_DYNCREATE(CLab3BitmapeView)

// Attributes
public:
	CLab3BitmapeDoc* GetDocument() const;
	double ugao1 = -90.0;
	double ugao2 = 90.0;
	double ugao3 = -95.0;
	CImage osnova;
	CImage ruka1;
	CImage ruka2;
	CImage saka;



// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab3BitmapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in Lab3-BitmapeView.cpp
inline CLab3BitmapeDoc* CLab3BitmapeView::GetDocument() const
   { return reinterpret_cast<CLab3BitmapeDoc*>(m_pDocument); }
#endif

