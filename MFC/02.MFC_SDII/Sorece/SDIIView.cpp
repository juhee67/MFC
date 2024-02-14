
// SDIIView.cpp: CSDIIView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDII.h"
#endif

#include "SDIIDoc.h"
#include "SDIIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIIView

IMPLEMENT_DYNCREATE(CSDIIView, CView)

BEGIN_MESSAGE_MAP(CSDIIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSDIIView 생성/소멸

CSDIIView::CSDIIView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIIView::~CSDIIView()
{
}

BOOL CSDIIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIIView 그리기

void CSDIIView::OnDraw(CDC* /*pDC*/)							// 주석 HH10/26		MFC_1 PPT 1장 
{
	CSDIIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	/*
	CDC* pDC = GetDC();//DC를 얻고								// 01 PPT-26
	pDC->Rectangle(CRect(0, 0, 100, 100));//박스를 그린다음
	ReleaseDC(pDC);//DC해제
	*/

	/*
	CPen cPen, * oldPen;										// 02 PPT-27		 펜을 만든다
	cPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));				// 5개 점으로 Red 255 0 0로 수정
	CDC* pDC = GetDC();
	oldPen = pDC->SelectObject(&cPen);
	pDC->Rectangle(CRect(0, 0, 100, 100));						// 직사각형 그림
	pDC->SelectObject(oldPen);				
	cPen.DeleteObject();										// 예전 거 지움
	ReleaseDC(pDC);	
	*/

	/*
	CPen cPen, * oldPen;										// 03 PPT-28
	cPen.CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	CBrush cBrush, * oldBrush;
	cBrush.CreateSolidBrush(RGB(255, 255, 0));

	CDC* pDC = GetDC();//DC를 얻고
	oldPen = pDC->SelectObject(&cPen);
	oldBrush = pDC->SelectObject(&cBrush);							// 백업

	pDC->Rectangle(CRect(0, 0, 100, 100));//박스를 그린다음
	pDC->SelectObject(oldBrush);
	cBrush.DeleteObject();

	pDC->SelectObject(oldPen);
	cPen.DeleteObject();
	ReleaseDC(pDC);//DC해제
	*/


	//Polyline와 PolyBezier에 사용할 POINT배열					// 04 PPT-30
	POINT pline[6] = { 50,133,146,99,246,133,247,212,58,216,50,133 };
	//다각형 칠하기에 사용할 POINT배열
	POINT pgon[4] = { 308,120,440,118,380,212,308,120 };
	RECT rect;
	CBrush cBrush, * oldBrush;
	//RoundRect에 사용할 모서리 둥근원의 x,y지름
	POINT round = { 50,50 };
	//브러쉬를 노랑색 브러쉬로 만든다
	cBrush.CreateSolidBrush(RGB(255, 255, 0));
	//클라이언트 영역을 얻는다.
	GetClientRect(&rect);
	//라운드 박스를 그린다.
	CDC* pDC = GetDC();//DC를 얻고								// 컴파일 안되면 주석처리

	pDC->RoundRect(&rect, round);
	//윈을 그린다.
	pDC->Ellipse(rect.left + 30, rect.top + 30,
		rect.right - 30, rect.bottom - 30);
	//0,0좌표에서 화면 전체에 대각선을 그린다.
	pDC->MoveTo(0, 0);
	pDC->LineTo(rect.right, rect.bottom);
	//다각형 외곽선을 그린다.
	pDC->Polyline(pline, 6);
	//베지어 곡선을 그린다.
	pDC->PolyBezier(pline, 4);
	//브러쉬를 설정하고
	oldBrush = pDC->SelectObject(&cBrush);
	//내부를 칠하는 다각형을 그린다.
	pDC->Polygon(pgon, 4);
	//이전 브러쉬를 설정하고
	pDC->SelectObject(oldBrush);
	//브러쉬를 삭제한다.
	cBrush.DeleteObject();




}


// CSDIIView 인쇄

BOOL CSDIIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSDIIView 진단

#ifdef _DEBUG
void CSDIIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIIDoc* CSDIIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIIDoc)));
	return (CSDIIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIIView 메시지 처리기
