#pragma once

class CDlgProperties : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgProperties)

public:
    CDlgProperties(double A, double A1, double A2, double A3, CWnd* pParent = NULL);   // standard constructor
    virtual ~CDlgProperties();

    // Dialog Data
    enum { IDD = IDD_PROP};

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();
    void OnOK();

    DECLARE_MESSAGE_MAP()
public:
    double A;
    double A1;
    double A2;
    double A3;
};
