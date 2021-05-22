#include "Main.h"


wxBEGIN_EVENT_TABLE(Main, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)

wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "MineSweeper with wxWidgets", wxPoint(30,30), wxSize(800,600) ) {
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight,0,0);

	nField = new int[nFieldWidth * nFieldHeight];
	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i = 0; i < nFieldWidth; ++i) {
	
		for (int j = 0; j < nFieldHeight; ++j) {
			btn[j * nFieldWidth + i] = new wxButton(this, 10000 + (j * nFieldHeight + i));
			btn[j * nFieldWidth + i]->SetFont(font);
			grid->Add(btn[j * nFieldHeight + i], 1, wxEXPAND | wxALL);

			btn[j * nFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);
			nField[j * nFieldWidth + i] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}

Main::~Main() {
	delete[]btn;
}
void Main::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (bFirstClick) {
		int mines = 30;
			
		while (mines) {
		
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}
		bFirstClick = false;
	}
	// Disables the button that is clicked
	btn[y * nFieldWidth + x]->Enable(false); 

	// Check if the player hits the mine

	if (nField[y * nFieldWidth + x] == -1) {
		wxMessageBox("BOOOOM!! You hit a mine GAMEOVER!!!");

		//resets the game
		bFirstClick = true;
		for (int i = 0; i < nFieldWidth; i++) {
			for (int j = 0; j < nFieldHeight; j++) {
				nField[j * nFieldWidth + i] = 0;
				btn[j * nFieldWidth + i]->SetLabel("");
				btn[j * nFieldWidth + i]->Enable(true);
			}
		}
	}
	else {
	// counts the nearby mines
		int mineCount = 0;
		for (int q = -1; q < 2; ++q) {
			for (int u = -1; u < 2; ++u) {
				if (x + q >= 0 && x + q < nFieldWidth && u + y >= 0 && u < nFieldHeight) {
				
					if (nField[(y + u) * nFieldWidth + (x + q)] == -1) {
						mineCount++;
					}
				}
			}
			//update buttons labe if there are neihboring mines
			if (mineCount > 0) {
				btn[y * nFieldWidth + x]->SetLabel(std::to_string(mineCount));
			}
		}
	}
	evt.Skip();
}
