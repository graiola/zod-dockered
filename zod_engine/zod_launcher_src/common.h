#ifndef _COMMON_H_
#define _COMMON_H_

namespace COMMON
{
	extern void split(char *dest, char *message, char split, int *initial, int d_size, int m_size);
	extern void clean_newline(char *message, int size);
	extern void lcase(char *message, int m_size);
	extern double current_time();
	extern void create_folder(char *foldername);
	extern void uni_pause(int m_sec);
	extern char *wtoc_s(const wchar_t *input);
	extern char *wtoc(const wchar_t *input, char *dest, int size);
	extern wchar_t *ctow_s(const char *input);
	extern wchar_t *ctow(const char *input, wchar_t *dest, int size);
	extern void print_dump(char *message, int size, char *name);
	extern bool points_within_distance(int x1, int y1, int x2, int y2, int distance);
	extern bool points_within_area(int px, int py, int ax, int ay, int aw, int ah);
	extern bool good_user_char(int c);
	extern bool good_user_string(const char *message);

	//inline functions...
	inline bool isz(float num) { return (num < 0.00001 && num > -0.00001); };
	inline bool isz(double num) { return (num < 0.00001 && num > -0.00001); };

	inline bool is1(float num) { return (num < 1.00001 && num > 0.99999); };
	inline bool is1(double num) { return (num < 1.00001 && num > 0.99999); };

	inline void swap(int &a, int &b)
	{
		int c;

		c = a;
		a = b;
		b = c;
	}
};

#endif
