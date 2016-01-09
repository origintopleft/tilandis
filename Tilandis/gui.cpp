#include "gui.h"

bool GUI::InitMFC() { //stub
	GUI::RegisterProtocol->Create(IDD_REGISTER_PROTOCOL);
}

bool GUI::ShowDialog(CDialog * tgt) {
	tgt->ShowWindow(SW_SHOWDEFAULT); // TODO: error checking
}