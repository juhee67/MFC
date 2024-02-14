
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CMainFrame : public CFrameWnd			// 상속
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.								
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();						// 소멸자
#ifdef _DEBUG									// 디버그 모드
	virtual void AssertValid() const;			// 삽입
	virtual void Dump(CDumpContext& dc) const;	// 한 스텝씩 진행하는 기능
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;				// 프로그램위 툴바
	CStatusBar        m_wndStatusBar;			// 창 밑에 

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);	// 윈도우창 만들기
	DECLARE_MESSAGE_MAP()

};


