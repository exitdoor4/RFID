#pragma once
#include "afxdialogex.h"
#include "RFID.h"
#include "RFIDDlg.h"
#include <mysql.h>

// CSetDB 대화 상자

class CSetDB : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDB)

public:
	CSetDB(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSetDB();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	CString m_strName;
	CString m_strPos;
	CString m_strImage;
	afx_msg void OnBnClickedOk();
	CString m_strPin;
	char query[2048];

};
