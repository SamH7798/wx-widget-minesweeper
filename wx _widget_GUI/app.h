#pragma once

#include "wx/wx.h"
#include"Main.h"


class MyApp : public wxApp
{
public:
	MyApp();
	~MyApp();

public:

	virtual bool OnInit();
private:
	Main* m_frame1 = nullptr;
};

