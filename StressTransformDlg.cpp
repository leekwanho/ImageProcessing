// StressTransformDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessingProject.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// CStressTransformDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStressTransformDlg, CDialog)

CStressTransformDlg::CStressTransformDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStressTransformDlg::IDD, pParent)
	, m_StartPoint(0)
	, m_EndPoint(0)
{

}

CStressTransformDlg::~CStressTransformDlg()
{
}

void CStressTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StartPoint);
	DDX_Text(pDX, IDC_EDIT2, m_EndPoint);
}


BEGIN_MESSAGE_MAP(CStressTransformDlg, CDialog)
END_MESSAGE_MAP()


// CStressTransformDlg 메시지 처리기입니다.
