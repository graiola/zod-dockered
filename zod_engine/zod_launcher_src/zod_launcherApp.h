//---------------------------------------------------------------------------
//
// Name:        zod_launcherApp.h
// Author:      Mike
// Created:     8/14/2010 6:01:04 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __ZOD_LAUNCHERFRMApp_h__
#define __ZOD_LAUNCHERFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class zod_launcherFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
