// UdpTableControl.cpp : implementation file
//

#include "stdafx.h"
#include "PortsViewer.h"
#include "UdpTableControl.h"
#include "ListControlInitializer.h"
#include "afxdialogex.h"
#include "PortTables.h"
#include "Format.h"
#include "ProcessHelper.h"
#include <algorithm>
#include <memory>
// CUdpTableControl dialog
using namespace std;

IMPLEMENT_DYNAMIC(CUdpTableControl, CDialog)

CUdpTableControl::CUdpTableControl(CWnd* pParent /*=NULL*/)
	: CDialog(CUdpTableControl::IDD, pParent)
{

}

CUdpTableControl::~CUdpTableControl()
{
}

void CUdpTableControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UDP, listControlUdp_);
}


BEGIN_MESSAGE_MAP(CUdpTableControl, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CUdpTableControl message handlers


BOOL CUdpTableControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	initializeControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CUdpTableControl::initializeControls()
{
	ListControlInitializer::initialize(*this, listControlUdp_);
	listControlUdp_.SetExtendedStyle(listControlUdp_.GetExtendedStyle()|LVS_EX_DOUBLEBUFFER);  
}


void CUdpTableControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
	//CRect rect;
	//GetClientRect(&rect);
	//dc.FillSolidRect(&rect, RGB(255, 0, 0));
}

void CUdpTableControl::refreshData()
{
	auto table = PortTables::instance().udpTable();
	listControlUdp_.SetRedraw(FALSE);
	listControlUdp_.DeleteAllItems();
	for(size_t i = 0; i != table.size(); ++i)
	{
		listControlUdp_.InsertItem(i, Format::toString(table[i]->dwOwningPid).c_str());
		listControlUdp_.SetItemText(i, 1, Format::toIP(table[i]->dwLocalAddr).c_str());
		listControlUdp_.SetItemText(i, 2, Format::toString(table[i]->dwLocalPort).c_str());
		listControlUdp_.SetItemText(i, 3, ProcessHelper::processName(table[i]->dwOwningPid).c_str());
	}
	listControlUdp_.SetRedraw(TRUE);
}
