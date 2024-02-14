
// SDIView.cpp: CSDIView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#endif

#include "SDIDoc.h"
#include "SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



BOOL exitFlag = TRUE;  //SDIIView.cpp의 맨 앞부분에 복사
UINT ThreadProc(LPVOID lParam)
{
	CBrush cBrush, * oldBrush;
	CDC* pDC;
	RECT rect;
	int    xLeft, xRight, yTop, yBottom, iRed, iGreen, iBlue;
	CSDIView* pView;
	pView = (CSDIView*)lParam;
	pView->GetClientRect(&rect);
	pDC = pView->GetDC();
	while (TRUE)
	{
		xLeft = rand() % rect.right;
		xRight = rand() % rect.right;
		yTop = rand() % rect.bottom;
		yBottom = rand() % rect.bottom;
		iRed = rand() & 255;
		iGreen = rand() & 255;
		iBlue = rand() & 255;
		cBrush.CreateSolidBrush(RGB(iRed, iGreen, iBlue));
		oldBrush = pDC->SelectObject(&cBrush);
		pDC->Rectangle(min(xLeft, xRight), min(yTop, yBottom),
			max(xLeft, xRight), max(yTop, yBottom));
		pDC->SelectObject(oldBrush);
		cBrush.DeleteObject();
		Sleep(1);
		if (exitFlag)  break;
	}
	pView->ReleaseDC(pDC);
	return 0;
}




// CSDIView

IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_THREADBEGIN, &CSDIView::OnThreadbegin)
	ON_COMMAND(ID_THREADEND, &CSDIView::OnThreadend)
	ON_UPDATE_COMMAND_UI(ID_THREADEND, &CSDIView::OnUpdateThreadend)
	ON_UPDATE_COMMAND_UI(ID_THREADBEGIN, &CSDIView::OnUpdateThreadbegin)
END_MESSAGE_MAP()

// CSDIView 생성/소멸

CSDIView::CSDIView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIView::~CSDIView()
{
}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIView 그리기

void CSDIView::OnDraw(CDC* /*pDC*/)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSDIView 인쇄

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSDIView 진단

#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIView 메시지 처리기


void CSDIView::OnThreadbegin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	exitFlag = FALSE;
	AfxBeginThread(ThreadProc, (LPVOID)this);

}


void CSDIView::OnThreadend()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	exitFlag = TRUE;

}


void CSDIView::OnUpdateThreadbegin(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (exitFlag)pCmdUI->Enable(TRUE);
	elsepCmdUI->Enable(FALSE);

}

void CSDIView::OnUpdateThreadend(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.

	if (!exitFlag)pCmdUI->Enable(TRUE);
	elsepCmdUI->Enable(FALSE);

}



