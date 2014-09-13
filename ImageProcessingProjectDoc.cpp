
// ImageProcessingProjectDoc.cpp : CImageProcessingProjectDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessingProject.h"
#endif

#include "ImageProcessingProjectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingProjectDoc

IMPLEMENT_DYNCREATE(CImageProcessingProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingProjectDoc, CDocument)
	ON_COMMAND(IDM_ZIP, &CImageProcessingProjectDoc::OnZip)
	ON_COMMAND(IDM_UNZIP, &CImageProcessingProjectDoc::OnUnzip)
END_MESSAGE_MAP()


// CImageProcessingProjectDoc 생성/소멸

CImageProcessingProjectDoc::CImageProcessingProjectDoc()
	: m_InputImage(NULL)
	, m_OutputImage(NULL)
	, m_width(0)
	, m_height(0)
	, m_Re_width(0)
	, m_Re_height(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingProjectDoc::~CImageProcessingProjectDoc()
{
}

BOOL CImageProcessingProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessingProjectDoc serialization

void CImageProcessingProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingProjectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingProjectDoc 진단

#ifdef _DEBUG
void CImageProcessingProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingProjectDoc 명령

#include <math.h>

BOOL CImageProcessingProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	double fLength = (double) File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);

	if ( log2Value == (int)log2Value  )
	{
		m_height = m_width = (long)sqrt(fLength);
	} 
	else {
		AfxMessageBox(L"정방향크기의이미지만지원함");
		return 0;
	}

	m_InputImage = new unsigned char* [m_height];
	for (int i=0; i<m_height; i++)
		m_InputImage[i] = new unsigned char [m_width];

	for (int i=0; i<m_height; i++)
		File.Read(m_InputImage[i], m_width);

	File.Close();

	return TRUE;
}


BOOL CImageProcessingProjectDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File;
	CFileDialog  SaveDlg(FALSE, L"raw", NULL, OFN_HIDEREADONLY);

	if(SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		for (int i=0; i<m_Re_height; i++)
			File.Write(m_OutputImage[i], m_Re_width);
		File.Close();
	}
	return true;
}


void CImageProcessingProjectDoc::OnCloseDocument()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int i;
	for (i=0; i<m_height; i++)
		delete m_InputImage[i];
	delete m_InputImage;

	if (m_OutputImage != NULL) {
		for (i=0; i<m_Re_height; i++)
			delete m_OutputImage[i];
		delete m_OutputImage;
	}
	CDocument::OnCloseDocument();
}


void CImageProcessingProjectDoc::OnEqualImage(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_InputImage[i][j];
		}
	}
}


#include "ConstantDlg.h"
#include "StressTransformDlg.h"

void CImageProcessingProjectDoc::OnSumConstant(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] + (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnSubConstant(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] - (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnMulConstant(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] * (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnDivConstant(void)
{

	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] / (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnAndOperate(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] & (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnOrOperate(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] | (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnXorOperate(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = m_InputImage[i][j] ^ (int) dlg.m_Constant;
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnNegaTransform(void)
{
	int i,j;

	m_Re_height=m_height;
	m_Re_width=m_width;

	// 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 영상처리 알고리즘 핵심
	int value;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = 255 - m_InputImage[i][j];
		}
	}

	return;
}


void CImageProcessingProjectDoc::OnGammaCorrection(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				value = pow(m_InputImage[i][j] , (double)(1/ dlg.m_Constant));
				if (value > 255)
					m_OutputImage[i][j] = 255;
				else if (value < 0)
					m_OutputImage[i][j] = 0;
				else
					m_OutputImage[i][j] = value;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnBinarization(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				if (m_InputImage[i][j]>(int) dlg.m_Constant)
					m_OutputImage[i][j] = 255;
				else
					m_OutputImage[i][j] = 0;
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnStressTransform(void)
{
	int i,j;
	CStressTransformDlg dlg;
	if(dlg.DoModal() == IDOK) {

		m_Re_height=m_height;
		m_Re_width=m_width;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int value;
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				if ((int)dlg.m_StartPoint<m_InputImage[i][j] && (int)dlg.m_EndPoint>m_InputImage[i][j])
					m_OutputImage[i][j] = 255;
				else
					m_OutputImage[i][j] = m_InputImage[i][j];
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnPosterRising(void)
{
	int i,j;

	m_Re_height=m_height;
	m_Re_width=m_width;

	// 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 영상처리 알고리즘 핵심
	int value;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_InputImage[i][j]>0 && m_InputImage[i][j]<=50)
				m_OutputImage[i][j] = 0;
			if(m_InputImage[i][j]>50 && m_InputImage[i][j]<=100)
				m_OutputImage[i][j] = 50;
			if(m_InputImage[i][j]>100 && m_InputImage[i][j]<=150)
				m_OutputImage[i][j] = 100;
			if(m_InputImage[i][j]>150 && m_InputImage[i][j]<=200)
				m_OutputImage[i][j] = 150;
			if(m_InputImage[i][j]>200 && m_InputImage[i][j]<=250)
				m_OutputImage[i][j] = 200;
		}
	}

	return;
}


void CImageProcessingProjectDoc::OnParabolaCap(void)
{
	int i,j;

	//룩업 테이블 생성
	double LUT[256]; // 0~255
	for(i=0;i<255;i++){
		LUT[i]=255 - 255* pow( i/128.0 -1 ,2.0 );
		if(LUT[i]>255.0)
			LUT[i]=255.0;
		if(LUT[i]<0.0)
			LUT[i]=0.0;
	}

	m_Re_height=m_height;
	m_Re_width=m_width;

	// 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 영상처리 알고리즘 핵심
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j]=(unsigned char)LUT[m_InputImage[i][j]];

		}
	}

	return;
}


void CImageProcessingProjectDoc::OnParabolaCup(void)
{
	int i,j;

	//룩업 테이블 생성
	double LUT[256]; // 0~255
	for(i=0;i<255;i++){
		LUT[i]=255* pow( i/128.0 -1 ,2.0 );
		if(LUT[i]>255.0)
			LUT[i]=255.0;
		if(LUT[i]<0.0)
			LUT[i]=0.0;
	}

	m_Re_height=m_height;
	m_Re_width=m_width;

	// 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 영상처리 알고리즘 핵심
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j]=(unsigned char)LUT[m_InputImage[i][j]];

		}
	}

	return;
}


void CImageProcessingProjectDoc::OnHistoStretch(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	int MIN,MAX;

	MIN=MAX=m_InputImage[0][0];

	//최대, 최소 명도값 찾기
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			if(m_InputImage[i][j]<MIN)
				MIN=m_InputImage[i][j];
			if(m_InputImage[i][j]>MAX)
				MAX=m_InputImage[i][j];
		}
	}

	//새로운 값 구하기
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = (unsigned char) ((m_InputImage[i][j]-MIN)*255.0 / (MAX-MIN));
		}
	}
}


void CImageProcessingProjectDoc::OnEndInSearch(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	int MIN,MAX;

	MIN=MAX=m_InputImage[0][0];

	//최대, 최소 명도값 찾기
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			if(m_InputImage[i][j]<MIN)
				MIN=m_InputImage[i][j];
			if(m_InputImage[i][j]>MAX)
				MAX=m_InputImage[i][j];
		}
	}

	MIN=MIN+50;
	MAX=MAX-50;

	//새로운 값 구하기
	int value;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			value=m_InputImage[i][j];
			if(value<MIN)
				m_OutputImage[i][j]=0;
			else if(value>MAX)
				m_OutputImage[i][j]=255;
			else
				m_OutputImage[i][j] = (unsigned char) ((m_InputImage[i][j]-MIN)*255.0 / (MAX-MIN));
		}
	}
}

double m_HIST[256];//원본 막대그래프
unsigned char m_Scale_HIST[256];//정규화된 막대그래프
double m_Sum_Of_Hist[256];//누적 그래프

void CImageProcessingProjectDoc::OnHistogram(void)
{
	m_Re_height=256;
	m_Re_width=256;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j,value;
	double MIN,MAX;

	//막대그래프 만들기(빈도수 탐색)
	for(i=0;i<256;i++)
		m_HIST[i]=0;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			value=m_InputImage[i][j];
			m_HIST[value]++;
		}
	}

	//막대그래프 정규화
	MIN=MAX=m_HIST[0];
	for(i=0;i<256;i++){
		if(m_HIST[i]<MIN)
			MIN=m_HIST[i];
		if(m_HIST[i]>MAX)
			MAX=m_HIST[i];
	}

	for(i=0;i<256;i++){
		m_Scale_HIST[i]=(unsigned char)((m_HIST[i]-MIN)*255.0 / (MAX-MIN));
	}

	//막대그래프 출력
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j]=255;
		}
	}

	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Scale_HIST[i]; j++) {
			m_OutputImage[255-j][i]=0;
		}
	}
}


void CImageProcessingProjectDoc::OnHistoEqual(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j,value;
	double SUM=0.0;

	//막대그래프 만들기(빈도수 관찰)
	for(i=0;i<256;i++)
		m_HIST[i]=0;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			value=m_InputImage[i][j];
			m_HIST[value]++;
		}
	}

	//누적막대그래프 sum[i]
	for(i=0;i<256;i++){
		SUM=SUM+m_HIST[i];
		m_Sum_Of_Hist[i]=SUM;
	}

	//정규화된 누적막대 그래프 n[i]=sum[i] * 255 / (m_width*m_height)

	int temp;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			temp=m_InputImage[i][j];
			m_OutputImage[i][j] = (unsigned char)(m_Sum_Of_Hist[temp] * 255.0 / (m_width*m_height));

		}
	}
}

double **m_TempImage;

void CImageProcessingProjectDoc::OnEmbossing(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double EmboMask[3][3]={ {1. , 0. , 0.},
	{0. , 0. , 0.},
	{0. , 0. , -1.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//128더하기 (어두우니까)
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_TempImage[i][j] += 128.0;
		}
	}

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


double** CImageProcessingProjectDoc::OnMaskProcess(double Mask[3][3])
{
	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int i,j;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+2];
	for (i=0; i<m_height+2; i++)
		tempInputImage[i] = new double [m_width+2];

	tempOutputImage = new double* [m_Re_height+2];
	for (i=0; i<m_Re_height+2; i++)
		tempOutputImage[i] = new double [m_Re_width+2];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+1][j+1] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			for(n=0;n<3;n++){
				for(m=0;m<3;m++){
					S=S+ Mask[n][m]*tempInputImage[i+n][j+m];
				}
			}
			tempOutputImage[i][j]=S;
			S=0.0;
		}
	}

	//메모리 해제
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	return tempOutputImage;
}


void CImageProcessingProjectDoc::OnBlurr(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double EmboMask[3][3]={ {1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnGaussianFilter(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double EmboMask[3][3]={ {1./16. , 1./8. , 1./16.},
	{1./8. , 1./4. , 1./8.},
	{1./16. , 1./8. , 1./16.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnSharpening(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double EmboMask[3][3]={ {-1. , -1. , -1.},
	{-1. , 9. , -1.},
	{-1. , -1. , -1.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnHpfSharp(void)
{

	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double EmboMask[3][3]={ {-1./9. , -1./9. , -1./9.},
	{-1./9. , 8./9. , -1./9.},
	{-1./9. , -1./9. , -1./9.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_TempImage[i][j]+=100;
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnLpfSharp(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j; 
	double EmboMask[3][3]={ {1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_TempImage[i][j]=(17*m_InputImage[i][j])-(unsigned char)m_TempImage[i][j];
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnBlurr2(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	int maskSize=7;
	double** Mask;

	//마스크 메모리 할당
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//마스크에 값 대입
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=1.0 / (maskSize * maskSize);
		}
	}

	//회선처리 함수호출
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


double** CImageProcessingProjectDoc::OnMaskProcess2(double** Mask, int mSize)
{
	//가변 크기 계산
	int addPix=(mSize/2)*2;
	int start=addPix/2;

	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int i,j;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+addPix];
	for (i=0; i<m_height+addPix; i++)
		tempInputImage[i] = new double [m_width+addPix];

	//임시 입력 초기화
	for(i=0; i<m_height+addPix; i++) {
		for(j=0; j<m_width+addPix; j++) {
			tempInputImage[i][j] = 127.0;
		}
	}


	tempOutputImage = new double* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		tempOutputImage[i] = new double [m_Re_width];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+start][j+start] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			for(n=0;n<mSize;n++){
				for(m=0;m<mSize;m++){
					S=S+ Mask[n][m]*tempInputImage[i+n][j+m];
				}
			}
			tempOutputImage[i][j]=S;
			S=0.0;
		}
	}

	//메모리 해제
	for(i=0;i<m_height+addPix;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	return tempOutputImage;
}


void CImageProcessingProjectDoc::OnDiffOperatorHor(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double myMask[3][3]={ {0. , -1. , 0.},
	{-1. , 2. , 0.},
	{0. , 0. , 0.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(myMask);


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	//임계값 처리 (옵션)
	int eValue=20;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_OutputImage[i][j]<=eValue)
				m_OutputImage[i][j]=0;
			if(m_OutputImage[i][j]>eValue)
				m_OutputImage[i][j]=255;
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnLog(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	///////////////////////////////////////////////////////////
	int maskSize=5;
	double ConMask[5][5]={{0. , 0. , -1. , 0. , 0.},
	{0. , -1. , -2. , -1. , 0.},
	{-1. , -2. , 16. , -2. , -1.},
	{0. , -1. , -2. , -1. , 0.},
	{0. , 0. , -1. , 0. , 0.} };
	///////////////////////////////////////////////////////////
	double** Mask;

	//마스크 메모리 할당
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//마스크에 값 대입
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=ConMask[i][j];
		}
	}

	//회선처리 함수호출
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}

	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnPriwitE(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double myMask[3][3]={ {1. , 1. , -1.},
	{1. , -2. , -1.},
	{1. , 1. , -1.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(myMask);


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	//임계값 처리 (옵션)
	int eValue=20;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_OutputImage[i][j]<=eValue)
				m_OutputImage[i][j]=0;
			if(m_OutputImage[i][j]>eValue)
				m_OutputImage[i][j]=255;
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnKirshE(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double myMask[3][3]={ {5. , -3. , -3.},
	{5. , 0. , -3.},
	{5. , -3. , -3.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(myMask);


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	//임계값 처리 (옵션)
	int eValue=20;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_OutputImage[i][j]<=eValue)
				m_OutputImage[i][j]=0;
			if(m_OutputImage[i][j]>eValue)
				m_OutputImage[i][j]=255;
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnRobinson3E(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double myMask[3][3]={ {1. , 0. , -1.},
	{1. , 0. , -1.},
	{1. , 0. , -1.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(myMask);


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	//임계값 처리 (옵션)
	int eValue=20;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_OutputImage[i][j]<=eValue)
				m_OutputImage[i][j]=0;
			if(m_OutputImage[i][j]>eValue)
				m_OutputImage[i][j]=255;
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnRobinson5E(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;
	double myMask[3][3]={ {1. , 0. , -1.},
	{2. , 0. , -2.},
	{1. , 0. , -1.} };

	//회선처리 함수호출
	m_TempImage=OnMaskProcess(myMask);


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}


	//임계값 처리 (옵션)
	int eValue=20;
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_OutputImage[i][j]<=eValue)
				m_OutputImage[i][j]=0;
			if(m_OutputImage[i][j]>eValue)
				m_OutputImage[i][j]=255;
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnDog(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	///////////////////////////////////////////////////////////
	int maskSize=7;
	double ConMask[7][7]={{0. , 0. , -1. , -1. , -1. , 0. , 0.},
	{0. , -2. , -3. , -3. , -3. , -2. , 0.},
	{-1. , -3. , 5. , 5. , 5. , -3. , -1.},
	{-1. , -3. , 5. , 16. , 5. , -3. , -1.},
	{-1. , -3. , 5. , 5. , 5. , -3. , -1.},
	{0. , -2. , -3. , -3. , -3. , -2. , 0.},
	{0. , 0. , -1. , -1. , -1. , 0. , 0.},};
	///////////////////////////////////////////////////////////
	double** Mask;

	//마스크 메모리 할당
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//마스크에 값 대입
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=ConMask[i][j];
		}
	}

	//회선처리 함수호출
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(m_TempImage[i][j]>255.0)
				m_TempImage[i][j]=255.0;
			if(m_TempImage[i][j]<0.0)
				m_TempImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = m_TempImage[i][j];
		}
	}

	for(i=0;i<m_Re_height;i++)
		delete m_TempImage[i];
	delete m_TempImage;
}


void CImageProcessingProjectDoc::OnHomogenOperator(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	//회선처리 함수호출
	////////////////////////////////////////////////////////

	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+2];
	for (i=0; i<m_height+2; i++)
		tempInputImage[i] = new double [m_width+2];

	tempOutputImage = new double* [m_Re_height+2];
	for (i=0; i<m_Re_height+2; i++)
		tempOutputImage[i] = new double [m_Re_width+2];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+1][j+1] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMaxValue(tempInputImage,i,j);
		}
	}

	//메모리 해제
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(tempOutputImage[i][j]>255.0)
				tempOutputImage[i][j]=255.0;
			if(tempOutputImage[i][j]<0.0)
				tempOutputImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = tempOutputImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete tempOutputImage[i];
	delete tempOutputImage;

}


double CImageProcessingProjectDoc::FindMaxValue(double** inImage, int x, int y)
{
	int n,m;
	double max=0.0, absValue;

	for(n=0;n<3;n++){
		for(m=0;m<3;m++){
			absValue=fabs(inImage[x+1][y+1]-inImage[x+n][y+m]);
			if(absValue>max)
				max=absValue;
		}
	}

	return max;
}


void CImageProcessingProjectDoc::OnMinusOperator(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	//회선처리 함수호출
	////////////////////////////////////////////////////////

	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+2];
	for (i=0; i<m_height+2; i++)
		tempInputImage[i] = new double [m_width+2];

	tempOutputImage = new double* [m_Re_height+2];
	for (i=0; i<m_Re_height+2; i++)
		tempOutputImage[i] = new double [m_Re_width+2];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+1][j+1] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMaxValue2(tempInputImage,i,j);
		}
	}

	//메모리 해제
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(tempOutputImage[i][j]>255.0)
				tempOutputImage[i][j]=255.0;
			if(tempOutputImage[i][j]<0.0)
				tempOutputImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = tempOutputImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete tempOutputImage[i];
	delete tempOutputImage;
}


double CImageProcessingProjectDoc::FindMaxValue2(double** inImage, int x, int y)
{
	double max=0.0, absValue;

	absValue=fabs(inImage[x][y]-inImage[x+2][y+2]);
	if(absValue>max)
		max=absValue;

	absValue=fabs(inImage[x][y+1]-inImage[x+2][y+1]);
	if(absValue>max)
		max=absValue;

	absValue=fabs(inImage[x][y+2]-inImage[x+2][y]);
	if(absValue>max)
		max=absValue;

	absValue=fabs(inImage[x+1][y+2]-inImage[x+1][y]);
	if(absValue>max)
		max=absValue;

	return max;
}


void CImageProcessingProjectDoc::OnMeanFilter(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	//회선처리 함수호출
	////////////////////////////////////////////////////////

	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+2];
	for (i=0; i<m_height+2; i++)
		tempInputImage[i] = new double [m_width+2];

	tempOutputImage = new double* [m_Re_height+2];
	for (i=0; i<m_Re_height+2; i++)
		tempOutputImage[i] = new double [m_Re_width+2];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+1][j+1] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMeanValue(tempInputImage,i,j);
		}
	}

	//메모리 해제
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(tempOutputImage[i][j]>255.0)
				tempOutputImage[i][j]=255.0;
			if(tempOutputImage[i][j]<0.0)
				tempOutputImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = tempOutputImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete tempOutputImage[i];
	delete tempOutputImage;
}


double CImageProcessingProjectDoc::FindMeanValue(double** inImage, int x, int y)
{
	int n,m;
	double sumValue=0.0;

	for(n=0;n<3;n++){
		for(m=0;m<3;m++){
			sumValue+=inImage[x+n][y+m];
		}
	}

	sumValue=sumValue/9.0;

	return sumValue;
}


void CImageProcessingProjectDoc::OnMedianFilter(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	//회선처리 함수호출
	////////////////////////////////////////////////////////

	//임시 입출력 배열, 마스크 연산 결과
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//메모리 할당
	tempInputImage = new double* [m_height+2];
	for (i=0; i<m_height+2; i++)
		tempInputImage[i] = new double [m_width+2];

	tempOutputImage = new double* [m_Re_height+2];
	for (i=0; i<m_Re_height+2; i++)
		tempOutputImage[i] = new double [m_Re_width+2];

	//m_InputImage-->tempInputImage
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempInputImage[i+1][j+1] = m_InputImage[i][j];
		}
	}

	//진짜 회선 처리
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMedianValue(tempInputImage,i,j);
		}
	}

	//메모리 해제
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255처리
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			if(tempOutputImage[i][j]>255.0)
				tempOutputImage[i][j]=255.0;
			if(tempOutputImage[i][j]<0.0)
				tempOutputImage[i][j]=0.0;
		}
	}


	//tempOutputImage-->m_OutputImage
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_OutputImage[i][j] = tempOutputImage[i][j];
		}
	}


	for(i=0;i<m_Re_height;i++)
		delete tempOutputImage[i];
	delete tempOutputImage;
}


double CImageProcessingProjectDoc::FindMedianValue(double** inImage, int x, int y)
{
	int n,m;
	double tempImage[9];
	double temp=0.0;

	for(n=0;n<3;n++){
		for(m=0;m<3;m++){
			tempImage[n*3 + m]=inImage[x+n][y+m];
		}
	}

	for(n=0;n<9;n++){
		for(m=n;m<9;m++){
			if(tempImage[n]<tempImage[m]){
				temp=tempImage[n];
				tempImage[n]=tempImage[m];
				tempImage[m]=temp;
			}
		}
	}

	return tempImage[4];
}


void CImageProcessingProjectDoc::OnZoomIn(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height*scale;
		m_Re_width=m_width*scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		for(i=0; i<m_height; i++) {
			for(j=0; j<m_width; j++) {
				m_OutputImage[i*scale][j*scale]=m_InputImage[i][j];
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnNearest(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height*scale;
		m_Re_width=m_width*scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				m_OutputImage[i][j]=m_InputImage[i/scale][j/scale];
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnBilinear(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height*scale;
		m_Re_width=m_width*scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		double C1,C2,C3,C4; //입력영상의 네 픽셀값
		double x,y;
		double r_H,r_W;
		int i_H,i_W;
		double N;

		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				r_H=i/(double)scale;
				r_W=j/(double)scale;
				i_H=(int)r_H;
				i_W=(int)r_W;
				x=r_W-i_W;
				y=r_H-i_H;
				if(i_H<0 || i_H>=(m_height-1) || i_W<0 || i_W>=(m_width-1)){
					m_OutputImage[i][j]=255;
				}
				else{
					C1=m_InputImage[i_H][i_W];
					C2=m_InputImage[i_H][i_W+1];
					C3=m_InputImage[i_H+1][i_W+1];
					C4=m_InputImage[i_H+1][i_W];

					N=C1*(1-x)*(1-y) + C2*x*(1-y) + C3*x*y + C4*(1-x)*y;

					m_OutputImage[i][j]=(unsigned char)N;
				}
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnZoomOut(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height/scale;
		m_Re_width=m_width/scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		for(i=0; i<m_height; i++) {
			for(j=0; j<m_width; j++) {
				m_OutputImage[i/scale][j/scale]=m_InputImage[i][j];
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnMedianSub(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height/scale;
		m_Re_width=m_width/scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int mSize=scale;
		double **Mask;
		Mask=new double*[mSize];
		for(i=0;i<mSize;i++)
			Mask[i]=new double[mSize];
		int n,m;

		for(i=0; i<m_height-(mSize/2); i+=mSize) {
			for(j=0; j<m_width-(mSize/2); j+=mSize) {
				//마스크 채우기
				for(n=0;n<mSize;n++){
					for(m=0;m<mSize;m++){
						Mask[n][m]=m_InputImage[i+n][j+m];
					}
				}

				m_OutputImage[i/mSize][j/mSize]=OnFindMedian(Mask,mSize);
			}
		}
	}
	return;
}


unsigned char CImageProcessingProjectDoc::OnFindMedian(double** Mask, int mSize)
{
	int i,j,index=0;
	double *Mask1;
	Mask1=new double[mSize*mSize];

	//2차원-->1차원
	for(i=0;i<mSize;i++)
		for(j=0;j<mSize;j++)
			Mask1[index++]=Mask[i][j];

	//정렬
	double temp;
	for(i=0;i<mSize*mSize;i++){
		for(j=0;j<mSize*mSize-1;j++){
			if(Mask1[j]>Mask1[j+1]){
				temp=Mask1[j];
				Mask1[j]=Mask1[j+1];
				Mask1[j+1]=temp;
			}
		}
	}

	return (unsigned char)Mask1[mSize*mSize/2];
}


void CImageProcessingProjectDoc::OnMeanSub(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int scale=(int)dlg.m_Constant;

		m_Re_height=m_height/scale;
		m_Re_width=m_width/scale;

		// 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 영상처리 알고리즘 핵심
		int mSize=scale;
		double **Mask;
		Mask=new double*[mSize];
		for(i=0;i<mSize;i++)
			Mask[i]=new double[mSize];
		int n,m;

		for(i=0; i<m_height-(mSize/2); i+=mSize) {
			for(j=0; j<m_width-(mSize/2); j+=mSize) {
				//마스크 채우기
				for(n=0;n<mSize;n++){
					for(m=0;m<mSize;m++){
						Mask[n][m]=m_InputImage[i+n][j+m];
					}
				}

				m_OutputImage[i/mSize][j/mSize]=OnFindMean(Mask,mSize);
			}
		}
	}
	return;
}



unsigned char CImageProcessingProjectDoc::OnFindMean(double** Mask, int mSize)
{
	int i,j;
	double mean=0.0;

	//합구하기
	for(i=0;i<mSize;i++){
		for(j=0;j<mSize;j++){
			mean+=Mask[i][j];
		}
	}

	return (unsigned char)(mean/(mSize*mSize));
}


void CImageProcessingProjectDoc::OnTranslation(void)
{
	int i,j;
	CStressTransformDlg dlg;
	if(dlg.DoModal() == IDOK) {
		m_Re_height=m_height;
		m_Re_width=m_width;

		// 출력이미지 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int dx=(int)dlg.m_EndPoint, dy=(int)dlg.m_StartPoint;

		for(i=0; i<m_height; i++) {
			for(j=0; j<m_width; j++) {
				if(i+dx>=0 && i+dx<m_Re_width && i+dy>=0 && j+dy<m_Re_height)
					m_OutputImage[i+dx][j+dy] = m_InputImage[i][j];
			}
		}

	}
	return;

}


void CImageProcessingProjectDoc::OnMirrorHor(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			m_OutputImage[m_height-i-1][j] = m_InputImage[i][j];
		}
	}
}


void CImageProcessingProjectDoc::OnMirrorVer(void)
{

	m_Re_height=m_height;
	m_Re_width=m_width;

	// 출력이미지 메모리 할당
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// 출력 이미지 영상 처리 <핵심 알고리즘>
	int i,j;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			m_OutputImage[i][m_width-j-1] = m_InputImage[i][j];
		}
	}
}


void CImageProcessingProjectDoc::OnRotation(void)
{
	int i,j;
	CConstantDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int angle=dlg.m_Constant;
		double r=angle*3.141592/180.0;
		double r90=(90-angle)*3.141592/180.0;

		m_Re_height=m_height*cos(r) + m_width*cos(r90); 
		m_Re_width=m_height*cos(r90) + m_width*cos(r);

		// 출력이미지 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];


		for(i=0; i<m_Re_height; i++) 
			for(j=0; j<m_Re_width; j++) 
				m_OutputImage[i][j]=255;

		//임시 입력 이미지
		m_TempImage = new double* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_TempImage[i] = new double [m_Re_width];
		for(i=0; i<m_Re_height; i++) 
			for(j=0; j<m_Re_width; j++) 
				m_TempImage[i][j]=255;

		//원영상 ---> 임시
		int dx=(m_Re_height - m_height)/2;
		int dy=(m_Re_width - m_width)/2;

		for(i=0; i<m_height; i++) 
			for(j=0; j<m_width; j++)
				m_TempImage[i+dx][j+dy] = m_InputImage[i][j];

		// 출력 이미지 영상 처리 <핵심 알고리즘>
		int x,y,xd,yd;
		int cx=m_Re_height/2 , cy=m_Re_width/2;


		for(i=0; i<m_Re_height; i++) {
			for(j=0; j<m_Re_width; j++) {
				x=i;
				y=j;
				xd=((x-cx)*cos(r) + (y-cy)*sin(r)) + cx;
				yd=(-(x-cx)*sin(r) + (y-cy)*cos(r)) + cy;
				if(xd>=0 && xd<m_Re_width && yd>=0 && yd<m_Re_height)
					m_OutputImage[x][y] = m_TempImage[xd][yd];
			}
		}
	}
	return;
}


void CImageProcessingProjectDoc::OnZip()
{
	int i,j;

	//one의 크기 : m_Input 폭x높이
	//one,zip 포인터 준비 및 메모리 할당
	unsigned char *one,*zip;
	one=new unsigned char[m_height*m_width];
	zip=new unsigned char[m_height*m_width*2];

	//one첨자 : index
	//m_InputImage --> one
	int index=0;
	for(i=0;i<m_height;i++)
		for(j=0;j<m_width;j++){
			one[index++]=m_InputImage[i][j];
		}

	unsigned char px1,px2;
	int count=1;
	px1=one[0];
	//압축하기
	index=0;
	for(i=1;i<m_height*m_width;i++){
		px2=one[i];
		//반복 : one의 개수만큼 for(i=1;i<one크기;i++)
		//1. px1과 px2가 다르면 zip에 저장
		//2. count가 255가 넘으면 zip에 저장
		//3. i가 one의 끝에 다다르면 zip에 저장
		if(px1!=px2 || count>=255 || i>=m_height*m_width-1){
			zip[index]=px1;
			zip[index+1]=count;
			count=1;
			px1=px2;
			index+=2;
		}
		else{
			//zip의 크기를 계속 카운트(index)
			count++;
			px1=px2;
		}
	}


	//zip의 크기만큼 저장
	CFile File;
	CFileDialog SaveDlg(FALSE,L"zup",NULL,OFN_HIDEREADONLY);
	if(SaveDlg.DoModal()==IDOK){
		File.Open(SaveDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
		File.Write(zip,index-2);
		File.Close();
		AfxMessageBox(L"저장 되었습니다.",NULL,NULL);
	}

	delete one,zip;
}


void CImageProcessingProjectDoc::OnUnzip()
{
	
	// 출력 이미지 영상 처리 <핵심 알고리즘>
	//압축 파일 선택
	CFile File;
	CFileDialog OpenDlg(TRUE);
	if(OpenDlg.DoModal()==IDOK){
		File.Open(OpenDlg.GetFileName(),CFile::modeRead);
		int iLen=File.GetLength();

		unsigned char *one,*zip;
		one=new unsigned char[m_height*m_width];
		zip=new unsigned char[iLen];

		File.Read(zip,iLen);
		File.Close();

		int index=0;
		for(int i=0;i<iLen;i+=2){
			int value=zip[i];
			int count=zip[i+1];
			for(int j=0;j<count;j++){
				one[index++]=value;
			}
		}

		m_Re_height=m_Re_width=(int)sqrt((double)index+2);

		// 출력이미지 메모리 할당
		m_OutputImage = new unsigned char* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];


		index=0;
		for(int i=0;i<m_Re_height;i++){
			for(int j=0;j<m_Re_width;j++){
				m_OutputImage[i][j]=one[index++];
			}
		}

		delete one,zip;
	}

}
