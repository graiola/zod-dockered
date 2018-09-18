#include "gwproduction.h"
#include "zfont_engine.h"
//#include "zbuilding.h"

#include "cgatling.h"
#include "cgun.h"
#include "chowitzer.h"
#include "cmissilecannon.h"

#include "vjeep.h"
#include "vlight.h"
#include "vmedium.h"
#include "vheavy.h"
#include "vapc.h"
#include "vmissilelauncher.h"
#include "vcrane.h"

#include "rgrunt.h"
#include "rpsycho.h"
#include "rsniper.h"
#include "rtough.h"
#include "rpyro.h"
#include "rlaser.h"

ZSDL_Surface GWProduction::base_img;
ZSDL_Surface GWProduction::name_label[GWPROD_TYPES_MAX];
ZSDL_Surface GWProduction::state_label[MAX_BUILDING_STATES][2];
ZSDL_Surface GWProduction::p_bar;
ZSDL_Surface GWProduction::p_bar_yellow;

GWProduction::GWProduction(ZTime *ztime_) : ZGuiWindow(ztime_)
{
	double &the_time = ztime->ztime;

	width = 112;
	height = 80;
	ref_id = -1;
	building_obj = NULL;
	draw_obj = NULL;
	state_i = 0;
	percentage_produced = 0;
	show_time = 0;
	show_time_img = NULL;
	health_percent = -1;
	health_percent_img = NULL;

	//for defaults sake
	SetType(GWPROD_FORT);
	state = -1;
	select_i = 0;
	SetState(BUILDING_SELECT);

	up_button.SetType(UP_GUI_BUTTON);
	down_button.SetType(DOWN_GUI_BUTTON);
	place_button.SetType(PLACE_GUI_BUTTON);
	ok_button.SetType(OK_GUI_BUTTON);
	cancel_button.SetType(CANCEL_GUI_BUTTON);

	next_state_time = the_time + 0.3;
}

GWProduction::~GWProduction()
{
	DeleteDrawObject();
	//ZSDL_FreeSurface(show_time_img);
	//ZSDL_FreeSurface(health_percent_img);
}

void GWProduction::Init()
{
	base_img.LoadBaseImage("assets/other/production_gui/base_image.png");
	name_label[GWPROD_ROBOT].LoadBaseImage("assets/other/production_gui/robot_factory_label.png");
	name_label[GWPROD_FORT].LoadBaseImage("assets/other/production_gui/fort_factory_label.png");
	name_label[GWPROD_VEHICLE].LoadBaseImage("assets/other/production_gui/vehicle_factory_label.png");
	p_bar.LoadBaseImage("assets/other/production_gui/percentage_bar.png");
	p_bar_yellow.LoadBaseImage("assets/other/production_gui/percentage_bar_yellow.png");

	state_label[BUILDING_PLACE][0].LoadBaseImage("assets/other/production_gui/place_label.png");
	state_label[BUILDING_PLACE][1].LoadBaseImage("assets/other/production_gui/placeless_label.png");

	state_label[BUILDING_SELECT][0].LoadBaseImage("assets/other/production_gui/select_label.png");
	state_label[BUILDING_SELECT][1].LoadBaseImage("assets/other/production_gui/selectless_label.png");

	state_label[BUILDING_BUILDING][0].LoadBaseImage("assets/other/production_gui/building_label.png");
	state_label[BUILDING_BUILDING][1].LoadBaseImage("assets/other/production_gui/buildingless_label.png");

	state_label[BUILDING_PAUSED][0].LoadBaseImage("assets/other/production_gui/paused_label.png");
	state_label[BUILDING_PAUSED][1].LoadBaseImage("assets/other/production_gui/pausedless_label.png");
}

void GWProduction::Process(double &the_time)
{
	if(killme) return;

	//do not process if we are not attached to a building object
	if(!building_obj)
	{
		killme = true;
		return;
	}

	//recheck state of the building, as well as set drawobject
	SetDrawObject();

	//process
	if(draw_obj) draw_obj->Process();

	if(state != BUILDING_SELECT)
	{
		percentage_produced = building_obj->PercentageProduced(the_time);
	}

	//set show time
	RecalcShowTime();

	if(the_time >= next_state_time)
	{
		state_i++;
		if(state_i>=2) state_i = 0;
		next_state_time = the_time + 0.3;
	}

	//health percent
	{
		int new_percent = 0;

		if(building_obj->GetMaxHealth())
			new_percent = 100 * building_obj->GetHealth() / building_obj->GetMaxHealth();

		if(new_percent < 0) new_percent = 0;
		if(new_percent > 100) new_percent = 100;

		if(new_percent != health_percent)
		{
			char message[50];

			health_percent = new_percent;

			//ZSDL_FreeSurface(health_percent_img);
			sprintf(message, "%d%c", health_percent, '%');
			printf("%s\n", message);
			//health_percent_img = ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(message);
			health_percent_img.LoadBaseImage(ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(message));
		}

	}
}

void GWProduction::RecalcShowTime()
{
	double &the_time = ztime->ztime;
	double new_time = -1;

	//setup ticker
	if(state == BUILDING_SELECT)
	{
		if(!building_obj) return;
		if(!buildlist) return;

		int b_level = building_obj->GetLevel();

		unsigned char &ot = buildlist->GetBuildList(building_type, b_level)[select_i].ot;
		unsigned char &oid = buildlist->GetBuildList(building_type, b_level)[select_i].oid;

		new_time = building_obj->BuildTimeModified(buildlist->UnitBuildTime(ot, oid));
		//new_time += building_obj->BuildTimeIncrease(new_time);
	}
	else
	{
		new_time = building_obj->ProductionTimeLeft(the_time);
	}

	if(show_time != (int)new_time)
		ResetShowTime((int)new_time);
}

void GWProduction::ResetShowTime(int new_time)
{
	int minutes, seconds;
	char message[50];

	//if(show_time_img)
	//{
	//	SDL_FreeSurface(show_time_img);
	//	show_time_img = NULL;
	//}

	show_time = new_time;

	//setup these numbers
	seconds = new_time % 60;
	new_time /= 60;
	minutes = new_time % 60;

	sprintf(message, "%d:%02d", minutes, seconds);
	//show_time_img = ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(message);
	show_time_img.LoadBaseImage(ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(message));
}

void GWProduction::DoRender(ZMap &the_map, SDL_Surface *dest)
{
	int lx, ly;
	SDL_Rect from_rect, to_rect;

	if(killme) return;

	if(!building_obj)
	{
		killme = true;
		return;
	}

	the_map.RenderZSurface(&base_img, x, y);
	//if(the_map.GetBlitInfo(base_img, x, y, from_rect, to_rect))
	//	SDL_BlitSurface( base_img, &from_rect, dest, &to_rect);

	lx = x + 9;
	ly = y + 6;

	the_map.RenderZSurface(&name_label[type], lx, ly);
	//if(the_map.GetBlitInfo(name_label[type], x + lx, y + ly, from_rect, to_rect))
	//	SDL_BlitSurface( name_label[type], &from_rect, dest, &to_rect);

	lx = x + 64;
	ly = y + 19;

	the_map.RenderZSurface(&state_label[state][state_i], lx, ly);
	//if(the_map.GetBlitInfo( state_label[state][state_i], x + lx, y + ly, from_rect, to_rect))
	//	SDL_BlitSurface( state_label[state][state_i], &from_rect, dest, &to_rect);

	//buttons
	up_button.DoRender(the_map, dest, x, y);
	down_button.DoRender(the_map, dest, x, y);
	ok_button.DoRender(the_map, dest, x, y);
	cancel_button.DoRender(the_map, dest, x, y);
	place_button.DoRender(the_map, dest, x, y);

	//this will draw the object if it is supposed to
	DrawObject(the_map, dest);

	DrawPercentageBar(the_map, dest);

	lx = x + 90;
	ly = y + 35;

	the_map.RenderZSurface(&show_time_img, lx, ly);
	//if(show_time_img)
	//	if(the_map.GetBlitInfo( show_time_img, x + 90, y + 35, from_rect, to_rect))
	//		SDL_BlitSurface( show_time_img, &from_rect, dest, &to_rect);

	if(health_percent_img.GetBaseSurface())
	{
		lx = x + 97 - (health_percent_img.GetBaseSurface()->w >> 1);
		ly = y + 7;

		the_map.RenderZSurface(&health_percent_img, lx, ly);
	}
		//if(the_map.GetBlitInfo( health_percent_img, x + 97 - (health_percent_img->w/2), y + 7, from_rect, to_rect))
		//	SDL_BlitSurface( health_percent_img, &from_rect, dest, &to_rect);
}

void GWProduction::DrawPercentageBar(ZMap &the_map, SDL_Surface *dest)
{
	SDL_Rect from_rect, to_rect;

	if(!building_obj) return;
	if(state == BUILDING_SELECT) return;

	the_map.RenderZSurface(&p_bar, x + 53, y + 21);
	//if(the_map.GetBlitInfo( p_bar, x + 53, y + 21, from_rect, to_rect))
	//	SDL_BlitSurface( p_bar, &from_rect, dest, &to_rect);

	if(p_bar_yellow.GetBaseSurface())
	if(the_map.GetBlitInfo( p_bar_yellow.GetBaseSurface(), x + 53, y + 21, from_rect, to_rect))
	{
		int max_h;

		max_h = (1.0 - percentage_produced) * p_bar_yellow.GetBaseSurface()->h;

		if(from_rect.h > max_h)
			from_rect.h = max_h;

		p_bar_yellow.BlitSurface(&from_rect, &to_rect);
		//SDL_BlitSurface( p_bar_yellow, &from_rect, dest, &to_rect);
	}
}

void GWProduction::DrawObject(ZMap &the_map, SDL_Surface *dest)
{
	SDL_Rect from_rect, to_rect;
	SDL_Surface *surface;

	if(!draw_obj) return;

	draw_obj->DoRender(the_map, dest);

	if(draw_obj->GetHoverNameImg().GetBaseSurface())
		the_map.RenderZSurface(&draw_obj->GetHoverNameImg(), x + 27 - (draw_obj->GetHoverNameImg().GetBaseSurface()->w/2), y + 61);

	//surface = draw_obj->GetHoverNameImg();
	//if(surface)
	//if(the_map.GetBlitInfo( surface, x + 27 - (surface->w/2), y + 61, from_rect, to_rect))
	//	SDL_BlitSurface( surface, &from_rect, dest, &to_rect);
}

void GWProduction::SetDrawObject()
{
	if(!building_obj) return;
	if(!buildlist) return;

	SetState(building_obj->GetBuildState());

	if(state == BUILDING_SELECT)
	{
		int b_level = building_obj->GetLevel();

		//make sure our select_i is kosher
		if(!buildlist->GetBuildList(building_type, b_level).size()) return;

		if(select_i >= buildlist->GetBuildList(building_type, b_level).size())
			select_i = 0;

		unsigned char &ot = buildlist->GetBuildList(building_type, b_level)[select_i].ot;
		unsigned char &oid = buildlist->GetBuildList(building_type, b_level)[select_i].oid;

		if(!draw_obj)
			ResetDrawObjectTo(ot, oid);
		else
		{
			unsigned char cot, coid;

			draw_obj->GetObjectID(cot, coid);

			if(ot != cot || coid != oid)
				ResetDrawObjectTo(ot, oid);
		}
	}
	else if(state == BUILDING_SELECT && building_obj && building_obj->GetBuiltCannonList().size())
	{
		unsigned char ot, oid;

		ot = CANNON_OBJECT;
		oid = building_obj->GetBuiltCannonList()[0];

		if(!draw_obj)
			ResetDrawObjectTo(ot, oid);
		else
		{
			unsigned char cot, coid;

			draw_obj->GetObjectID(cot, coid);

			if(ot != cot || coid != oid)
				ResetDrawObjectTo(ot, oid);
		}
	}
	else
	{
		unsigned char ot, oid;

		building_obj->GetBuildUnit(ot, oid);

		if(!draw_obj)
			ResetDrawObjectTo(ot, oid);
		else
		{
			unsigned char cot, coid;

			draw_obj->GetObjectID(cot, coid);

			if(ot != cot || coid != oid)
				ResetDrawObjectTo(ot, oid);
		}
	}
}

void GWProduction::ResetDrawObjectTo(unsigned char &ot, unsigned char &oid)
{
	DeleteDrawObject();

	if(!building_obj) return;

	switch(ot)
	{
	case CANNON_OBJECT:
		switch(oid)
		{
		case GATLING:
			draw_obj = new CGatling(ztime);
			break;
		case GUN:
			draw_obj = new CGun(ztime);
			break;
		case HOWITZER:
			draw_obj = new CHowitzer(ztime);
			break;
		case MISSILE_CANNON:
			draw_obj = new CMissileCannon(ztime);
			break;
		}
		break;
	case VEHICLE_OBJECT:
		switch(oid)
		{
		case JEEP:
			draw_obj = new VJeep(ztime);
			break;
		case LIGHT:
			draw_obj = new VLight(ztime);
			break;
		case MEDIUM:
			draw_obj = new VMedium(ztime);
			break;
		case HEAVY:
			draw_obj = new VHeavy(ztime);
			break;
		case APC:
			draw_obj = new VAPC(ztime);
			break;
		case MISSILE_LAUNCHER:
			draw_obj = new VMissileLauncher(ztime);
			break;
		case CRANE:
			draw_obj = new VCrane(ztime);
			break;
		}

		//for fun
		if(draw_obj) draw_obj->SetDirection(rand()%MAX_ANGLE_TYPES);
		break;
	case ROBOT_OBJECT:
		switch(oid)
		{
		case GRUNT:
			draw_obj = new RGrunt(ztime);
			break;
		case PSYCHO:
			draw_obj = new RPsycho(ztime);
			break;
		case SNIPER:
			draw_obj = new RSniper(ztime);
			break;
		case TOUGH:
			draw_obj = new RTough(ztime);
			break;
		case PYRO:
			draw_obj = new RPyro(ztime);
			break;
		case LASER:
			draw_obj = new RLaser(ztime);
			break;
		}
		break;
	}

	if(draw_obj) 
	{
		int w, h;

		draw_obj->GetDimensionsPixel(w, h);

		draw_obj->SetOwner((team_type)building_obj->GetOwner());
		draw_obj->SetCords(x + 27 - (w/2), y + 40 - (h/2));
	}
}

void GWProduction::DeleteDrawObject()
{
	if(draw_obj)
	{	
		delete draw_obj;
		draw_obj = 0;
	}
}

void GWProduction::SetState(int state_)
{
	if(building_obj && building_obj->GetBuiltCannonList().size()) state_ = BUILDING_PLACE;
	if(building_obj && building_obj->IsDestroyed()) state_ = BUILDING_PAUSED;

	if(state == state_) return;

	state = state_;

	switch(state)
	{
	case BUILDING_PLACE:
		up_button.SetActive(false);
		down_button.SetActive(false);
		ok_button.SetActive(false);
		cancel_button.SetActive(true);
		place_button.SetActive(true);
		break;
	case BUILDING_SELECT:
		up_button.SetActive(true);
		down_button.SetActive(true);
		ok_button.SetActive(true);
		cancel_button.SetActive(true);
		place_button.SetActive(false);
		break;
	case BUILDING_BUILDING:
		up_button.SetActive(false);
		down_button.SetActive(false);
		ok_button.SetActive(true);
		cancel_button.SetActive(true);
		place_button.SetActive(false);
		break;
	case BUILDING_PAUSED:
		up_button.SetActive(false);
		down_button.SetActive(false);
		ok_button.SetActive(true);
		cancel_button.SetActive(true);
		place_button.SetActive(false);
		break;
	}
}

void GWProduction::SetType(int type_)
{
	type = type_;

	switch(type)
	{
	case GWPROD_FORT:
		building_type = FORT_FRONT;
		break;
	case GWPROD_VEHICLE:
		building_type = VEHICLE_FACTORY;
		break;
	case GWPROD_ROBOT:
		building_type = ROBOT_FACTORY;
		break;
	}
}

void GWProduction::SetBuildingObj(ZBuilding *building_obj_)
{
	building_obj = building_obj_;
}

void GWProduction::SetRefID(int ref_id_)
{
	ref_id = ref_id_;
}

int GWProduction::GetRefID()
{
	return ref_id;
}

void GWProduction::DoUpButton()
{
	if(!building_obj) return;
	if(!buildlist) return;

	int b_level = building_obj->GetLevel();

	//make sure our select_i is kosher
	if(!buildlist->GetBuildList(building_type, b_level).size()) return;

	select_i++;

	if(select_i >= buildlist->GetBuildList(building_type, b_level).size())
		select_i = 0;
}

void GWProduction::DoDownButton()
{
	if(!building_obj) return;
	if(!buildlist) return;

	int b_level = building_obj->GetLevel();

	//make sure our select_i is kosher
	if(!buildlist->GetBuildList(building_type, b_level).size()) return;

	select_i--;

	if(select_i < 0)
		select_i = buildlist->GetBuildList(building_type, b_level).size() - 1;
}

void GWProduction::DoOkButton()
{
	switch(state)
	{
	case BUILDING_PLACE:
		//the ok button doesnt show during the place state
		break;
	case BUILDING_SELECT:
		//tell server to start this production
		if(draw_obj && building_obj)
		{
			unsigned char ot, oid;

			draw_obj->GetObjectID(ot, oid);

			gflags.send_new_production = true;
			gflags.pot = ot;
			gflags.poid = oid;
			gflags.pref_id = building_obj->GetRefID();
		}
		break;
	case BUILDING_PAUSED:
	case BUILDING_BUILDING:
		killme = true;
		break;
	}
}

void GWProduction::DoCancelButton()
{
	switch(state)
	{
	case BUILDING_PAUSED:
	case BUILDING_PLACE:
	case BUILDING_SELECT:
		killme = true;
		break;
	case BUILDING_BUILDING:
		//tell server to cancel this production
		gflags.send_stop_production = true;
		gflags.pref_id = building_obj->GetRefID();
		break;
	}
}

void GWProduction::DoPlaceButton()
{
	if(!building_obj) return;
	if(!building_obj->GetBuiltCannonList().size()) return;
	if(!building_obj->GetConnectedZone()) return;

	gflags.place_cannon = true;
	gflags.coid = building_obj->GetBuiltCannonList()[0];
	gflags.cref_id = building_obj->GetRefID();
	gflags.cleft = building_obj->GetConnectedZone()->x;
	gflags.cright = gflags.cleft + building_obj->GetConnectedZone()->w;
	gflags.ctop = building_obj->GetConnectedZone()->y;
	gflags.cbottom = gflags.ctop + building_obj->GetConnectedZone()->h;

	//also good bye
	killme = true;
}

bool GWProduction::Click(int x_, int y_)
{
	int x_local, y_local;

	x_local = x_ - x;
	y_local = y_ - y;

	up_button.Click(x_local, y_local);
	down_button.Click(x_local, y_local);
	ok_button.Click(x_local, y_local);
	cancel_button.Click(x_local, y_local);
	place_button.Click(x_local, y_local);

	if(x_ < x) return false;
	if(y_ < y) return false;
	if(x_ >= x + width) return false;
	if(y_ >= y + height) return false;

	return true;
}

bool GWProduction::UnClick(int x_, int y_)
{
	int x_local, y_local;

	gflags.Clear();

	x_local = x_ - x;
	y_local = y_ - y;

	if(up_button.UnClick(x_local, y_local)) DoUpButton();
	if(down_button.UnClick(x_local, y_local)) DoDownButton();
	if(ok_button.UnClick(x_local, y_local)) DoOkButton();
	if(cancel_button.UnClick(x_local, y_local)) DoCancelButton();
	if(place_button.UnClick(x_local, y_local)) DoPlaceButton();

	if(x_ < x) return false;
	if(y_ < y) return false;
	if(x_ >= x + width) return false;
	if(y_ >= y + height) return false;

	return true;
}

bool GWProduction::WheelUpButton()
{
	if(up_button.IsActive()) DoUpButton();

	return true;
}

bool GWProduction::WheelDownButton()
{
	if(down_button.IsActive()) DoDownButton();

	return true;
}
