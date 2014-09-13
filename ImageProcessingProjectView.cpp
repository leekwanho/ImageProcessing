
// ImageProcessingProjectView.cpp : CImageProcessingProjectView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CImageProcessingProjectView 생성/소멸

CImageProcessingProjectView::CImageProcessingProjectView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingProjectView::~CImageProcessingProjectView()
{
}

BOOL CImageProcessingProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingProjectView 그리기

void CImageProcessingProjectView::OnDraw(CDC* pDC)
{
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
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


// CImageProcessingProjectView 인쇄


void CImageProcessingProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CImageProcessingProjectView 진단

#ifdef _DEBUG
void CImageProcessingProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingProjectDoc* CImageProcessingProjectView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingProjectDoc)));
	return (CImageProcessingProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingProjectView 메시지 처리기


void CImageProcessingProjectView::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSumConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEqualImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEqualImage();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMulConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnStressTransform();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnPosterRising()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPosterRising();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnParabolaCap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCap();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnParabolaCup()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnParabolaCup();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHistoEqual()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnEmbossing()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnGaussianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpening();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBlurr2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr2();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDiffOperatorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnLog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLog();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnPriwitE()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPriwitE();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnKirshE()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnKirshE();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRobinson3E()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobinson3E();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRobinson5E()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRobinson5E();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnDog()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDog();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnHomogenOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMinusOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMinusOperator();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMeanFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMedianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianFilter();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZoomIn()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnNearest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNearest();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnBilinear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZoomOut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZoomOut();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMedianSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianSub();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMeanSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanSub();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnTranslation();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMirrorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorHor();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnMirrorVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorVer();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnRotation();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnZip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnZip();
	Invalidate(TRUE);
}


void CImageProcessingProjectView::OnUnzip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessingProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUnzip();
	Invalidate(TRUE);
}
