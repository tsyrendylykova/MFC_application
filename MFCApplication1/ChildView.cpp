#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _USE_MATH_DEFINES
#include <math.h>

CChildView::CChildView()
{
    m_nCatched = -1; // initialization
}

CChildView::~CChildView()
{
    // clear the memory allocated for the circles
    for (int i = 0; m_Objects.size(); i++) {
        delete m_Objects[i];
    }
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
    CMy2DPoint center(200, 200);
    CMy2DObjectB11 figure, figure2;

    figure.SetA(240);
    figure.SetA1(120);
    figure.SetA2(80);
    figure.SetA3(40);
    figure.SetCenter(center);
    figure.SetAngle(0);

    for (int i = 0; i < m_Objects.size(); i++) {
        m_Objects[i]->Draw(dc);
    }
}
int CChildView::FindObject(CPoint point) {
    int nObj = -1;
    for (int i = m_Objects.size() - 1; i >= 0; i--) {
        if (m_Objects[i]->IsInside(point.x, point.y)) {
            nObj = i;
            break;
        }
    }
    return nObj;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_nCatched = FindObject(point);
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
    if (m_nCatched >= 0) {
        CRect rect;
        GetClientRect(&rect);
        point.x = min(rect.right, max(rect.left, point.x));
        point.y = min(rect.bottom, max(rect.top, point.y));
        CPoint Delta = point - m_MousePos;
        m_Objects[m_nCatched]->Move(Delta.x, Delta.y);
        m_MousePos = point;
        Invalidate();  // redraw content
    }
    CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnNewFigure() {
    MessageBox(L"Привет");
    
    /*CRect rect;
    GetClientRect(&rect);
    m_Objects.push_back(new CMy2DObjectB11(rand() % rect.Width(), rand() % rect.Height(), 6, 3, 2, 1, 0));
    Invalidate();*/
}
