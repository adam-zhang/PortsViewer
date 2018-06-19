#include "StdAfx.h"
#include "ListControlInitializer.h"


ListControlInitializer::ListControlInitializer(void)
{
}


ListControlInitializer::~ListControlInitializer(void)
{
}


static void addHeaders(CListCtrl& control)
{
	CRect rect;
	control.GetClientRect(&rect);
	int width = (rect.right - rect.left) / 4;
	control.InsertColumn(0, TEXT("PID"), 0, width);
	control.InsertColumn(1, TEXT("IP"), 0, width);
	control.InsertColumn(2, TEXT("Port"), 0, width);
	control.InsertColumn(3, TEXT("Full Name"), 0, width);
}


void adjustListControlSize(CDialog& parent, CListCtrl& control)
{
	CRect rect;
	parent.GetClientRect(&rect);
	rect.top += 5;
	rect.bottom -= 35;
	rect.left += 5;
	rect.right -= 35;
	control.MoveWindow(rect);
}

void ListControlInitializer::initialize(CDialog& parent, CListCtrl& control)
{
	adjustListControlSize(parent, control);
	addHeaders(control);
}