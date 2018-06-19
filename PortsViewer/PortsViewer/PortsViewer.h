
// PortsViewer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPortsViewerApp:
// See PortsViewer.cpp for the implementation of this class
//

class CPortsViewerApp : public CWinApp
{
public:
	CPortsViewerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPortsViewerApp theApp;