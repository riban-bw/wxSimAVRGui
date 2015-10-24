#include "profiledialog.h"
#include "avrprofile.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(ProfileDialog)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)

//(*IdInit(ProfileDialog)
const long ProfileDialog::ID_STATICTEXT4 = wxNewId();
const long ProfileDialog::ID_CMBPROFILE = wxNewId();
const long ProfileDialog::ID_BTNDELETE = wxNewId();
const long ProfileDialog::ID_STATICTEXT1 = wxNewId();
const long ProfileDialog::ID_TXTPROFILENAME = wxNewId();
const long ProfileDialog::ID_STATICTEXT2 = wxNewId();
const long ProfileDialog::ID_CHOICE1 = wxNewId();
const long ProfileDialog::ID_STATICTEXT3 = wxNewId();
const long ProfileDialog::ID_SPINCTRL1 = wxNewId();
const long ProfileDialog::ID_STATICTEXT5 = wxNewId();
const long ProfileDialog::ID_TEXTCTRL2 = wxNewId();
const long ProfileDialog::ID_CANCEL = wxNewId();
const long ProfileDialog::ID_OK = wxNewId();
//*)

BEGIN_EVENT_TABLE(ProfileDialog,wxDialog)
	//(*EventTable(ProfileDialog)
	//*)
END_EVENT_TABLE()

ProfileDialog::ProfileDialog(wxWindow* parent, std::map<long,avrProfile*>* pMapProfile) :
    m_pMapProfile(pMapProfile)
{
	//(*Initialize(ProfileDialog)
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer3;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Profile"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer2->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pCmbProfile = new wxChoice(this, ID_CMBPROFILE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CMBPROFILE"));
	m_pCmbProfile->SetSelection( m_pCmbProfile->Append(_("New profile")) );
	FlexGridSizer2->Add(m_pCmbProfile, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pBtnDelete = new wxBitmapButton(this, ID_BTNDELETE, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BTNDELETE"));
	m_pBtnDelete->SetToolTip(_("Delete the selected profile"));
	FlexGridSizer2->Add(m_pBtnDelete, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Profile name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pTxtProfileName = new wxTextCtrl(this, ID_TXTPROFILENAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TXTPROFILENAME"));
	FlexGridSizer2->Add(m_pTxtProfileName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("MCU:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer2->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pCmbMcu = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer2->Add(m_pCmbMcu, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Frequency:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer2->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pSpnFrequency = new wxSpinCtrl(this, ID_SPINCTRL1, _T("8000000"), wxDefaultPosition, wxDefaultSize, 0, 0, 32000000, 8000000, _T("ID_SPINCTRL1"));
	m_pSpnFrequency->SetValue(_T("8000000"));
	FlexGridSizer2->Add(m_pSpnFrequency, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Description:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer2->Add(StaticText5, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pTxtDescription = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	FlexGridSizer2->Add(m_pTxtDescription, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pBtnCancel = new wxButton(this, ID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCEL"));
	FlexGridSizer3->Add(m_pBtnCancel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pBtnConfirm = new wxButton(this, ID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_OK"));
	FlexGridSizer3->Add(m_pBtnConfirm, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_CMBPROFILE,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ProfileDialog::OnCmbProfileSelect);
	Connect(ID_BTNDELETE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileDialog::OnBtnDeleteClick);
	Connect(ID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileDialog::OnBtnConfirmClick);
	//*)
	for(std::map<long,avrProfile*>::iterator it = m_pMapProfile->begin(); it != m_pMapProfile->end(); it++)
    {
        m_pCmbProfile->Append(it->second->GetName(), it->second);
    }
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

void ProfileDialog::OnCmbProfileSelect(wxCommandEvent& event)
{
    avrProfile* pProfile = (avrProfile*)event.GetClientData();
    if(pProfile)
    {
        SetProfileName(pProfile->GetName());
        SetDeviceType(pProfile->GetDeviceType());
        SetFrequency(pProfile->GetFrequency());
        SetDescription(pProfile->GetDescription());
    }
}

void ProfileDialog::OnBtnDeleteClick(wxCommandEvent& event)
{
    int nSelection = m_pCmbProfile->GetSelection();
    avrProfile* pProfile = (avrProfile*)(m_pCmbProfile->GetClientData(nSelection));
    if(!pProfile)
        return;
    if(wxYES != wxMessageBox("Delete profile " + pProfile->GetName() + "?", "Delete profile", wxYES_NO))
        return;

    m_pMapProfile->erase(pProfile->GetId());
    m_pCmbProfile->Delete(nSelection);
    delete pProfile;
    m_pCmbProfile->Select(0);
}

void ProfileDialog::OnBtnConfirmClick(wxCommandEvent& event)
{
    wxString sName = m_pTxtProfileName->GetValue();
    wxString sDeviceType = m_pCmbMcu->GetString(m_pCmbMcu->GetSelection());

    if(sName.IsEmpty())
    {
        wxMessageBox("Cannot add profile without a name");
        return;
    }
    //Check for existing profile
    avrProfile* pProfile = NULL;
    for(std::map<long,avrProfile*>::iterator it = m_pMapProfile->begin(); it != m_pMapProfile->end(); ++it)
    {
        if(it->second->GetName() != sName)
            continue;
        pProfile = it->second;
        break;
    }
    if(pProfile)
    {
        if(wxYES != wxMessageBox("Update profie " + sName + "?", "Update profile", wxYES_NO))
           return;
    }
    else
        pProfile = new avrProfile(sName, wxNewId(), sDeviceType, m_pSpnFrequency->GetValue(), m_pTxtDescription->GetValue());

    (*m_pMapProfile)[pProfile->GetId()] = pProfile;
    EndModal(wxID_OK);
}
