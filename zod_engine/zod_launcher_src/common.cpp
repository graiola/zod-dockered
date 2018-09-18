#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "common.h"

#ifdef _WIN32
#include <windows.h>
#include <time.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#endif

namespace COMMON
{
	
void create_folder(char *foldername)
{
#ifdef WIN32 //if windows
	mkdir(foldername);
#else
	mkdir(foldername,-1);
#endif
}

double current_time()
{
#ifdef WIN32
	//windows version
	static int first_sec = 0;
	static int first_msec = 0;
	SYSTEMTIME st;

	GetSystemTime(&st);

	if(!first_sec)
	{
		first_sec = (int)time(0);
		first_msec = st.wMilliseconds;
	}

	return ((time(0) - first_sec) + ((st.wMilliseconds - first_msec) * 0.001));

#else
	//linux version
	static int first_sec = 0;
	static int first_usec = 0;
	struct timeval new_time;

	//set current time
	gettimeofday(&new_time, NULL);

	//set if not set
	if(!first_sec)
	{
		first_sec = new_time.tv_sec;
		first_usec = new_time.tv_usec;
	}

	return (new_time.tv_sec - first_sec) + ((new_time.tv_usec - first_usec) * 0.000001);
#endif
}
	
void split(char *dest, char *message, char split, int *initial, int d_size, int m_size)
{
	int i, a = 0;
	
	for(i = *initial; i < 100100100 && i < m_size; i++)
	{
		// check to see if at end of string
		if (!message[i]) break;
		else if (message[i] != split) //check to see if at the split mark
		{
			if(a < d_size)
			{
				dest[a] = message[i];
				a++;
			}
		}
		else
			break;
	}

	//"cap" return string
	if(a < d_size) dest[a] = 0;
	else if(d_size > 0) dest[d_size - 1] = 0;
	
	//return point to continue search
	if (message[i] == 0)
		*initial = i;
	else
		*initial = ++i;
	
	return;
}

void clean_newline(char *message, int size)
{
	int i;
	
	for(i=0;i<size;i++)
	{
		if(message[i] == '\r')
		{
			message[i] = 0;
			break;
		}
		else if(message[i] == '\n')
		{
			message[i] = 0;
			break;
		}
		else if(!message[i])
			break;
	}
}

void lcase(char *message, int m_size)
{
	int i;

	for(i=0;i<m_size && message[i];i++)
		message[i] = tolower(message[i]);
}

void uni_pause(int m_sec)
{
#ifdef _WIN32 //if windows
	Sleep(m_sec);	//win version
#else
	usleep(m_sec * 1000);	//lin version
#endif
}

void print_dump(char *message, int size, char *name)
{
	int i;
	
	printf("raw dump:%s:", name);
	for(i=0;i<size;i++)
		printf("%0.2x ", message[i]);
	printf("\n");
}

bool points_within_distance(int x1, int y1, int x2, int y2, int distance)
{
	//quick prelim tests
	if(x2 < x1 - distance) return false;
	if(x2 > x1 + distance) return false;
	if(y2 < y1 - distance) return false;
	if(y2 > y1 + distance) return false;

	//semi quick tests
	int sh_dist = distance * 0.707106781; //sin(45)
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	if(dx < sh_dist && dy < sh_dist) return true;

	//slow test
	if(sqrt((float)((dx * dx) + (dy * dy))) > distance) return false;

	return true;
}

bool points_within_area(int px, int py, int ax, int ay, int aw, int ah)
{
	if(px < ax) return false;
	if(py < ay) return false;
	if(px > ax + aw) return false;
	if(py > ay + ah) return false;

	return true;
}

bool good_user_char(int c)
{
	if(isalnum(c)) return true;
	if(c == ' ') return true;
	if(c == '@') return true;
	if(c == '.') return true;
	if(c == '_') return true;
	if(c == '-') return true;

	return false;
}

bool good_user_string(const char *message)
{
	int i, len;

	len = strlen(message);

	if(!strlen(message)) return false;

	for(i=0;message[i];i++)
		if(!good_user_char(message[i]))
			return false;

	//any double spaces?
	for(i=0;i<len-1;i++)
		if(message[i] == ' ' && message[i+1] == ' ')
			return false;

	//spaces at ends?
	if(message[0] == ' ') return false;
	if(message[len-1] == ' ') return false;

	return true;
}

};
