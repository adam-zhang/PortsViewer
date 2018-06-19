
// PortsViewerDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include <memory>
#include <vector>
#include <map>

class CTcpTableControl;
class CUdpTableControl;

enum
{
	UDP_TABLE_CONTROL,
	TCP_TABLE_CONTROL,
};

// CPortsViewerDlg dialog
class CPortsViewerDlg : public CDialogEx
{
// Construction
public:
	CPortsViewerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PORTSVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl tableControl;
	std::shared_ptr<CTcpTableControl> tcpTableControl_;
	std::shared_ptr<CUdpTableControl> udpTableControl_;
	std::map<DWORD, std::shared_ptr<CDialog>> pages_;
private:
	LRESULT onUserMessageUpdate(WPARAM, LPARAM);
private:
	void createUdpControl(CTabCtrl&);
	void createTcpControl(CTabCtrl&);
	void initializeTableControl(CTabCtrl&);
	void showUdpTableControl();
	void showTcpTableControl();
	void showPageControl(DWORD);
public:
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};
