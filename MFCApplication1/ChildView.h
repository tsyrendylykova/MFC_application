#pragma once
#include "My2DObjectB11.h"
#include <vector>
// CChildView window

class CChildView : public CWnd
{
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
    std::vector<CMy2DObjectB11 *> m_Objects;
    int m_nCatched;
    CPoint m_MousePos;

    // if the point is inside of a figure,
    // the function will return its number, otherwise -1
    int FindObject(CPoint point);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnNewFigure();
};

