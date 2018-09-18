#ifndef _OHUT_H_
#define _OHUT_H_

#include "zobject.h"

class OHut : public ZObject
{
	public:
		OHut(ZTime *ztime_, ZSettings *zsettings_ = NULL, int palette_ = DESERT);
		
		static void Init();

		void DoRender(ZMap &the_map, SDL_Surface *dest, int shift_x = 0, int shift_y = 0);
		int Process();

		void SetOwner(team_type owner_);
		void SetMapImpassables(ZMap &tmap);
		void UnSetMapImpassables(ZMap &tmap);

		void ChangePalette(int palette_);
	private:
		static ZSDL_Surface render_img[MAX_PLANET_TYPES];

		int palette;
};

#endif
