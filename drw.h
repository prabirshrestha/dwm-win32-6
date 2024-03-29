/* See LICENSE file for copyright and license details. */
#if USE_WINAPI
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT			0x0500

#include <windows.h>
#include <winuser.h>
#endif

/* for portibility */
#if USE_WINAPI
#define True TRUE
#define False FALSE
#define Bool BOOL
#define Window HWND
#define Atom int
#define Display void*
#define true TRUE
#define false FALSE
#endif

typedef struct {
	unsigned long rgb;
} Clr;

typedef struct {
#if USE_XLIB
	Cursor cursor;
#elif USE_WINAPI
	void *cursor;
#endif
} Cur;

typedef struct {
	int ascent;
	int descent;
	unsigned int h;
#if USE_XLIB
	XFontSet set;
	XFontStruct *xfont;
#elif USE_WINAPI
	HFONT font;
	TEXTMETRIC tm;
#endif
} Fnt;

typedef struct {
	Clr *fg;
	Clr *bg;
	Clr *border;
} ClrScheme;

typedef struct {
	unsigned int w, h;
#if USE_XLIB
	Display *dpy;
#elif USE_WINAPI
	void *dpy;
#endif
	int screen;
#if USE_XLIB
	Window root;
	Drawable drawable;
	GC gc;
#elif USE_WINAPI
	HWND root;
	HWND hcanvas;
	HDC gc; 
	HDC drawable;
	HBITMAP hbmp;
	HDC hdc;
#endif
	ClrScheme *scheme;
	Fnt *font;
} Drw;

typedef struct {
	unsigned int w;
	unsigned int h;
} Extnts;

/* Drawable abstraction */
Drw *drw_create(Display *dpy, int screen, Window win, unsigned int w, unsigned int h);
void drw_resize(Drw *drw, unsigned int w, unsigned int h);
void drw_free(Drw *drw);

/* Fnt abstraction */
#if USE_XLIB
Fnt *drw_font_create(Display *dpy, const char *fontname);
#elif USE_WINAPI
Fnt *drw_font_create(Display *dpy, const char *fontname, HWND canvas);
#endif
void drw_font_free(Display *dpy, Fnt *font);
#if USE_XLIB
void drw_font_getexts(Fnt *font, const char *text, unsigned int len, Extnts *extnts);
unsigned int drw_font_getexts_width(Fnt *font, const char *text, unsigned int len);
#elif USE_WINAPI
void drw_font_getexts(Drw *drw, Fnt *font, const char *text, unsigned int len, Extnts *extnts);
unsigned int drw_font_getexts_width(Drw *drw, Fnt *font, const char *text, unsigned int len);
#endif

/* Colour abstraction */
Clr *drw_clr_create(Drw *drw, const char *clrname);
void drw_clr_free(Clr *clr);

/* Cursor abstraction */
Cur *drw_cur_create(Drw *drw, int shape);
void drw_cur_free(Drw *drw, Cur *cursor);

/* Drawing context manipulation */
void drw_setfont(Drw *drw, Fnt *font);
void drw_setscheme(Drw *drw, ClrScheme *scheme);

/* Drawing functions */
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int empty, int invert);
void drw_text(Drw *drw, int x, int y, unsigned int w, unsigned int h, const char *text, int invert);

/* Map functions */
void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h);
