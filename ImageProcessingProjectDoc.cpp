
// ImageProcessingProjectDoc.cpp : CImageProcessingProjectDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CImageProcessingProjectDoc ����/�Ҹ�

CImageProcessingProjectDoc::CImageProcessingProjectDoc()
	: m_InputImage(NULL)
	, m_OutputImage(NULL)
	, m_width(0)
	, m_height(0)
	, m_Re_width(0)
	, m_Re_height(0)
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingProjectDoc::~CImageProcessingProjectDoc()
{
}

BOOL CImageProcessingProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingProjectDoc serialization

void CImageProcessingProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessingProjectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageProcessingProjectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingProjectDoc ����

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


// CImageProcessingProjectDoc ���

#include <math.h>

BOOL CImageProcessingProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	double fLength = (double) File.GetLength();
	double log2Value = log(sqrt(fLength)) / log(2.0);

	if ( log2Value == (int)log2Value  )
	{
		m_height = m_width = (long)sqrt(fLength);
	} 
	else {
		AfxMessageBox(L"������ũ�����̹�����������");
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

	// �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

	// �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ����ó�� �˰��� �ٽ�
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

	//��� ���̺� ����
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

	// �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ����ó�� �˰��� �ٽ�
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

	//��� ���̺� ����
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

	// �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ����ó�� �˰��� �ٽ�
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	int MIN,MAX;

	MIN=MAX=m_InputImage[0][0];

	//�ִ�, �ּ� ���� ã��
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			if(m_InputImage[i][j]<MIN)
				MIN=m_InputImage[i][j];
			if(m_InputImage[i][j]>MAX)
				MAX=m_InputImage[i][j];
		}
	}

	//���ο� �� ���ϱ�
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	int MIN,MAX;

	MIN=MAX=m_InputImage[0][0];

	//�ִ�, �ּ� ���� ã��
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

	//���ο� �� ���ϱ�
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

double m_HIST[256];//���� ����׷���
unsigned char m_Scale_HIST[256];//����ȭ�� ����׷���
double m_Sum_Of_Hist[256];//���� �׷���

void CImageProcessingProjectDoc::OnHistogram(void)
{
	m_Re_height=256;
	m_Re_width=256;

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j,value;
	double MIN,MAX;

	//����׷��� �����(�󵵼� Ž��)
	for(i=0;i<256;i++)
		m_HIST[i]=0;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			value=m_InputImage[i][j];
			m_HIST[value]++;
		}
	}

	//����׷��� ����ȭ
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

	//����׷��� ���
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j,value;
	double SUM=0.0;

	//����׷��� �����(�󵵼� ����)
	for(i=0;i<256;i++)
		m_HIST[i]=0;

	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			value=m_InputImage[i][j];
			m_HIST[value]++;
		}
	}

	//��������׷��� sum[i]
	for(i=0;i<256;i++){
		SUM=SUM+m_HIST[i];
		m_Sum_Of_Hist[i]=SUM;
	}

	//����ȭ�� �������� �׷��� n[i]=sum[i] * 255 / (m_width*m_height)

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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double EmboMask[3][3]={ {1. , 0. , 0.},
	{0. , 0. , 0.},
	{0. , 0. , -1.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//128���ϱ� (��ο�ϱ�)
	for(i=0; i<m_Re_height; i++) {
		for(j=0; j<m_Re_width; j++) {
			m_TempImage[i][j] += 128.0;
		}
	}

	//0~255ó��
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
	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int i,j;
	int n,m;

	//�޸� �Ҵ�
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

	//��¥ ȸ�� ó��
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

	//�޸� ����
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	return tempOutputImage;
}


void CImageProcessingProjectDoc::OnBlurr(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double EmboMask[3][3]={ {1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double EmboMask[3][3]={ {1./16. , 1./8. , 1./16.},
	{1./8. , 1./4. , 1./8.},
	{1./16. , 1./8. , 1./16.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double EmboMask[3][3]={ {-1. , -1. , -1.},
	{-1. , 9. , -1.},
	{-1. , -1. , -1.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double EmboMask[3][3]={ {-1./9. , -1./9. , -1./9.},
	{-1./9. , 8./9. , -1./9.},
	{-1./9. , -1./9. , -1./9.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j; 
	double EmboMask[3][3]={ {1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.},
	{1./9. , 1./9. , 1./9.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(EmboMask);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;

	int maskSize=7;
	double** Mask;

	//����ũ �޸� �Ҵ�
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//����ũ�� �� ����
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=1.0 / (maskSize * maskSize);
		}
	}

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255ó��
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
	//���� ũ�� ���
	int addPix=(mSize/2)*2;
	int start=addPix/2;

	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int i,j;
	int n,m;

	//�޸� �Ҵ�
	tempInputImage = new double* [m_height+addPix];
	for (i=0; i<m_height+addPix; i++)
		tempInputImage[i] = new double [m_width+addPix];

	//�ӽ� �Է� �ʱ�ȭ
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

	//��¥ ȸ�� ó��
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

	//�޸� ����
	for(i=0;i<m_height+addPix;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	return tempOutputImage;
}


void CImageProcessingProjectDoc::OnDiffOperatorHor(void)
{
	m_Re_height=m_height;
	m_Re_width=m_width;


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double myMask[3][3]={ {0. , -1. , 0.},
	{-1. , 2. , 0.},
	{0. , 0. , 0.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(myMask);


	//0~255ó��
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


	//�Ӱ谪 ó�� (�ɼ�)
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

	//����ũ �޸� �Ҵ�
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//����ũ�� �� ����
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=ConMask[i][j];
		}
	}

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double myMask[3][3]={ {1. , 1. , -1.},
	{1. , -2. , -1.},
	{1. , 1. , -1.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(myMask);


	//0~255ó��
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


	//�Ӱ谪 ó�� (�ɼ�)
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double myMask[3][3]={ {5. , -3. , -3.},
	{5. , 0. , -3.},
	{5. , -3. , -3.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(myMask);


	//0~255ó��
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


	//�Ӱ谪 ó�� (�ɼ�)
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double myMask[3][3]={ {1. , 0. , -1.},
	{1. , 0. , -1.},
	{1. , 0. , -1.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(myMask);


	//0~255ó��
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


	//�Ӱ谪 ó�� (�ɼ�)
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;
	double myMask[3][3]={ {1. , 0. , -1.},
	{2. , 0. , -2.},
	{1. , 0. , -1.} };

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess(myMask);


	//0~255ó��
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


	//�Ӱ谪 ó�� (�ɼ�)
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

	//����ũ �޸� �Ҵ�
	Mask=new double* [maskSize];
	for(i=0;i<maskSize;i++)
		Mask[i]=new double [maskSize];

	//����ũ�� �� ����
	for(i=0; i<maskSize; i++) {
		for(j=0; j<maskSize; j++) {
			Mask[i][j]=ConMask[i][j];
		}
	}

	//ȸ��ó�� �Լ�ȣ��
	m_TempImage=OnMaskProcess2(Mask,maskSize);

	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;

	//ȸ��ó�� �Լ�ȣ��
	////////////////////////////////////////////////////////

	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//�޸� �Ҵ�
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

	//��¥ ȸ�� ó��
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMaxValue(tempInputImage,i,j);
		}
	}

	//�޸� ����
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;

	//ȸ��ó�� �Լ�ȣ��
	////////////////////////////////////////////////////////

	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//�޸� �Ҵ�
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

	//��¥ ȸ�� ó��
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMaxValue2(tempInputImage,i,j);
		}
	}

	//�޸� ����
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;

	//ȸ��ó�� �Լ�ȣ��
	////////////////////////////////////////////////////////

	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//�޸� �Ҵ�
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

	//��¥ ȸ�� ó��
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMeanValue(tempInputImage,i,j);
		}
	}

	//�޸� ����
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255ó��
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


	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];


	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	int i,j;

	//ȸ��ó�� �Լ�ȣ��
	////////////////////////////////////////////////////////

	//�ӽ� ����� �迭, ����ũ ���� ���
	double **tempInputImage,**tempOutputImage,S=0.0;
	int n,m;

	//�޸� �Ҵ�
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

	//��¥ ȸ�� ó��
	for(i=0; i<m_height; i++) {
		for(j=0; j<m_width; j++) {
			tempOutputImage[i][j]=FindMedianValue(tempInputImage,i,j);
		}
	}

	//�޸� ����
	for(i=0;i<m_height+2;i++)
		delete tempInputImage[i];
	delete tempInputImage;

	////////////////////////////////////////////////////////


	//0~255ó��
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
		double C1,C2,C3,C4; //�Է¿����� �� �ȼ���
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
		int mSize=scale;
		double **Mask;
		Mask=new double*[mSize];
		for(i=0;i<mSize;i++)
			Mask[i]=new double[mSize];
		int n,m;

		for(i=0; i<m_height-(mSize/2); i+=mSize) {
			for(j=0; j<m_width-(mSize/2); j+=mSize) {
				//����ũ ä���
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

	//2����-->1����
	for(i=0;i<mSize;i++)
		for(j=0;j<mSize;j++)
			Mask1[index++]=Mask[i][j];

	//����
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

		// �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ����ó�� �˰��� �ٽ�
		int mSize=scale;
		double **Mask;
		Mask=new double*[mSize];
		for(i=0;i<mSize;i++)
			Mask[i]=new double[mSize];
		int n,m;

		for(i=0; i<m_height-(mSize/2); i+=mSize) {
			for(j=0; j<m_width-(mSize/2); j+=mSize) {
				//����ũ ä���
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

	//�ձ��ϱ�
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

		// ����̹��� �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];

		// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

	// ����̹��� �޸� �Ҵ�
	m_OutputImage = new unsigned char* [m_Re_height];
	for (int i=0; i<m_Re_height; i++)
		m_OutputImage[i] = new unsigned char [m_Re_width];

	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

		// ����̹��� �޸� �Ҵ�
		m_OutputImage = new unsigned char* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_OutputImage[i] = new unsigned char [m_Re_width];


		for(i=0; i<m_Re_height; i++) 
			for(j=0; j<m_Re_width; j++) 
				m_OutputImage[i][j]=255;

		//�ӽ� �Է� �̹���
		m_TempImage = new double* [m_Re_height];
		for (int i=0; i<m_Re_height; i++)
			m_TempImage[i] = new double [m_Re_width];
		for(i=0; i<m_Re_height; i++) 
			for(j=0; j<m_Re_width; j++) 
				m_TempImage[i][j]=255;

		//������ ---> �ӽ�
		int dx=(m_Re_height - m_height)/2;
		int dy=(m_Re_width - m_width)/2;

		for(i=0; i<m_height; i++) 
			for(j=0; j<m_width; j++)
				m_TempImage[i+dx][j+dy] = m_InputImage[i][j];

		// ��� �̹��� ���� ó�� <�ٽ� �˰���>
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

	//one�� ũ�� : m_Input ��x����
	//one,zip ������ �غ� �� �޸� �Ҵ�
	unsigned char *one,*zip;
	one=new unsigned char[m_height*m_width];
	zip=new unsigned char[m_height*m_width*2];

	//one÷�� : index
	//m_InputImage --> one
	int index=0;
	for(i=0;i<m_height;i++)
		for(j=0;j<m_width;j++){
			one[index++]=m_InputImage[i][j];
		}

	unsigned char px1,px2;
	int count=1;
	px1=one[0];
	//�����ϱ�
	index=0;
	for(i=1;i<m_height*m_width;i++){
		px2=one[i];
		//�ݺ� : one�� ������ŭ for(i=1;i<oneũ��;i++)
		//1. px1�� px2�� �ٸ��� zip�� ����
		//2. count�� 255�� ������ zip�� ����
		//3. i�� one�� ���� �ٴٸ��� zip�� ����
		if(px1!=px2 || count>=255 || i>=m_height*m_width-1){
			zip[index]=px1;
			zip[index+1]=count;
			count=1;
			px1=px2;
			index+=2;
		}
		else{
			//zip�� ũ�⸦ ��� ī��Ʈ(index)
			count++;
			px1=px2;
		}
	}


	//zip�� ũ�⸸ŭ ����
	CFile File;
	CFileDialog SaveDlg(FALSE,L"zup",NULL,OFN_HIDEREADONLY);
	if(SaveDlg.DoModal()==IDOK){
		File.Open(SaveDlg.GetPathName(),CFile::modeCreate | CFile::modeWrite);
		File.Write(zip,index-2);
		File.Close();
		AfxMessageBox(L"���� �Ǿ����ϴ�.",NULL,NULL);
	}

	delete one,zip;
}


void CImageProcessingProjectDoc::OnUnzip()
{
	
	// ��� �̹��� ���� ó�� <�ٽ� �˰���>
	//���� ���� ����
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

		// ����̹��� �޸� �Ҵ�
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
