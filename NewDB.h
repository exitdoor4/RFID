#pragma once
#include "afxdialogex.h"


// CNewDB 대화 상자

class CNewDB : public CDialogEx
{
	DECLARE_DYNAMIC(CNewDB)

public:
	CNewDB(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CNewDB();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWDB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
