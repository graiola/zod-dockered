#ifndef _ZTIME_H_
#define _ZTIME_H_

class ZTime
{
public:
	ZTime();

	void UpdateTime();
	void Pause();
	void Resume();
	inline bool IsPaused() { return paused; }

	double ztime;
	double lost_time;
	double pause_time;
	bool paused;
};

#endif
