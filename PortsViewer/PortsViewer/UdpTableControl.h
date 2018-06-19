#pragma once
#include "afxcmn.h"
#include <vector>
#include <memory>

class PortInformation;
// CUdpTableControl dialog

class CUdpTableControl : public CDialog
{
	DECLARE_DYNAMIC(CUdpTableControl)

public:
	CUdpTableControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUdpTableControl();

// Dialog Data
	enum { IDD = IDD_DIALOG_UDP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl listControlUdp_;
private:
	std::vector<std::shared_ptr<PortInformation>> ports_;
private:
	void initializeControls();
	void adjustListControlSize();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void refreshData();
};
