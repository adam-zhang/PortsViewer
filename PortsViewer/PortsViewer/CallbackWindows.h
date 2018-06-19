#pragma once
#include "Singleton.h"

class CallbackWindows : public Singleton<CallbackWindows>
{
public:
	CallbackWindows(void);
	~CallbackWindows(void);
public:
	void setMainWindow(CWnd* window)
	{ mainWindow_ = window;}
	CWnd* mainWindow()
	{ return mainWindow_;}
private:
	CWnd* mainWindow_;
};

