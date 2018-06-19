
// PortsViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PortsViewer.h"
#include "PortsViewerDlg.h"
#include "afxdialogex.h"
#include "TcpTableControl.h"
#include "UdpTableControl.h"
#include "CallbackWindows.h"
#include "NetworkTimer.h"
#include "Messages.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPortsViewerDlg dialog




CPortsViewerDlg::CPortsViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPortsViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPortsViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, tableControl);
}

BEGIN_MESSAGE_MAP(CPortsViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CPortsViewerDlg::OnTcnSelchangeTabMain)
	ON_MESSAGE(WM_USER_UPDATE, &onUserMessageUpdate)
END_MESSAGE_MAP()

void adjustControlSize(CTabCtrl& control, shared_ptr<CDialog> p)
{
	CRect rect;
	control.GetClientRect(&rect);
	rect.top += 30;
	rect.left += 15;
	rect.right += 7;
	rect.bottom += 8;
	p->MoveWindow(rect);
	TRACE("rect top:%d, bottom:%d, left:%d, right:%d\n", rect.top, rect.bottom, rect.left, rect.right);
}

void CPortsViewerDlg::createUdpControl(CTabCtrl& control)
{
	control.InsertItem(0, TEXT("UDP"));
	tcpTableControl_ = make_shared<CTcpTableControl>();
	tcpTableControl_->Create(IDD_DIALOG_TCP);
	adjustControlSize(control, tcpTableControl_);
	pages_.insert(make_pair(TCP_TABLE_CONTROL, tcpTableControl_));
}

void CPortsViewerDlg::createTcpControl(CTabCtrl& control)
{
	control.InsertItem(1, TEXT("TCP"));
	udpTableControl_ = make_shared<CUdpTableControl>();
	udpTableControl_->Create(IDD_DIALOG_UDP);
	adjustControlSize(control, udpTableControl_);
	pages_.insert(make_pair(UDP_TABLE_CONTROL, udpTableControl_));
}

void CPortsViewerDlg::initializeTableControl(CTabCtrl& control)
{
	createUdpControl(control);
	createTcpControl(control);
	control.SetCurSel(0);
	udpTableControl_->ShowWindow(TRUE);
}


// CPortsViewerDlg message handlers

BOOL CPortsViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CallbackWindows::instance().setMainWindow(this);
	NetworkTimer::instance().run();
	initializeTableControl(tableControl);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPortsViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPortsViewerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPortsViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPortsViewerDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	switch(tableControl.GetCurSel())
	{
	case UDP_TABLE_CONTROL:
		showUdpTableControl();
		break;
	case TCP_TABLE_CONTROL:
		showTcpTableControl();
		break;
	}
	*pResult = 0;
}

void CPortsViewerDlg::showUdpTableControl()
{
	showPageControl(UDP_TABLE_CONTROL);
}

void CPortsViewerDlg::showTcpTableControl()
{
	showPageControl(TCP_TABLE_CONTROL);
}

void CPortsViewerDlg::showPageControl(DWORD index)
{
	for(auto i = pages_.begin(); i != pages_.end(); ++i)
	{
		(*i).second->ShowWindow((*i).first == index);
	}
}

LRESULT CPortsViewerDlg::onUserMessageUpdate(WPARAM, LPARAM)
{
	tcpTableControl_->refreshData();
	udpTableControl_->refreshData();
	return 0;
}
