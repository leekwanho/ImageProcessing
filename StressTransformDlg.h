#pragma once


// CStressTransformDlg ��ȭ �����Դϴ�.

class CStressTransformDlg : public CDialog
{
	DECLARE_DYNAMIC(CStressTransformDlg)

public:
	CStressTransformDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStressTransformDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_StartPoint;
	int m_EndPoint;
};
