// SetDB.cpp: 구현 파일
//

#include "pch.h"
#include "SetDB.h"

extern CString index[6];
extern MYSQL* conn;

// CSetDB 대화 상자



IMPLEMENT_DYNAMIC(CSetDB, CDialogEx)

CSetDB::CSetDB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETBOX, pParent)
	, m_strName(index[1])
	, m_strPos(index[2])
	, m_strImage(index[3])
	, m_strPin(index[0])
{
}

CSetDB::~CSetDB()
{
}

void CSetDB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strPos);
	DDX_Text(pDX, IDC_EDIT3, m_strImage);
	DDX_Text(pDX, IDC_Pin, m_strPin);
}


BEGIN_MESSAGE_MAP(CSetDB, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &CSetDB::OnBnClickedOk)
	
END_MESSAGE_MAP()


// CSetDB 메시지 처리기




void CSetDB::OnBnClickedOk()
{
	MYSQL* subconn = conn;
	
	CString test = _T("sdfaf");

	UpdateData(TRUE);
	sprintf_s(query, 2048,"UPDATE test SET name ='%S', job ='%S' WHERE Pin ='%S'", 
		m_strName, m_strPos, m_strPin);

	printf("%s",query);

	if (mysql_query(subconn, query))
	{
		printf("update failed\n");
	}

	CDialogEx::OnOK();
}


