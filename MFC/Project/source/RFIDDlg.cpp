
// RFIDDlg.cpp: 구현 파일

#include "is_d2xx.h"
#include "pch.h"
#include "framework.h"
#include "RFID.h"
#include "RFIDDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <mysql.h>	// for DB 연동

// sound 출력용
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "mmsystem.h"

#include <iostream>

#pragma comment(lib,"winmm.lib") // 라이브러리 불러오기
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRFIDDlg 대화 상자


CRFIDDlg::CRFIDDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RFID_DIALOG, pParent)
	, m_strRfid(_T(""))
	, m_strholdNum(_T(""))
	, m_strLevel(_T(""))
	, m_strScore(_T(""))
	, m_strNum(_T(""))
	, m_strHeight(_T(""))
	, m_strLevelNum(_T(""))
	, m_strLastHold(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
CRFIDDlg::~CRFIDDlg()
{
	OnDisconnect();
}

void CRFIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strRfid);
	DDX_Control(pDX, IDC_COMBO1, m_holdNumber);
	DDX_CBString(pDX, IDC_COMBO1, m_strholdNum);
	DDX_Control(pDX, IDC_COMBO2, m_level);
	DDX_CBString(pDX, IDC_COMBO2, m_strLevel);
	DDX_Text(pDX, IDC_EDIT5, m_strScore);
	DDX_Text(pDX, IDC_EDIT7, m_strNum);
	DDX_Text(pDX, IDC_EDIT6, m_strHeight);
	DDX_Text(pDX, IDC_EDIT3, m_strLevelNum);
	DDX_Text(pDX, IDC_EDIT2, m_strLastHold);
}

BEGIN_MESSAGE_MAP(CRFIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CRFIDDlg::OnConnect)
	ON_BN_CLICKED(IDC_BUTTON3, &CRFIDDlg::OnReadOnce)
	ON_BN_CLICKED(IDC_BUTTON2, &CRFIDDlg::OnDisconnect)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRFIDDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRFIDDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON7, &CRFIDDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CRFIDDlg 메시지 처리기

BOOL CRFIDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_level.AddString(_T("6"));
	m_level.AddString(_T("7"));
	
	m_holdNumber.AddString(_T("1"));
	m_holdNumber.AddString(_T("2"));
	m_holdNumber.AddString(_T("3"));
	m_holdNumber.AddString(_T("4"));
	m_holdNumber.AddString(_T("5"));

	m_level.SetCurSel(0);				// 디폴트 값
	m_holdNumber.SetCurSel(0);			// 디폴트 값
	UpdateData(FALSE);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRFIDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRFIDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRFIDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRFIDDlg::OnConnect()	// RFID연결 버튼1
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//열린 포트번호 찾기
	if (is_GetDeviceNumber(&usbnumber) == IS_OK)
	{
		printf("FTDI USB To Serial 연결된 개수 : %d\n", usbnumber);
		if (is_GetSerialNumber(0, readSerialNumber) == IS_OK)
		{
			if (memcmp(changeSerialNumber, readSerialNumber, sizeof(changeSerialNumber) != 0))
			{
				if (is_SetSerialNumber(0, changeSerialNumber) == IS_OK)
				{
					printf(" USB To Serial Number 를 변경 하였습니다.\n");
					printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
				}
			}
			else
				printf(" FTDI SerialNumber :  %s \n", changeSerialNumber);
		}
	}

	//열린 포트번호로 연결
	unsigned long portNumber;
	if (is_GetCOMPort_NoConnect(0, &portNumber) == IS_OK)
	{
		printf("COM Port : %d\n", portNumber);
	}
	if (is_OpenSerialNumber(&ftHandle, readSerialNumber, 115200) != IS_OK)
	{
		printf("USB To Serial과 통신 연결 실패\n");
		//return -1;
	}
	else {
		printf("Serial포트 %d와 통신 연결성공!! \n", portNumber);
	}
	Sleep(100);
	flag_r = 0;

}


void CRFIDDlg::OnReadOnce()	// 1회읽기 버튼3
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString temp, temp1 = _T("");
	CString temp2 = _T("f0 ee 68 cb 50 01 04 e0 ");
	CString temp3 = _T("13 fb 67 cb 50 01 04 e0 ");
	CString temp4 = _T("01 e0 7e 5b ");
	CString temp5 = _T("31 16 f0 5b ");

	//ISO15693 모드로 읽기( 싱글모드 읽기 )					
	if (flag_r == 0)
	{
		if (is_WriteReadCommand(ftHandle, CM1_ISO15693, CM2_ISO15693_ACTIVE + BUZZER_OFF,		
			writeLength, wirteData, &readLength, readData) == IS_OK)
		{
			int i;
			printf("ISO 15693 UID : ");
			for (i = 0; i < readLength; i++)
			{
				printf("%02x ", readData[i]);			
				temp.Format(_T("%02x "), readData[i]);
				temp1 += temp;
			}
			m_strRfid = temp1;					
			UpdateData(FALSE);
			printf("(160~170cm)\n");


			// ISO 15693 f0 ee 68 cb 50 01 04 e0
			if (temp1.Compare(temp2) == 0)		
			{
				//DB
				MYSQL* conn;
				MYSQL* conn_result;
				unsigned int timeout_sec = 1;

				conn = mysql_init(NULL);
				mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
				conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "juhee", "mysql", 3306, NULL, 0);//비밀번호 

				if (NULL == conn_result)
				{
					cout << "DB Connection Fail" << endl;
				}
				else
				{
					cout << "DB Connection Success" << endl;

					char query[1024];
					MYSQL_RES* result;
					MYSQL_ROW row;

					sprintf_s(query, 1024, "SELECT * FROM climb WHERE num=1");	// num=1	 

					// Send Query
					if (mysql_query(conn, query))
					{
						cout << "SELECT Fail" << endl;
					}

					CString pic = _T("");
					CString sound = _T("");
					CString heigth = _T("");
					CString wall_num = _T("");

					// Get Response
					result = mysql_store_result(conn);

					int fields = mysql_num_fields(result);    // 필드 갯수 구함

					while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
					{
						pic = row[1];
						sound = row[2];
						heigth = row[3];
						wall_num = row[4];

						CRect m_rect;
						CBitmap m_bitmap;
						m_bitmap.DeleteObject();
						m_bitmap.Attach((HBITMAP)LoadImage(NULL, pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));	// solution1.bmp 출력
						CDC* pDC = GetDC();
						CDC memDC;
						memDC.CreateCompatibleDC(pDC);
						memDC.SelectObject(m_bitmap);

						((CStatic*)GetDlgItem(IDC_STATIC))->GetWindowRect(m_rect);
						ScreenToClient(&m_rect);
						CClientDC   dc(this);
						dc.BitBlt(20, 15, 160, 400, &memDC, 0, 0, SRCCOPY);	// x좌표, y좌표, 가로크기, 세로크기

						ReleaseDC(pDC);
						DeleteDC(memDC);

						PlaySoundW(sound, NULL, SND_FILENAME | SND_ASYNC);	//level6.wav sound 출력

						m_strHeight = heigth;// 160~170cm 출력
						m_strNum = wall_num;// wall_1 출력
						UpdateData(FALSE);
					}
					mysql_free_result(result);
					mysql_close(conn);
				}
			}


			// ISO 15693 13 fb 67 cb 50 01 04 e0
			if (temp1.Compare(temp3) == 0)									 
			{
				//DB
				MYSQL* conn;
				MYSQL* conn_result;
				unsigned int timeout_sec = 1;

				conn = mysql_init(NULL);
				mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
				conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "juhee", "mysql", 3306, NULL, 0);//비밀번호 

				if (NULL == conn_result)
				{
					cout << "DB Connection Fail" << endl;
				}
				else
				{
					cout << "DB Connection Success" << endl;

					char query[1024];
					MYSQL_RES* result;
					MYSQL_ROW row;

					sprintf_s(query, 1024, "SELECT * FROM climb WHERE num=3");	// num=3	

					// Send Query
					if (mysql_query(conn, query))
					{
						cout << "SELECT Fail" << endl;
					}

					CString pic = _T("");
					CString sound = _T("");
					CString heigth = _T("");
					CString wall_num = _T("");

					// Get Response
					result = mysql_store_result(conn);

					int fields = mysql_num_fields(result);    // 필드 갯수 구함

					while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
					{
						pic = row[1];
						sound = row[2];
						heigth = row[3];
						wall_num = row[4];

						CRect m_rect;
						CBitmap m_bitmap;
						m_bitmap.DeleteObject();
						m_bitmap.Attach((HBITMAP)LoadImage(NULL, pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));	// solution3.bmp 출력
						CDC* pDC = GetDC();
						CDC memDC;
						memDC.CreateCompatibleDC(pDC);
						memDC.SelectObject(m_bitmap);

						((CStatic*)GetDlgItem(IDC_STATIC))->GetWindowRect(m_rect);
						ScreenToClient(&m_rect);
						CClientDC   dc(this);
						dc.BitBlt(20, 15, 160, 400, &memDC, 0, 0, SRCCOPY);	// x좌표, y좌표, 가로크기, 세로크기

						ReleaseDC(pDC);
						DeleteDC(memDC);

						PlaySoundW(sound, NULL, SND_FILENAME | SND_ASYNC);	//level6.wav sound 출력

						m_strHeight = heigth;	// 160~170cm 출력
						m_strNum = wall_num; 	// wall_2 출력
						UpdateData(FALSE);
					}
					mysql_free_result(result);
					mysql_close(conn);
				}
			}
		}
	}



	//ISO14443A 모드로 읽기 수정
	if (flag_r == 0)
	{
		if (is_WriteReadCommand(ftHandle, CM1_ISO14443AB, CM2_ISO14443A_ACTIVE + BUZZER_OFF,		//BUZZER_ON
			writeLength, wirteData, &readLength, readData) == IS_OK)
		{
			int i;
			printf("ISO 14443AB UID : ");
			for (i = 0; i < readLength; i++)
			{
				printf("%02x ", readData[i]);
				temp.Format(_T("%02x "), readData[i]);
				temp1 += temp;
			}
			m_strRfid = temp1;
			UpdateData(FALSE);
			printf("(170~180cm)\n");


			// ISO 14443A 01 e0 7e 5b
			if (temp1.Compare(temp4) == 0)									 
			{
				PlaySoundW(_T("level7.wav"), NULL, SND_FILENAME | SND_ASYNC);
				//DB
				MYSQL* conn;
				MYSQL* conn_result;
				unsigned int timeout_sec = 1;

				conn = mysql_init(NULL);
				mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
				conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "juhee", "mysql", 3306, NULL, 0);//비밀번호 

				if (NULL == conn_result)
				{
					cout << "DB Connection Fail" << endl;
				}
				else
				{
					cout << "DB Connection Success" << endl;

					char query[1024];
					MYSQL_RES* result;
					MYSQL_ROW row;

					sprintf_s(query, 1024, "SELECT * FROM climb WHERE num=2");	// num=2	

					// Send Query
					if (mysql_query(conn, query))
					{
						cout << "SELECT Fail" << endl;
					}

					CString pic = _T("");
					CString sound = _T("");
					CString heigth = _T("");
					CString wall_num = _T("");

					// Get Response
					result = mysql_store_result(conn);

					int fields = mysql_num_fields(result);    // 필드 갯수 구함

					while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
					{
						pic = row[1];
						sound = row[2];
						heigth = row[3];
						wall_num = row[4];

						CRect m_rect;
						CBitmap m_bitmap;
						m_bitmap.DeleteObject();
						m_bitmap.Attach((HBITMAP)LoadImage(NULL, pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));// solution2.bmp 출력
						CDC* pDC = GetDC();
						CDC memDC;
						memDC.CreateCompatibleDC(pDC);
						memDC.SelectObject(m_bitmap);

						((CStatic*)GetDlgItem(IDC_STATIC))->GetWindowRect(m_rect);
						ScreenToClient(&m_rect);
						CClientDC   dc(this);
						dc.BitBlt(20, 15, 160, 400, &memDC, 0, 0, SRCCOPY);	// x좌표, y좌표, 가로크기, 세로크기

						ReleaseDC(pDC);
						DeleteDC(memDC);

						PlaySoundW(sound, NULL, SND_FILENAME | SND_ASYNC);	//level7.wav sound 출력

						m_strHeight = heigth;// 170~180cm 출력
						m_strNum = wall_num; // wall_1 출력
						UpdateData(FALSE);
					}
					mysql_free_result(result);
					mysql_close(conn);
				}
			}


			// ISO 14443A 31 16 f0 5b
			if (temp1.Compare(temp5) == 0)									
			{
				//DB
				MYSQL* conn;
				MYSQL* conn_result;
				unsigned int timeout_sec = 1;

				conn = mysql_init(NULL);
				mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
				conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "juhee", "mysql", 3306, NULL, 0);//비밀번호 

				if (NULL == conn_result)
				{
					cout << "DB Connection Fail" << endl;
				}
				else
				{
					cout << "DB Connection Success" << endl;

					char query[1024];
					MYSQL_RES* result;
					MYSQL_ROW row;

					sprintf_s(query, 1024, "SELECT * FROM climb WHERE num=4");	// num=4	

					// Send Query
					if (mysql_query(conn, query))
					{
						cout << "SELECT Fail" << endl;
					}

					CString pic = _T("");
					CString sound = _T("");
					CString heigth = _T("");
					CString wall_num = _T("");

					// Get Response
					result = mysql_store_result(conn);

					int fields = mysql_num_fields(result);    // 필드 갯수 구함

					while (row = mysql_fetch_row(result))     // 모든 레코드 탐색
					{
						pic = row[1];
						sound = row[2];
						heigth = row[3];
						wall_num = row[4];

						CRect m_rect;
						CBitmap m_bitmap;
						m_bitmap.DeleteObject();
						m_bitmap.Attach((HBITMAP)LoadImage(NULL, pic, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));	// solution4.bmp 출력
						CDC* pDC = GetDC();
						CDC memDC;
						memDC.CreateCompatibleDC(pDC);
						memDC.SelectObject(m_bitmap);

						((CStatic*)GetDlgItem(IDC_STATIC))->GetWindowRect(m_rect);
						ScreenToClient(&m_rect);
						CClientDC   dc(this);
						dc.BitBlt(20, 15, 160, 400, &memDC, 0, 0, SRCCOPY);	// x좌표, y좌표, 가로크기, 세로크기		

						ReleaseDC(pDC);
						DeleteDC(memDC);

						PlaySoundW(sound, NULL, SND_FILENAME | SND_ASYNC);	//level7.wav sound 출력

						m_strHeight = heigth;	// 170~180cm 출력
						m_strNum = wall_num; 	// wall_2 출력
						UpdateData(FALSE);
					}
					mysql_free_result(result);
					mysql_close(conn);
				}
			}

		}
	}

}


void CRFIDDlg::OnDisconnect()// RFID해제 버튼2
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		// 무선파워를 끊어요.
	is_RfOff(ftHandle);
	//USB 포트를 Close
	if (is_Close(ftHandle) == IS_OK)
	{
		printf("연결을 닫습니다. ");

		CRect m_rect;
		CBitmap m_bitmap;
		CString Path_img = _T("img\\reader.bmp");
		m_bitmap.DeleteObject();
		m_bitmap.Attach((HBITMAP)LoadImage(NULL, Path_img, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
		CDC* pDC = GetDC();
		CDC memDC;

		memDC.CreateCompatibleDC(pDC);
		memDC.SelectObject(m_bitmap);
		((CStatic*)GetDlgItem(IDC_STATIC))->GetWindowRect(m_rect);
		ScreenToClient(&m_rect);
		CClientDC   dc(this);

		dc.BitBlt(20, 15, 160, 400, &memDC, 0, 0, SRCCOPY);	// x좌표, y좌표, 가로크기, 세로크기

		ReleaseDC(pDC);
		DeleteDC(memDC);

		m_strRfid = _T("");
		m_strHeight = _T("");
		m_strNum = _T("");
		m_strLevelNum = _T("");
		m_strLastHold = _T("");

		UpdateData(FALSE);
	}
}


void CRFIDDlg::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	SetDlgItemText(IDC_EDIT2, m_strholdNum);
}


void CRFIDDlg::OnCbnSelchangeCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	SetDlgItemText(IDC_EDIT3, m_strLevel);
}


void CRFIDDlg::OnBnClickedButton7()	// 점수계산하기 버튼7
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT3, m_strLevelNum);// 변수에 ID의 값 넣음
	GetDlgItemText(IDC_EDIT2, m_strLastHold);// 변수에 ID의 값 넣음
	m_strScore.Format(_T("%d점"), _ttoi(m_strLevelNum) * _ttoi(m_strLastHold));	// _ttoi()는 CString 형을 int로 변환하는 함수
	SetDlgItemText(IDC_EDIT5, m_strScore);
}
