
// RFIDDlg.h: 헤더 파일
//

#pragma once
#include "is_d2xx.h"
#include <mysql.h>



// CRFIDDlg 대화 상자
class CRFIDDlg : public CDialogEx
{
// 생성입니다.
public:
	CRFIDDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CRFIDDlg();
	
	IS_HANDLE ftHandle = 0;
	char readSerialNumber[100] = "COM07";
	char changeSerialNumber[100] = "RFID01";
	short usbnumber;
	unsigned char writeData[1024];
	unsigned short writeLength = 0;
	unsigned char readData[1024];
	unsigned short readLength = 0;
	
	MYSQL* conn_result;
	unsigned int timeout_sec = 1;
	MYSQL_RES* result;
	MYSQL_ROW row;
	char query[1024];

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RFID_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strRfid;
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	CStatic m_info_RFID;
	CStatic m_info_DB;
	afx_msg void OnReadOnce();

	CWinThread* m_pThread;
	bool m_isWorkingThread;

	void DB_Connect();
	void Send_Query(CString temp);
	CStatic m_Index1;
	CStatic m_index2;
	CStatic m_index3;
	afx_msg void Show_Windows();
	int image_flag;
	CStatic m_control_picture;
	afx_msg void OnBnClickedEnd();
	afx_msg void OnSetDB();
	CString temp1;

	
//	CButton m_strCtrl;
	CButton strctrl;
};

UINT ThreadForCounting(LPVOID param);
class CSetDB;


