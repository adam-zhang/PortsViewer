#pragma once
#include "afxcmn.h"


// CTcpTableControl dialog

class CTcpTableControl : public CDialog
{
	DECLARE_DYNAMIC(CTcpTableControl)

public:
	CTcpTableControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTcpTableControl();

// Dialog Data
	enum { IDD = IDD_DIALOG_TCP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl listControlTcp_;
public:
	virtual BOOL OnInitDialog();
public:
	void refreshData();
private:
	void initializeControls();
public:
	afx_msg void OnPaint();
};
