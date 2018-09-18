The Zod Engine by Nighsoft
Please visit http://zod.sourceforge.net/

The linux release of the Zod Engine has been compiled with Ubuntu 10.10 32 bit. 
If you do not have this OS however it may still run for you, otherwise you will 
have to recompile the sources.

To run The Zod Engine -
1. Install the required library dependencies.
2. Simply run zod_launcher while inside of this folder.

Installing the required libraries -
The required libraries for this game are as follows...
* SDL
* SDL_ttf
* SDL_mixer
* SDL_image
* libmysqlclient (or sometimes called libmysql)
* wx (sometimes called libwx, or libwxgtk)
Notes: It is possible to compile the game without mysql support. 
Also wx is only needed for the zod_launcher.

Installing the required libraries on Ubuntu -
sudo apt-get install libsdl-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev libsdl-image1.2-dev libmysqlclient-dev libwxgtk2.8-dev

Howto Compile -
The Zod Engine is made up up multiple programs - the engine, the launcher, the map editor, etc.
In order to compile any of these you will need the respective development versions of their library dependencies.
To compile the zod engine go into the zod_src folder with a terminal and type in: make
To compile the zod launcher go into the zod_launcher_src folder with a terminal and type in: make
The executable outputs will be called 'zod' and 'zod_launcher' respectively, just copy these back into
the original zod_engine folder.

Compiling on Ubuntu -
sudo apt-get install build-essential

For anymore questions or help please visit the forums at http://zod.sourceforge.net/

http://www.nighsoft.com
http://zod.sourceforge.net
freaknigh@hotmail.com