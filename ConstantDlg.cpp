// ConstantDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessingProject.h"
#include "ConstantDlg.h"
#include "afxdialogex.h"


// CConstantDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CConstantDlg, CDialog)

CConstantDlg::CConstantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConstantDlg::IDD, pParent)
	, m_Constant(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialog)
END_MESSAGE_MAP()


// CConstantDlg 메시지 처리기입니다.
