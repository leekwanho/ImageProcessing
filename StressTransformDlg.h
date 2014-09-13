#pragma once


// CStressTransformDlg 대화 상자입니다.

class CStressTransformDlg : public CDialog
{
	DECLARE_DYNAMIC(CStressTransformDlg)

public:
	CStressTransformDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStressTransformDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_StartPoint;
	int m_EndPoint;
};
