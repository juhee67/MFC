
// MFC01View.h: CMFC01View 클래스의 인터페이스
//

#pragma once


class CMFC01View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFC01View() noexcept;
	DECLARE_DYNCREATE(CMFC01View)

// 특성입니다.
public:
	CMFC01Doc* GetDocument() const;					// 연결 (GetDocument() 이용)

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.		// 이 안에서만 코딩함
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);									// 윈도우 만들기 전에
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);								
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);						
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);						

// 구현입니다.
public:
	virtual ~CMFC01View();
#ifdef _DEBUG
	virtual void AssertValid() const;				// (공통)
	virtual void Dump(CDumpContext& dc) const;		// (공통)
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFC01View.cpp의 디버그 버전
inline CMFC01Doc* CMFC01View::GetDocument() const
   { return reinterpret_cast<CMFC01Doc*>(m_pDocument); }
#endif

