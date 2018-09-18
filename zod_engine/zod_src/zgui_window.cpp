#include "zgui_window.h"
#include "common.h"

using namespace COMMON;

ZGuiTextBox::ZGuiTextBox()
{
	max_text = -1;
	passworded = false;
	good_chars_only = false;

	x_offset = 0;
	y_offset = 0;
	width = 0;
	active = true;
	selected = false;
}

void ZGuiTextBox::SetOffsets(int x_offset_, int y_offset_)
{
	x_offset = x_offset_;
	y_offset = y_offset_;
}

void ZGuiTextBox::SetWidth(int width_)
{
	width = width_;
}

void ZGuiTextBox::SetMaxText(int max_text_)
{
	max_text = max_text_;
}

void ZGuiTextBox::SetPassworded(bool passworded_)
{
	passworded = passworded_;

	CreateRender();
}

void ZGuiTextBox::SetUseGoodChars(bool good_chars_only_)
{
	good_chars_only = good_chars_only_;
}

void ZGuiTextBox::DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x, int shift_y)
{
	if(!active) return;

	if(!render_img.GetBaseSurface()) return;

	int clear_w = width - 4;

	if(render_img.GetBaseSurface()->w < clear_w)
	{
		the_map.RenderZSurface(&render_img, shift_x + x_offset + 2, shift_y + y_offset + 2);
	}
	else
	{
		SDL_Rect from_rect, to_rect;

		from_rect.x = render_img.GetBaseSurface()->w - clear_w;
		from_rect.y = 0;
		from_rect.w = clear_w;
		from_rect.h = render_img.GetBaseSurface()->h;

		int map_shift_x;
		int map_shift_y;
		the_map.GetViewShift(map_shift_x, map_shift_y);

		to_rect.x = shift_x + x_offset + 2 - map_shift_x;
		to_rect.y = shift_y + y_offset + 2 - map_shift_y;

		render_img.BlitSurface(&from_rect, &to_rect);
	}
}

bool ZGuiTextBox::Click(int x, int y)
{
	if(!active) return false;

	if(x < x_offset) return false;
	if(y < y_offset) return false;
	if(x > x_offset + width) return false;
	if(y > y_offset + 11) return false;

	return true;
}

void ZGuiTextBox::KeyPress(int c)
{
	if(c == 8) //delete key
	{
		if(text.length())
			text.erase(text.length()-1,1);
	}
	else
	{
		if(max_text != -1 && text.length() >= max_text) return;
		if(good_chars_only && !good_user_char(c)) return;

		//add it to the string
		text += c;
	}

	CreateRender();
}

void ZGuiTextBox::CreateRenderIfNeeded()
{
	if(!render_img.GetBaseSurface()) CreateRender();
}

void ZGuiTextBox::CreateRender()
{
	string render_str;

	if(passworded)
		render_str = string(text.length(), '*');
	else
		render_str = text;

	if(selected)
		render_str += "{";

	render_img.LoadBaseImage(ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(render_str.c_str()));

	//render_img.LoadBaseImage(ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(text.c_str()));
}

string &ZGuiTextBox::GetText()
{
	return text;
}

void ZGuiTextBox::SetActive(bool active_)
{
	active = active_;
}

bool ZGuiTextBox::IsActive()
{
	return active;
}

void ZGuiTextBox::SetSelected(bool selected_)
{
	selected = selected_;

	CreateRender();
}

bool ZGuiTextBox::IsSelected()
{
	return selected;
}

bool ZGuiButton::finished_init = false;

ZSDL_Surface ZGuiButton::button_img[MAX_GUI_BUTTON_TYPES][MAX_GUI_BUTTON_STATES];

ZGuiButton::ZGuiButton()
{
	type = OK_GUI_BUTTON;
	state = GUI_BUTTON_NORMAL;
	x_offset = 0;
	y_offset = 0;
}

void ZGuiButton::Init()
{
	string filename;
	string buttonname;

	string gwprod_folder = "assets/other/production_gui/";
	string menu_folder = "assets/other/menus/";

	LoadButtonImages(button_img[PLACE_GUI_BUTTON], gwprod_folder, "place");
	LoadButtonImages(button_img[OK_GUI_BUTTON], gwprod_folder, "ok");
	LoadButtonImages(button_img[CANCEL_GUI_BUTTON], gwprod_folder, "cancel");
	LoadButtonImages(button_img[UP_GUI_BUTTON], gwprod_folder, "up");
	LoadButtonImages(button_img[DOWN_GUI_BUTTON], gwprod_folder, "down");
	LoadButtonImages(button_img[LOGIN_MENU_BUTTON], menu_folder, "login");
	LoadButtonImages(button_img[CREATE_MENU_BUTTON], menu_folder, "create");
	LoadButtonImages(button_img[OK_MENU_BUTTON], menu_folder, "ok");
	LoadButtonImages(button_img[CANCEL_MENU_BUTTON], menu_folder, "cancel");

	finished_init = true;
}

void ZGuiButton::LoadButtonImages(ZSDL_Surface *the_button, string foldername, string buttonname)
{
	string filename;

	filename = foldername + buttonname + "_button.png";
	the_button[GUI_BUTTON_NORMAL].LoadBaseImage(filename);// = IMG_Load_Error(filename);
	filename = foldername + buttonname + "_button_pressed.png";
	the_button[GUI_BUTTON_PRESSED].LoadBaseImage(filename);// = IMG_Load_Error(filename);
}

void ZGuiButton::SetType(int type_)
{
	type = type_;

	switch(type)
	{
	case PLACE_GUI_BUTTON:
	case OK_GUI_BUTTON:
		SetOffsets(67, 60);
		//x_offset = 67;
		//y_offset = 60;
		break;
	case CANCEL_GUI_BUTTON:
		SetOffsets(67, 47);
		//x_offset = 67;
		//y_offset = 47;
		break;
	case DOWN_GUI_BUTTON:
		SetOffsets(50, 64);
		//x_offset = 50;
		//y_offset = 64;
		break;
	case UP_GUI_BUTTON:
		SetOffsets(50, 21);
		//x_offset = 50;
		//y_offset = 21;
		break;
	}
}

void ZGuiButton::SetOffsets(int x_offset_, int y_offset_)
{
	x_offset = x_offset_;
	y_offset = y_offset_;
}

void ZGuiButton::SetActive(bool active_)
{
	active = active_;
}

bool ZGuiButton::IsActive()
{
	return active;
}

bool ZGuiButton::Click(int x, int y)
{
	if(!finished_init) return false;

	if(!active) return false;

	if(!button_img[type][state].GetBaseSurface()) return false;

	if(x < x_offset) return false;
	if(y < y_offset) return false;
	if(x > x_offset + button_img[type][state].GetBaseSurface()->w) return false;
	if(y > y_offset + button_img[type][state].GetBaseSurface()->h) return false;

	state = GUI_BUTTON_PRESSED;

	return true;
}

bool ZGuiButton::UnClick(int x, int y)
{
	if(!finished_init) return false;

	if(!active) return false;

	if(state == GUI_BUTTON_NORMAL) return false;

	if(!button_img[type][state].GetBaseSurface()) return false;

	state = GUI_BUTTON_NORMAL;

	if(x < x_offset) return false;
	if(y < y_offset) return false;
	if(x > x_offset + button_img[type][state].GetBaseSurface()->w) return false;
	if(y > y_offset + button_img[type][state].GetBaseSurface()->h) return false;

	return true;
}

void ZGuiButton::DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x, int shift_y)
{
	SDL_Rect from_rect, to_rect;

	if(!finished_init) return;

	if(!active) return;

	the_map.RenderZSurface(&button_img[type][state], shift_x + x_offset, shift_y + y_offset);
	//if(the_map.GetBlitInfo( button_img[type][state], shift_x + x_offset, shift_y + y_offset, from_rect, to_rect))
	//		SDL_BlitSurface( button_img[type][state], &from_rect, dest, &to_rect);
}

ZGuiWindow::ZGuiWindow(ZTime *ztime_)
{
	killme = false;
	buildlist = NULL;
	ztime = ztime_;
	x = y = 0;
	width = height = 0;
}

void ZGuiWindow::Process(double &the_time)
{

}

void ZGuiWindow::DoRender(ZMap &the_map, SDL_Surface *dest)
{

}

void ZGuiWindow::SetBuildList(ZBuildList *buildlist_)
{
	buildlist = buildlist_;
}

bool ZGuiWindow::KillMe()
{
	return killme;
}

gui_flags &ZGuiWindow::GetGFlags()
{
	return gflags;
}

bool ZGuiWindow::Click(int x_, int y_)
{
	if(x_ < x) return false;
	if(y_ < y) return false;
	if(x_ >= x + width) return false;
	if(y_ >= y + height) return false;

	return true;
}

bool ZGuiWindow::UnClick(int x_, int y_)
{
	if(x_ < x) return false;
	if(y_ < y) return false;
	if(x_ >= x + width) return false;
	if(y_ >= y + height) return false;

	return true;
}

void ZGuiWindow::SetCords(int center_x, int center_y)
{
	x = center_x - (width >> 1);
	y = center_y - (height >> 1);

	if(x < 16) x = 16;
	if(y < 16) y = 16;
}
