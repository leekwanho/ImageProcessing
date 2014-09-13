
// ImageProcessingProjectView.cpp : CImageProcessingProjectView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessingProject.h"
#endif

#include "ImageProcessingProjectDoc.h"
#include "ImageProcessingProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingProjectView

IMPLEMENT_DYNCREATE(CImageProcessingProjectView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingProjectView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_SUM_CONSTANT, &CImageProcessingProjectView::OnSumConstant)
	ON_COMMAND(IDM_EQUAL_IMAGE, &CImageProcessingProjectView::OnEqualImage)
	ON_COMMAND(IDM_SUB_CONSTANT, &CImageProcessingProjectView::OnSubConstant)
	ON_COMMAND(IDM_MUL_CONSTANT, &CImageProcessingProjectView::OnMulConstant)
	ON_COMMAND(IDM_DIV_CONSTANT, &CImageProcessingProjectView::OnDivConstant)
	ON_COMMAND(IDM_AND_OPERATE, &CImageProcessingProjectView::OnAndOperate)
	ON_COMMAND(IDM_OR_OPERATE, &CImageProcessingProjectView::OnOrOperate)
	ON_COMMAND(IDM_XOR_OPERATE, &CImageProcessingProjectView::OnXorOperate)
	ON_COMMAND(IDM_NEGA_TRANSFORM, &CImageProcessingProjectView::OnNegaTransform)
	ON_COMMAND(IDM_GAMMA_CORRECTION, &CImageProcessingProjectView::OnGammaCorrection)
	ON_COMMAND(IDM_BINARIZATION, &CImageProcessingProjectView::OnBinarization)
	ON_COMMAND(IDM_STRESS_TRANSFORM, &CImageProcessingProjectView::OnStressTransform)
	ON_COMMAND(IDM_POSTER_RISING, &CImageProcessingProjectView::OnPosterRising)
	ON_COMMAND(IDM_PARABOLA_CAP, &CImageProcessingProjectView::OnParabolaCap)
	ON_COMMAND(IDM_PARABOLA_CUP, &CImageProcessingProjectView::OnParabolaCup)
	ON_COMMAND(IDM_HISTO_STRETCH, &CImageProcessingProjectView::OnHistoStretch)
	ON_COMMAND(IDM_END_IN_SEARCH, &CImageProcessingProjectView::OnEndInSearch)
	ON_COMMAND(IDM_HISTOGRAM, &CImageProcessingProjectView::OnHistogram)
	ON_COMMAND(IDM_HISTO_EQUAL, &CImageProcessingProjectView::OnHistoEqual)
	ON_COMMAND(IDM_EMBOSSING, &CImageProcessingProjectView::OnEmbossing)
	ON_COMMAND(IDM_BLURR, &CImageProcessingProjectView::OnBlurr)
	ON_COMMAND(IDM_GAUSSIAN_FILTER, &CImageProcessingProjectView::OnGaussianFilter)
	ON_COMMAND(IDM_SHARPENING, &CImageProcessingProjectView::OnSharpening)
	ON_COMMAND(IDM_HPF_SHARP, &CImageProcessingProjectView::OnHpfSharp)
	ON_COMMAND(IDM_LPF_SHARP, &CImageProcessingProjectView::OnLpfSharp)
	ON_COMMAND(IDM_BLURR2, &CImageProcessingProjectView::OnBlurr2)
	ON_COMMAND(IDM_DIFF_OPERATOR_HOR, &CImageProcessingProjectView::OnDiffOperatorHor)
	ON_COMMAND(IDM_LOG, &CImageProcessingProjectView::OnLog)
	ON_COMMAND(IDM_PRIWIT_E, &CImageProcessingProjectView::OnPriwitE)
	ON_COMMAND(IDM_KIRSH_E, &CImageProcessingProjectView::OnKirshE)
	ON_COMMAND(IDM_ROBINSON3_E, &CImageProcessingProjectView::OnRobinson3E)
	ON_COMMAND(IDM_ROBINSON5_E, &CImageProcessingProjectView::OnRobinson5E)
	ON_COMMAND(IDM_DOG, &CImageProcessingProjectView::OnDog)
	ON_COMMAND(IDM_HOMOGEN_OPERATOR, &CImageProcessingProjectView::OnHomogenOperator)
	ON_COMMAND(IDM_MINUS_OPERATOR, &CImageProcessingProjectView::OnMinusOperator)
	ON_COMMAND(IDM_MEAN_FILTER, &CImageProcessingProjectView::OnMeanFilter)
	ON_COMMAND(IDM_MEDIAN_FILTER, &CImageProcessingProjectView::OnMedianFilter)
	ON_COMMAND(IDM_ZOOM_IN, &CImageProcessingProjectView::OnZoomIn)
	ON_COMMAND(IDM_NEAREST, &CImageProcessingProjectView::OnNearest)
	ON_COMMAND(IDM_BILINEAR, &CImageProcessingProjectView::OnBilinear)
	ON_COMMAND(IDM_ZOOM_OUT, &CImageProcessingProjectView::OnZoomOut)
	ON_COMMAND(IDM_MEDIAN_SUB, &CImageProcessingProjectView::OnMedianSub)
	ON_COMMAND(IDM_MEAN_SUB, &CImageProcessingProjectView::OnMeanSub)
	ON_COMMAND(IDM_TRANSLATION, &CImageProcessingProjectView::OnTranslation)
	ON_COMMAND(IDM_MIRROR_HOR, &CImageProcessingProjectView::OnMirrorHor)
	ON_COMMAND(IDM_MIRROR_VER, &CImageProcessingProjectView::OnMirrorVer)
	ON_COMMAND(IDM_ROTATION, &CImageProcessingProjectView::OnRotation)
	ON_COMMAND(IDM_ZIP, &CImageProcessingProjectView::OnZip)
	ON_COMMAND(IDM_UNZIP, &CImageProcessingProjectView::OnUnzip)
END_MESSAGE_MAP()

// CImageProcessingProjectView ����/�Ҹ�

CImageProcessingProjectView::CImageProcessingProjectView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingProjectView::~CImageProcessingProjectView()
{
}

BOOL CImageProcessingProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingProjectView �׸���

void CImageProcessingProjectView::OnDraw(CDC* pDC)
{
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	int i,j;
	unsigned char R,G,B;
	for (i=0; i<pDoc->m_height; i++) {
		for (j=0; j<pDoc->m_width; j++) {
			R=G=B=pDoc->m_InputImage[i][j];
			pDC->SetPixel(j+5, i+5, RGB(R,G,B));
		}
	}

	for (i=0; i<pDoc->m_Re_height; i++) {
		for (j=0; j<pDoc->m_Re_width; j++) {
			R=G=B=pDoc->m_OutputImage[i][j];
			pDC->SetPixel(j+pDoc->m_width+10, i+5, RGB(R,G,B));
		}
	}
}


// CImageProcessingProjectView �μ�


void CImageProcessingProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessingProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CImageProcessingProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessingProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessingProjectView ����

#ifdef _DEBUG
void CImageProcessingProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingProjectDoc* CImageProcessingProjectView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingProjectDoc)));
	return (CImageProcessingProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingProjectView �޽��� ó����


void CImageProcessingProjectView::OnSumConstant()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSumConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEqualImage()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnSubConstant()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMulConstant()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMulConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDivConstant()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnAndOperate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnOrOperate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnXorOperate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnNegaTransform()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnGammaCorrection()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBinarization()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnStressTransform()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnPosterRising()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPosterRising();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnParabolaCap()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCap();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnParabolaCup()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCup();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistoStretch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEndInSearch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistogram()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistoEqual()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEmbossing()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBlurr()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnGaussianFilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnSharpening()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHpfSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnLpfSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBlurr2()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr2();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDiffOperatorHor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnLog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLog();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnPriwitE()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPriwitE();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnKirshE()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnKirshE();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRobinson3E()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobinson3E();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRobinson5E()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobinson5E();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDog()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDog();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHomogenOperator()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMinusOperator()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMinusOperator();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMeanFilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMedianFilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZoomIn()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnNearest()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNearest();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBilinear()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZoomOut()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOut();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMedianSub()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianSub();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMeanSub()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanSub();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnTranslation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnTranslation();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMirrorHor()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorHor();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMirrorVer()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorVer();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRotation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotation();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZip()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZip();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnUnzip()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUnzip();
	Invalidate(TRUE);
}
