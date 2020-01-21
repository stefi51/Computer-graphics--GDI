
// Lab2-GDI transformacijeView.cpp : implementation of the CLab2GDItransformacijeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab2-GDI transformacije.h"
#endif

#include "Lab2-GDI transformacijeDoc.h"
#include "Lab2-GDI transformacijeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLab2GDItransformacijeView

IMPLEMENT_DYNCREATE(CLab2GDItransformacijeView, CView)

BEGIN_MESSAGE_MAP(CLab2GDItransformacijeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLab2GDItransformacijeView construction/destruction


POINT*  CLab2GDItransformacijeView::VratiOktagon(float x, float y, float m)
{
	float r = m / 2.0;
	  POINT * pt= new POINT[8];

	for (int i = 0; i < 8; i++)
	{
		pt[i].x = sin(((3.1415 * 2) / 8)*i)*r + x;
		pt[i].y = cos(((3.1415 * 2) / 8)*i)*r + y;
	}

	return pt;
}

POINT * CLab2GDItransformacijeView::VratiPopunu(POINT * prvi, POINT * drugi)
{
	POINT * pt = new POINT[4];
	pt[0] = prvi[7];
	pt[1] = prvi[1];
	pt[2] = drugi[3];
	pt[3] = drugi[5];
	return pt;
}

POINT * CLab2GDItransformacijeView::VratiRomb(float x, float y, float duzina)
{
	

	float dijagonala = float((duzina *  sqrt(2.0)) / 2);
	POINT * pt = new POINT[4];
	pt[0].x = x - dijagonala;
	pt[0].y = y;

	pt[1].x = x;
	pt[1].y = y - dijagonala;

	pt[2].x = x + dijagonala;
	pt[2].y = y;

	pt[3].x = x;
	pt[3].y = y + dijagonala;

	return pt;
}

POINT RastojanjeIzmedjuDveTacke(POINT prva, POINT druga)
{
	static POINT pola;
	pola.x = (prva.x + druga.x) / 2;
	pola.y = (prva.y + druga.y) / 2;
	return pola;
}

POINT * CLab2GDItransformacijeView::VratiPopunuRomb(POINT * prvi, POINT * drugi)
{

	POINT * popunaRomb = new POINT[4];
	popunaRomb[0] = RastojanjeIzmedjuDveTacke(prvi[0], prvi[3]);
	popunaRomb[1] = RastojanjeIzmedjuDveTacke(prvi[2], prvi[3]);


	popunaRomb[2] = RastojanjeIzmedjuDveTacke(drugi[2], drugi[1]);
	popunaRomb[3] = RastojanjeIzmedjuDveTacke(drugi[1], drugi[0]);


	return popunaRomb;
	
}

POINT * CLab2GDItransformacijeView::VratiHeksagon(float x, float y, float k)
{
	float r = k / 2;
	POINT *heksa = new POINT[6];
	for (int i = 0; i < 6; i++)
	{
		heksa[i].x = x + r * cos(i * 60 * toRad);
		heksa[i].y = y + r * sin(i * 60 * toRad);
	}

	return heksa;
}


void CLab2GDItransformacijeView::CrtajSaku(CDC * pDC, float x, float y)
{
	CPen * olovka = new CPen(PS_SOLID, 3, RGB(0, 250, 0));
	CBrush* cetka2 = new CBrush(HS_BDIAGONAL, RGB(0, 255, 0));
	pDC->SelectObject(olovka);
	pDC->SelectObject(cetka2);
	POINT *heksaDole = this->VratiHeksagon(x+42 , y, 100);
	POINT *heksaGore = this->VratiHeksagon(x+42, y, 70);
	POINT *saka = new POINT[8];
	for(int i=0;i<=4;i++)
	{ 
	   if(i<=3)
	   { 
		saka[i] = heksaDole[i];
	   }
	else
	{
		for (int j = 3; j >-1; j--)
		{
			saka[i] = heksaGore[j];
			i++;
		}
	}
	}
	POINT izmedju = RastojanjeIzmedjuDveTacke(saka[3], saka[4]);
	
	

	pDC->Polygon(saka, 8);

     pDC->Ellipse(izmedju.x - 20, izmedju.y - 20, izmedju.x + 20, izmedju.y + 20);
}


void CLab2GDItransformacijeView::CrtajRombRuku(CDC * pDC, float x, float y)
{
	
	POINT *velikiRomb = this->VratiRomb(x, y, 100);
	POINT *maliRomb = this->VratiRomb(x , y- 250, 80);
	POINT *rombUnutra1 = this->VratiRomb(x, y, 25);
	POINT *rombUnutra2 = this->VratiRomb(x, y -250, 25);
	POINT *popuna = this->VratiPopunuRomb(velikiRomb, maliRomb);
	//pDC->LineTo(velikiRomb[0]);

	CPen * olovka = new CPen(PS_SOLID, 5, RGB(0, 0, 255));
	CPen * olovka2 = new CPen(PS_SOLID, 3, RGB(0, 0, 255));
	CBrush* cetka = new CBrush(RGB(0, 255, 0));
	CBrush* cetka2 = new CBrush(HS_BDIAGONAL,RGB(0, 255, 250));
	
	pDC->SelectObject(olovka);
	pDC->SelectObject(cetka2);
	pDC->Polygon(popuna, 4);
	

	pDC->SelectObject(cetka);
	
	pDC->SelectObject(olovka2);

	pDC->Polygon(velikiRomb, 4);
	pDC->Polygon(rombUnutra1, 4);
	
	pDC->Polygon(maliRomb, 4);
	
	pDC->Polygon(rombUnutra2,4);
	//float dijagonala = float((100 *  sqrt(2.0)) / 2);
	//float dijagonala2 = float((80 *  sqrt(2.0)) / 2);
	
	
	
	PlayEnhMetaFile(pDC->m_hDC, opruga, CRect(velikiRomb[0].x+10,velikiRomb[0].y+10,maliRomb[2].x,maliRomb[2].y));



}

void CLab2GDItransformacijeView::CrtajPostolje(CDC * pDC, float x, float y, float duzina)
{

	CPen * olovka = new CPen(PS_SOLID, 3, RGB(255, 0, 255));
	pDC->SelectObject(olovka);

	CBrush* cetka = new CBrush(RGB(0, 0, 255));
	pDC->SelectObject(cetka);

	float dijagonala = float((duzina *  sqrt(2.0)) / 2);
	POINT * Vrh = new POINT[3];
	POINT *trapez = new POINT[4];
	Vrh[0].x = x - duzina/ 2;
	Vrh[0].y = y + duzina / 2;
	Vrh[1].x = x;
	Vrh[1].y = y ;
	Vrh[2].x = x + duzina / 2;
	Vrh[2].y = y + duzina / 2;

	//pDC->BeginPath();
	pDC->Polygon(Vrh, 3);
	CRgn trougaRGN,pravougaonik,spojeni;

	
	pDC->Rectangle(Vrh[0].x, Vrh[0].y, Vrh[2].x, Vrh[2].y + duzina / 2);
	/*
	trougaRGN.CreatePolygonRgn(Vrh, 3, WINDING);
	pravougaonik.CreateRectRgn(Vrh[0].x, Vrh[0].y, Vrh[2].x, Vrh[2].y + duzina / 2);
	spojeni.CombineRgn(&trougaRGN, &pravougaonik, RGN_XOR);
	
	pDC->SelectClipRgn(&spojeni);
	*/
	trapez[0] = Vrh[0];
	trapez[0].y += duzina / 2;
	trapez[1] = Vrh[2];
	trapez[1].y += duzina / 2;
	trapez[3].x = trapez[0].x- duzina / 2;
	trapez[3].y = trapez[0].y+duzina / 2;

	trapez[2].x = trapez[1].x + duzina / 2;
	trapez[2].y = trapez[1].y + duzina / 2;
	
	pDC->Polygon(trapez, 4);
	//pDC->EndPath();
	//pDC->StrokeAndFillPath();
	//pDC->SelectClipPath(RGN_XOR);
	
	pDC->Rectangle(trapez[3].x-duzina / 2, trapez[3].y , trapez[2].x + duzina / 2, trapez[2].y + duzina / 2);
}

void CLab2GDItransformacijeView::CrtajCvet(CDC * pdc, POINT p, float duzina)
{
	POINT pt[4], pt2[4];


	
	pt[0].x = p.x - duzina;
	pt[0].y = p.y - duzina;

	pt[1].x = p.x + duzina;
	pt[1].y = p.y - duzina;

	pt[2].x = p.x + duzina;
	pt[2].y = p.y + duzina;

	pt[3].x = p.x - duzina;
	pt[3].y = p.y + duzina;


	pdc->BeginPath();

	


	pdc->Arc(pt[0].x, pt[0].y, pt[2].x, pt[2].y, pt[0].x, p.y, pt[2].x, p.y);
	//pdc->Arc(pt[0].x-(duzina/2), pt[0].y-duzina, p.x, p.y-(duzina/2), pt[0].x-(duzina/2), pt[0].y -(duzina / 2), p.x, p.y-(duzina/2));
	pdc->Arc(pt[0].x, pt[0].y-2*duzina, pt[0].x, pt[0].y, pt[0].x-duzina, pt[0].y, pt[0].x - duzina, pt[0].y - 2 * duzina);


	pdc->EndPath();

	//pdc->FillPath();
	pdc->StrokeAndFillPath();

	
}

CLab2GDItransformacijeView::CLab2GDItransformacijeView()
{
	// TODO: add construction code here

}

CLab2GDItransformacijeView::~CLab2GDItransformacijeView()
{
}

BOOL CLab2GDItransformacijeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CLab2GDItransformacijeView::Rotacija(CDC * pDC, double ugao, bool smer, float dx, float dy)
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

void CLab2GDItransformacijeView::Translacija(CDC * pDC, bool smer, float dx, float dy)
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

void CLab2GDItransformacijeView::Refleksija(CDC * pDC, bool smer, bool HV, float dx, float dy)
{

	XFORM xform;
	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 =-1;
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



void CLab2GDItransformacijeView::CrtajOktagonRuku(CDC * pDC, float x, float y)
{
	
	

	CBrush* cetka = new CBrush(RGB(0, 0, 255));
	pDC->SelectObject(cetka);

	POINT * oktagonVeliki= this->VratiOktagon(x, y, 150);
	POINT * oktagonMali = this->VratiOktagon(x, y+250, 100);
	POINT * oktagonUnutra = this->VratiOktagon(x, y , 50);
	POINT * oktagonUnutra2 = this->VratiOktagon(x, y + 250, 50);
	POINT *popuna = this->VratiPopunu(oktagonVeliki, oktagonMali);

	CPen * olovka = new CPen(PS_SOLID, 5, RGB(250, 0, 0));
	pDC->SelectObject(olovka);

	pDC->Polygon(popuna, 4);

	CPen * olovka2 = new CPen(PS_SOLID, 3, RGB(250, 0, 0));
	pDC->SelectObject(olovka2);
	pDC->Polygon(oktagonVeliki, 8);
	pDC->Polygon(oktagonMali, 8);

	pDC->Polygon(oktagonUnutra, 8);
	pDC->Polygon(oktagonUnutra2, 8);

	PlayEnhMetaFile(pDC->m_hDC, opruga, CRect(oktagonVeliki[6].x+17 , oktagonVeliki[6].y - 12, oktagonMali[2].x+7, oktagonMali[2].y+7));
	

}

// CLab2GDItransformacijeView drawing

void CLab2GDItransformacijeView::OnDraw(CDC* pDC)
{
	CLab2GDItransformacijeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen * olovka = new CPen(PS_SOLID, 2, RGB(250, 0, 0));
	CPen *staraOl = pDC->SelectObject(olovka);

	CBrush* cetka = new CBrush(RGB(0, 255, 0));
	//CBrush * staraCe = pDC->SelectObject(cetka);

	pDC->SetGraphicsMode(GM_ADVANCED);
	

	this->Rotacija(pDC, 180, 1, 120, 155);
	this->CrtajPostolje(pDC, 0, 0, 80);

	this->Rotacija(pDC, ugaoVeliki, 0, 0, 0);
	
	this->CrtajOktagonRuku(pDC, 0, 0);
	
	this->Translacija(pDC, 0, 0, 250);
	this->Rotacija(pDC, ugaoMali, 0, 0, 0);
	this->CrtajRombRuku(pDC, 0, 0);
	

	this->Translacija(pDC, 0, 0, -250);
	this->Rotacija(pDC, -90, 0, 0, 0);
	XFORM* pom = new XFORM();
		pDC->GetWorldTransform(pom);

	this->Rotacija(pDC, ugaoTreci, 0, 0, 0);
	

	this->CrtajSaku(pDC, 0, 0);
	
	
	pDC->SetWorldTransform(pom);
	this->Refleksija(pDC, 0, 0, 0, 0);
	this->Rotacija(pDC,ugaoTreci, 0, 0, 0);
	this->CrtajSaku(pDC, 0, 0);

	
	this->Translacija(pDC, 0, 100, 100);
	


}


// CLab2GDItransformacijeView printing

BOOL CLab2GDItransformacijeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab2GDItransformacijeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab2GDItransformacijeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab2GDItransformacijeView diagnostics

#ifdef _DEBUG
void CLab2GDItransformacijeView::AssertValid() const
{
	CView::AssertValid();
}

void CLab2GDItransformacijeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab2GDItransformacijeDoc* CLab2GDItransformacijeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab2GDItransformacijeDoc)));
	return (CLab2GDItransformacijeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLab2GDItransformacijeView message handlers


void CLab2GDItransformacijeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case 0x31:
	{
		//::MessageBox(NULL, _T("Pritisak"), _T("Radi"), MB_OK);

		ugaoVeliki += 5;
		Invalidate();
		break;
	}
	case 0x32:
	{
		//::MessageBox(NULL, _T("Pritisak"), _T("Radi"), MB_OK);

		ugaoVeliki -= 5;
		Invalidate();
		break;
	}

	case 0x33:
	{
		ugaoMali += 5;
		Invalidate();
		break;
	}

	case 0x34:
	{
		ugaoMali -= 5;
		Invalidate();
		break;
	}

	case 0x35: {
		ugaoTreci += 5;
	
		Invalidate();
		break;
	}
	case 0x36: {
		
		ugaoTreci -= 5;
	
		Invalidate();
		break;
	}
	}

	//CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
