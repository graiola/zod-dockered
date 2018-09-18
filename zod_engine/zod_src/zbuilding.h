#ifndef _ZBUILDING_H_
#define _ZBUILDING_H_

#include <algorithm>
#include "zobject.h"
#include "estandard.h"

enum building_state
{
	BUILDING_PLACE, BUILDING_SELECT, BUILDING_BUILDING, BUILDING_PAUSED, MAX_BUILDING_STATES
};

class ZBuilding : public ZObject
{
	public:
		ZBuilding(ZTime *ztime_, ZSettings *zsettings_ = NULL, planet_type palette_ = DESERT);
		~ZBuilding();
		
		static void Init();
		virtual void ChangePalette(planet_type palette_);
		void ReRenderBase();
		int GetBuildState();
		int GetLevel();
		void SetLevel(int level_);
		virtual bool SetBuildingDefaultProduction();
		virtual bool SetBuildingProduction(unsigned char ot, unsigned char oid);
		virtual void CreateBuildingStateData(char *&data, int &size);
		virtual void ProcessSetBuildingStateData(char *data, int size);
		virtual bool StopBuildingProduction();
		double PercentageProduced(double &the_time);
		double ProductionTimeLeft(double &the_time);
		virtual bool GetBuildingCreationPoint(int &x, int &y);
		virtual bool GetBuildingCreationMovePoint(int &x, int &y);
		virtual bool BuildUnit(double &the_time, unsigned char &ot, unsigned char &oid);
		virtual bool StoreBuiltCannon(unsigned char oid);
		virtual void ResetProduction();
		bool GetBuildUnit(unsigned char &ot, unsigned char &oid);
		virtual void CreateBuiltCannonData(char *&data, int &size);
		virtual void ProcessSetBuiltCannonData(char *data, int size);
		virtual bool RemoveStoredCannon(unsigned char oid);
		virtual bool HaveStoredCannon(unsigned char oid);
		virtual void SetOwner(team_type owner_);
		vector<unsigned char> &GetBuiltCannonList();
		virtual void DoDeathEffect(bool do_fire_death, bool do_missile_death);
		virtual void DoReviveEffect();
		int CannonsInZone(ZOLists &ols);
		virtual void ProcessBuildingsEffects(double &the_time);
		virtual bool ResetBuildTime(float zone_ownage);
		virtual void SetZoneOwnage(float zone_ownage_) { zone_ownage = zone_ownage_; }
		virtual bool RecalcBuildTime();
		double BuildTimeModified(double base_build_time);
	protected:
		void ResetShowTime(int new_time);

		planet_type palette;
		int level;
		bool do_base_rerender;
		int build_state;
		unsigned char bot, boid;
		double binit_time, bfinal_time;
		int unit_create_x, unit_create_y;
		int unit_move_x, unit_move_y;
		vector<unsigned char> built_cannon_list;
		float zone_ownage;

		int show_time;
		ZSDL_Surface show_time_img;

		SDL_Rect effects_box;
		int max_effects;
		vector<EStandard*> extra_effects;
		
		static ZSDL_Surface level_img[MAX_BUILDING_LEVELS];
		static ZSDL_Surface exhaust[13];
		static ZSDL_Surface little_exhaust[4];
	private:
};

#endif
