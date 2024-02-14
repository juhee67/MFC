
// MExDiaryView.h: CMExDiaryView 클래스의 인터페이스
//

#pragma once


class CMExDiaryView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMExDiaryView() noexcept;
	DECLARE_DYNCREATE(CMExDiaryView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MEXDIARY_FORM };
#endif

// 특성입니다.
public:
	CMExDiaryDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMExDiaryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();									
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strDate;												// 자동 추가			// PPT-20 
	CString m_strSubject;																
	CString m_strContent;																
	afx_msg void OnChangeContent();
	afx_msg void OnChangeDate();
	afx_msg void OnChangeSubject();
};

#ifndef _DEBUG  // MExDiaryView.cpp의 디버그 버전
inline CMExDiaryDoc* CMExDiaryView::GetDocument() const
   { return reinterpret_cast<CMExDiaryDoc*>(m_pDocument); }
#endif

