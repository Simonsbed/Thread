
// ThreadView.cpp: CThreadView 클래스의 구현
//

#include "stdafx.h"
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Thread.h"
#endif

#include "ThreadDoc.h"
#include "ThreadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CThreadView

IMPLEMENT_DYNCREATE(CThreadView, CView)

BEGIN_MESSAGE_MAP(CThreadView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)


	ON_COMMAND(ID_32771, &CThreadView::OnFindmin)
	ON_MESSAGE(WMMIN, &CThreadView::OnMinFound)
END_MESSAGE_MAP()

// CThreadView 생성/소멸

CThreadView::CThreadView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CThreadView::~CThreadView()
{
}

BOOL CThreadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CThreadView 그리기

void CThreadView::OnDraw(CDC* pDC)
{
	CThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->TextOut(10, 10, pDoc->str);
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CThreadView 인쇄

BOOL CThreadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CThreadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CThreadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CThreadView 진단

#ifdef _DEBUG
void CThreadView::AssertValid() const
{
	CView::AssertValid();
}

void CThreadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CThreadDoc* CThreadView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CThreadDoc)));
	return (CThreadDoc*)m_pDocument;
}
#endif //_DEBUG


// CThreadView 메시지 처리기

UINT MyThread(LPVOID pParam);
UINT MyThread(LPVOID pParam)
{
	SData* pData = (SData*)pParam;
	// Find max 여기에 최대값을 찾는 프로그램을 작성하세요.
	pData->min = pData->array[0];
	for (int i = 1; i < 10; i++)
	{
		if (pData->array[i] < pData->min)
			pData->min = pData->array[i];
	}
	::PostMessage(pData->NotifyWindow, WMMIN, 0, 0);
	return 0;
}


//LRESULT CThreadView::OnMinFound(WPARAM wParam, LPARAM lParam)
//{
//	CThreadDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	CString msg;
//	msg.Format(L"Min of the array = %d", data.min);
//	pDoc->str = msg;
//	TerminateThread(Thread, 0);
//	Invalidate();
//	return 0L;
//}


void CThreadView::OnFindmin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	data.array[0] = 240;
	data.array[1] = 423;
	data.array[2] = 433;
	data.array[3] = 456;
	data.array[4] = 45;
	data.array[5] = 942;
	data.array[6] = 210;
	data.array[7] = 207;
	data.array[8] = 1004;
	data.array[9] = 172;
	data.min = 0;
	data.NotifyWindow = m_hWnd;
	AfxBeginThread(MyThread, &data);
}


afx_msg LRESULT CThreadView::OnMinFound(WPARAM wParam, LPARAM lParam)
{
	CThreadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CString msg;
	msg.Format(L"Min of the array = %d", data.min);
	pDoc->str = msg;
	TerminateThread(Thread, 0);
	Invalidate();
	return 0L;
}
