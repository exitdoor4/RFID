
// RFIDDlg.cpp: 구현 파일
//

#include "is_d2xx.h"
#include "framework.h"
#include "afxdialogex.h"
#include "SetDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString index[6];
MYSQL* conn;

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
public:
//	
//	afx_msg void OnConnect();
//	afx_msg void OnImage();
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
	,m_strRfid(_T(""))
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
	DDX_Control(pDX, IDC_INFORFID, m_info_RFID);
	DDX_Control(pDX, IDC_INFODB, m_info_DB);
	DDX_Control(pDX, IDC_INDEX1, m_Index1);
	DDX_Control(pDX, IDC_INDEX2, m_index2);
	DDX_Control(pDX, IDC_INDEX3, m_index3);
	DDX_Control(pDX, IDC_LAMP_IMAGE, m_control_picture);
}

BEGIN_MESSAGE_MAP(CRFIDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BSTART, &CRFIDDlg::OnConnect)
	ON_BN_CLICKED(IDC_STOP, &CRFIDDlg::OnDisconnect)
	

	ON_BN_CLICKED(IDOK, &CRFIDDlg::OnBnClickedEnd)
	ON_BN_CLICKED(IDC_BUTTON3, &CRFIDDlg::OnSetDB)
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
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_isWorkingThread = TRUE;
	

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









void CRFIDDlg::OnConnect()
{
	// 열린 포트 찾는 과정 
	if (is_GetDeviceNumber(&usbnumber) == IS_OK)
	{
		printf("FTDI USB To Serial 연결된 개수 :%d\n", usbnumber);
		if (is_GetSerialNumber(0, readSerialNumber) == IS_OK)
		{
			if (memcmp(changeSerialNumber, readSerialNumber, sizeof(changeSerialNumber) != 0))
			{
				if (is_SetSerialNumber(0, changeSerialNumber) == IS_OK)
				{
					printf("USB To Serial Number 를 변경하였습니다.\n");
					printf("FTDI SerialNumber : %s\n", changeSerialNumber);
				}
			}
			else
				printf("FTDI SerialNumber : %s\n", changeSerialNumber);
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
		//return -1
	}
	else
	{
		printf("Serial포트 %d와 통신 연결성공!! \n", portNumber);
		m_info_RFID.SetWindowTextW(_T("ON"));
		m_pThread = AfxBeginThread(ThreadForCounting, this); // 쓰레드 온
		DB_Connect();
	}
	Sleep(100);
}





void CRFIDDlg::OnDisconnect()
{
	// 무선 파워를 끊기
	is_RfOff(ftHandle);
	//USB 포트 닫기
	if (is_Close(ftHandle) == IS_OK)
	{
		printf("연결을 닫습니다.");
		m_info_RFID.SetWindowTextW(_T("OFF"));
		m_isWorkingThread = false;
		WaitForSingleObject(m_pThread->m_hThread, 5000);

		mysql_free_result(result);
		mysql_close(conn);
		m_info_DB.SetWindowTextW(_T("OFF"));
	}

}


void CRFIDDlg::OnReadOnce()
{
	CString temp, temp1 = _T("");
	

	if (is_WriteReadCommand(ftHandle, CM1_ISO14443AB, CM2_ISO14443A_ACTIVE,
		writeLength, writeData, &readLength, readData) == IS_OK)
	{
		int i;
		printf("ISO 14443A UID:");
		for (i = 0; i < readLength; i++)
		{
			temp.Format(_T("%02x"), readData[i]);
			temp1 += temp;
		}
		Send_Query(temp1);
		Show_Windows();
	
		printf("\n");
	}
}

// 스레드 구현
UINT ThreadForCounting(LPVOID param)
{
	CRFIDDlg* pMain = (CRFIDDlg*)param;
	while (pMain->m_isWorkingThread)
	{
		Sleep(500);
		pMain->OnReadOnce();
	}
	return 0;
}



void CRFIDDlg::DB_Connect()
{
	conn = mysql_init(NULL);
	mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout_sec);
	conn_result = mysql_real_connect(conn, "127.0.0.1", "root", "1234512345", "test", 3306, NULL, 0);

	if (conn_result == NULL)
	{
		printf("DB Connection Fail");
	}
	else
	{
		printf("DB Connection Success");
		m_info_DB.SetWindowTextW(_T("ON"));
	}
}


void CRFIDDlg::Send_Query(CString temp1)
{
	//sprintf_s(query, 1024, "SELECT * FROM test WHERE pin='43153915'");
	sprintf_s(query, 1024, "SELECT * FROM test WHERE pin='%S' ", temp1);

	mysql_query(conn, "set Names euckr");

	if (mysql_query(conn, query))
	{
		printf("SELECT Fail");
	}

	result = mysql_store_result(conn);

	int fields = mysql_num_fields(result);
	
	
	row = mysql_fetch_row(result);
	
	index[0] = row[0];
	index[1] = row[1];
	index[2] = row[2];
	index[3] = row[3];
	index[4] = row[4];

	if (index[4] == "off")
	{
		sprintf_s(query, 1024, "UPDATE test SET login ='on' WHERE pin = '%S'", temp1);

		if (mysql_query(conn, query))
		{
			printf("error1");
		}
	}
	else if (index[4] == "on")
	{
		sprintf_s(query, 1024, "UPDATE test Set login ='off' WHERE pin = '%S'", temp1);
		if (mysql_query(conn, query))
		{
			printf("error2");
		}
	}
	



	
	printf("\n");
	
}



void CRFIDDlg::Show_Windows()
{

	m_Index1.SetWindowTextW(index[1]);
	m_index2.SetWindowTextW(index[2]);
	if (index[4] == "off")
	{
		m_index3.SetWindowTextW(_T("login"));
	}
	else if(index[4]=="on")
	{
		m_index3.SetWindowTextW(_T("logout"));
	}
	

	CRect rect;
	m_control_picture.GetWindowRect(rect);
	CDC* dc;
	dc = m_control_picture.GetDC();
	CImage image;
	image.Load(index[3]);

	image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
	ReleaseDC(dc);

}


void CRFIDDlg::OnBnClickedEnd()
{
	CDialogEx::OnOK();
	OnDisconnect();
	return;
}


void CRFIDDlg::OnSetDB()
{
	CSetDB dlg;
	dlg.DoModal();
}

