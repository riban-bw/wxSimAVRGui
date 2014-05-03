#include "mainframe.h"
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/filedlg.h>
#include <wx/display.h>
#include <wx/textdlg.h>
#include <wx/wfstream.h>
#include <wx/stdstream.h>
#include "wxsimavr.h"
#include "profiledialog.h"

#include "images/play.xpm"
#include "images/pause.xpm"
#include "images/stop.xpm"
#include "images/reset.xpm"

//(*InternalHeaders(mainFrame)
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
//*)

//(*IdInit(mainFrame)
const long mainFrame::ID_TOOLBARITEM_START = wxNewId();
const long mainFrame::ID_TOOLBARITEM_PAUSE = wxNewId();
const long mainFrame::ID_TOOLBARITEM_STOP = wxNewId();
const long mainFrame::ID_TOOLBARITEM_RESET = wxNewId();
const long mainFrame::ID_TOOLBAR_CONTROL = wxNewId();
const long mainFrame::ID_LBLDEVICETYPE = wxNewId();
const long mainFrame::ID_LBLFREQUENCY = wxNewId();
const long mainFrame::ID_SPNFREQ = wxNewId();
const long mainFrame::ID_TXTLOG = wxNewId();
const long mainFrame::ID_PNLMAIN = wxNewId();
const long mainFrame::ID_MENUITEM_FIRMWARE = wxNewId();
const long mainFrame::ID_MENUITEM_CODE = wxNewId();
const long mainFrame::ID_MENUITEM_LOADHEX = wxNewId();
const long mainFrame::idMenuQuit = wxNewId();
const long mainFrame::ID_MENUITEM_SAVEPROFILE = wxNewId();
const long mainFrame::ID_MENUITEM_PROFILE = wxNewId();
const long mainFrame::ID_MENUITEM_MCU = wxNewId();
const long mainFrame::ID_MENUITEM_WIPE = wxNewId();
const long mainFrame::ID_MENUITEM_SERIAL = wxNewId();
const long mainFrame::ID_MENUITEM_VCD = wxNewId();
const long mainFrame::ID_MENUITEM_VCDFILE = wxNewId();
const long mainFrame::ID_MENUITEM_START = wxNewId();
const long mainFrame::ID_MENUITEM_PAUSE = wxNewId();
const long mainFrame::ID_MENUITEM_STOP = wxNewId();
const long mainFrame::ID_MENUITEM_RESET = wxNewId();
const long mainFrame::ID_MENUITEM_LOGTOFILE = wxNewId();
const long mainFrame::ID_MENUITEM_LOGVERBOSE = wxNewId();
const long mainFrame::idMenuAbout = wxNewId();
const long mainFrame::ID_STATUSBAR = wxNewId();
//*)
const long mainFrame::ID_MENUITEM_DELETEPROFILE = wxNewId();
const long mainFrame::ID_MENUITEM_RENAMEPROFILE = wxNewId();
const long mainFrame::ID_MENUITEM_NEWPROFILE = wxNewId();


BEGIN_EVENT_TABLE(mainFrame,wxFrame)
	//(*EventTable(mainFrame)
	//*)
END_EVENT_TABLE()

mainFrame::mainFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size) :
    m_pDeviceType(NULL),
    m_lFrequency(16000000),
    m_nLogMax(1000),
    m_bScrollLock(false),
    m_bInit(false),
    m_pFileLog(NULL),
    m_pFnFirmware(NULL),
    m_pFnCode(NULL),
    m_pFnConfig(NULL),
    m_pFnVcd(NULL)
{
	//(*Initialize(mainFrame)
	wxMenuItem* MenuItem2;
	wxFlexGridSizer* FlexGridSizer1;
	wxFlexGridSizer* FlexGridSizer2;
	wxMenu* Menu1;
	wxStaticText* StaticText1;
	wxFlexGridSizer* FlexGridSizer3;
	wxMenu* Menu2;

	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
	m_pAuiManager = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
	m_pToolbarControl = new wxAuiToolBar(this, ID_TOOLBAR_CONTROL, wxPoint(75,96), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
	m_pToolbarControl->AddTool(ID_TOOLBARITEM_START, _("Start"), play_xpm, wxNullBitmap, wxITEM_NORMAL, _("Start simulator"), wxEmptyString, NULL);
	m_pToolbarControl->AddTool(ID_TOOLBARITEM_PAUSE, _("Pause"), pause_xpm, wxNullBitmap, wxITEM_NORMAL, _("Pause simulator"), wxEmptyString, NULL);
	m_pToolbarControl->AddTool(ID_TOOLBARITEM_STOP, _("Stop"), stop_xpm, wxNullBitmap, wxITEM_NORMAL, _("Stop simulator"), wxEmptyString, NULL);
	m_pToolbarControl->AddTool(ID_TOOLBARITEM_RESET, _("Reset"), reset_xpm, wxNullBitmap, wxITEM_NORMAL, _("Reset MCU"), wxEmptyString, NULL);
	m_pToolbarControl->Realize();
	m_pAuiManager->AddPane(m_pToolbarControl, wxAuiPaneInfo().Name(_T("ToolbarControl")).ToolbarPane().Caption(_("Toolbar")).CloseButton(false).Layer(10).Top().Gripper());
	m_pPnlMain = new wxPanel(this, ID_PNLMAIN, wxPoint(172,246), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PNLMAIN"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(1);
	FlexGridSizer3 = new wxFlexGridSizer(0, 0, 0, 0);
	FlexGridSizer3->AddGrowableCol(4);
	StaticText1 = new wxStaticText(m_pPnlMain, wxID_ANY, _("MCU"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("wxID_ANY"));
	FlexGridSizer3->Add(StaticText1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pLblDeviceType = new wxStaticText(m_pPnlMain, ID_LBLDEVICETYPE, _("-"), wxDefaultPosition, wxSize(100,17), wxALIGN_CENTRE, _T("ID_LBLDEVICETYPE"));
	m_pLblDeviceType->SetBackgroundColour(wxColour(255,255,255));
	FlexGridSizer3->Add(m_pLblDeviceType, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pLblFrequency = new wxStaticText(m_pPnlMain, ID_LBLFREQUENCY, _("Frequency"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_LBLFREQUENCY"));
	FlexGridSizer3->Add(m_pLblFrequency, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	m_pSpnFreq = new wxSpinCtrl(m_pPnlMain, ID_SPNFREQ, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 99999999, 0, _T("ID_SPNFREQ"));
	m_pSpnFreq->SetValue(_T("0"));
	FlexGridSizer3->Add(m_pSpnFreq, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	FlexGridSizer2->AddGrowableRow(0);
	m_pTxtLog = new wxTextCtrl(m_pPnlMain, ID_TXTLOG, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TXTLOG"));
	FlexGridSizer2->Add(m_pTxtLog, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	m_pPnlMain->SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(m_pPnlMain);
	FlexGridSizer1->SetSizeHints(m_pPnlMain);
	m_pAuiManager->AddPane(m_pPnlMain, wxAuiPaneInfo().Name(_T("PanelMain")).CenterPane().Caption(_("Main Panel")).FloatingPosition(wxPoint(0,0)).FloatingSize(wxSize(0,0)));
	m_pAuiManager->Update();
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
	m_pMenuitemSaveProfile = new wxMenuItem(m_pMenuProfile, ID_MENUITEM_SAVEPROFILE, _("Save current profile\tShift+Ctrl+S"), _("Saves the current profile with new name"), wxITEM_NORMAL);
	m_pMenuProfile->Append(m_pMenuitemSaveProfile);
	m_pMenuDevice->Append(ID_MENUITEM_PROFILE, _("Profile"), m_pMenuProfile, wxEmptyString);
	m_pMenuMcu = new wxMenu();
	m_pMenuMcu->Break();
	m_pMenuDevice->Append(ID_MENUITEM_MCU, _("MCU"), m_pMenuMcu, wxEmptyString);
	m_pMenuitemWipe = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_WIPE, _("Wipe device"), _("Wipe all data from device"), wxITEM_NORMAL);
	m_pMenuDevice->Append(m_pMenuitemWipe);
	m_pMenuitemSerial = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_SERIAL, _("Enable Serial Port"), _("Enable the serial port on the MCU"), wxITEM_CHECK);
	m_pMenuDevice->Append(m_pMenuitemSerial);
	m_pMenuitemVcd = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_VCD, _("Enable VCD logging"), wxEmptyString, wxITEM_CHECK);
	m_pMenuDevice->Append(m_pMenuitemVcd);
	m_pMenuitemVcdFile = new wxMenuItem(m_pMenuDevice, ID_MENUITEM_VCDFILE, _("Select VCD log file"), _("Selects the file to log VCD traces to"), wxITEM_NORMAL);
	m_pMenuDevice->Append(m_pMenuitemVcdFile);
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
	m_pMenuitemLogVerbose = new wxMenuItem(m_pMenuLog, ID_MENUITEM_LOGVERBOSE, _("Verbose"), _("Enable verbose logging"), wxITEM_CHECK);
	m_pMenuLog->Append(m_pMenuitemLogVerbose);
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

	Connect(ID_TOOLBARITEM_START,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuStart);
	Connect(ID_TOOLBARITEM_PAUSE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuPause);
	Connect(ID_TOOLBARITEM_STOP,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuStop);
	Connect(ID_TOOLBARITEM_RESET,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuReset);
	Connect(ID_SPNFREQ,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&mainFrame::OnSpnFreqChange);
	Connect(ID_MENUITEM_FIRMWARE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemFirmwareSelected);
	Connect(ID_MENUITEM_CODE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemCodeSelected);
	Connect(ID_MENUITEM_LOADHEX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemLoadHexSelected);
	Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnQuit);
	Connect(ID_MENUITEM_SAVEPROFILE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemSaveProfileSelected);
	Connect(ID_MENUITEM_WIPE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemWipeSelected);
	Connect(ID_MENUITEM_SERIAL,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemSerialSelected);
	Connect(ID_MENUITEM_VCD,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemVcdSelected);
	Connect(ID_MENUITEM_VCDFILE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemVcdFileSelected);
	Connect(ID_MENUITEM_START,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuStart);
	Connect(ID_MENUITEM_PAUSE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuPause);
	Connect(ID_MENUITEM_STOP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuStop);
	Connect(ID_MENUITEM_RESET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemMcuReset);
	Connect(ID_MENUITEM_LOGTOFILE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemLogToFileSelected);
	Connect(ID_MENUITEM_LOGVERBOSE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnMenuitemLogVerboseSelected);
	Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&mainFrame::OnAbout);
	//*)
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&mainFrame::OnClose);
    Connect(wxID_ANY, wxEVT_AVR_STATUS, (wxObjectEventFunction)&mainFrame::HandleAvrStatus);
    Connect(wxID_ANY, wxEVT_AVR_WRITE, (wxObjectEventFunction)&mainFrame::HandleAvrWrite);

    //Configure logging
    m_pLog = new wxLogTextCtrl(m_pTxtLog);

    wxLog::SetActiveTarget(m_pLog);
    wxLog::SetTimestamp("%Y-%m-%d %H:%M:%S");

    Running(AVR_STATUS_STOPPED);

    wxString sTmp;
    if(wxGetEnv("HOME", &sTmp))
        m_pFnConfig = new wxFileName(sTmp + "/.config/riban/wxsimavr/config.cfg");

    ReadConfig();
    m_pSpnFreq->SetValue(m_lFrequency);
    int nId = m_pMenuDevice->FindItem(m_pDeviceType->name);
    if(wxNOT_FOUND != nId)
    {
        //Select MCU device type
        wxCommandEvent event(0, wxEVT_COMMAND_MENU_SELECTED);
        event.SetId(nId);
        OnMenuDeviceType(event);
        m_pMenuDevice->Check(nId, true);
    }
    m_bInit = true;
    wxLogDebug("mainFrame completed constructor\n");
}

mainFrame::~mainFrame()
{
    //(*Destroy(mainFrame)
    //*)
    wxLogDebug("__FUNCTION__");
    delete m_pFnFirmware;
    delete m_pFnHex;
    delete m_pFnCode;
    delete m_pFnConfig;
    delete m_pFnVcd;
    delete m_pFileLog;
    wxLog::SetActiveTarget(NULL); //Reset log destination before deleting logging handler
    delete m_pLog;
    m_pAuiManager->UnInit(); //fixes assertion described here: http://forums.wxwidgets.org/viewtopic.php?f=1&t=32138
}

void mainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void mainFrame::OnClose(wxCloseEvent &event)
{
    wxLogMessage("Application closing");
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

void mainFrame::OnAbout(wxCommandEvent& event)
{
    for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); it++)
        wxLogVerbose("MCU device type id=%ld, name='%s'", it->second->id, it->second->name);
    wxMessageBox("wxSimAVRGui - Brian Walton\n(C) riban 2014", "About");
}

void mainFrame::OnMenuitemMcuStart(wxCommandEvent& event)
{
    wxLogDebug("__FUNCTION__");
    if(!m_pDeviceType)
        return; //No device type selected
    if(!m_pAvr)
    {
        //Create instance of the wxAvr thread
        m_pAvr = new wxAvr(this, m_pDeviceType->name, m_lFrequency);
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
                wxLogMessage("UART /tmp/simavr-uart0");
            }
            if(m_bVcdEnabled)
            {
                m_pAvr->InitVcd(wxFileName("walt.vcd"), 100000); //!@todo Set VCD filename
                for(unsigned int nIndex = 0; nIndex < 8; ++nIndex)
                    m_pAvr->AddSignal(nIndex, wxString::Format("Output %d", nIndex));
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

void mainFrame::OnMenuitemMcuStop(wxCommandEvent& event)
{
    wxLogDebug("__FUNCTION__");
    if(m_pAvr)
    {
        m_pAvr->Stop();
        m_pAvr->StopUart();
    }
}

void mainFrame::OnMenuitemMcuPause(wxCommandEvent& event)
{
    if(m_pAvr && m_pAvr->IsRunning())
    {
        if(m_pAvr->Pause() != wxTHREAD_NO_ERROR )
            wxLogError(wxT("Can't pause the thread!"));
        else
            wxLogMessage("Paused MCU");
    }
}

void mainFrame::EnableAllMenuItems(wxMenu* pMenu, bool bEnable)
{
    if(!pMenu)
        return;
    for(size_t nPos = 0; nPos < pMenu->GetMenuItemCount(); nPos++)
        pMenu->FindItemByPosition(nPos)->Enable(bEnable);
}

void mainFrame::Running(unsigned int nState)
{
    switch(nState)
    {
        case AVR_STATUS_STOPPED:
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_START, true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_PAUSE, false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_STOP,  false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_RESET, false);
            m_pMenuitemStart->Enable();
            m_pMenuitemPause->Enable(false);
            m_pMenuitemStop->Enable(false);
            m_pMenuitemReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Stopped"), 2);
            if(m_bInit)
                wxLogMessage("MCU stopped");
            EnableAllMenuItems(m_pMenuDevice);
            m_pMenuitemCode->Enable();
            m_pMenuitemFirmware->Enable();
            m_pMenuitemLoadHex->Enable();
            break;
        case AVR_STATUS_RUNNING:
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_START, false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_PAUSE, true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_STOP,  true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_RESET, true);
            m_pMenuitemStart->Enable(false);
            m_pMenuitemPause->Enable();
            m_pMenuitemStop->Enable();
            m_pMenuitemReset->Enable();
            m_pStatusBar->SetStatusText(wxT("Running"), 2);
            m_pMenuitemCode->Enable(false);
            m_pMenuitemFirmware->Enable(false);
            m_pMenuitemLoadHex->Enable(false);
            wxLogMessage("MCU running");
            EnableAllMenuItems(m_pMenuDevice, false);
            break;
        case AVR_STATUS_PAUSED:
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_START, true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_PAUSE, false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_STOP,  true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_RESET, false);
            m_pMenuitemStart->Enable();
            m_pMenuitemPause->Enable(false);
            m_pMenuitemStop->Enable();
            m_pMenuitemReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Paused"), 2);
            m_pMenuitemCode->Enable(false);
            m_pMenuitemFirmware->Enable(false);
            m_pMenuitemLoadHex->Enable(false);
            wxLogMessage("MCU paused");
            EnableAllMenuItems(m_pMenuDevice, false);
            break;
        case AVR_STATUS_CRASHED:
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_START, true);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_PAUSE, false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_STOP,  false);
            m_pToolbarControl->EnableTool(ID_TOOLBARITEM_RESET, false);
            m_pMenuitemStart->Enable();
            m_pMenuitemPause->Enable(false);
            m_pMenuitemStop->Enable(false);
            m_pMenuitemReset->Enable(false);
            m_pStatusBar->SetStatusText(wxT("Crashed"), 2);
            m_pMenuitemCode->Enable();
            m_pMenuitemFirmware->Enable();
            m_pMenuitemLoadHex->Enable();
            wxLogMessage("MCU crashed");
            EnableAllMenuItems(m_pMenuDevice);
            break;
    }
    m_pToolbarControl->Refresh();
}

void mainFrame::OnMenuitemMcuReset(wxCommandEvent& event)
{
    if(m_pAvr)
        m_pAvr->Reset();
}

void mainFrame::OnMenuDeviceType(wxCommandEvent& event)
{
    std::map<long,avrDevice*>::iterator it = m_mDevices.find(event.GetId());
    if(it == m_mDevices.end())
        return;
    avrDevice* pDevice = it->second;
    if(!pDevice)
        return;
    m_pDeviceType = pDevice;
    m_pLblDeviceType->SetLabel(pDevice->name);
}

void mainFrame::OnMenuProfile(wxCommandEvent& event)
{
    avrProfile* pProfile = m_mProfiles[event.GetId()];
    if(!pProfile)
        return;
    if(!pProfile->pDevice)
        return;
    m_pDeviceType = pProfile->pDevice;
    m_pLblDeviceType->SetLabel(m_pDeviceType->name);
    m_lFrequency = pProfile->lFrequency;
    m_pSpnFreq->SetValue(m_lFrequency);
}

void mainFrame::ReadConfig()
{
    if(!m_pFnConfig)
        return; //Configuration path not configured
    wxString sGroup, sTmp;
    long lCookie;

    //Populate map of MCU types
    wxConfig* pConfig = new wxConfig("wxSimAVRGui", "riban", m_pFnConfig->GetPath() + "/mcu.cfg");
    bool bMore = pConfig->GetFirstGroup(sGroup, lCookie);
    while(bMore)
    {
        AddDeviceType(sGroup, pConfig->Read(sGroup + "/description", wxEmptyString));
        bMore = pConfig->GetNextGroup(sGroup, lCookie);
    }
    delete pConfig;

    //Create a default MCU type if non configured
    if(0 == m_mDevices.size())
        AddDeviceType("atmega328", "AVR ATmega328 - 8 bit, 32MB Flash, 2MB RAM");

    //Populate map of profiles
    pConfig = new wxConfig("wxSimAVRGui", "riban", m_pFnConfig->GetPath() + "/profile.cfg");
    bMore = pConfig->GetFirstGroup(sGroup, lCookie);
    while(bMore)
    {
        wxString sName, sDeviceType, sTitle, sDescription;
        long lFrequency;
        pConfig->Read(sGroup + "/device", &sDeviceType, wxEmptyString);
        pConfig->Read(sGroup + "/name", &sTitle, wxEmptyString);
        pConfig->Read(sGroup + "/description", &sDescription, wxEmptyString);
        pConfig->Read(sGroup + "/frequency", &lFrequency, 0l);
        if(!AddProfile(sGroup, sDeviceType, lFrequency, sTitle, sDescription))
            wxLogError("Configuration error: Bad configuration of profile [%s]", sGroup.c_str());
        bMore = pConfig->GetNextGroup(sGroup, lCookie);
    }
    delete pConfig;

    //Read application configuration
    pConfig = new wxConfig("wxSimAVRGui", "riban", m_pFnConfig->GetPath() + ("/config.cfg"));
    pConfig->Read("/state/mcu", &sTmp, wxEmptyString);
    m_pDeviceType = GetDeviceTypeByDeviceName(sTmp);
    if(!m_pDeviceType)
    {
        std::map<long,avrDevice*>::iterator it = m_mDevices.begin();
        m_pDeviceType = it->second; //This exists because it is specifically created above if m_pDeviceType is empty
        wxLogMessage("MCU device type not configured - using first defined (%s)", m_pDeviceType->name);
    }
    pConfig->Read("/state/frequency", &m_lFrequency);
    if(pConfig->Read("/state/firmware", &sTmp))
        m_pFnFirmware = new wxFileName(sTmp);
    if(pConfig->Read("/state/ihex", &sTmp))
        m_pFnHex= new wxFileName(sTmp);
    pConfig->Read("/state/serial", &m_bSerialEnabled, false);
    pConfig->Read("/state/vcdfile", &sTmp, "wxSimAVR.vcd");
    m_pFnVcd = new wxFileName(sTmp);
    pConfig->Read("/state/vcd", &m_bVcdEnabled, false);
    m_pMenuitemSerial->Check(m_bSerialEnabled);
    m_pMenuitemVcd->Check(m_bVcdEnabled);

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
	EnableLogToFile(bTmp);
	pConfig->Read(wxT("/Log/Verbose"), &bTmp, false);
	wxLog::SetVerbose(bTmp);
	m_pMenuitemLogVerbose->Check(bTmp);

    delete pConfig;
}

void mainFrame::WriteConfig()
{
    if(!m_pFnConfig)
        return;
    if(!m_pFnConfig->DirExists())
    {
        if(m_pFnConfig->Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL))
            wxLogMessage("Created configuration directory");
        else
        {
            wxLogMessage("Failed to create configuration directory");
            return;
        }
    }

    wxConfig* pConfig = new wxConfig("wxSimAVRGui", "riban", m_pFnConfig->GetPath() + "/config.cfg");
    if(m_pDeviceType)
        pConfig->Write("/state/mcu", m_pDeviceType->name);
    pConfig->Write("/state/frequency", m_lFrequency);
    if(m_pFnFirmware)
        pConfig->Write("/state/firmware", m_pFnFirmware->GetFullPath());
    else
        pConfig->DeleteEntry("/state/firmware");
    if(m_pFnHex)
        pConfig->Write("/state/ihex", m_pFnHex->GetFullPath());
    else
        pConfig->DeleteEntry("/state/ihex");
    pConfig->Write(wxT("/state/serial"), m_bSerialEnabled);
    if(m_pFnVcd)
        pConfig->Write("/state/vcdfile", m_pFnVcd->GetFullPath());
    pConfig->Write("/state/vcd", m_bVcdEnabled);

    //Environment
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
	pConfig->Write(wxT("/Log/Verbose"), wxLog::GetVerbose());
    delete pConfig;

    //Profile
    pConfig = new wxConfig("wxSimAVRGui", "riban", m_pFnConfig->GetPath() + "/profile.cfg", wxEmptyString, wxCONFIG_USE_NO_ESCAPE_CHARACTERS);
    pConfig->DeleteAll();
    for(std::map<long,avrProfile*>::iterator it = m_mProfiles.begin(); it != m_mProfiles.end(); it++)
    {
        avrProfile* pProfile = it->second;
        pConfig->Write(pProfile->name + "/description", pProfile->description);
        pConfig->Write(pProfile->name + "/frequency", pProfile->lFrequency);
        pConfig->Write(pProfile->name + "/device", pProfile->pDevice->name);
    }
    delete pConfig;
}

void mainFrame::OnSpnFreqChange(wxSpinEvent& event)
{
    m_lFrequency = m_pSpnFreq->GetValue();
}

void mainFrame::HandleAvrStatus(wxCommandEvent &event)
{
    wxLogDebug("__FUNCTION__");
    Running(event.GetInt());
}

void mainFrame::HandleAvrWrite(wxCommandEvent &event)
{
    wxLogDebug("__FUNCTION__");
}

void mainFrame::OnMenuitemFirmwareSelected(wxCommandEvent& event)
{
    wxString sPath, sFile;
    if(m_pFnFirmware)
    {
        sPath = m_pFnFirmware->GetPath();
        sFile = m_pFnFirmware->GetName();
    }
    wxFileDialog dlg(this, "Select firmware file", sPath, sFile);
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

void mainFrame::OnMenuitemCodeSelected(wxCommandEvent& event)
{
    wxLogMessage("Load Code not implemented");
    return;
    wxFileDialog dlg(this, "Select code file");
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

void mainFrame::OnMenuitemLoadHexSelected(wxCommandEvent& event)
{
    wxString sPath, sFile;
    if(m_pFnHex)
    {
        sPath = m_pFnHex->GetPath();
        sFile = m_pFnHex->GetName();
    }
    wxFileDialog dlg(this, "Select hex file", sPath, sFile, "Intel hex files (*.ihex;*.hex)|*.ihex;*.hex|All files (*.*)|*.*");
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

void mainFrame::OnMenuitemWipeSelected(wxCommandEvent& event)
{
    if(wxYES != wxMessageBox("This will clear the program memory of the device.\n\nAre you sure?", "Wipe memory", wxYES_NO|wxCENTER))
        return;
    delete m_pFnCode;
    m_pFnCode = NULL;
    delete m_pFnFirmware;
    m_pFnFirmware = NULL;
    delete m_pFnHex;
    m_pFnHex = NULL;
    if(m_pAvr)
        m_pAvr->Init();
    wxLogMessage("Wiping MCU");
}

void mainFrame::EnableLogToFile(bool bEnable)
{
    if(bEnable)
    {
        wxString sHome;
        wxGetEnv("HOME", &sHome);
        wxFileName fnLogPath(sHome + "/log/riban/wxSimAVRGui.log"); //!@todo Use appropriate path to log file
        if(!fnLogPath.DirExists())
            fnLogPath.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
        if(!fnLogPath.DirExists()) //Can't create log path
        {
            m_pMenuitemLogToFile->Check(false);
            return;
        }
        if(!m_pFileLog)
            m_pFileLog = new wxFile();
        wxFileOutputStream* pStream = new wxFileOutputStream(*m_pFileLog);
        m_pFileLog->Open(fnLogPath.GetFullPath(), wxFile::write_append); //Open file with append - shame this isn't easier in wxWidgets
        if(!m_pFileLog || !m_pFileLog->IsOpened()) //Can't create log file
        {
            delete m_pFileLog;
            m_pMenuitemLogToFile->Check(false);
            return;
        }
        new wxLogChain(new wxLogStream(new wxStdOutputStream(*pStream)));
		wxLogMessage("Start logging to file: %s", fnLogPath.GetFullPath());
    }
    else
    {
        if(!m_pFileLog)
            return;
		wxLogMessage("Stop logging to file");
		//!@todo delete the 3 objects used for logging to file; wxStdOutputStream, wxLogStream & wxLogChain
		delete wxLog::SetActiveTarget(m_pLog);
		delete m_pFileLog;
		m_pFileLog = NULL;
    }
	m_pMenuitemLogToFile->Check(NULL != m_pFileLog);
}

void mainFrame::OnMenuitemLogToFileSelected(wxCommandEvent& event)
{
    EnableLogToFile(m_pMenuitemLogToFile->IsChecked());
}

void mainFrame::OnMenuitemSerialSelected(wxCommandEvent& event)
{
    m_bSerialEnabled = m_pMenuitemSerial->IsChecked();
}

void mainFrame::OnMenuitemVcdFileSelected(wxCommandEvent& event)
{
    wxString sPath, sFile;
    if(m_pFnVcd)
    {
        sPath = m_pFnVcd->GetPath();
        sFile = m_pFnVcd->GetName();
    }
    wxFileDialog dlg(this, "Select file to log VCD trace", sPath, sFile, "VCD files (*.vcd)|*.vcd|All files (*.*)|*.*", wxFD_SAVE);
    int nResult = dlg.ShowModal();
    if(nResult != wxID_OK)
        return;
    if(m_pFnVcd)
        delete m_pFnVcd;

    m_pFnVcd = new wxFileName(dlg.GetPath());
}

void mainFrame::OnMenuitemVcdSelected(wxCommandEvent& event)
{
    m_bVcdEnabled = m_pMenuitemVcd->IsChecked();
}

void mainFrame::OnMenuitemSaveProfileSelected(wxCommandEvent& event)
{
    if(!m_pDeviceType)
    {
        wxLogMessage("Can't create profile when MCU not defined");
        return;
    }
    ProfileDialog dlg(this);
    dlg.SetProfileName(m_pDeviceType->name);
    dlg.SetDescription(m_pDeviceType->description);
    dlg.SetFrequency(m_lFrequency);
    for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); it++) //!@todo last iteration of this is crashing app!!!<<<***
        dlg.AddMcu(it->second->name);
    dlg.SetDeviceType(m_pDeviceType->name);

    if(dlg.ShowModal() == wxID_OK)
    {
        wxString sName = dlg.GetProfileName();
        avrDevice* pDevice = GetDeviceTypeByDeviceName(dlg.GetDeviceType());
        if(!pDevice)
            return;
        wxString sDeviceType = pDevice->name;
        long lFrequency = dlg.GetFrequency();
        wxString sTitle = dlg.GetTitle();
        wxString sDescription = dlg.GetDescription();

        AddProfile(sName, sDeviceType, lFrequency, sTitle, sDescription);
    }
}

avrProfile* mainFrame::AddProfile(const wxString& sName, const wxString& sDeviceType, long lFrequency, const wxString& sTitle, const wxString& sDescription)
{
    if(sName.IsEmpty())
    {
        wxLogMessage("Cannot add profile without a name");
        return NULL;
    }
    //Check for existing profile
    bool bDuplicate = false;
    for(std::map<long,avrProfile*>::iterator it = m_mProfiles.begin(); it != m_mProfiles.end(); ++it)
    {
        if(it->second->name != sName)
            continue;
        bDuplicate = true;
        break;
    }
    if(bDuplicate)
    {
        if(wxYES != wxMessageBox("Profile " + sName + " already exists. Replace?", "Duplicate profile name", wxYES_NO))
           return NULL;
    }

    avrDevice* pDevice = GetDeviceTypeByDeviceName(sDeviceType);
    if(!pDevice)
        return NULL; //There is no device of that type defined

    avrProfile* pProfile = new avrProfile;
    pProfile->pDevice = pDevice;
    pProfile->id = wxNewId();
    if(sTitle.IsEmpty())
        pProfile->name = sName;
    else
        pProfile->name = sTitle;
    if(!sDescription.IsEmpty())
        pProfile->description = sDescription;
    pProfile->lFrequency = lFrequency?lFrequency:8000000l;
    m_mProfiles[pProfile->id] = (pProfile);
    m_pMenuProfile->Append(new wxMenuItem(m_pMenuProfile, pProfile->id, pProfile->name, pProfile->description, wxITEM_NORMAL));
    Connect(pProfile->id, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&mainFrame::OnMenuProfile);
//    Connect(pProfile->id, wxEVT_ANY, (wxObjectEventFunction)&mainFrame::ShowProfileContext);
    //!@todo Add context menu to remove or replace profiles - don't know if you can have context menu drivern from menu item
    return pProfile;
}

avrDevice* mainFrame::GetDeviceTypeByDeviceName(const wxString& sName)
{
    for(std::map<long,avrDevice*>::iterator it = m_mDevices.begin(); it != m_mDevices.end(); it++)
    {
        if(it->second->name == sName)
            return it->second;
    }
    return NULL;
}

avrDevice* mainFrame::AddDeviceType(const wxString& sName, const wxString& sDescription)
{
    avrDevice* pDevice = GetDeviceTypeByDeviceName(sName);
    if(!pDevice)
        pDevice = new avrDevice(wxNewId(), sName, sDescription);
    pDevice->name = sName;
    pDevice->description = sDescription;
    m_mDevices[pDevice->id] = pDevice;
    m_pMenuMcu->Append(new wxMenuItem(m_pMenuMcu, pDevice->id, pDevice->name, pDevice->description, wxITEM_RADIO));
    Connect(pDevice->id, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&mainFrame::OnMenuDeviceType);
    return pDevice;
}

void mainFrame::OnMenuitemProfileContext(wxCommandEvent& event)
{
    //!@todo This does nothing (yet)
    wxLogMessage("Context menu");
}

void mainFrame::ShowProfileContext(wxCommandEvent& event)
{
    //!@todo This does nothing (yet)
    wxLogMessage("ShowMcuContext");
    wxMenu menuContext;
    new wxMenuItem(&menuContext, ID_MENUITEM_DELETEPROFILE, "Delete", "Delete this MCU type");
    new wxMenuItem(&menuContext, ID_MENUITEM_RENAMEPROFILE, "Rename", "Rename this MCU type");
    new wxMenuItem(&menuContext, ID_MENUITEM_NEWPROFILE, "New", "Create new MCU type");
    Connect(ID_MENUITEM_DELETEPROFILE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&mainFrame::OnMenuitemProfileContext);
    Connect(ID_MENUITEM_RENAMEPROFILE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&mainFrame::OnMenuitemProfileContext);
    Connect(ID_MENUITEM_NEWPROFILE, wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&mainFrame::OnMenuitemProfileContext);
    PopupMenu(&menuContext);
}

void mainFrame::OnMenuitemLogVerboseSelected(wxCommandEvent& event)
{
    wxLog::SetVerbose(event.IsChecked());
}
