#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgProperties.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDlgProperties, CDialogEx)

CDlgProperties::CDlgProperties(double m_A, double m_A1, double m_A2, double m_A3, CWnd* pParent /*=NULL*/)
    : CDialogEx(CDlgProperties::IDD, pParent)
    , A(m_A)
    , A1(m_A1)
    , A2(m_A2)
    , A3(m_A3)
{
}

CDlgProperties::~CDlgProperties()
{
}

void CDlgProperties::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, A);
    DDX_Text(pDX, IDC_EDIT2, A1);
    DDX_Text(pDX, IDC_EDIT3, A2);
    DDX_Text(pDX, IDC_EDIT4, A3);
}


BEGIN_MESSAGE_MAP(CDlgProperties, CDialogEx)
END_MESSAGE_MAP()


BOOL CDlgProperties::OnInitDialog() {

    CDialogEx::OnInitDialog();
    CString str;

    str.Format(_T("%.2lf"), A);
    SetDlgItemText(IDC_EDIT1, str);
    
    str.Format(_T("%.2lf"), A1);
    SetDlgItemText(IDC_EDIT2, str);
    
    str.Format(_T("%.2lf"), A2);
    SetDlgItemText(IDC_EDIT3, str);
    
    str.Format(_T("%.2lf"), A3);
    SetDlgItemText(IDC_EDIT4, str);
    
    //str.Format(_T("%.2lf"), Angle);
    //SetDlgItemText(IDC_Angle, str);

    return TRUE;
}

void CDlgProperties::OnOK() {

    CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
    CString str;
    
    pEdit->GetWindowText(str);
    A = _wtof(str);

    CDialog::OnOK();
}