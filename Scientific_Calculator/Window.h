#pragma once

#include "wx/wx.h"
#include "ButtonIDs.h"

class CalculatorProcessor;

class Window : public wxFrame
{
private:
	wxTextCtrl* textInput = nullptr;

	// Event Table Functions
	void OnButtonClick(wxCommandEvent& event);
	
	// Calulator methods
	void HandleClear();
	void HandleDelete();
	void HandleNegative();
	void HandleCalculation();

	// Make ButtonFactory as a friend so it can access OnButtonClick
	friend class ButtonFactory;

	wxDECLARE_EVENT_TABLE();

public:
	Window();
	~Window();
};

