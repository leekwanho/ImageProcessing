
// ImageProcessingProjectDoc.h : CImageProcessingProjectDoc Ŭ������ �������̽�
//


#pragma once


class CImageProcessingProjectDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingProjectDoc();
	DECLARE_DYNCREATE(CImageProcessingProjectDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageProcessingProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char**m_InputImage;
	unsigned char**m_OutputImage;
	int m_width;
	int m_height;
	int m_Re_width;
	int m_Re_height;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnSumConstant(void);
	void OnEqualImage(void);
	void OnSubConstant(void);
	void OnMulConstant(void);
	void OnDivConstant(void);
	void OnAndOperate(void);
	void OnOrOperate(void);
	void OnXorOperate(void);
	void OnNegaTransform(void);
	void OnGammaCorrection(void);
	void OnBinarization(void);
	void OnStressTransform(void);
	void OnPosterRising(void);
	void OnParabolaCap(void);
	void OnParabolaCup(void);
	void OnHistoStretch(void);
	void OnEndInSearch(void);
	void OnHistogram(void);
	void OnHistoEqual(void);
	void OnEmbossing(void);
	double** OnMaskProcess(double Mask[3][3]);
	void OnBlurr(void);
	void OnGaussianFilter(void);
	void OnSharpening(void);
	void OnHpfSharp(void);
	void OnLpfSharp(void);
	void OnBlurr2(void);
	double** OnMaskProcess2(double** Mask, int mSize);
	void OnDiffOperatorHor(void);
	void OnLog(void);
	void OnPriwitE(void);
	void OnKirshE(void);
	void OnRobinson3E(void);
	void OnRobinson5E(void);
	void OnDog(void);
	void OnHomogenOperator(void);
	double FindMaxValue(double** inImage, int x, int y);
	void OnMinusOperator(void);
	double FindMaxValue2(double** inImage, int x, int y);
	void OnMeanFilter(void);
	double FindMeanValue(double** inImage, int x, int y);
	void OnMedianFilter(void);
	double FindMedianValue(double** inImage, int x, int y);
	void OnZoomIn(void);
	void OnNearest(void);
	void OnBilinear(void);
	void OnZoomOut(void);
	void OnMedianSub(void);
	void OnMeanSub(void);
	unsigned char OnFindMedian(double** Mask, int mSize);
	unsigned char OnFindMean(double** Mask, int mSize);
	void OnTranslation(void);
	void OnMirrorHor(void);
	void OnMirrorVer(void);
	void OnRotation(void);
	afx_msg void OnZip();
	afx_msg void OnUnzip();
};
