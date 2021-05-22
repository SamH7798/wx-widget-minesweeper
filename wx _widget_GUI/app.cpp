#include "app.h"
#include"Main.h"

wxIMPLEMENT_APP(MyApp);

MyApp::MyApp() {

}

MyApp::~MyApp() {

}

bool MyApp::OnInit() {

	m_frame1 = new Main();

	m_frame1->Show();
	return true;
}