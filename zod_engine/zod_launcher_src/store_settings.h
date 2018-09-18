#ifndef _STORE_SETTINGS_H_
#define _STORE_SETTINGS_H_

#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct settings_struct
{
    string connect_address;
    string map_name;
    string settings_filename;
    string player_name;
    string login_name;
    string login_password;
    string resolution_w;
    string resolution_h;
    
    string team;
    
    bool is_dedicated;
    bool f_isa_m;
    bool red;
    bool blue;
    bool green;
    bool yellow;
    bool windowed;
    bool no_music;
    bool no_sound;
    bool no_opengl;
    bool bland_cursor;
};

extern settings_struct g_settings;

extern void StoreSettings();
extern void LoadSettings();

#endif
