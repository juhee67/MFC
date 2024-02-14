
// MExDiaryDoc.cpp: CMExDiaryDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MExDiary.h"
#endif

#include "MExDiaryDoc.h"

#include <propkey.h>



#include <fcntl.h>																		// 
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMExDiaryDoc

IMPLEMENT_DYNCREATE(CMExDiaryDoc, CDocument)											// PPT-29

BEGIN_MESSAGE_MAP(CMExDiaryDoc, CDocument)
//ON_COMMAND(ID_FILE_OPEN, &CMExDiaryDoc::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CMExDiaryDoc::OnOpenDocument)
//ON_COMMAND(ID_FILE_SAVE, &CMExDiaryDoc::OnSaveDocument)
END_MESSAGE_MAP()


// CMExDiaryDoc 생성/소멸

CMExDiaryDoc::CMExDiaryDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

	memset(m_strDate, 0, sizeof(m_strDate));											//
	memset(m_strSubject, 0, sizeof(m_strSubject));
	memset(m_strContent, 0, sizeof(m_strContent));
}

CMExDiaryDoc::~CMExDiaryDoc()
{
}

BOOL CMExDiaryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMExDiaryDoc serialization

void CMExDiaryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMExDiaryDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMExDiaryDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMExDiaryDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMExDiaryDoc 진단

#ifdef _DEBUG
void CMExDiaryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMExDiaryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMExDiaryDoc 명령

void CMExDiaryDoc::SetSubject(char* subject)
{
	// TODO: 여기에 구현 코드 추가.

	strcpy_s(m_strSubject, sizeof(m_strSubject), subject);								// PPT-25
}


void CMExDiaryDoc::SetContent(char* content)
{
	// TODO: 여기에 구현 코드 추가.

	strcpy_s(m_strContent, sizeof(m_strContent), content);									
}


void CMExDiaryDoc::SetDate(char* date)
{
	// TODO: 여기에 구현 코드 추가.

	strcpy_s(m_strDate, sizeof(m_strDate), date);
}


char* CMExDiaryDoc::GetDate()
{
	// TODO: 여기에 구현 코드 추가.

	return m_strDate;
}


char* CMExDiaryDoc::GetSubject()
{
	// TODO: 여기에 구현 코드 추가.
	
	return m_strSubject;
}


char* CMExDiaryDoc::GetContent()
{
	// TODO: 여기에 구현 코드 추가.
	
	return m_strContent;
}


BOOL CMExDiaryDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	int fd = _open(lpszPathName, _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);
	if (fd != -1) // 파일이 정상적으로 열렸을 경우에만 처리
	{
		_read(fd, m_strDate, sizeof(m_strDate));
		_read(fd, m_strSubject, sizeof(m_strSubject));
		_read(fd, m_strContent, sizeof(m_strContent));

		_close(fd);
	}

	return TRUE;
}


BOOL CMExDiaryDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	int fd = _open(lpszPathName, _O_CREAT | _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);
	if (fd != -1)
	{
		_write(fd, m_strDate, sizeof(m_strDate));
		_write(fd, m_strSubject, sizeof(m_strSubject));
		_write(fd, m_strContent, sizeof(m_strContent));

		_close(fd);
	}

	return TRUE;
}
