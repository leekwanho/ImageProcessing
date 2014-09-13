// StressTransformDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessingProject.h"
#include "StressTransformDlg.h"
#include "afxdialogex.h"


// CStressTransformDlg ��ȭ �����Դϴ�.

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


// CStressTransformDlg �޽��� ó�����Դϴ�.
