#include "profiledialog.h"

//(*InternalHeaders(ProfileDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(ProfileDialog)
const long ProfileDialog::ID_STATICTEXT1 = wxNewId();
const long ProfileDialog::ID_TXTPROFILENAME = wxNewId();
const long ProfileDialog::ID_STATICTEXT2 = wxNewId();
const long ProfileDialog::ID_CHOICE1 = wxNewId();
const long ProfileDialog::ID_STATICTEXT3 = wxNewId();
const long ProfileDialog::ID_SPINCTRL1 = wxNewId();
const long ProfileDialog::ID_STATICTEXT5 = wxNewId();
const long ProfileDialog::ID_TEXTCTRL2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ProfileDialog,wxDialog)
	//(*EventTable(ProfileDialog)
	//*)
END_EVENT_TABLE()

ProfileDialog::ProfileDialog(wxWindow* parent)
{
	//(*Initialize(ProfileDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Profile name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pTxtProfileName = new wxTextCtrl(this, ID_TXTPROFILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXTPROFILENAME"));
	FlexGridSizer2->Add(m_pTxtProfileName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("MCU:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pCmbMcu = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer2->Add(m_pCmbMcu, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pSpnFrequency = new wxSpinCtrl(this, ID_SPINCTRL1, _T("8000000"), wxDefaultPosition, wxDefaultSize, 0, 0, 32000000, 8000000, _T("ID_SPINCTRL1"));
	m_pSpnFrequency->SetValue(_T("8000000"));
	FlexGridSizer2->Add(m_pSpnFrequency, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Description:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pTxtDescription = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(m_pTxtDescription, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	FlexGridSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

ProfileDialog::~ProfileDialog()
{
	//(*Destroy(ProfileDialog)
	//*)
}

wxString ProfileDialog::GetProfileName()
{
    return m_pTxtProfileName->GetValue();
}

wxString ProfileDialog::GetDeviceType()
{
    return m_pCmbMcu->GetString(m_pCmbMcu->GetSelection());
}

long ProfileDialog::GetFrequency()
{
    return m_pSpnFrequency->GetValue();
}

wxString ProfileDialog::GetDescription()
{
    return m_pTxtDescription->GetValue();
}


void ProfileDialog::SetProfileName(const wxString & sName)
{
    m_pTxtProfileName->ChangeValue(sName);
}

void ProfileDialog::SetDeviceType(const wxString & sDeviceType)
{
    unsigned int nIndex = 0;
    for(; nIndex < m_pCmbMcu->GetCount(); ++nIndex)
        if(m_pCmbMcu->GetString(nIndex) == sDeviceType)
            break;
    m_pCmbMcu->Select(nIndex); //!@todo How does this handle empty list?
}

void ProfileDialog::SetFrequency(long lFrequency)
{
    m_pSpnFrequency->SetValue(lFrequency);
}

void ProfileDialog::SetDescription(const wxString & sDescription)
{
    m_pTxtDescription->ChangeValue(sDescription);
}

void ProfileDialog::AddMcu(const wxString& sMcu)
{
    m_pCmbMcu->Append(sMcu);
}
