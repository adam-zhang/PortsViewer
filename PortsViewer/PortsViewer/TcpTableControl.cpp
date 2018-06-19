// TcpTableControl.cpp : implementation file
//

#include "stdafx.h"
#include "PortsViewer.h"
#include "TcpTableControl.h"
#include "ListControlInitializer.h"
#include "afxdialogex.h"
#include "PortInformation.h"
#include "PortTables.h"
#include "Format.h"
#include "ProcessHelper.h"
#include <cassert>
#include <algorithm>

using namespace std;
// CTcpTableControl dialog

IMPLEMENT_DYNAMIC(CTcpTableControl, CDialog)

CTcpTableControl::CTcpTableControl(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpTableControl::IDD, pParent)
{

}

CTcpTableControl::~CTcpTableControl()
{
}

void CTcpTableControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TCP, listControlTcp_);
}


BEGIN_MESSAGE_MAP(CTcpTableControl, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTcpTableControl message handlers


BOOL CTcpTableControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initializeControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

static void adjustListControlSize(CDialog& parent, CListCtrl& control)
{
	CRect rect;
	parent.GetClientRect(&rect);
	rect.top += 5;
	rect.left += 5;
	rect.bottom -= 105;
	rect.right -= 35;
	control.MoveWindow(&rect);
}


//typedef struct _MIB_TCPROW_OWNER_PID
//{
//    DWORD       dwState;
//    DWORD       dwLocalAddr;
//    DWORD       dwLocalPort;
//    DWORD       dwRemoteAddr;
//    DWORD       dwRemotePort;
//    DWORD       dwOwningPid;
//} MIB_TCPROW_OWNER_PID, *PMIB_TCPROW_OWNER_PID;

void addHeaders(CListCtrl& control)
{
	CRect rect;
	control.GetClientRect(&rect);
	TCHAR* headers[] = {TEXT("PID"), TEXT("Local Address"), TEXT("Local Port"), TEXT("Remote Address"), TEXT("Remote Port"), TEXT("Full Name")};
	auto width = 100;
	for(size_t i = 0; i != sizeof(headers) / sizeof(headers[0]); ++i)
	{
		auto ret = control.InsertColumn(i, headers[i], 0, width);
		assert(ret != -1);
	}
}

void CTcpTableControl::initializeControls()
{
	adjustListControlSize(*this, listControlTcp_);	
	addHeaders(listControlTcp_);
	listControlTcp_.SetExtendedStyle(listControlTcp_.GetExtendedStyle()|LVS_EX_DOUBLEBUFFER);  
}

void CTcpTableControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	//CRect rect;
	//GetClientRect(&rect);
	//dc.FillSolidRect(&rect, RGB(255, 255, 0));
}

void addRow(CListCtrl& control, size_t index, const shared_ptr<MIB_TCPROW_OWNER_PID>& p)
{
	control.InsertItem(index, Format::toString(p->dwOwningPid).c_str());
	control.SetItemText(index, 1, Format::toIP(p->dwLocalAddr).c_str());
	control.SetItemText(index, 2, Format::toString(p->dwLocalPort).c_str());
	control.SetItemText(index, 3, Format::toIP(p->dwRemoteAddr).c_str());
	control.SetItemText(index, 4, Format::toString(p->dwRemotePort).c_str());
	control.SetItemText(index, 5, ProcessHelper::processName(p->dwOwningPid).c_str());
}

void CTcpTableControl::refreshData()
{
	SetRedraw(FALSE);
	auto v = PortTables::instance().tcpTable(); //(UDP_TABLE);
	listControlTcp_.LockWindowUpdate();
	listControlTcp_.DeleteAllItems();
	listControlTcp_.SetRedraw(FALSE);
	for(size_t i = 0; i < v.size(); ++i)
		addRow(listControlTcp_, i, v[i]);
	listControlTcp_.UnlockWindowUpdate();
	listControlTcp_.SetRedraw(TRUE);
	SetRedraw(TRUE);
}
