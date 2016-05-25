#pragma once
#include "MyModel.h"
#include "DlgProperties.h"
// CChildView window

class CChildView : public CWnd
{
    MyModel *model;

    // Construction
public:
    CChildView();

    // Attributes
public:

    // Operations
public:

    // Overrides
protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    int m_nCatched;
    CPoint m_MousePos;

    // Implementation
public:
    virtual ~CChildView();

    // Generated message map functions
protected:
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
    afx_msg void OnNewFigure();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

