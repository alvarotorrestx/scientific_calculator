#include "ButtonFactory.h"
#include "Window.h"

wxButton* ButtonFactory::CreateButton(wxWindow* parent, wxWindowID id, wxString label, const wxPoint& pos, const wxSize& size)
{
    // Instantiate new button with parameters
    wxButton* button = new wxButton(parent, id, label, pos, size);

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
