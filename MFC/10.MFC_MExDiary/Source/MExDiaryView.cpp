
// MExDiaryView.cpp: CMExDiaryView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MExDiary.h"
#endif

#include "MExDiaryDoc.h"
#include "MExDiaryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMExDiaryView

IMPLEMENT_DYNCREATE(CMExDiaryView, CFormView)

BEGIN_MESSAGE_MAP(CMExDiaryView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMExDiaryView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_EN_CHANGE(IDC_CONTENT, &CMExDiaryView::OnChangeContent)
	ON_EN_CHANGE(IDC_DATE, &CMExDiaryView::OnChangeDate)
	ON_EN_CHANGE(IDC_SUBJECT, &CMExDiaryView::OnChangeSubject)
END_MESSAGE_MAP()

// CMExDiaryView 생성/소멸

CMExDiaryView::CMExDiaryView() noexcept
	: CFormView(IDD_MEXDIARY_FORM)
	, m_strDate(_T(""))												// 자동 추가			// PPT-20
	, m_strSubject(_T(""))
	, m_strContent(_T(""))
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMExDiaryView::~CMExDiaryView()
{
}

void CMExDiaryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATE, m_strDate);								// 자동 추가			// PPT-20
	DDX_Text(pDX, IDC_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_CONTENT, m_strContent);
}

BOOL CMExDiaryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMExDiaryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

	CMExDiaryDoc* pDoc = (CMExDiaryDoc*)GetDocument();										// PPT-28

	m_strSubject = pDoc->GetSubject();
	m_strDate = pDoc->GetDate();
	m_strContent = pDoc->GetContent();

	UpdateData(FALSE);

}


// CMExDiaryView 인쇄


void CMExDiaryView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMExDiaryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMExDiaryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMExDiaryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMExDiaryView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}

void CMExDiaryView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMExDiaryView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMExDiaryView 진단

#ifdef _DEBUG
void CMExDiaryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMExDiaryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMExDiaryDoc* CMExDiaryView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMExDiaryDoc)));
	return (CMExDiaryDoc*)m_pDocument;
}
#endif //_DEBUG


// CMExDiaryView 메시지 처리기


void CMExDiaryView::OnChangeContent()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CMExDiaryDoc* pDoc = (CMExDiaryDoc*)GetDocument();									// PPT-27
	pDoc->SetContent(LPSTR(LPCTSTR(m_strContent)));

}


void CMExDiaryView::OnChangeDate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CMExDiaryDoc* pDoc = (CMExDiaryDoc*)GetDocument();									// PPT-27
	pDoc->SetDate(LPSTR(LPCTSTR(m_strDate)));

}


void CMExDiaryView::OnChangeSubject()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	CMExDiaryDoc* pDoc = (CMExDiaryDoc*)GetDocument();									// PPT-27
	pDoc->SetSubject(LPSTR(LPCTSTR(m_strSubject)));

}



