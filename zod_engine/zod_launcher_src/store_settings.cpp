#include "store_settings.h"
#include "common.h"

#include <stdio.h>

using namespace COMMON;

settings_struct g_settings;

void StoreSettings()
{
	FILE *fp;

	fp = fopen("zod_launcher_settings.txt", "w");

	if(!fp) return;

	fprintf(fp, "connect_address=%s\n", g_settings.connect_address.c_str());
	fprintf(fp, "map_name=%s\n", g_settings.map_name.c_str());
	fprintf(fp, "settings_filename=%s\n", g_settings.settings_filename.c_str());
	fprintf(fp, "player_name=%s\n", g_settings.player_name.c_str());
	fprintf(fp, "login_name=%s\n", g_settings.login_name.c_str());
	fprintf(fp, "login_password=%s\n", g_settings.login_password.c_str());
	fprintf(fp, "resolution_w=%s\n", g_settings.resolution_w.c_str());
	fprintf(fp, "resolution_h=%s\n", g_settings.resolution_h.c_str());
	
	fprintf(fp, "team=%s\n", g_settings.team.c_str());
	
	fprintf(fp, "is_dedicated=%d\n", g_settings.is_dedicated);
	fprintf(fp, "f_isa_m=%d\n", g_settings.f_isa_m);
	fprintf(fp, "red=%d\n", g_settings.red);
	fprintf(fp, "blue=%d\n", g_settings.blue);
	fprintf(fp, "green=%d\n", g_settings.green);
	fprintf(fp, "yellow=%d\n", g_settings.yellow);
	fprintf(fp, "windowed=%d\n", g_settings.windowed);
	fprintf(fp, "no_music=%d\n", g_settings.no_music);
	fprintf(fp, "no_sound=%d\n", g_settings.no_sound);
	fprintf(fp, "no_opengl=%d\n", g_settings.no_opengl);
	fprintf(fp, "bland_cursor=%d\n", g_settings.bland_cursor);

	fclose(fp);
}

void LoadSettings()
{
	FILE *fp;

	fp = fopen("zod_launcher_settings.txt", "r");

	if(!fp) return;

	const int buf_size = 500;
	char cur_line[buf_size];
	char variable[buf_size];
	char value[buf_size];
	bool loaded = false;

	while(fgets(cur_line , buf_size , fp))
	{
		clean_newline(cur_line, buf_size);

		if(strlen(cur_line))
		{
			int pt = 0;

			//don't read comment lines
			if(cur_line[0] == '#') continue;

			//parse this line
			split(variable, cur_line, '=', &pt, buf_size, buf_size);
			split(value, cur_line, '=', &pt, buf_size, buf_size);

			if(!strcmp(variable, "connect_address"))
				g_settings.connect_address = value;
			else if(!strcmp(variable, "map_name"))
				g_settings.map_name = value;
			else if(!strcmp(variable, "settings_filename"))
				g_settings.settings_filename = value;
			else if(!strcmp(variable, "player_name"))
				g_settings.player_name = value;
			else if(!strcmp(variable, "login_name"))
				g_settings.login_name = value;
			else if(!strcmp(variable, "login_password"))
				g_settings.login_password = value;
			else if(!strcmp(variable, "resolution_w"))
				g_settings.resolution_w = value;
			else if(!strcmp(variable, "resolution_h"))
				g_settings.resolution_h = value;
				
			else if(!strcmp(variable, "team"))
				g_settings.team = value;
				
			else if(!strcmp(variable, "is_dedicated"))
				g_settings.is_dedicated = atoi(value);
			else if(!strcmp(variable, "f_isa_m"))
				g_settings.f_isa_m = atoi(value);
			else if(!strcmp(variable, "red"))
				g_settings.red = atoi(value);
			else if(!strcmp(variable, "blue"))
				g_settings.blue = atoi(value);
			else if(!strcmp(variable, "green"))
				g_settings.green = atoi(value);
			else if(!strcmp(variable, "yellow"))
				g_settings.yellow = atoi(value);
			else if(!strcmp(variable, "windowed"))
				g_settings.windowed = atoi(value);
			else if(!strcmp(variable, "no_music"))
				g_settings.no_music = atoi(value);
			else if(!strcmp(variable, "no_sound"))
				g_settings.no_sound = atoi(value);
			else if(!strcmp(variable, "no_opengl"))
				g_settings.no_opengl = atoi(value);
			else if(!strcmp(variable, "bland_cursor"))
				g_settings.bland_cursor = atoi(value);
		}
	}

	fclose(fp);
}
