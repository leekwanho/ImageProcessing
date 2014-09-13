
// ImageProcessingProjectView.h : CImageProcessingProjectView Ŭ������ �������̽�
//

#pragma once


class CImageProcessingProjectView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingProjectView();
	DECLARE_DYNCREATE(CImageProcessingProjectView)

// Ư���Դϴ�.
public:
	CImageProcessingProjectDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CImageProcessingProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSumConstant();
	afx_msg void OnEqualImage();
	afx_msg void OnSubConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	afx_msg void OnNegaTransform();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarization();
	afx_msg void OnStressTransform();
	afx_msg void OnPosterRising();
	afx_msg void OnParabolaCap();
	afx_msg void OnParabolaCup();
	afx_msg void OnHistoStretch();
	afx_msg void OnEndInSearch();
	afx_msg void OnHistogram();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnBlurr2();
	afx_msg void OnDiffOperatorHor();
	afx_msg void OnLog();
	afx_msg void OnPriwitE();
	afx_msg void OnKirshE();
	afx_msg void OnRobinson3E();
	afx_msg void OnRobinson5E();
	afx_msg void OnDog();
	afx_msg void OnHomogenOperator();
	afx_msg void OnMinusOperator();
	afx_msg void OnMeanFilter();
	afx_msg void OnMedianFilter();
	afx_msg void OnZoomIn();
	afx_msg void OnNearest();
	afx_msg void OnBilinear();
	afx_msg void OnZoomOut();
	afx_msg void OnMedianSub();
	afx_msg void OnMeanSub();
	afx_msg void OnTranslation();
	afx_msg void OnMirrorHor();
	afx_msg void OnMirrorVer();
	afx_msg void OnRotation();
	afx_msg void OnZip();
	afx_msg void OnUnzip();
};

#ifndef _DEBUG  // ImageProcessingProjectView.cpp�� ����� ����
inline CImageProcessingProjectDoc* CImageProcessingProjectView::GetDocument() const
   { return reinterpret_cast<CImageProcessingProjectDoc*>(m_pDocument); }
#endif

