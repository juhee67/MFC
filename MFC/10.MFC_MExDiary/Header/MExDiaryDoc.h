
// MExDiaryDoc.h: CMExDiaryDoc 클래스의 인터페이스
//


#pragma once

#define MAXCONTENTSIZE 1024															// PTT-22
#define MAXSUBJECTSIZE 256
#define MAXDATESIZE 80

class CMExDiaryDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMExDiaryDoc() noexcept;
	DECLARE_DYNCREATE(CMExDiaryDoc)

// 특성입니다.
public:
	char m_strDate[MAXDATESIZE + 1];												// PTT-23
	char m_strSubject[MAXSUBJECTSIZE + 1];
	char m_strContent[MAXCONTENTSIZE + 1];

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMExDiaryDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	void SetSubject(char* subject);
	void SetContent(char* content);
	void SetDate(char* date);
	char* GetDate();														
	char* GetSubject();
	char* GetContent();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);									// PPT-29
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
