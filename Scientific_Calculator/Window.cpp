#include "Window.h"
#include <wx/tokenzr.h>
#include "ButtonFactory.h"
#include "CalculatorProcessor.h"

wxBEGIN_EVENT_TABLE(Window, wxFrame)
wxEND_EVENT_TABLE()

Window::Window() : wxFrame(nullptr, wxID_ANY, "Calculator-inator", wxPoint(250, 250), wxSize(500, 650))
{
	// Set frame bg color
	this->SetBackgroundColour(wxColor(25,28,30));

	// Main sizer to wrap entire calculator
	wxBoxSizer* mainWrapperSizer = new wxBoxSizer(wxVERTICAL);
	
	// Create and add text input to main sizer
	textInput = new wxTextCtrl(this, TEXT_INPUT_BUTTON_ID, "", wxDefaultPosition, wxSize(500, 100), wxTE_RIGHT | wxBORDER_NONE);
	textInput->SetBackgroundColour(wxColor(55, 73, 85));
	textInput->SetForegroundColour(wxColor(215, 215, 215));
	textInput->SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	// Set cursor to pointer when hovering
	textInput->SetCursor(wxCursor(wxCURSOR_HAND));
	mainWrapperSizer->Add(textInput, 0, wxEXPAND | wxALL, 10);

	// Create the top row sizer for first row of unary operator buttons, clear and delete btns
	wxBoxSizer* topRowSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create top row buttons - unary operator buttons, clear and delete btns
	topRowSizer->Add(ButtonFactory::CreateSinButton(this), 1, wxEXPAND | wxALL, 5);
	topRowSizer->Add(ButtonFactory::CreateCosButton(this), 1, wxEXPAND | wxALL, 5);
	topRowSizer->Add(ButtonFactory::CreateTanButton(this), 1, wxEXPAND | wxALL, 5);
	topRowSizer->Add(ButtonFactory::CreateClearButton(this), 1, wxEXPAND | wxALL, 5);
	topRowSizer->Add(ButtonFactory::CreateBackspaceButton(this), 1, wxEXPAND | wxALL, 5);

	// Add top row sizer to the main wrapper sizer
	mainWrapperSizer->Add(topRowSizer, 0, wxEXPAND | wxALL, 5);

	// Create a grid sizer to hold the numbers, ., and (-) buttons
	wxGridSizer* numbersGridSizer = new wxGridSizer(4, 3, 5, 5);
		
	// Create calculator number, -, and . buttons
	// 7,8,9
	// 4,5,6
	// 1,2,3
	// -,0,.
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_7_BUTTON_ID, "7"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_8_BUTTON_ID, "8"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_9_BUTTON_ID, "9"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_4_BUTTON_ID, "4"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_5_BUTTON_ID, "5"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_6_BUTTON_ID, "6"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_1_BUTTON_ID, "1"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_2_BUTTON_ID, "2"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_3_BUTTON_ID, "3"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateNegativeButton(this), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateButton(this, NUM_0_BUTTON_ID, "0"), 1, wxEXPAND | wxALL, 5);
	numbersGridSizer->Add(ButtonFactory::CreateDecimalButton(this), 1, wxEXPAND | wxALL, 5);

	// Create vertical side buttons sizer for binary operators
	wxBoxSizer* sideButtonsSizer = new wxBoxSizer(wxVERTICAL);

	// Create all operator buttons
	sideButtonsSizer->Add(ButtonFactory::CreateAddButton(this), 1, wxEXPAND | wxALL, 5);
	sideButtonsSizer->Add(ButtonFactory::CreateSubtractButton(this), 1, wxEXPAND | wxALL, 5);
	sideButtonsSizer->Add(ButtonFactory::CreateMultiplyButton(this), 1, wxEXPAND | wxALL, 5);
	sideButtonsSizer->Add(ButtonFactory::CreateDivideButton(this), 1, wxEXPAND | wxALL, 5);
	sideButtonsSizer->Add(ButtonFactory::CreateModuloButton(this), 1, wxEXPAND | wxALL, 5);
	sideButtonsSizer->Add(ButtonFactory::CreateEqualsButton(this), 1, wxEXPAND | wxALL, 5);

	// Combine numbers and side buttons sizers into one sizer
	wxBoxSizer* numsAndFuncSizer = new wxBoxSizer(wxHORIZONTAL);
	numsAndFuncSizer->Add(numbersGridSizer, 3, wxEXPAND | wxALL, 5);
	numsAndFuncSizer->Add(sideButtonsSizer, 1, wxEXPAND | wxALL, 5);

	// Add combined sizers to the main wrapper sizer
	mainWrapperSizer->Add(numsAndFuncSizer, 1, wxEXPAND | wxALL, 5);

	// Set sizer
	this->SetSizerAndFit(mainWrapperSizer);
}

Window::~Window()
{
	CalculatorProcessor::CleanUpInstance();
}

void Window::OnButtonClick(wxCommandEvent& event)
{
	// Get set button id
	int buttonId = event.GetId();

	// Find button using id
	wxButton* button = dynamic_cast<wxButton*>(FindWindow(buttonId));

	// Get the button label
	wxString label = button->GetLabel();

	wxString text = textInput->GetValue();

	// If conditions per label
	if (label == "AC")
	{
		if (!text.IsEmpty())
			// Clear text input
			HandleClear();
	}
	else if (label == "DEL")
	{
		wxString text = textInput->GetValue();
		if (!text.IsEmpty())
			// Delete input per single input
			HandleDelete();
	}
	else if (label == "(-)")
	{
		if (!text.IsEmpty())
			// Make number negative
			HandleNegative();
	}
	else if (label == "=")
	{
		if (!text.IsEmpty())
			// Calculate current input
			HandleCalculation();
	}
	else
	{
		// Append button label to text input
		textInput->AppendText(label);
	}
}

void Window::HandleClear()
{
	textInput->Clear();
}

void Window::HandleDelete()
{
	wxString text = textInput->GetValue();
	textInput->Remove(text.Length() - 1, text.Length());
}

void Window::HandleNegative()
{
	wxString text = textInput->GetValue();

	// Add spaces around operators before tokenizing
	wxString formattedText = text;
	formattedText.Replace("+", " + ");
	formattedText.Replace("-", " - ");
	formattedText.Replace("*", " * ");
	formattedText.Replace("/", " / ");
	formattedText.Replace("%", " % ");

	// Tokenize input by spaces
	wxStringTokenizer tokenizer(formattedText, " ", wxTOKEN_STRTOK);
	std::vector<std::string> tokens;

	// Store each token in the tokens vector
	while (tokenizer.HasMoreTokens()) {
		wxString token = tokenizer.GetNextToken();
		tokens.push_back(std::string(token.mb_str()));
	}

	// Ensure tokens is not empty
	if (tokens.empty()) return;

	// Find the last number in the input
	for (int i = tokens.size() - 1; i >= 0; i--) {
		if (isdigit(tokens[i][0]) || (tokens[i][0] == '-' && tokens[i].size() > 1)) {
			// If number is already negative, remove "-"
			if (tokens[i][0] == '-') {
				tokens[i] = tokens[i].substr(1);
			}
			else {
				// Otherwise, make number negative
				tokens[i] = "-" + tokens[i];
			}

			break;
		}
	}

	// Bug fix to ensure we remove double negatives
	for (size_t i = 0; i < tokens.size(); i++) {
		if (tokens[i] == "-" && i + 1 < tokens.size() && tokens[i + 1][0] == '-') {
			tokens.erase(tokens.begin() + i);
			tokens[i] = tokens[i].substr(1);
		}
	}

	// Reset input text
	wxString newText = "";

	for (const auto& token : tokens) {
		if (!token.empty()) newText += token + " ";
	}

	// Update the input field
	textInput->SetValue(newText.Trim());
}

void Window::HandleCalculation()
{
	wxString text = textInput->GetValue();
	text.MakeLower();

	// Add spaces around operators, parentheses and functions before tokenizing
	wxString formattedText = text;
	formattedText.Replace("(", " ( ");
	formattedText.Replace(")", " ) ");
	formattedText.Replace("+", " + ");
	formattedText.Replace("-", " - ");
	formattedText.Replace("*", " * ");
	formattedText.Replace("/", " / ");
	formattedText.Replace("%", " % ");
	formattedText.Replace("sin", " sin ");
	formattedText.Replace("cos", " cos ");
	formattedText.Replace("tan", " tan ");

	// Tokenize input by spaces
	wxStringTokenizer tokenizer(formattedText, " ", wxTOKEN_STRTOK);
	std::vector<std::string> tokens;

	// Store each token in the tokens vector
	while (tokenizer.HasMoreTokens()) {
		wxString token = tokenizer.GetNextToken();
		tokens.push_back(std::string(token.mb_str()));
	}

	// Ensure tokens is not empty
	if (tokens.empty()) return;

	// Call the singleton CalculatorProcessor to calculate the result
	float result = CalculatorProcessor::GetInstance()->Calculate(std::string(formattedText.mb_str()));

	// Handle error case
	if (std::isnan(result) || std::isinf(result)) {
		textInput->SetValue("ERR");
	}
	else {
		// Display the calculated result
		textInput->SetValue(wxString::Format("%.4f", result));
	}
}
