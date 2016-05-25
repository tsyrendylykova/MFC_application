#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
    m_nCatched = -1;

    this->model = new MyModel();
}

CChildView::~CChildView()
{
    delete this->model;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEWHEEL()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_BUTTON32771, OnNewFigure)
	ON_WM_ERASEBKGND()
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

    CDC dcMem;
    dcMem.CreateCompatibleDC(&dc);

    CRect rect;
    GetClientRect(&rect);

    CBitmap bmp;
    bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
    CBitmap *pOldBmp = dcMem.SelectObject(&bmp);
    dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), 0xFFFFFF);

    this->model->Draw_buff(dcMem);

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
    dcMem.SelectObject(pOldBmp);
	
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
    ReleaseCapture();
    Invalidate();                    
    CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_nCatched >= 0) {
        CRect rect;
        GetClientRect(&rect);
        point.x = min(rect.right, max(rect.left, point.x));
        point.y = min(rect.bottom, max(rect.top, point.y));
        
        CPoint delta = point - m_MousePos;

        this->model->MoveFigure(m_nCatched, delta.x, delta.y);
        m_MousePos = point;
        Invalidate();  // redraw content
    }
    CWnd::OnMouseMove(nFlags, point);
}

BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{   
    POINT client_point;
    client_point.x = point.x;
    client_point.y = point.y;
    CChildView::ScreenToClient(&client_point);
    int current_figure = this->model->FindObject(client_point.x, client_point.y);
    if (current_figure >= 0) {
        const double PI = 3.141592654;
        const double K = 5;
        double angle = this->model->GetAngle(current_figure);

        angle += (double)zDelta / WHEEL_DELTA * PI / 180 * K;
        if (angle > 2 * PI || angle < -2 * PI) {
            angle = 0;
        }
        
        this->model->Rotate(current_figure, angle);
        Invalidate();  // redraw content
    }
    return CWnd::OnMouseWheel(nFlags, zDelta, point);
}

void CChildView::OnNewFigure() {
    CRect rect;
    GetClientRect(&rect);
    
    this->model->AddFigure(rect.Width(), rect.Height());
    
    Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC){
	// Do not call base class implementation
	// return CWnd::OnEraseBkgnd(pDC);
	return true;
}

void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{    
    int currentFigure = this->model->FindObject(point.x, point.y);
    if (currentFigure >= 0) {
        CDlgProperties dlg(model->GetA(currentFigure), model->GetA1(currentFigure),
            model->GetA2(currentFigure), model->GetA3(currentFigure));
        if (dlg.DoModal()) {
            model->SetA(currentFigure, dlg.A);
            model->SetA1(currentFigure, dlg.A1);
            model->SetA2(currentFigure, dlg.A2);
            model->SetA3(currentFigure, dlg.A3);
            Invalidate();
        };
    }

    CWnd::OnLButtonDblClk(nFlags, point);
}