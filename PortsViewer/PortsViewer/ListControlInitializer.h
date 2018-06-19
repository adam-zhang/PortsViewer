#pragma once

class ListControlInitializer
{
private:
	ListControlInitializer(void);
	~ListControlInitializer(void);
public:
	static void initialize(CDialog& ,CListCtrl&);
};

