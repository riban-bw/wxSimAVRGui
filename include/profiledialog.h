#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

//(*Headers(ProfileDialog)
#include <wx/bmpbuttn.h>
#include <wx/spinctrl.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)
#include <map>

class avrProfile;

class ProfileDialog: public wxDialog
{
	public:

		ProfileDialog(wxWindow* parent, std::map<long,avrProfile*>* pMapProfile);
		virtual ~ProfileDialog();

        /** @brief  Get the profile name
        *   @return <i>wxString</i> Profile name
        */
		wxString GetProfileName();

        /** @brief  Get the device type
        *   @return <i>wxString</i> MCU device type
        */
        wxString GetDeviceType();

        /** @brief  Get frequency
        *   @return <i>wxString</i> Frequency
        */
        long GetFrequency();

        /** @brief Get description
        *   @return <i>wxString</i>
        */
        wxString GetDescription();

        /** @brief Set name
        *   @param sName Name
        */
        void SetProfileName(const wxString & sName);

        /** @brief  Set device type
        *   @param  sDeviceType MCU type
        */
        void SetDeviceType(const wxString & sDeviceType);

        /** @brief  Set frequency
        *   @param  lFrequency Frequency
        */
        void SetFrequency(long lFrequency);

        /** @brief  Set description
        *   @param  sDescription Description
        */
        void SetDescription(const wxString & sDescription);

        /** @brief  Add MCU type
        *   @param  sMcu Name of MCU
        */
        void AddMcu(const wxString& sMcu);


		//(*Declarations(ProfileDialog)
		wxTextCtrl* m_pTxtProfileName;
		wxButton* m_pBtnConfirm;
		wxChoice* m_pCmbMcu;
		wxSpinCtrl* m_pSpnFrequency;
		wxButton* m_pBtnCancel;
		wxStaticText* StaticText1;
		wxStaticText* StaticText3;
		wxBitmapButton* m_pBtnDelete;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText2;
		wxTextCtrl* m_pTxtDescription;
		wxChoice* m_pCmbProfile;
		//*)

	protected:

		//(*Identifiers(ProfileDialog)
		static const long ID_STATICTEXT4;
		static const long ID_CMBPROFILE;
		static const long ID_BTNDELETE;
		static const long ID_STATICTEXT1;
		static const long ID_TXTPROFILENAME;
		static const long ID_STATICTEXT2;
		static const long ID_CHOICE1;
		static const long ID_STATICTEXT3;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT5;
		static const long ID_TEXTCTRL2;
		static const long ID_CANCEL;
		static const long ID_OK;
		//*)

	private:

		//(*Handlers(ProfileDialog)
		void OnCmbProfileSelect(wxCommandEvent& event);
		void OnBtnDeleteClick(wxCommandEvent& event);
		void OnBtnConfirmClick(wxCommandEvent& event);
		//*)
		std::map<long,avrProfile*>* m_pMapProfile;

		DECLARE_EVENT_TABLE()
};

#endif
