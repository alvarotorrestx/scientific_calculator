#pragma once

#include "wx/wx.h"
#include "ButtonIDs.h"

class ButtonFactory
{
public:
	// Create button method
	static wxButton* CreateButton(wxWindow* parent, wxWindowID id, wxString label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

    // Specific button creation functions
    static wxButton* CreateSinButton(wxWindow* parent);
    static wxButton* CreateCosButton(wxWindow* parent);
    static wxButton* CreateTanButton(wxWindow* parent);
    static wxButton* CreateClearButton(wxWindow* parent);
    static wxButton* CreateBackspaceButton(wxWindow* parent);
    static wxButton* CreateAddButton(wxWindow* parent);
    static wxButton* CreateSubtractButton(wxWindow* parent);
    static wxButton* CreateMultiplyButton(wxWindow* parent);
    static wxButton* CreateDivideButton(wxWindow* parent);
    static wxButton* CreateModuloButton(wxWindow* parent);
    static wxButton* CreateEqualsButton(wxWindow* parent);
    static wxButton* CreateNegativeButton(wxWindow* parent);
    static wxButton* CreateDecimalButton(wxWindow* parent);
};

