
// MFC01View.cpp: CMFC01View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC01.h"
#endif

#include "MFC01Doc.h"
#include "MFC01View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC01View

IMPLEMENT_DYNCREATE(CMFC01View, CView)

BEGIN_MESSAGE_MAP(CMFC01View, CView)
	// 표준 인쇄 명령입니다.											// 세군데 수정 필요
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)						// 메세지 아이디 함수 연결 이 메세지 뜨면 함수 실행
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)				//
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)		//
END_MESSAGE_MAP()

// CMFC01View 생성/소멸

CMFC01View::CMFC01View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFC01View::~CMFC01View()
{
}

BOOL CMFC01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFC01View 그리기

void CMFC01View::OnDraw(CDC* pDC)					// pDC 주석처리 풀어줌
{
	CMFC01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	// 글자 쓰기 전에 폰트 바꿔야 (글자 크기, 색 등 변경 가능)
	CFont cFont, * oldFont;							// 06 PTT-18 앞 코드 복사
	//폰트를 만든다.
	cFont.CreateFont(24, 12,//v,h size				// 새로운 폰트 만든다   16 8로 수정. 24 12로 수정하면 확대됨
		0, 0,//angle								// 기울임 각도
		FW_DONTCARE,//bold							// 글자 속성들 true 하면 바뀐다
		FALSE,//italic
		FALSE,//under line
		FALSE,//STRIKEOUT pulg
		DEFAULT_CHARSET,//CHAR SET
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH, _T("궁서체"));				// 고딕체로 수정. 윈도우 시스템 디렉토리 ~ 에서 가져옴
	//oldFont backup
	oldFont = pDC->SelectObject(&cFont);


	/*																	// 01
	CString test = _T("Hello MFC SDI interface test!!");
	pDC->TextOutW(0, 0, test);							// 자료형 타입 CString으로 줌
	*/

	/*																	// 02 PTT-13
	char temp[80];
	sprintf_s(temp, "안녕하세요 MFC 테스트입니다.");
	//pDC->TextOut(0, 0, temp, strlen(temp));			// r구버전은 됨, 현재 x
	pDC->TextOut(0, 0, (LPCWSTR)temp, strlen(temp));	// 
	// MFC에서 는 자료형 CString 씀
	*/

	CString test = _T("Hello MFC SDI interface test!!");				// 03 PTT-14
	pDC->TextOutW(0, 0, test);

	test.Format(_T("HORZRES(가로크기)=%d"),
		pDC->GetDeviceCaps(HORZRES));
	pDC->TextOut(0, 20, test);
	test.Format(_T("VERTRES(새로크기=%d"),
		pDC->GetDeviceCaps(VERTRES));
	pDC->TextOut(0, 40, test);

	test = _T("DrawText Example");										// 04 PTT-16										
		//set box area
		CRect rect = CRect(0, 60, 400, 100);
	//call DrawText function
	pDC->DrawText(test, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);					

	test = _T("ExtTextOut Example");  //foreground color is blue		// 05 PTT-17   _T( ) 필요
	pDC->SetTextColor(RGB(225, 0, 0));									// 글자색 Red : 225 0 0
	pDC->SetBkColor(RGB(255, 255, 0)); // background color is yellow	// 배경색 변경 
	pDC->ExtTextOut(0, 120, ETO_CLIPPED | ETO_OPAQUE, CRect(0, 120, 400, 200), test, NULL);


	//oldFont를 다시 설정한다.											// 06 PTT-18 뒷코드. 사용이 끝나면 원 위치로
	pDC->SelectObject(oldFont); // restore oldFont
	//delete current font
	cFont.DeleteObject();



}


// CMFC01View 인쇄

BOOL CMFC01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFC01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFC01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFC01View 진단

#ifdef _DEBUG
void CMFC01View::AssertValid() const
{
	CView::AssertValid();
}

void CMFC01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFC01Doc* CMFC01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFC01Doc)));
	return (CMFC01Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFC01View 메시지 처리기
