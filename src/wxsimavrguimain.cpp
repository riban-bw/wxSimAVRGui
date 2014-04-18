/***************************************************************
 * Name:      wxArduinoMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2014-03-23
 * Copyright: Brian Walton (riban.co.uk)
 * License:
 **************************************************************/

#include "wxsimavrguimain.h"
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/filedlg.h>
#include <wx/display.h>
#include "wxsimavr.h"

#include "images/play.xpm"
#include "images/play_disabled.xpm"
#include "images/pause.xpm"
#include "images/pause_disabled.xpm"
#include "images/stop.xpm"
#include "images/stop_disabled.xpm"
#include "images/reset.xpm"
#include "images/reset_disabled.xpm"
//#include "images/greenled.xpm"

//(*InternalHeaders(wxArduinoFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
//*)

//(*IdInit(wxArduinoFrame)
const long wxArduinoFrame::ID_LBLDEVICETYPE = wxNewId();
const long wxArduinoFrame::ID_LBLFREQUENCY = wxNewId();
const long wxArduinoFrame::ID_SPNFREQ = wxNewId();
const long wxArduinoFrame::ID_BMPLED1 = wxNewId();
const long wxArduinoFrame::ID_LSTLOG = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_FIRMWARE = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_CODE = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_LOADHEX = wxNewId();
const long wxArduinoFrame::idMenuQuit = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_PROFILE = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_MCU = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_WIPE = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_SERIAL = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_START = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_PAUSE = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_STOP = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_RESET = wxNewId();
const long wxArduinoFrame::ID_MENUITEM_LOGTOFILE = wxNewId();
const long wxArduinoFrame::idMenuAbout = wxNewId();
const long wxArduinoFrame::ID_STATUSBAR = wxNewId();
const long wxArduinoFrame::ID_TOOLBAR_START = wxNewId();
const long wxArduinoFrame::ID_TOOLBAR_PAUSE = wxNewId();
const long wxArduinoFrame::ID_TOOLBAR_STOP = wxNewId();
const long wxArduinoFrame::ID_TOOLBAR_RESET = wxNewId();
const long wxArduinoFrame::ID_TOOLBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxArduinoFrame,wxFrame)
    //(*EventTable(wxArduinoFrame)
    //*)
END_EVENT_TABLE()

wxArduinoFrame::wxArduinoFrame(wxWindow* parent,wxWindowID id) :
    m_pDeviceType(NULL),
    m_lFrequency(16000000),
    m_nLogMax(1000),
    m_bScrollLock(false),
    m_pFileLog(NULL),
    m_pFnFirmware(NULL),
    m_pFnCode(NULL)
{
    //(*Initialize(wxArduinoFrame)
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer4;
    wxStaticText* StaticText1;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    FlexGridSizer3 = new wxFlexGridSizer(0, 0, 0, 0);
    FlexGridSizer3->AddGrowableCol(4);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("MCU"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("wxID_ANY"));
    FlexGridSizer3->Add(StaticText1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_pLblDeviceType = new wxStaticText(this, ID_LBLDEVICETYPE, _("-"), wxDefaultPosition, wxSize(100,17), wxALIGN_CENTRE, _T("ID_LBLDEVICETYPE"));
    m_pLblDeviceType->SetBackgroundColour(wxColour(255,255,255));
    FlexGridSizer3->Add(m_pLblDeviceType, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_pLblFrequency = new wxStaticText(this, ID_LBLFREQUENCY, _("Frequency"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_LBLFREQUENCY"));
    FlexGridSizer3->Add(m_pLblFrequency, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    m_pSpnFreq = new wxSpinCtrl(this, ID_SPNFREQ, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 99999999, 0, _T("ID_SPNFREQ"));
    m_pSpnFreq->SetValue(_T("0"));
    FlexGridSizer3->Add(m_pSpnFreq, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(1);
    FlexGridSizer4 = new wxFlexGridSizer(1, 0, 0, 0);
    m_pBmpLed1 = new wxStaticBitmap(this, ID_BMPLED1, wxBitmap(wxImage(_T("/home/brian/src/wxArduino/images/amberled.png"))), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, _T("ID_BMPLED1"));
    FlexGridSizer4->Add(m_pBmpLed1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_pLstLog = new wxListBox(this, ID_LSTLOG, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LSTLOG"));
    FlexGridSizer2->Add(m_pLstLog, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    m_pMenubar = new wxMenuBar();
    Menu1 = new wxMenu();
    m_pMenuitemFirmware = new wxMenuItem(Menu1, ID_MENUITEM_FIRMWARE, _("Firmware"), _("Load firmware"), wxITEM_NORMAL);
    Menu1->Append(m_pMenuitemFirmware);
    m_pMenuitemCode = new wxMenuItem(Menu1, ID_MENUITEM_CODE, _("Load Code"), _("Load code"), wxITEM_NORMAL);
    Menu1->Append(m_pMenuitemCode);
    m_pMenuitemLoadHex = new wxMenuItem(Menu1, ID_MENUITEM_LOADHEX, _("Load Hex\tCtrl-O"), _("Load Intel hex file"), wxITEM_NORMAL);
    Menu1->Append(m_pMenuitemLoadHex);
    m_pMenuitemQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit application"), wxITEM_NORMAL);
    Menu1->Append(m_pMenuitemQuit);
    m_pMenubar->Append(Menu1, _("&File"));
    m_pMenuDevice = new wxMenu();
    m_pMenuProfile = new wxMenu();
    m_pMenuProfile->Break();
    m_pMenuDevice->Append(ID_MENUITEM_PROFILE, _("Profile"), m_pMenuProfile, wxEmptyString);
    m_pMenuMcu = new wxMenu();
    m_pMenuMcu->Break();
    m_pMenuDevice->Append(ID_MENUITEM_MCU, _("MCU"), m_pMenuMcu, wxEmptyString);
    m_pMenuitemWipe = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_WIPE, _("Wipe device"), _("Wipe all data from device"), wxITEM_NORMAL);
    m_pMenuDevice->Append(m_pMenuitemWipe);
    m_pMenuitemSerial = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_SERIAL, _("Enable Serial Port"), _("Enable the serial port on the MCU"), wxITEM_CHECK);
    m_pMenuDevice->Append(m_pMenuitemSerial);
    m_pMenubar->Append(m_pMenuDevice, _("Device"));
    Menu3 = new wxMenu();
    m_pMenuitemStart = new wxMenuItem(Menu3, ID_MENUITEM_START, _("Start\tF9"), _("Start MCU"), wxITEM_NORMAL);
    m_pMenuitemStart->SetBitmap(play_xpm);
    Menu3->Append(m_pMenuitemStart);
    m_pMenuitemPause = new wxMenuItem(Menu3, ID_MENUITEM_PAUSE, _("Pause"), _("Pause MCU"), wxITEM_NORMAL);
    m_pMenuitemPause->SetBitmap(pause_xpm);
    Menu3->Append(m_pMenuitemPause);
    m_pMenuitemStop = new wxMenuItem(Menu3, ID_MENUITEM_STOP, _("Stop\tCtrl-F9"), _("Stop MCU"), wxITEM_NORMAL);
    m_pMenuitemStop->SetBitmap(stop_xpm);
    Menu3->Append(m_pMenuitemStop);
    m_pMenuitemReset = new wxMenuItem(Menu3, ID_MENUITEM_RESET, _("Reset\tCtrl-R"), _("Reset MCU"), wxITEM_NORMAL);
    m_pMenuitemReset->SetBitmap(reset_xpm);
    Menu3->Append(m_pMenuitemReset);
    m_pMenubar->Append(Menu3, _("Control"));
    m_pMenuLog = new wxMenu();
    m_pMenuitemLogToFile = new wxMenuItem(m_pMenuLog, ID_MENUITEM_LOGTOFILE, _("Log to file"), _("Record log entries to file"), wxITEM_CHECK);
    m_pMenuLog->Append(m_pMenuitemLogToFile);
    m_pMenubar->Append(m_pMenuLog, _("Log"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    m_pMenubar->Append(Menu2, _("Help"));
    SetMenuBar(m_pMenubar);
    m_pStatusBar = new wxStatusBar(this, ID_STATUSBAR, 0, _T("ID_STATUSBAR"));
    int __wxStatusBarWidths_1[3] = { -10, -10, -10 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    m_pStatusBar->SetFieldsCount(3,__wxStatusBarWidths_1);
    m_pStatusBar->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(m_pStatusBar);
    m_pToolBar = new wxToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR"));
    m_pToolbarStart = m_pToolBar->AddTool(ID_TOOLBAR_START, _("Start"), play_xpm, play_disabled_xpm, wxITEM_NORMAL, _("Start MCU"), _("Start MCU"));
    m_pToolbarPause = m_pToolBar->AddTool(ID_TOOLBAR_PAUSE, _("Pause"), pause_xpm, pause_disabled_xpm, wxITEM_NORMAL, _("Pause MCU"), _("Pause MCU"));
    m_pToolbarStop = m_pToolBar->AddTool(ID_TOOLBAR_STOP, _("Stop"), stop_xpm, stop_disabled_xpm, wxITEM_NORMAL, _("Stop MCU"), _("Stop MCU"));
    m_pToolbarReset = m_pToolBar->AddTool(ID_TOOLBAR_RESET, _("Reset"), reset_xpm, reset_disabled_xpm, wxITEM_NORMAL, _("Reset MCU"), _("Reset MCU"));
    m_pToolBar->Realize();
    SetToolBar(m_pToolBar);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);

    Connect(ID_SPNFREQ,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&wxArduinoFrame::OnSpnFreqChange);
    Connect(ID_MENUITEM_FIRMWARE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemFirmwareSelected);
    Connect(ID_MENUITEM_CODE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemCodeSelected);
    Connect(ID_MENUITEM_LOADHEX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemLoadHexSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnQuit);
    Connect(ID_MENUITEM_WIPE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemWipeSelected);
    Connect(ID_MENUITEM_SERIAL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemSerialSelected);
    Connect(ID_MENUITEM_START,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnStartClick);
    Connect(ID_MENUITEM_PAUSE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnPauseClick);
    Connect(ID_MENUITEM_STOP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnStopClick);
    Connect(ID_MENUITEM_RESET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnResetClick);
    Connect(ID_MENUITEM_LOGTOFILE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnMenuitemLogToFileSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxArduinoFrame::OnAbout);
    Connect(ID_TOOLBAR_START,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnStartClick);
    Connect(ID_TOOLBAR_PAUSE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnPauseClick);
    Connect(ID_TOOLBAR_STOP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnStopClick);
    Connect(ID_TOOLBAR_RESET,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&wxArduinoFrame::OnBtnResetClick);
    //*)
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&wxArduinoFrame::OnClose);
    Connect(wxID_ANY, wxEVT_AVR_STATUS, (wxObjectEventFunction)&wxArduinoFrame::HandleAvrStatus);
    Connect(wxID_ANY, wxEVT_AVR_WRITE, (wxObjectEventFunction)&wxArduinoFrame::HandleAvrWrite);
    Running(AVR_STATUS_STOPPED);
    ReadConfig();
    m_pSpnFreq->SetValue(m_lFrequency);

    wxLogDebug(_("wxArduinoFrame completed constructor\n"));
}

wxArduinoFrame::~wxArduinoFrame()
{
    wxLogDebug(_("wxArduinoFrame::~wxArduinoFrame()"));
    //(*Destroy(wxArduinoFrame)
    //*)
    delete m_pFnFirmware;
    delete m_pFnCode;
}

void wxArduinoFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxArduinoFrame::OnClose(wxCloseEvent &event)
{
    wxLogDebug(_("wxArduinoFrame::OnClose\n"));
    WriteConfig();
    if(m_pAvr)
    {
        if(m_pAvr->Delete() != wxTHREAD_NO_ERROR )
            wxLogError(wxT("Can't delete the thread!"));
        else
            m_pAvr = NULL;
    }
    for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); it++)
        delete it->second;
    Destroy();
}

void wxArduinoFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("wxArduino - Brian Walton\n(C) riban 2014"), _("About"));
}

void wxArduinoFrame::OnBtnStartClick(wxCommandEvent& event)
{
    wxLogDebug(_("wxArduinoFrame::OnBtnStartClick\n"));
    if(!m_pDeviceType)
        return; //No device type selected
    if(!m_pAvr)
    {
        //Create instance of the wxAvr thread
        m_pAvr = new wxAvr(this, m_pDeviceType->device, m_lFrequency);
        if(!m_pAvr)
            return; //Just in case the creation fails
        m_pAvr->Create();
    }

    switch(m_pAvr->GetStatus())
    {
        case AVR_STATUS_PAUSED:
            if(wxTHREAD_NO_ERROR != m_pAvr->Resume())
                wxLogError(wxT("Can't resume thread!"));
            return;
            break;
        case AVR_STATUS_CRASHED:
        case AVR_STATUS_DONE:
        case AVR_STATUS_STOPPED:
        default:
            if(m_pFnFirmware)
                m_pAvr->LoadFirmware(m_pFnFirmware->GetFullPath());
            if(m_pFnHex)
                m_pAvr->LoadHex(m_pFnHex->GetFullPath());
            if(m_bSerialEnabled)
            {
                m_pAvr->StartUart('0');
                Log(_("UART /tmp/simavr-uart0"));
            }
            if(m_bVcdEnabled)
            {
                m_pAvr->InitVcd(wxFileName(_("walt.vcd")), 100000); //!@todo Set VCD filename
                for(unsigned int nIndex = 0; nIndex < 8; ++nIndex)
                    m_pAvr->AddSignal(nIndex, wxString::Format(_("Output %d"), nIndex));
                m_pAvr->StartVcd();
            }
            if(m_pAvr->IsPaused())
            {
                m_pAvr->Reset();
                if(wxTHREAD_NO_ERROR != m_pAvr->Resume())
                    wxLogError(wxT("Can't resume thread!"));
            }
            else if(wxTHREAD_NO_ERROR != m_pAvr->Run())
            {
                wxLogError(wxT("Can't create the thread! Error"));
                m_pAvr->Delete();
                m_pAvr = NULL;
                return;
            }
    }
}


void wxArduinoFrame::OnBtnStopClick(wxCommandEvent& event)
{
    wxLogDebug(_("wxArduinoFrame::~OnBtnStopClick"));
    if(m_pAvr)
    {
        m_pAvr->Stop();
        m_pAvr->StopUart();
    }
}

void wxArduinoFrame::OnBtnPauseClick(wxCommandEvent& event)
{
    if(m_pAvr && m_pAvr->IsRunning())
    {
        if(m_pAvr->Pause() != wxTHREAD_NO_ERROR )
            wxLogError(wxT("Can't pause the thread!"));
        else
            Log(_("Paused MCU"));
    }
}


void wxArduinoFrame::EnableAllMenuItems(wxMenu* pMenu, bool bEnable)
{
    if(!pMenu)
        return;
    for(size_t nPos = 0; nPos < pMenu->GetMenuItemCount(); nPos++)
        pMenu->FindItemByPosition(nPos)->Enable(bEnable);
}

void wxArduinoFrame::Running(unsigned int nState)
{
    switch(nState)
    {
        case AVR_STATUS_STOPPED:
            m_pMenuitemStart->Enable();
            m_pToolbarStart->Enable(true);
            m_pMenuitemPause->Enable(false);
            m_pToolbarPause->Enable(false);
            m_pMenuitemStop->Enable(false);
            m_pToolbarStop->Enable(false); //!@todo this isn't disabling the toolbar button (but is stopping events) Maybe a gtk implementation thing
            m_pMenuitemReset->Enable(false);
            m_pToolbarReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Stopped"), 2);
            Log(_("MCU stopped"));
            EnableAllMenuItems(m_pMenuDevice);
            m_pMenuitemCode->Enable();
            m_pMenuitemFirmware->Enable();
            m_pMenuitemLoadHex->Enable();
            break;
        case AVR_STATUS_RUNNING:
            m_pMenuitemStart->Enable(false);
            m_pToolbarStart->Enable(false);
            m_pMenuitemPause->Enable();
            m_pToolbarPause->Enable(true);
            m_pMenuitemStop->Enable();
            m_pToolbarStop->Enable(true);
            m_pMenuitemReset->Enable();
            m_pToolbarReset->Enable(true);
            m_pStatusBar->SetStatusText(wxT("Running"), 2);
            m_pMenuitemCode->Enable(false);
            m_pMenuitemFirmware->Enable(false);
            m_pMenuitemLoadHex->Enable(false);
            Log(_("MCU running"));
            EnableAllMenuItems(m_pMenuDevice, false);
            break;
        case AVR_STATUS_PAUSED:
            m_pMenuitemStart->Enable();
            m_pToolbarStart->Enable(true);
            m_pMenuitemPause->Enable(false);
            m_pToolbarPause->Enable(false);
            m_pMenuitemStop->Enable();
            m_pToolbarStop->Enable(true);
            m_pMenuitemReset->Enable(false);
            m_pToolbarReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Paused"), 2);
            m_pMenuitemCode->Enable(false);
            m_pMenuitemFirmware->Enable(false);
            m_pMenuitemLoadHex->Enable(false);
            Log(_("MCU paused"));
            EnableAllMenuItems(m_pMenuDevice, false);
            break;
        case AVR_STATUS_CRASHED:
            m_pMenuitemStart->Enable();
            m_pToolbarStart->Enable(true);
            m_pMenuitemPause->Enable(false);
            m_pToolbarPause->Enable(false);
            m_pMenuitemStop->Enable(false);
            m_pToolbarStop->Enable(false);
            m_pMenuitemReset->Enable(false);
            m_pToolbarReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Crashed"), 2);
            m_pMenuitemCode->Enable();
            m_pMenuitemFirmware->Enable();
            m_pMenuitemLoadHex->Enable();
            Log(_("MCU crashed"));
            EnableAllMenuItems(m_pMenuDevice);
            break;
    }
}

void wxArduinoFrame::OnBtnResetClick(wxCommandEvent& event)
{
    if(m_pAvr)
        m_pAvr->Reset();
}

void wxArduinoFrame::OnMenuDeviceType(wxCommandEvent& event)
{
    avrDevice* pDevice = m_mDevices[event.GetId()];
    if(!pDevice)
        return;
    m_pDeviceType = pDevice;
    m_pLblDeviceType->SetLabel(pDevice->name);
}

void wxArduinoFrame::OnMenuProfile(wxCommandEvent& event)
{
    avrProfile* pProfile = m_mProfiles[event.GetId()];
    if(!pProfile)
        return;
    if(!pProfile->pDevice)
        return;
    m_pDeviceType = pProfile->pDevice;
    m_pLblDeviceType->SetLabel(m_pDeviceType->name);
    m_lFrequency = pProfile->lFrequency;
    m_pSpnFreq->SetValue(m_lFrequency); //!@todo not working
}

void wxArduinoFrame::ReadConfig()
{
    wxConfig* pConfig = new wxConfig(_("wxarduino"), _("riban"), _(".config/riban/wxarduino/mcu.cfg"));
    wxString sGroup, sTmp;
    long lCookie;
    bool bMore = pConfig->GetFirstGroup(sGroup, lCookie);
    while(bMore)
    {
        if(!pConfig->Read(sGroup + _("/name"), &sTmp))
            sTmp = sGroup;
        bool bDuplicate = false;
        for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); ++it)
        {
            if(it->second->name != sGroup)
                continue;
            bDuplicate = true;
            break;
        }
        avrDevice* pDevice = new avrDevice;
        pDevice->id = wxNewId();
        pDevice->device = sGroup;
        pDevice->name = sTmp;
        if(!pConfig->Read(sGroup + _("/description"), &sTmp))
            pDevice->description = sTmp;
        m_mDevices[pDevice->id] = (pDevice);
        m_pMenuMcu->Append(new wxMenuItem(m_pMenuMcu, pDevice->id, pDevice->name, pDevice->description, wxITEM_RADIO));
        Connect(pDevice->id, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxArduinoFrame::OnMenuDeviceType);
        bMore = pConfig->GetNextGroup(sGroup, lCookie);
    }
    delete pConfig;

    pConfig = new wxConfig(_("wxarduino"), _("riban"), _(".config/riban/wxarduino/profile.cfg"));
    bMore = pConfig->GetFirstGroup(sGroup, lCookie);
    while(bMore)
    {
        if(pConfig->Read(sGroup + _("/device"), &sTmp))
        {
            bool bDuplicate = false;
            for(std::map<long,avrProfile*>::iterator it = m_mProfiles.begin(); it != m_mProfiles.end(); ++it)
            {
                if(it->second->name != sGroup)
                    continue;
                bDuplicate = true;
                break;
            }
            if(bDuplicate)
                break;

            pConfig->Read(sGroup + _("/device"), &sTmp, m_pDeviceType->device);
            avrDevice* pDevice = NULL;
            for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); ++it)
            {
                if(it->second->device != sTmp)
                    continue;
                pDevice = it->second;
                break;
            }
            if(!pDevice)
                break;

            avrProfile* pProfile = new avrProfile;
            pProfile->pDevice = pDevice;
            pProfile->id = wxNewId();
            pProfile->name = sGroup;
            if(!pConfig->Read(sGroup + _("/name"), &sTmp))
                sTmp = sGroup;
            pProfile->name = sTmp;
            if(!pConfig->Read(sGroup + _("/description"), &sTmp))
                pProfile->description = sTmp;
            pConfig->Read(sGroup + _("/frequency"), &(pProfile->lFrequency), 8000000l);

            m_mProfiles[pProfile->id] = (pProfile);
            wxMenuItem* pMenuitem = m_pMenuProfile->Append(new wxMenuItem(m_pMenuProfile, pProfile->id, pProfile->name, pProfile->description, wxITEM_NORMAL));
            Connect(pProfile->id, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&wxArduinoFrame::OnMenuProfile);
        }
        else
            wxLogError(_("Configuration error: Undefined device [%s} used in profile [%s]"), sTmp.c_str(), sGroup.c_str());
        bMore = pConfig->GetNextGroup(sGroup, lCookie);
    }
    delete pConfig;

    pConfig = new wxConfig(_("wxarduino"), _("riban"), _(".config/riban/wxarduino/config.cfg"));
    pConfig->Read(_("/state/mcu"), &sTmp);
    for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); ++it)
    {
        if(sTmp == it->second->device)
        {
            int nId = m_pMenuDevice->FindItem(it->second->name);
            if(wxNOT_FOUND != nId)
            {
                wxMenuEvent event(wxEVT_COMMAND_MENU_SELECTED);
                event.SetId(nId);
                GetEventHandler()->ProcessEvent(event);
                m_pMenuDevice->Check(nId, true);
            }
            break;
        }
    }
    pConfig->Read(_("/state/frequency"), &m_lFrequency);
    if(pConfig->Read(_("/state/firmware"), &sTmp))
        m_pFnFirmware = new wxFileName(sTmp);
    if(pConfig->Read(_("/state/ihex"), &sTmp))
        m_pFnHex= new wxFileName(sTmp);
    pConfig->Read(_("/state/serial"), &m_bSerialEnabled, false);
    m_pMenuitemSerial->Check(m_bSerialEnabled);

    int nWidth = 600;
    int nHeight = 400;
    int nX = 10;
    int nY = 10;
    long lTmp;
    bool bTmp;
    if(pConfig->Read(wxT("/Layout/Width"), &lTmp))
		nWidth = lTmp;
	if(pConfig->Read(wxT("/Layout/Height"), &lTmp))
		nHeight = lTmp;
	if(pConfig->Read(wxT("/Layout/PosX"), &lTmp))
		nX = lTmp;
	if(pConfig->Read(wxT("/Layout/PosY"), &lTmp))
		nY = lTmp;
	if(pConfig->Read(wxT("/Layout/Maximised"), &bTmp))
		Maximize(bTmp);
	SetSize(nWidth, nHeight);
    //Check saved location is visible
    bool bCanSee = false;
	for(unsigned int nDisplay = 0; nDisplay < wxDisplay::GetCount(); nDisplay++)
    {
        bCanSee |= wxDisplay(nDisplay).GetGeometry().Intersects(wxRect(nX, nY, nWidth, nHeight));
    }
    if(bCanSee)
        Move(nX, nY);
	bTmp = false;
	pConfig->Read(wxT("/Log/File"), &bTmp, false);
	OpenLogFile(bTmp);
//	pConfig->Read(wxT("/Log/Verbose"), &m_bVerboseLogging, false);
//	m_pMenuVerbose->Check(m_bVerboseLogging);

    delete pConfig;
}

void wxArduinoFrame::WriteConfig()
{
    wxConfig* pConfig = new wxConfig(_("wxarduino"), _("riban"), _(".config/riban/wxarduino/config.cfg"));
    if(m_pDeviceType)
        pConfig->Write(_("/state/mcu"), m_pDeviceType->device);
    pConfig->Write(_("/state/frequency"), m_lFrequency);
    if(m_pFnFirmware)
        pConfig->Write(_("/state/firmware"), m_pFnFirmware->GetFullPath());
    else
        pConfig->DeleteEntry(_("/state/firmware"));
    if(m_pFnHex)
        pConfig->Write(_("/state/ihex"), m_pFnHex->GetFullPath());
    else
        pConfig->DeleteEntry(_("/state/ihex"));
    pConfig->Write(wxT("/state/serial"), m_bSerialEnabled);
    if(IsMaximized())
        pConfig->Write(wxT("/Layout/Maximised"), true);
    else
    {
        pConfig->Write(wxT("/Layout/Maximised"), false);
        pConfig->Write(wxT("/Layout/Width"), GetSize().GetWidth());
        pConfig->Write(wxT("/Layout/Height"), GetSize().GetHeight());
        pConfig->Write(wxT("/Layout/PosX"), GetPosition().x);
        pConfig->Write(wxT("/Layout/PosY"), GetPosition().y);
    }
    pConfig->Write(wxT("/Log/File"), (NULL != m_pFileLog));
//	pConfig->Write(wxT("/Log/Verbose"), m_bVerboseLogging);
    delete pConfig;
}

void wxArduinoFrame::OnSpnFreqChange(wxSpinEvent& event)
{
    m_lFrequency = m_pSpnFreq->GetValue();
}

void wxArduinoFrame::HandleAvrStatus(wxCommandEvent &event)
{
    wxLogDebug(_("wxArduinoFrame::HandleAvrStatus"));
    //Don't do anything that is thread unsafe like GUI stuff or wx class manipulation
//    switch(event.GetInt())
//    {
//        case AVR_STATUS_STOPPED:
//        case AVR_STATUS_CRASHED:
//            m_pAvr = NULL; //!@todo not actually destroying when crash
//    }
    Running(event.GetInt());
    wxLogDebug(_("wxArduinoFrame::HandleAvrStatus - end"));
}

void wxArduinoFrame::HandleAvrWrite(wxCommandEvent &event)
{
    wxLogDebug(_("wxArduinoFrame::HandleAvrWrite"));
}

void wxArduinoFrame::OnMenuitemFirmwareSelected(wxCommandEvent& event)
{
    wxString sPath, sFile;
    if(m_pFnFirmware)
    {
        sPath = m_pFnFirmware->GetPath();
        sFile = m_pFnFirmware->GetName();
    }
    wxFileDialog dlg(this, _("Select firmware file"), sPath, sFile);
    int nResult = dlg.ShowModal();
    if(nResult != wxID_OK)
        return;
    if(m_pFnFirmware)
        delete m_pFnFirmware;

    m_pFnFirmware = new wxFileName(dlg.GetPath());
    if(!m_pFnFirmware->FileExists())
    {
        delete m_pFnFirmware;
        m_pFnFirmware = NULL;
    }
    if(m_pAvr && !m_pAvr->IsRunning())
    {
        m_pAvr->LoadFirmware(m_pFnFirmware->GetPath());
        m_pSpnFreq->SetValue(m_pAvr->GetFrequency());
        m_pLblDeviceType->SetLabel(m_pAvr->GetMcuType());
    }
}

void wxArduinoFrame::OnMenuitemCodeSelected(wxCommandEvent& event)
{
    wxMessageBox(_("Load Code not implemented"));
    return;
    wxFileDialog dlg(this, _("Select code file"));
    int nResult = dlg.ShowModal();
    if(nResult != wxID_OK)
        return;
    if(m_pFnCode)
        delete m_pFnCode;

    m_pFnCode= new wxFileName(dlg.GetPath());
    if(!m_pFnCode->FileExists())
    {
        delete m_pFnCode;
        m_pFnCode = NULL;
    }
//    if(m_pAvr && !m_pAvr->IsRunning())
//        m_pAvr->LoadCode(m_pFnFirmware->GetPath());

}

void wxArduinoFrame::OnMenuitemLoadHexSelected(wxCommandEvent& event)
{
    wxString sPath, sFile;
    if(m_pFnHex)
    {
        sPath = m_pFnHex->GetPath();
        sFile = m_pFnHex->GetName();
    }
    wxFileDialog dlg(this, _("Select hex file"), sPath, sFile, _("Intel hex files (*.ihex;*.hex)|*.ihex;*.hex|All files (*.*)|*.*"));
    int nResult = dlg.ShowModal();
    if(nResult != wxID_OK)
        return;
    if(m_pFnHex)
        delete m_pFnHex;

    m_pFnHex = new wxFileName(dlg.GetPath());
    if(!m_pFnHex->FileExists())
    {
        delete m_pFnHex;
        m_pFnHex = NULL;
        return;
    }
    if(m_pAvr && !m_pAvr->IsRunning())
        m_pAvr->LoadHex(m_pFnHex->GetPath());
}

void wxArduinoFrame::OnMenuitemWipeSelected(wxCommandEvent& event)
{
    if(wxYES != wxMessageBox(_("This will clear the program memory of the device.\n\nAre you sure?"), _("Wipe memory"), wxYES_NO|wxCENTER))
        return;
    delete m_pFnCode;
    m_pFnCode = NULL;
    delete m_pFnFirmware;
    m_pFnFirmware = NULL;
    delete m_pFnHex;
    m_pFnHex = NULL;
    if(m_pAvr)
        m_pAvr->Init();
    Log(_("Wiping MCU"));
}

void wxArduinoFrame::Log(const wxChar *szString, ...)
{
    va_list argptr;
    va_start(argptr, szString);

    wxString sMessage;
    sMessage.PrintfV(szString, argptr);
    va_end(argptr);

    //Limit list to LOG_MAX entries
    if(m_pLstLog->GetCount() >= m_nLogMax)
        m_pLstLog->Delete(0);
    //Create timestamp
    wxString sTimeStamp = wxDateTime::Now().FormatISODate();
    sTimeStamp << wxT(" ") << wxDateTime::Now().FormatISOTime() << wxT(" - ");
    //Write message to log
    int nIndex = m_pLstLog->Append(sTimeStamp + sMessage);
    //Scroll lock
    if(!m_bScrollLock)
        m_pLstLog->SetFirstItem(nIndex);
	if(!m_pFileLog)
		return;
	if(m_dtLog != wxDateTime::Today())
	{
		//Create new log file by closing and re-opening
		delete m_pFileLog;
		m_pFileLog = NULL;
		m_dtLog = wxDateTime::Today();
		OpenLogFile(true);
	}
	m_pFileLog->Write(sTimeStamp + sMessage + wxT("\r\n"));
}

void wxArduinoFrame::OpenLogFile(bool bOpen)
{
	if(bOpen && !m_pFileLog)
	{
		wxString sLogPath = _("log/riban/wxArduino"); //!@todo use appropriate log file path (or system logging mechanism)
		if(!wxFileName::DirExists(sLogPath))
			wxFileName::Mkdir(sLogPath, 0777, wxPATH_MKDIR_FULL);
		m_pFileLog = new wxFile(wxString::Format(wxT("%s/%s.log"), sLogPath.c_str(), wxDateTime::Now().FormatISODate().c_str()), wxFile::write_append);
		m_dtLog = wxDateTime::Today();
		Log(wxT("--Start logging to file--"));
	}
	if(!bOpen && m_pFileLog)
	{
		Log(wxT("--Stop logging to file--"));
		delete m_pFileLog;
		m_pFileLog = NULL;
	}
	m_pMenuitemLogToFile->Check(NULL != m_pFileLog);
}

void wxArduinoFrame::OnMenuitemLogToFileSelected(wxCommandEvent& event)
{
    OpenLogFile(m_pMenuitemLogToFile->IsCheckable());
}

void wxArduinoFrame::OnMenuitemSerialSelected(wxCommandEvent& event)
{
    m_bSerialEnabled = m_pMenuitemSerial->IsChecked();
}
