#pragma once


// CConstantDlg ��ȭ �����Դϴ�.

class CConstantDlg : public CDialog
{
	DECLARE_DYNAMIC(CConstantDlg)

public:
	CConstantDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CConstantDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
