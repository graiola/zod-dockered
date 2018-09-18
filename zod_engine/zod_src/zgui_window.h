#ifndef _ZGUIWINDOW_H_
#define _ZGUIWINDOW_H_

#include "constants.h"
#include "zsdl.h"
#include "zsdl_opengl.h"
#include "zmap.h"
#include "common.h"
#include "zbuildlist.h"
#include "ztime.h"
#include "zfont_engine.h"
#include "zobject.h"

class gui_flags
{
public:
	gui_flags(){ Clear(); };

	void Clear()
	{
		send_new_production = false;
		send_stop_production = false;
		place_cannon = false;
		do_login = false;
		open_createuser = false;
		do_createuser = false;
		open_login = false;

		login_name.clear();
		login_password.clear();
		user_name.clear();
		email.clear();
	}

	bool send_new_production;
	int pref_id;
	unsigned char pot, poid;

	bool send_stop_production;

	bool place_cannon;
	int cref_id;
	unsigned char coid;
	int cleft, cright, ctop, cbottom;

	bool do_login;
	bool open_createuser;
	bool do_createuser;
	bool open_login;
	string login_name;
	string login_password;
	string user_name;
	string email;
};

enum gui_button_state
{
	GUI_BUTTON_NORMAL, GUI_BUTTON_PRESSED, MAX_GUI_BUTTON_STATES
};

enum gui_button_type
{
	PLACE_GUI_BUTTON, OK_GUI_BUTTON, CANCEL_GUI_BUTTON, 
	UP_GUI_BUTTON, DOWN_GUI_BUTTON, LOGIN_MENU_BUTTON,
	CREATE_MENU_BUTTON, OK_MENU_BUTTON, CANCEL_MENU_BUTTON,
	MAX_GUI_BUTTON_TYPES
};

class ZGuiButton
{
	public:
		ZGuiButton();

		static void Init();

		void SetType(int type_);
		void SetOffsets(int x_offset_, int y_offset_);
		void DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x, int shift_y);
		bool Click(int x, int y);
		bool UnClick(int x, int y);
		void SetActive(bool active_);
		bool IsActive();
		
	protected:
		static bool finished_init;

		static void LoadButtonImages(ZSDL_Surface *the_button, string foldername, string buttonname);
		static ZSDL_Surface button_img[MAX_GUI_BUTTON_TYPES][MAX_GUI_BUTTON_STATES];

		int x_offset;
		int y_offset;

		int type;
		int state;
		bool active;
};

class ZGuiTextBox
{
public:
	ZGuiTextBox();

	void SetOffsets(int x_offset_, int y_offset_);
	void SetWidth(int width_);
	void DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x, int shift_y);
	bool Click(int x, int y);
	void KeyPress(int c);
	string &GetText();
	void SetActive(bool active_);
	bool IsActive();
	void SetSelected(bool selected_);
	bool IsSelected();
	void SetMaxText(int max_text_);
	void SetPassworded(bool passworded_);
	void SetUseGoodChars(bool good_chars_only_);
	void CreateRenderIfNeeded();

protected:
	void CreateRender();

	ZSDL_Surface render_img;

	string text;
	int max_text;
	bool passworded;
	bool good_chars_only;

	int x_offset;
	int y_offset;

	int width;
	bool active;
	bool selected;
};

class ZGuiWindow
{
	public:
		ZGuiWindow(ZTime *ztime_);

		virtual void Process(double &the_time);
		virtual void DoRender(ZMap &the_map, SDL_Surface *dest);
		virtual bool Click(int x_, int y_);
		virtual bool UnClick(int x_, int y_);
		virtual bool KeyPress(int c) { return false; }
		virtual bool WheelUpButton() { return false; }
		virtual bool WheelDownButton() { return false; }
		virtual ZObject *GetBuildingObj() { return NULL; }
		void SetCords(int x_, int y_);
		void SetBuildList(ZBuildList *buildlist_);
		bool KillMe();
		gui_flags &GetGFlags();
	protected:
		bool killme;
		int x, y;
		int width, height;

		gui_flags gflags;

		ZBuildList *buildlist;
		ZTime *ztime;
};

#endif
