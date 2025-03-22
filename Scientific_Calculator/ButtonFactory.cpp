#include "ButtonFactory.h"
#include "Window.h"

wxButton* ButtonFactory::CreateButton(wxWindow* parent, wxWindowID id, wxString label, const wxPoint& pos, const wxSize& size)
{
    // Instantiate new button with NO borders & NO system theming
    wxButton* button = new wxButton(parent, id, label, pos, size, wxBORDER_NONE | wxBU_EXACTFIT);

    // Color variables
    wxColour bgColor, fgColor, hoverBgColor, hoverFgColor;

    // Style Buttons Based on Label
    if (isdigit(label[0])) {  // Number buttons
        bgColor = wxColour(55, 73, 85);
        fgColor = wxColour(215, 215, 215);

        hoverBgColor = wxColour(118, 209, 255);
        hoverFgColor = wxColour(0, 0, 0);
    }
    else { // Operator / function buttons
        bgColor = wxColour(118, 209, 255);
        fgColor = wxColour(0, 0, 0);

        hoverBgColor = fgColor;
        hoverFgColor = bgColor;
    }

    // Set initial colors
    button->SetBackgroundColour(bgColor);
    button->SetForegroundColour(fgColor);
    button->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Handle hover button colors
    button->Bind(wxEVT_ENTER_WINDOW, [button, hoverBgColor, hoverFgColor](wxMouseEvent&) {
        button->SetBackgroundColour(hoverBgColor);
        button->SetForegroundColour(hoverFgColor);
        button->SetOwnBackgroundColour(hoverBgColor);
        button->Refresh();
        });

    // Handle hover exit colors
    button->Bind(wxEVT_LEAVE_WINDOW, [button, bgColor, fgColor](wxMouseEvent&) {
        button->SetBackgroundColour(bgColor);
        button->SetForegroundColour(fgColor);
        button->SetOwnBackgroundColour(bgColor);
        button->Refresh();
        });

    // Set cursor to pointer when hovering
    button->SetCursor(wxCursor(wxCURSOR_HAND));

    // Bind button click event to OnButtonClick in Window
    Window* window = dynamic_cast<Window*>(parent);
    if (window) {
        button->Bind(wxEVT_BUTTON, &Window::OnButtonClick, window);
    }

    return button;
}

wxButton* ButtonFactory::CreateSinButton(wxWindow* parent)
{
    return CreateButton(parent, SIN_BUTTON_ID, "sin");
}

wxButton* ButtonFactory::CreateCosButton(wxWindow* parent)
{
    return CreateButton(parent, COS_BUTTON_ID, "cos");
}

wxButton* ButtonFactory::CreateTanButton(wxWindow* parent)
{
    return CreateButton(parent, TAN_BUTTON_ID, "tan");
}

wxButton* ButtonFactory::CreateClearButton(wxWindow* parent)
{
    return CreateButton(parent, CLEAR_BUTTON_ID, "AC");
}

wxButton* ButtonFactory::CreateBackspaceButton(wxWindow* parent)
{
    return CreateButton(parent, BACKSPACE_BUTTON_ID, "DEL");
}

wxButton* ButtonFactory::CreateAddButton(wxWindow* parent)
{
    return CreateButton(parent, ADD_BUTTON_ID, "+");
}

wxButton* ButtonFactory::CreateSubtractButton(wxWindow* parent)
{
    return CreateButton(parent, SUBTRACT_BUTTON_ID, "-");
}

wxButton* ButtonFactory::CreateMultiplyButton(wxWindow* parent)
{
    return CreateButton(parent, MULTIPLY_BUTTON_ID, "*");
}

wxButton* ButtonFactory::CreateDivideButton(wxWindow* parent)
{
    return CreateButton(parent, DIVIDE_BUTTON_ID, "/");
}

wxButton* ButtonFactory::CreateModuloButton(wxWindow* parent)
{
    return CreateButton(parent, MODULO_BUTTON_ID, "%");
}

wxButton* ButtonFactory::CreateEqualsButton(wxWindow* parent)
{
    return CreateButton(parent, EQUALS_BUTTON_ID, "=");
}

wxButton* ButtonFactory::CreateNegativeButton(wxWindow* parent)
{
    return CreateButton(parent, NEGATIVE_BUTTON_ID, "(-)");
}

wxButton* ButtonFactory::CreateDecimalButton(wxWindow* parent)
{
    return CreateButton(parent, DECIMAL_BUTTON_ID, ".");
}
