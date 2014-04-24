/***************************************************************
 * Name:      wxSimAVRGuiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2014-03-23
 * Copyright: Brian Walton (riban.co.uk)
 * License:
 **************************************************************/

#include "wxsimavrguiapp.h"

//(*AppHeaders
#include "mainframe.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxSimAVRGuiApp);

bool wxSimAVRGuiApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	mainFrame* Frame = new mainFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
