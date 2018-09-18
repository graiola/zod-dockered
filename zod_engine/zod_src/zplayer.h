#ifndef _ZPLAYER_H_
#define _ZPLAYER_H_

#include "zclient.h"
#include "zsdl.h"
#include "zsdl_opengl.h"
#include "cursor.h"
#include "zmini_map.h"
#include "zfont_engine.h"
#include "zeffect.h"
#include "zcomp_message_engine.h"
#include "zgui_window.h"
#include "zteam.h"
#include "zmusic_engine.h"
//#include "zgfile.h"

#include "gwproduction.h"
#include "gwlogin.h"
#include "gwcreateuser.h"

struct news_entry
{
   public:
      char r,g,b;
      string message;
      double death_time;
      ZSDL_Surface text_image;
};

struct key_event
{
	int the_key;
	int the_unicode;
};

class selection_info
{
public:
	void SetZTime(ZTime *ztime_) { ztime = ztime_;}

	void Clear()
	{
		have_explosives = false;
		can_pickup_grenades = false;
		can_move = false;
		can_equip = false;
		can_attack = false;
		can_repair = false;
		can_be_repaired = false;
		selected_list.clear();
	}
	void ClearAll()
	{
		Clear();
		for(int i=0;i<10;i++)
			quick_group[i].clear();
	}
	void LoadGroup(int group);
	void SetGroup(int group);
	bool UpdateGroupMember(ZObject *obj);
	void SetupGroupDetails();
	void DeleteObject(ZObject *obj);

	bool have_explosives;
	bool can_pickup_grenades;
	bool can_move;
	bool can_equip;
	bool can_attack;
	bool can_repair;
	bool can_be_repaired;
	vector<ZObject*> selected_list;
	vector<ZObject*> quick_group[10];

	ZTime *ztime;
};

class mouse_button_info
{
public:
	mouse_button_info() { x=y=map_x=map_y=down=0; }
	int x, y;
	int map_x, map_y;
	bool down;
	bool started_over_hud;
	bool started_over_gui;
};

class ZPlayer : public ZClient
{
	public:
		ZPlayer();
		
		void SetDimensions(int w, int h);
		void SetSoundsOff(bool setoff);
		void SetMusicOff(bool setoff);
		void SetPlayerTeam(team_type player_team);
		void DisableCursor(bool disable_zcursor_);
		void SetWindowed(bool is_windowed_);
		void SetUseOpenGL(bool use_opengl_);
		void SetLoginName(string login_name_);
		void SetLoginPassword(string login_password_);
		void Setup();
		void Run();
	private:
		static int Load_Graphics(void *nothing);
		void InitSDL();
		void SetupEHandler();
		void SetupSelectionImages();
		void DoSplash();
		void ProcessSDL();
		void RenderScreen();
		void RenderObjects();
		void RenderSmallMapFiller();
		void RenderPreviousCursor();
		void RenderMouse();
		void RenderNews();
		void RenderGUI();
		void ProcessSocketEvents();
		void ProcessGame();
		void ProcessVerbalWarnings();
		void CollectSelectables();
		bool CouldCollectSelectables();
		void SelectZObject(ZObject *obj);
		void DetermineCursor();
		void ClearDevWayPointsOfSelected();
		void AddDevWayPointToSelected();
		void SendDevWayPointsOfSelected();
		bool DevWayPointsNoWay();
		bool ShiftDown();
		bool CtrlDown();
		bool AltDown();
		void ShowPcursor(int x, int y);
		void SetPcursor();
		void GiveHudSelected();
		void ProcessScroll();
		void ProcessResetGame();
		bool DoKeyScrollRight();
		bool DoKeyScrollLeft();
		bool DoKeyScrollUp();
		bool DoKeyScrollDown();
		bool DoMouseScrollRight();
		bool DoMouseScrollLeft();
		bool DoMouseScrollUp();
		bool DoMouseScrollDown();
		void StartMouseScrolling(int new_mouse_x, int new_mouse_y);
		void MissileObjectParticles(int x_, int y_, int radius, int particles);
		void DeleteObjectCleanUp(ZObject *obj);
		bool GuiAbsorbLClick();
		bool GuiAbsorbLUnClick();
		void DeleteCurrentGuiWindow();
		void ProcessChangeObjectAmount();
		void ProcessUnicode(int key);
		void PlayBuildingSounds();
		void FocusCameraTo(int map_x, int map_y);
		void ProcessFocusCamerato();
		void FocusCameraToFort();
		void InitAnimals();
		void ClearAnimals();
		void ProcessDisconnect();
		void AddNewsEntry(string message, int r = 255, int g = 255, int b = 255);
		void DisplayPlayerList();
		void DisplayFactoryProductionList();
		void DisplayFactoryProductionListUnit(ZObject *obj);
		void SendVoteYes();
		void SendVoteNo();
		void SendVotePass();
		void SendLogin();
		void SendCreateUser(string username, string lname, string lpass, string email);
		void InitMenus();
		void RefindOurFortRefID();
		void SetNextSoundSetting();

		//place cannon stuff
		void InitPlaceCannon();
		void SetPlaceCannonCords();
		void RenderPlaceCannon();
		bool DoPlaceCannon();
		
		//button stuff
		void ReSetupButtons();
		void HandleButton(hud_buttons button);
		void RandomlySelectUnitType(int type);
		void A_Button();
		void B_Button();
		void D_Button();
		void G_Button();
		void Menu_Button();
		void R_Button();
		void T_Button();
		void V_Button();
		void Z_Button();

		EventHandler<ZPlayer> ehandler;
		
		//tcp events
		static void test_event(ZPlayer *p, char *data, int size, int dummy);
		static void connect_event(ZPlayer *p, char *data, int size, int dummy);
		static void disconnect_event(ZPlayer *p, char *data, int size, int dummy);
		static void store_map_event(ZPlayer *p, char *data, int size, int dummy);
		static void add_new_object_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_zone_info_event(ZPlayer *p, char *data, int size, int dummy);
		static void display_news_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_waypoints_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_rallypoints_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_loc_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_team_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_attack_object_event(ZPlayer *p, char *data, int size, int dummy);
		static void delete_object_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_health_event(ZPlayer *p, char *data, int size, int dummy);
		static void end_game_event(ZPlayer *p, char *data, int size, int dummy);
		static void reset_game_event(ZPlayer *p, char *data, int size, int dummy);
		static void fire_object_missile_event(ZPlayer *p, char *data, int size, int dummy);
		static void destroy_object_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_building_state_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_building_cannon_list_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_computer_message_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_object_group_info_event(ZPlayer *p, char *data, int size, int dummy);
		static void do_crane_anim_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_repair_building_anim_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_settings_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_lid_open_event(ZPlayer *p, char *data, int size, int dummy);
		static void snipe_object_event(ZPlayer *p, char *data, int size, int dummy);
		static void driver_hit_effect_event(ZPlayer *p, char *data, int size, int dummy);
		static void clear_player_list_event(ZPlayer *p, char *data, int size, int dummy);
		static void add_player_event(ZPlayer *p, char *data, int size, int dummy);
		static void delete_player_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_name_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_team_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_mode_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_ignored_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_voteinfo_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_loginfo_event(ZPlayer *p, char *data, int size, int dummy);
		static void update_game_paused_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_vote_info_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_player_id_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_selectable_map_list_event(ZPlayer *p, char *data, int size, int dummy);
		static void display_login_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_grenade_amount_event(ZPlayer *p, char *data, int size, int dummy);
		static void pickup_grenade_event(ZPlayer *p, char *data, int size, int dummy);
		static void do_portrait_anim_event(ZPlayer *p, char *data, int size, int dummy);
		static void team_ended_event(ZPlayer *p, char *data, int size, int dummy);
		static void set_team_event(ZPlayer *p, char *data, int size, int dummy);
		static void poll_buy_regkey(ZPlayer *p, char *data, int size, int dummy);
		static void set_regkey(ZPlayer *p, char *data, int size, int dummy);
		
		//sdl events
		static void resize_event(ZPlayer *p, char *data, int size, int dummy);
		static void lclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void lunclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void rclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void runclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void mclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void munclick_event(ZPlayer *p, char *data, int size, int dummy);
		static void wheelup_event(ZPlayer *p, char *data, int size, int dummy);
		static void wheeldown_event(ZPlayer *p, char *data, int size, int dummy);
		static void keydown_event(ZPlayer *p, char *data, int size, int dummy);
		static void keyup_event(ZPlayer *p, char *data, int size, int dummy);
		static void motion_event(ZPlayer *p, char *data, int size, int dummy);
		
		int init_w, init_h;
		
		SDL_Surface *screen;
		TTF_Font *ttf_font;
		TTF_Font *ttf_font_7;
		int mouse_x, mouse_y;
		mouse_button_info lbutton, rbutton, mbutton;
		ZCursor cursor;
		ZCursor Pcursor;
		double pcursor_death_time;
		int pcursor_x, pcursor_y;
		bool disable_zcursor;
		bool lshift_down, rshift_down;
		bool right_down, left_down, up_down, down_down;
		bool lctrl_down, rctrl_down, lalt_down, ralt_down;
		double last_vert_scroll_time, last_horz_scroll_time;
		double vert_scroll_over, horz_scroll_over;
		bool collect_chat_message;
		string chat_message;
		int focus_to_x, focus_to_y;
		bool do_focus_to;
		double last_focus_to_time;
		double focus_to_original_distance;
		double final_focus_to_time;
		bool is_windowed;
		bool use_opengl;
		//bool music_on;
		int loaded_percent;
		bool show_chat_history;
		string login_name;
		string login_password;
		int fort_ref_id;
		int sound_setting;
		
		ZSDL_Surface splash_screen;
		Mix_Music *splash_music;
		SDL_Surface *game_icon;
		SDL_Thread *gload_thread;
		ZHud zhud;
		ZGuiWindow *gui_window;
		float splash_fade;
		vector<news_entry*> news_list;
		selection_info select_info;
		vector<ZEffect*> effect_list;
		vector<ZEffect*> new_effect_list;
		vector<ZObject*> bird_list;
		ZCompMessageEngine zcomp_msg;

		bool place_cannon;
		int place_cannon_ref_id;
		unsigned char place_cannon_oid;
		ZSDL_Surface place_cannon_ok_img;
		ZSDL_Surface place_cannon_nok_img;
		int place_cannon_tx, place_cannon_ty;
		int place_cannon_left, place_cannon_right;
		int place_cannon_top, place_cannon_bottom;

		ZSDL_Surface  selection_img[MAX_TEAM_TYPES];

		ZObject *hover_object;
		bool hover_object_can_attack;
		bool hover_object_can_enter_fort;

		//menus
		ZGuiWindow *active_menu;
		GWLogin *login_menu;
		GWCreateUser *create_user_menu;

		bool graphics_loaded;
};

#endif
