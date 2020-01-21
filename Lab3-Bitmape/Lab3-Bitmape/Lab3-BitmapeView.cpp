
// Lab3-BitmapeView.cpp : implementation of the CLab3BitmapeView class
//

#include "stdafx.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab3-Bitmape.h"
#endif

#include "Lab3-BitmapeDoc.h"
#include "Lab3-BitmapeView.h"

//#include "Lab2-BitmapeView.rc"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab3BitmapeView

IMPLEMENT_DYNCREATE(CLab3BitmapeView, CView)

BEGIN_MESSAGE_MAP(CLab3BitmapeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CLab3BitmapeView construction/destruction

CLab3BitmapeView::CLab3BitmapeView()
{
	

}

CLab3BitmapeView::~CLab3BitmapeView()
{

}

BOOL CLab3BitmapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab3BitmapeView drawing
void Rotacija(CDC * pDC, double ugao, bool smer, float dx, float dy)
{
	// 1- desna
	//0 -leva
	XFORM xform;
	double ugaoRad = ugao * toRad;
	xform.eM11 = cos(ugaoRad);
	xform.eM12 = sin(ugaoRad);
	xform.eM21 = -sin(ugaoRad);
	xform.eM22 = cos(ugaoRad);
	xform.eDx = dx;
	xform.eDy = dy;

	if (smer)
	{
		pDC->ModifyWorldTransform(&xform, MWT_RIGHTMULTIPLY);
	}
	else {

		pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);

	}

}

void Translacija(CDC * pDC, bool smer, float dx, float dy)
{
	XFORM xform;
	xform.eM11 = 1.0;
	xform.eM12 = 0.0;
	xform.eM21 = 0.0;
	xform.eM22 = 1.0;
	xform.eDx = dx;
	xform.eDy = dy;

	// 1- desna
	//0 -leva

	if (smer)
	{
		pDC->ModifyWorldTransform(&xform, MWT_RIGHTMULTIPLY);
	}
	else {

		pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);

	}


}

void Refleksija(CDC * pDC, bool smer, float dx, float dy,bool horizontalna)
{

	XFORM xform;
	if (horizontalna){
		xform.eM11 = 1;

		xform.eM22 = -1;
	}
	else{
		xform.eM11 = -1;

		xform.eM22 = 1;

	}


	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eDx = dx;
	xform.eDy = dy;

	// 1- desna
	//0 -leva

	if (smer)
	{
		pDC->ModifyWorldTransform(&xform, MWT_RIGHTMULTIPLY);
	}
	else {

		pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);

	}

}
void SaraBitmapa(CBitmap *osnovnaBitmapa,int dezen,int boja)
{
	BITMAP bm;
	osnovnaBitmapa->GetBitmap(&bm);
	BYTE *baferBitmap = new BYTE[bm.bmWidthBytes*bm.bmHeight];
	osnovnaBitmapa->GetBitmapBits(bm.bmWidthBytes*bm.bmHeight, baferBitmap);
	int N = 20, m = 0;
	if (dezen == 0){
	for (int i = 0; i < bm.bmHeight; i++)
	{
		for (int j = 0; j <= bm.bmWidthBytes; j += 3)
		{
			if ((i / N + j / (N * 3)) % 2 == 0)
			{
				if (boja == 0) {
					baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
				}
				else if (boja == 1) {
					baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
				}
				else if (boja == 2) {
					baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
				}
			}
		}
	}
	}
	else if (dezen == 1) {//horizontalna
		for (int i = 0; i < bm.bmHeight; i++)
		{
			for (int j = 0; j <= bm.bmWidthBytes; j += 3)
			{
				if ((i / N) % 2 == 0)
				{
					if (boja == 0) {
						baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
						baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
					}
					else if (boja == 1) {
						baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
						baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
					}
					else if (boja == 2) {
						baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
						baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
					}
				}
			}
		}
	}
	else if (dezen == 2){
		int N = 8, m = 0; int a = bm.bmHeight / N;
		int sirinaVeci = bm.bmHeight / N * 2;
		int sirinaManji = bm.bmHeight / N;
		int centar = bm.bmWidthBytes / 2;
		for (int i = 0; i < bm.bmHeight; i++)
		{
			for (int j = 0; j <= bm.bmWidthBytes; j += 3)
			{

				for (int m = 0; m <= bm.bmHeight * 2; m += a * 2)
				{
					int x = j; int y = i;
					if (j < bm.bmWidthBytes / 2)
					{
						if (y<x + m && y>x + (m - a))
						{
							baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
							baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
						}
					}
					else
					{
						int x = j; int y = i;
						if (y<-x + m && y>-x + (m - a))
						{
							baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
							baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
						}


					}
				}


			}

		}
	}else if (dezen == 3){

		int N = 25, m = 0; int a = bm.bmHeight / N;
		for (int i = 0; i < bm.bmHeight; i++)
		{
			for (int j = 0; j <= bm.bmWidthBytes; j += 3)
			{
				for (int k = 0; k <= bm.bmHeight; k += 2 * a)
				{
					int xpom = abs(bm.bmWidthBytes / 2 / 3 - j / 3);
					int ypom = abs(bm.bmHeight / 2 - i);
					xpom *= xpom;
					ypom *= ypom;
					if (xpom + ypom>pow((float)k + (float)a, 2) && xpom + ypom <pow((float)k + 2 * a, 2))
					{
						if (boja == 0) {
							baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
							baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
						}
						else if (boja == 1) {
							baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
							baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
						}
						else if (boja == 2) {
							baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
							baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
						}
					}
				}
			}
			
		}
		
	}
	/*
	for (int i = 0; i < bm.bmHeight; i++)
	{
		for (int j = 0; j <= bm.bmWidthBytes; j += 3)
		{
			if ((i / N) % 2 == 0)
			{
				if (boja == 0) {
					baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
				}
				else if (boja == 1) {
					baferBitmap[(i * bm.bmWidthBytes) + j] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
				}
				else if (boja == 2) {
					baferBitmap[(i * bm.bmWidthBytes) + j - 1] = 0;
					baferBitmap[(i * bm.bmWidthBytes) + j + 1] = 0;
				}
			}
		}
	}*/
	
	osnovnaBitmapa->SetBitmapBits(bm.bmWidthBytes*bm.bmHeight, baferBitmap);

}

void CrtajBitmapu(CDC *pDC, CString naziv,bool sara,int dezen,int boja)
{
	CImage slika;
	slika.Load(naziv);

	CBitmap osnovnaBitmapa;
	CBitmap maskaBitmapa;
	osnovnaBitmapa.Attach(slika.Detach());
	BITMAP bm;//pomocna bitmapa da bi se uzela velicina slike
	osnovnaBitmapa.GetBitmap(&bm);

	maskaBitmapa.CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);//Maska je monohromatska


	CDC* srcDC = new CDC();
	CDC* dstDC = new CDC();
	srcDC->CreateCompatibleDC(NULL);
	dstDC->CreateCompatibleDC(NULL);


	//selektovanje bitmapa
	CBitmap *oldSrcBmp = srcDC->SelectObject(&osnovnaBitmapa);
	CBitmap *oldDstBmp = dstDC->SelectObject(&maskaBitmapa);


	//uzimanje boje koja je pozadina na slici
	COLORREF topLeft = srcDC->GetPixel(5, 5);
	COLORREF oldBkcolor = srcDC->SetBkColor(topLeft);//selektovanje te boje za backgroundColor



	dstDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, srcDC, 0, 0, SRCCOPY);
	srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, dstDC, 0, 0, SRCAND);

	srcDC->SelectObject(oldSrcBmp);
	dstDC->SelectObject(oldDstBmp);
	srcDC->DeleteDC();
	dstDC->DeleteDC();
	delete srcDC;
	delete dstDC;

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	if (sara)
	{
		SaraBitmapa(&osnovnaBitmapa, dezen,boja);
	}
	memDC->SelectObject(&maskaBitmapa);

	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCAND);

	memDC->SelectObject(&osnovnaBitmapa);
	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCPAINT);
	memDC->DeleteDC();
	delete memDC;
	osnovnaBitmapa.DeleteObject();
	maskaBitmapa.DeleteObject();

}




void CLab3BitmapeView::OnDraw(CDC* pDC)
{
	CLab3BitmapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//XYKJX
	//RRCSN

	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	int y = rect.bottom;
	int x = rect.right;
	pDC->SetWindowExt(rect.right, rect.bottom);
	pDC->SetViewportExt(rect.right, rect.bottom);
	pDC->SetWindowOrg(0, 0);
	pDC->SetGraphicsMode(GM_ADVANCED);


	CDC * memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap memBitmapa;
	memDC->SetGraphicsMode(GM_ADVANCED);
	memBitmapa.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(memBitmapa);
	XFORM * pomMem = new XFORM();
	memDC->GetWorldTransform(pomMem);
	memDC->Rectangle(0, 0, rect.Width(), rect.Height());


	
	Rotacija(memDC, -180, 0, 150, 380);
	XFORM* pom2 = new XFORM();
	memDC->GetWorldTransform(pom2);
	Translacija(memDC, 0, -35, 260);

	CrtajBitmapu(memDC, CString("osnova.bmp"),false,0,0);

	memDC->SetWorldTransform(pom2);
	
	Rotacija(memDC, ugao1, 0, 62, 288);
	Translacija(memDC, 0, -62, -288);
	

	CrtajBitmapu(memDC, CString("ruka1.bmp"),true,0,0);
	


	Rotacija(memDC, ugao2, 0, 62, 40);
	Translacija(memDC, 0, -62, -40);
	Translacija(memDC, 0, 0, -190);


	CrtajBitmapu(memDC, CString("ruka2.bmp"),true,3,1);

	XFORM* pom = new XFORM();
	memDC->GetWorldTransform(pom);

	Rotacija(memDC, ugao3, 0, 60, 38);
	Translacija(memDC, 0, -35, -62);

	CrtajBitmapu(memDC, CString("ruka3.bmp"),false,0,0);

	memDC->SetWorldTransform(pom);


	Refleksija(memDC, 0, 1, 0, 0);

	Rotacija(memDC, ugao3, 0, -60, 38);
	Translacija(memDC, 0, -35, -62);
	CrtajBitmapu(memDC, CString("ruka3.bmp"),false,0,0);

	memDC->SetWorldTransform(pomMem);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);
	memDC->DeleteDC();
	delete memDC;
}


// CLab3BitmapeView printing

BOOL CLab3BitmapeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab3BitmapeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab3BitmapeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab3BitmapeView diagnostics

#ifdef _DEBUG
void CLab3BitmapeView::AssertValid() const
{
	CView::AssertValid();
}

void CLab3BitmapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab3BitmapeDoc* CLab3BitmapeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab3BitmapeDoc)));
	return (CLab3BitmapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab3BitmapeView message handlers


void CLab3BitmapeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 0x31:
	{
		//::MessageBox(NULL, _T("Pritisak"), _T("Radi"), MB_OK);

		ugao1 += 5;
		Invalidate();
		break;
	}
	case 0x32:
	{
		//::MessageBox(NULL, _T("Pritisak"), _T("Radi"), MB_OK);

		ugao1 -= 5;
		Invalidate();
		break;
	}

	case 0x33:
	{
		ugao2 += 5;
		Invalidate();
		break;
	}

	case 0x34:
	{
		ugao2 -= 5;
		Invalidate();
		break;
	}

	case 0x35: {
		ugao3 += 5;

		Invalidate();
		break;
	}
	case 0x36: {

		ugao3 -= 5;

		Invalidate();
		break;
	}
	}
}


BOOL CLab3BitmapeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
