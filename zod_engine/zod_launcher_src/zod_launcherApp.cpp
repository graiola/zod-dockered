//---------------------------------------------------------------------------
//
// Name:        zod_launcherApp.cpp
// Author:      Mike
// Created:     8/14/2010 6:01:04 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "zod_launcherApp.h"
#include "zod_launcherFrm.h"

IMPLEMENT_APP(zod_launcherFrmApp)

bool zod_launcherFrmApp::OnInit()
{
    zod_launcherFrm* frame = new zod_launcherFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int zod_launcherFrmApp::OnExit()
{
	return 0;
}
