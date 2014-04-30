/***************************************************************
 * Name:      mainframe.h
 * Purpose:   Defines main application frame
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2014-03-23
 * Copyright: Brian Walton (riban.co.uk)
 * License:
 **************************************************************/

#pragma once

//(*Headers(mainFrame)
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/aui/aui.h>
#include <wx/textctrl.h>
//*)

#include <map>

/** Class represents a type of AVR device */
class avrDevice
{
    public:
        avrDevice(long lId, const wxString& sName, const wxString sDescription = wxEmptyString) : id(lId), name(sName), description(sDescription) {};
        long id; //!< Unique ID used by application to identify device, e.g. as menu event id
        wxString name; //!< Name of device
//        wxString device; //!< Name of device used by simavr
        wxString description; //!< Long description of device
};

/** Class represents a profile of AVR device */
class avrProfile
{
    public:
        long id; //!< Unique ID used by application to identify profile, e.g. as menu event id
        wxString name; //!< Descriptive name of profile used in menus and logs
        wxString description; //!< Long description
        avrDevice* pDevice; //!< Pointer to device type
        long lFrequency; //!< Frequency of device
};

class wxAvr;
class wxFileName;
class wxFile;
class wxDateTime;
class wxLogTextCtrl;

class mainFrame: public wxFrame
{
	public:

		mainFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~mainFrame();

        /** @brief  Handle close events
        *   @param  event The close event
        */
        void OnClose(wxCloseEvent &event);

		//(*Declarations(mainFrame)
		wxAuiManager* m_pAuiManager;
		wxMenuItem* m_pMenuitemLogVerbose;
		wxMenu* m_pMenuDevice;
		wxSpinCtrl* m_pSpnFreq;
		wxMenuItem* m_pMenuitemVcd;
		wxStaticText* m_pLblDeviceType;
		wxMenuBar* m_pMenubar;
		wxMenuItem* m_pMenuitemLoadHex;
		wxStatusBar* m_pStatusBar;
		wxMenuItem* m_pMenuitemStop;
		wxMenuItem* m_pMenuitemWipe;
		wxMenuItem* m_pMenuitemLogToFile;
		wxMenu* Menu3;
		wxMenu* m_pMenuProfile;
		wxMenuItem* m_pMenuitemCode;
		wxPanel* m_pPnlMain;
		wxMenu* m_pMenuLog;
		wxMenuItem* m_pMenuitemStart;
		wxMenuItem* m_pMenuitemQuit;
		wxMenuItem* m_pMenuitemReset;
		wxMenuItem* m_pMenuitemFirmware;
		wxTextCtrl* m_pTxtLog;
		wxMenuItem* m_pMenuitemSaveProfile;
		wxMenu* m_pMenuMcu;
		wxMenuItem* m_pMenuitemVcdFile;
		wxStaticText* m_pLblFrequency;
		wxMenuItem* m_pMenuitemPause;
		wxAuiToolBar* m_pToolbarControl;
		wxMenuItem* m_pMenuitemSerial;
		//*)

	protected:
        wxAvr* m_pAvr; //!< Pointer to the AVR thread class instance
        friend class wxAvr; // allow it to access our m_pAvr

		//(*Identifiers(mainFrame)
		static const long ID_TOOLBARITEM_START;
		static const long ID_TOOLBARITEM_PAUSE;
		static const long ID_TOOLBARITEM_STOP;
		static const long ID_TOOLBARITEM_RESET;
		static const long ID_TOOLBAR_CONTROL;
		static const long ID_LBLDEVICETYPE;
		static const long ID_LBLFREQUENCY;
		static const long ID_SPNFREQ;
		static const long ID_TXTLOG;
		static const long ID_PNLMAIN;
		static const long ID_MENUITEM_FIRMWARE;
		static const long ID_MENUITEM_CODE;
		static const long ID_MENUITEM_LOADHEX;
		static const long idMenuQuit;
		static const long ID_MENUITEM_SAVEPROFILE;
		static const long ID_MENUITEM_PROFILE;
		static const long ID_MENUITEM_MCU;
		static const long ID_MENUITEM_WIPE;
		static const long ID_MENUITEM_SERIAL;
		static const long ID_MENUITEM_VCD;
		static const long ID_MENUITEM_VCDFILE;
		static const long ID_MENUITEM_START;
		static const long ID_MENUITEM_PAUSE;
		static const long ID_MENUITEM_STOP;
		static const long ID_MENUITEM_RESET;
		static const long ID_MENUITEM_LOGTOFILE;
		static const long ID_MENUITEM_LOGVERBOSE;
		static const long idMenuAbout;
		static const long ID_STATUSBAR;
		//*)
		static const long ID_MENUITEM_DELETEPROFILE;
		static const long ID_MENUITEM_RENAMEPROFILE;
		static const long ID_MENUITEM_NEWPROFILE;

	private:

		//(*Handlers(mainFrame)
		void OnQuit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);
		void OnMenuDeviceType(wxCommandEvent& event);
		void OnMenuProfile(wxCommandEvent& event);
		void OnSpnFreqChange(wxSpinEvent& event);
		void OnMenuitemFirmwareSelected(wxCommandEvent& event);
		void OnMenuitemCodeSelected(wxCommandEvent& event);
		void OnMenuitemLoadHexSelected(wxCommandEvent& event);
		void OnMenuitemWipeSelected(wxCommandEvent& event);
		void OnMenuitemLogToFileSelected(wxCommandEvent& event);
		void OnMenuitemSerialSelected(wxCommandEvent& event);
		void OnMenuitemMcuStart(wxCommandEvent& event);
		void OnMenuitemMcuPause(wxCommandEvent& event);
		void OnMenuitemMcuStop(wxCommandEvent& event);
		void OnMenuitemMcuReset(wxCommandEvent& event);
		void OnMenuitemVcdFileSelected(wxCommandEvent& event);
		void OnMenuitemVcdSelected(wxCommandEvent& event);
		void OnMenuitemSaveProfileSelected(wxCommandEvent& event);
		void OnMenuitemLogVerboseSelected(wxCommandEvent& event);
		//*)

        /** @brief  Updates dispaly with current running state
        *   @param  nState Running state
        */
        void Running(unsigned int nState);

        /** @brief  Read (load) configuration and persistent state
        */
        void ReadConfig();

        /** @brief  Write (save) configuration and persistent state
        */
        void WriteConfig();

        /** @brief  Handle AVR thread status event
        *   @param  event AVR thread event
        */
        void HandleAvrStatus(wxCommandEvent &event);

        /** @brief  Handle AVR thread pin write event
        *   @param  event AVR thread event
        */
        void HandleAvrWrite(wxCommandEvent &event);

        /** @brief  Helper function to enable / disable all child menu items of a wxMenu
        *   @param  pMenu Pointer to the menu
        *   @param  bEnable True to enable, false to disable. Default = true;
        */
        void EnableAllMenuItems(wxMenu* pMenu, bool bEnable = true);

        /** @brief	Enables logging to file
        *   @param	bEnable True to start logging, false to stop
        **/
        void EnableLogToFile(bool bEnable = true);

        /** @brief  Adds a profile
        *   @param  sName Name of profile
        *   @param  sDeviceType Name of device type
        *   @param  lFrequency MCU frequency
        *   @param  sTitle Descriptive name of profile. Default is profile name.
        *   @param  sDescription Long description of profile. Default is empty.
        *   @return <i>avrProfile*</i> Pointer to new profile or null if failed to create new profile
        */
        avrProfile* AddProfile(const wxString& sName, const wxString& sDeviceType, long lFrequency = 8000000l, const wxString& sTitle = wxEmptyString, const wxString& sDescription = wxEmptyString);

        /** @brief  Gets a pointer to an avr device type
        *   @param  sName Name of the MCU device
        *   @return <i>avrDevice*</i> Pointer to device or NULL if device type not found
        */
        avrDevice* GetDeviceTypeByDeviceName(const wxString& sName);

        /** @brief  Adds a device type to the map of device types
        *   @param  sName MCU name
        *   @param  sDescription Long description of MCU
        *   @return <i>avrDevice*</i> Pointer to new device type
        */
        avrDevice* AddDeviceType(const wxString& sName, const wxString& sDescription);

        /** @brief  Handle MCU menu item context menu event
        */
        void OnMenuitemProfileContext(wxCommandEvent& event);

        void ShowProfileContext(wxCommandEvent& event);

        std::map<long,avrDevice*> m_mDevices; //!< Map pointers to supported AVR device types, indexed by wxEvent ID
        std::map<long,avrProfile*> m_mProfiles; //!< Map pointers to AVR profiles, indexed by wxEvent ID
        avrDevice* m_pDeviceType; //!< Pointer to current device type
        long m_lFrequency; //!< Frequency of device
        size_t m_nLogMax; //!< Maximum number of log entries to show
        bool m_bScrollLock; //!< True to disable automatic scrolling of log window when new message logged
        bool m_bSerialEnabled; //!< True to enable serial port
        bool m_bVcdEnabled; //!< True if enable VCD logging
        bool m_bInit; //!< True if initiated, i.e. started up and configuration loaded
        wxFile* m_pFileLog; //!< Pointer to file to log to. Null to disable logging to file.
        wxFileName* m_pFnFirmware; //!< Pointer to name of firmware file
        wxFileName* m_pFnCode; //!< Pointer to name of code file
        wxFileName* m_pFnHex; //!< Pointer to name of Intel hex file
        wxFileName* m_pFnConfig; //!< Pointer to name of configuration file. Also used for path to other configuration data.
        wxFileName* m_pFnVcd; //!< Pointer to name of VCD logging file.
        wxLogTextCtrl* m_pLog; //!< Directs log messages to display

		DECLARE_EVENT_TABLE()
};


