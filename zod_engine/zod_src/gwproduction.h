#ifndef _ZGWPRODUCTION_H_
#define _ZGWPRODUCTION_H_

#include "zgui_window.h"
#include "zbuilding.h"

enum gwprod_type
{
	GWPROD_ROBOT, GWPROD_VEHICLE, GWPROD_FORT, GWPROD_TYPES_MAX
};

//enum gwprod_state
//{
//	GWPROD_PLACE, GWPROD_SELECT, GWPROD_BUILDING, GWPROD_PAUSED, MAX_GWPROD_STATES
//};

class ZObject;
class ZBuilding;

class GWProduction : public ZGuiWindow
{
	public:
		GWProduction(ZTime *ztime_);
		~GWProduction();

		static void Init();

		void Process(double &the_time);
		void DoRender(ZMap &the_map, SDL_Surface *dest);
		void SetType(int type_);
		void SetRefID(int ref_id_);
		void SetBuildingObj(ZBuilding *building_obj_);
		int GetRefID();
		bool Click(int x_, int y_);
		bool UnClick(int x_, int y_);
		bool WheelUpButton();
		bool WheelDownButton();
		ZObject *GetBuildingObj() { return building_obj; }
		void SetState(int state_);
	protected:
		void DrawPercentageBar(ZMap &the_map, SDL_Surface *dest);
		void DrawObject(ZMap &the_map, SDL_Surface *dest);
		void SetDrawObject();
		void ResetDrawObjectTo(unsigned char &ot, unsigned char &oid);
		void DeleteDrawObject();
		void ResetShowTime(int new_time);
		void RecalcShowTime();

		void DoUpButton();
		void DoDownButton();
		void DoOkButton();
		void DoCancelButton();
		void DoPlaceButton();

		static ZSDL_Surface base_img;
		static ZSDL_Surface name_label[GWPROD_TYPES_MAX];
		static ZSDL_Surface state_label[MAX_BUILDING_STATES][2];
		static ZSDL_Surface p_bar;
		static ZSDL_Surface p_bar_yellow;

		ZGuiButton up_button;
		ZGuiButton down_button;
		ZGuiButton ok_button;
		ZGuiButton cancel_button;
		ZGuiButton place_button;

		int type;
		int building_type;
		int ref_id;
		int state;
		double percentage_produced;
		bool rerender_show_time;
		ZBuilding *building_obj;
		ZObject *draw_obj;

		int show_time;
		ZSDL_Surface show_time_img;

		int health_percent;
		ZSDL_Surface health_percent_img;

		int state_i;
		double next_state_time;

		int select_i;
};

#endif
