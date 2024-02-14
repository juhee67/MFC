
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFC01.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)		
	ON_WM_CREATE()								// 새로운 윈도우 만들 때 
END_MESSAGE_MAP()

static UINT indicators[] =
{	// 상태바에 현재 상태 보여줌
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,		
	ID_INDICATOR_NUM,		
	ID_INDICATOR_SCRL,		
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)		// 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;											// error 발생

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||			// 메뉴바
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))						// 상태바 
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));		// 상태바를 현재 속성으로 붙여서 실행

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);								// 만들어진 툴바를 도킹할 수 있는 상태로 만듦
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);											// 도킹
	// 현재까지 윈도우창 만듦

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)							// 윈도우 만들기 전에 해야될 것들
{
	if( !CFrameWnd::PreCreateWindow(cs) )			// 만들어져있지 않으면 만들어라
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const		// 함수
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

