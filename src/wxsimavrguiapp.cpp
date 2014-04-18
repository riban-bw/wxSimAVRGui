/***************************************************************
 * Name:      wxArduinoApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2014-03-23
 * Copyright: Brian Walton (riban.co.uk)
 * License:
 **************************************************************/

#include "wxsimavrguiapp.h"

//(*AppHeaders
#include "wxsimavrguimain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxArduinoApp);

bool wxArduinoApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxArduinoFrame* Frame = new wxArduinoFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
