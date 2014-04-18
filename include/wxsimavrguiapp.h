/***************************************************************
 * Name:      wxArduinoApp.h
 * Purpose:   Defines Application Class
 * Author:    Brian Walton (brian@riban.co.uk)
 * Created:   2014-03-23
 * Copyright: Brian Walton (riban.co.uk)
 * License:
 **************************************************************/

#ifndef WXARDUINOAPP_H
#define WXARDUINOAPP_H

#include <wx/app.h>

class wxArduinoApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // WXARDUINOAPP_H
