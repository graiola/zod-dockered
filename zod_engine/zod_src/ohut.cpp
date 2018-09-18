#include "ohut.h"

ZSDL_Surface OHut::render_img[MAX_PLANET_TYPES];

OHut::OHut(ZTime *ztime_, ZSettings *zsettings_, int palette_) : ZObject(ztime_, zsettings_)
{
	palette = palette_;

	object_name = "hut";
	object_type = MAP_ITEM_OBJECT;
	object_id = HUT_ITEM;
	width = 1;
	height = 1;
	width_pix = width * 16;
	height_pix = height * 16;
	attacked_by_explosives = true;

	InitTypeId(object_type, object_id);

	//max_health = HUT_MAX_HEALTH;
	//health = max_health;
}
		
void OHut::Init()
{
	string filename;
	int i;

	for(i=0;i<MAX_PLANET_TYPES;i++)
	{
		filename = "assets/other/map_items/hut_" + planet_type_string[i] + ".png";
		render_img[i].LoadBaseImage(filename);// = ZSDL_IMG_Load(filename);
	}
}

void OHut::DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x, int shift_y)
{
	int &x = loc.x;
	int &y = loc.y;
	SDL_Rect from_rect, to_rect;

	if(the_map.GetBlitInfo( render_img[palette].GetBaseSurface(), x, y, from_rect, to_rect))
	{
		to_rect.x += shift_x;
		to_rect.y += shift_y;

		render_img[palette].BlitSurface(&from_rect, &to_rect);
		//SDL_BlitSurface( render_img[palette], &from_rect, dest, &to_rect);
	}
}

int OHut::Process()
{
	return 0;
}

void OHut::ChangePalette(int palette_)
{
	palette = palette_;
}

void OHut::SetMapImpassables(ZMap &tmap)
{
	int tx, ty;

	tx = loc.x / 16;
	ty = loc.y / 16;

	tmap.SetImpassable(tx, ty);
}

void OHut::UnSetMapImpassables(ZMap &tmap)
{
	int tx, ty;

	tx = loc.x / 16;
	ty = loc.y / 16;

	tmap.SetImpassable(tx, ty, false);
}

void OHut::SetOwner(team_type owner_)
{
	//do nothing
}
