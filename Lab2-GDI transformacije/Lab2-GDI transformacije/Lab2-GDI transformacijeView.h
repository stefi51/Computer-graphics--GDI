
// Lab2-GDI transformacijeView.h : interface of the CLab2GDItransformacijeView class
//

#pragma once
#define   toRad 0.017453292
#define pi 3.14;
#define toStep 57.29;
class CLab2GDItransformacijeView : public CView
{
protected: // create from serialization only
	CLab2GDItransformacijeView() ;
	DECLARE_DYNCREATE(CLab2GDItransformacijeView)

// Attributes
public:
	CLab2GDItransformacijeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void Rotacija(CDC * pDC,double ugao,bool smer, float dx, float dy);
	void Translacija(CDC * pDC, bool smer, float dx, float dy);
	void Refleksija(CDC *pDC, bool smer, bool HV, float dx, float dy);
	void CrtajOktagonRuku(CDC * pDC, float x, float y);
	POINT * VratiOktagon(float x, float y, float m);
	POINT *VratiPopunu(POINT* prvi, POINT *drugi);
	POINT *VratiRomb(float x, float y, float duzina);
	POINT *VratiPopunuRomb(POINT* prvi, POINT* drugi);
	POINT *VratiHeksagon(float x, float y, float r);
	void   CrtajSaku(CDC *pDC, float x, float y);
	void CrtajRombRuku(CDC *pDC, float x, float y);
	void CrtajPostolje(CDC *pDC, float x, float y,float a);
	void CrtajCvet(CDC *pDC, POINT p, float a);

	double ugaoVeliki = 90.0;
	double ugaoMali = -90.0;
	double ugaoTreci = 0.0;
	HENHMETAFILE opruga = GetEnhMetaFile(L"Opruga.emf");
	
	
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLab2GDItransformacijeView();
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
};

#ifndef _DEBUG  // debug version in Lab2-GDI transformacijeView.cpp
inline CLab2GDItransformacijeDoc* CLab2GDItransformacijeView::GetDocument() const
   { return reinterpret_cast<CLab2GDItransformacijeDoc*>(m_pDocument); }
#endif


