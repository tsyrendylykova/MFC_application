#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
    m_nCatched = -1; // initialization

    this->model = new MyModel();
}

CChildView::~CChildView()
{
    delete this->model;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_BUTTON32771, OnNewFigure)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() {
    CPaintDC dc(this);

    this->model->Draw(dc);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_nCatched = this->model->FindObject(point.x, point.y);
    if (m_nCatched >= 0) {
        m_MousePos = point;
        SetCapture();   // the window will handle the mouse message
                        // even if the mouse is outside the window
    }

    CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
    m_nCatched = -1;
    ReleaseCapture();   // the window will not handle the mouse message
                        // when the mouse is outside the window
    CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    //if (m_nCatched >= 0) {
    //    CRect rect;
    //    GetClientRect(&rect);
    //    point.x = min(rect.right, max(rect.left, point.x));
    //    point.y = min(rect.bottom, max(rect.top, point.y));
    //    CPoint Delta = point - m_MousePos;
    //    m_Objects[m_nCatched]->Move(Delta.x, Delta.y);
    //    m_MousePos = point;
    //    Invalidate();  // redraw content
    //}
    CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnNewFigure() {
    CRect rect;
    GetClientRect(&rect);
    
    this->model->AddFigure(rect.Width(), rect.Height());
    
    Invalidate();
}
