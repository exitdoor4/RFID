// NewDB.cpp: 구현 파일
//


#include "RFID.h"
#include "framework.h"
#include "afxdialogex.h"
#include "NewDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNewDB 대화 상자

IMPLEMENT_DYNAMIC(CNewDB, CDialogEx)

CNewDB::CNewDB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEWDB, pParent)
{

}

CNewDB::~CNewDB()
{
}

void CNewDB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewDB, CDialogEx)
END_MESSAGE_MAP()


// CNewDB 메시지 처리기
