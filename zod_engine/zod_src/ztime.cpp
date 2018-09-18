#include "ztime.h"
#include "common.h"

using namespace COMMON;

ZTime::ZTime()
{
	ztime = 0;
	lost_time = 0;
	pause_time = 0;
	paused = false;
}

void ZTime::UpdateTime()
{
	if(!paused) ztime = current_time() - lost_time;
}

void ZTime::Pause()
{
	if(paused) return;

	paused = true;

	pause_time = current_time();
}

void ZTime::Resume()
{
	if(!paused) return;

	paused = false;

	lost_time += current_time() - pause_time;
}
