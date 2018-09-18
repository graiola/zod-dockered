///-----------------------------------------------------------------
///
/// @file      zod_launcherFrm.h
/// @author    Mike
/// Created:   8/14/2010 6:01:04 PM
/// @section   DESCRIPTION
///            zod_launcherFrm class declaration
///
///------------------------------------------------------------------

#ifndef __ZOD_LAUNCHERFRM_H__
#define __ZOD_LAUNCHERFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/menu.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbox.h>
////Header Include End

////Dialog Style Start
#undef zod_launcherFrm_STYLE
#define zod_launcherFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class zod_launcherFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
		void WxButton1Click(wxCommandEvent& event);
	public:
		zod_launcherFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("zod_launcher"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = zod_launcherFrm_STYLE);
		virtual ~zod_launcherFrm();
		void Mnuquit1005Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
		void WxEdit1Updated(wxCommandEvent& event);
		void WxCheckBox1Click(wxCommandEvent& event);
		void WxCheckBox2Click(wxCommandEvent& event);
		void WxEdit2Updated(wxCommandEvent& event);
		void WxEdit3Updated(wxCommandEvent& event);
		void WxChoice1Selected(wxCommandEvent& event );
		void WxEdit4Updated(wxCommandEvent& event);
		void WxEdit5Updated(wxCommandEvent& event);
		void WxCheckBox3Click(wxCommandEvent& event);
		void WxCheckBox4Click(wxCommandEvent& event);
		void WxCheckBox5Click(wxCommandEvent& event);
		void WxButton3Click(wxCommandEvent& event);
		void WxEdit7Updated(wxCommandEvent& event);
		void WxCheckBox6Click(wxCommandEvent& event);
		void WxCheckBox7Click(wxCommandEvent& event);
		void WxCheckBox8Click(wxCommandEvent& event);
		void WxCheckBox9Click(wxCommandEvent& event);
		void WxCheckBox10Click(wxCommandEvent& event);
		void WxCheckBox11Click(wxCommandEvent& event);
		void WxEdit8Updated(wxCommandEvent& event);
		void WxEdit9Updated(wxCommandEvent& event);
		void WxButton4Click(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton4;
		wxStaticText *WxStaticText11;
		wxStaticText *WxStaticText10;
		wxTextCtrl *WxEdit9;
		wxTextCtrl *WxEdit8;
		wxMenuBar *WxMenuBar1;
		wxCheckBox *WxCheckBox11;
		wxCheckBox *WxCheckBox10;
		wxCheckBox *WxCheckBox9;
		wxCheckBox *WxCheckBox8;
		wxStaticBox *WxStaticBox5;
		wxCheckBox *WxCheckBox7;
		wxCheckBox *WxCheckBox6;
		wxTextCtrl *WxEdit7;
		wxStaticText *WxStaticText9;
		wxButton *WxButton3;
		wxStaticText *WxStaticText8;
		wxTextCtrl *WxEdit6;
		wxStaticBox *WxStaticBox4;
		wxCheckBox *WxCheckBox5;
		wxCheckBox *WxCheckBox4;
		wxCheckBox *WxCheckBox3;
		wxStaticText *WxStaticText7;
		wxTextCtrl *WxEdit5;
		wxTextCtrl *WxEdit4;
		wxStaticText *WxStaticText6;
		wxChoice *WxChoice1;
		wxStaticText *WxStaticText5;
		wxTextCtrl *WxEdit3;
		wxStaticText *WxStaticText4;
		wxStaticBox *WxStaticBox3;
		wxTextCtrl *WxEdit2;
		wxStaticText *WxStaticText3;
		wxCheckBox *WxCheckBox2;
		wxCheckBox *WxCheckBox1;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxTextCtrl *WxEdit1;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxStaticBox *WxStaticBox2;
		wxStaticBox *WxStaticBox1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON4 = 1044,
			ID_WXSTATICTEXT11 = 1043,
			ID_WXSTATICTEXT10 = 1042,
			ID_WXEDIT9 = 1041,
			ID_WXEDIT8 = 1040,
			ID_MNU_FILE_1001 = 1001,
			ID_MNU_QUIT_1005 = 1005,
			ID_MNU_ABOUT_1003 = 1003,
			ID_MNU_ABOUT_1004 = 1004,
			
			ID_WXCHECKBOX11 = 1039,
			ID_WXCHECKBOX10 = 1038,
			ID_WXCHECKBOX9 = 1037,
			ID_WXCHECKBOX8 = 1036,
			ID_WXSTATICBOX5 = 1035,
			ID_WXCHECKBOX7 = 1034,
			ID_WXCHECKBOX6 = 1033,
			ID_WXEDIT7 = 1032,
			ID_WXSTATICTEXT9 = 1031,
			ID_WXBUTTON3 = 1030,
			ID_WXSTATICTEXT8 = 1028,
			ID_WXEDIT6 = 1027,
			ID_WXSTATICBOX4 = 1026,
			ID_WXCHECKBOX5 = 1025,
			ID_WXCHECKBOX4 = 1024,
			ID_WXCHECKBOX3 = 1023,
			ID_WXSTATICTEXT7 = 1022,
			ID_WXEDIT5 = 1021,
			ID_WXEDIT4 = 1020,
			ID_WXSTATICTEXT6 = 1019,
			ID_WXCHOICE1 = 1018,
			ID_WXSTATICTEXT5 = 1017,
			ID_WXEDIT3 = 1016,
			ID_WXSTATICTEXT4 = 1015,
			ID_WXSTATICBOX3 = 1014,
			ID_WXEDIT2 = 1013,
			ID_WXSTATICTEXT3 = 1012,
			ID_WXCHECKBOX2 = 1011,
			ID_WXCHECKBOX1 = 1010,
			ID_WXSTATICTEXT2 = 1009,
			ID_WXSTATICTEXT1 = 1008,
			ID_WXEDIT1 = 1007,
			ID_WXBUTTON2 = 1006,
			ID_WXBUTTON1 = 1005,
			ID_WXSTATICBOX2 = 1004,
			ID_WXSTATICBOX1 = 1003,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void ResetCommandLine();
		
		bool form_loaded;
};

#endif
