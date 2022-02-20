/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;   /* 0 means no systray */
static const char *fonts[]               = { "Noto Sans:Bold:size=9:antialias=true", "Font Awesome:size=11:antialias=true" };
static const char dmenufont[]            = "Noto Sans:Bold:size=9:antialias=true";

static char normfgcolor[]                = "#bbbbbb";
static char normbgcolor[]                = "#222222";
static char normbordercolor[]            = "#444444";

static char selfgcolor[]                 = "#eeeeee";
static char selbgcolor[]                 = "#9f0000";
static char selbordercolor[]             = "#9f0000";





static
const
char *colors[][ColCount] = {
	/*                fg            bg            border          */
	[SchemeNorm]  = { normfgcolor,  normbgcolor,  normbordercolor },
	[SchemeSel]   = { selfgcolor,   selbgcolor,   selbordercolor  },
};


/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	WM_WINDOW_ROLE(STRING) = role
	 *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
	 */
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "zoom", .tags = 0 << 1, .isfloating = 1)
	RULE(.class = "wine", .tags = 0 << 1, .isfloating = 1)
	RULE(.class = "Galculator", .tags = 0, .isfloating = 1)
	RULE(.class = "Grsync", .tags = 0, .isfloating = 1)
	RULE(.class = "mpv", .tags = 0 << 1, .isfloating = 1)
	RULE(.class = "Sxiv", .tags = 0 << 1, .isfloating = 1)

/*	RULE(.class = "Gimp", .tags = 1 << 4)
	RULE(.class = "Firefox", .tags = 1 << 7) */
};



/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


/* Position of the monocle layout in the layouts variable, used by warp and fullscreen patches */
#define MONOCLE_LAYOUT_POS 2

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },



/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
	"dmenu_run",
	"-m", dmenumon,
	"-fn", dmenufont,
	"-nb", normbgcolor,
	"-nf", normfgcolor,
	"-sb", selbgcolor,
	"-sf", selfgcolor,
	NULL
};
static const char *termcmd[]  = { "st", NULL };
static const char *web[] = { "chromium", NULL };
static const char *email[] = { "geary", NULL };
static const char *xeditor[] = { "geany", NULL };
static const char *metting[] = { "zoom", NULL };
static const char *wall[] = { "nitrogen", NULL };
static const char *files[] = { "pcmanfm", NULL };
static const char *find[] = { "synapse", NULL };
static const char *office[] = { "libreoffice", NULL };
static const char *lyd[] = { "pavucontrol", NULL };
static const char *lock[] = { "slock", NULL };
static const char *web2[] = { "qutebrowser", NULL };
static const char *youtube[] = { "freetube", NULL };
static const char *logout[] = {"lxsession-logout", NULL };
static const char *screenshot[] = { "scrot", NULL };


static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_p,          spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,                  SHCMD("st -e fish") },
	{ MODKEY|ShiftMask,		XK_b,	   spawn, 	   {.v = web } },
	{ MODKEY|ShiftMask,		XK_i,	   spawn, 	   {.v = web2 } },
	{ MODKEY|ShiftMask,		XK_y,	   spawn, 	   {.v = youtube } },
	{ MODKEY|ShiftMask,		XK_l,	   spawn, 	   {.v = logout } },
	{ MODKEY|ShiftMask,		XK_e,	   spawn,	   {.v = email } },
	{ MODKEY|ShiftMask,		XK_g,	   spawn,	   {.v = xeditor } },
	{ MODKEY|ShiftMask,		XK_z,      spawn,	   {.v = metting } },
        { MODKEY|ShiftMask,		XK_n,	   spawn,	   {.v = wall } },
    	{ MODKEY|ShiftMask,		XK_f,	   spawn,	   {.v = files } },
	{ MODKEY|Mod1Mask,		XK_x,	   spawn,	   {.v = lock } },
	{ MODKEY,        		XK_s,      spawn,	   {.v = screenshot } },
	{ MODKEY|ControlMask|ShiftMask,	XK_s,      spawn,	   SHCMD("scrot -s") },
	{ MODKEY,	        	XK_r,	   spawn,	   {.v = find } },
	{ MODKEY|ShiftMask,		XK_o,	   spawn,	   {.v = office } },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   {.v = lyd } },
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   SHCMD("tabbed -c surf -e") },
	{ MODKEY|ShiftMask,		XK_v,	   spawn,	   SHCMD("virt-manager") },
	{ Mod1Mask,	        	XK_s,	   spawn,	   SHCMD("stalonetray") },
	{ Mod1Mask,	        	XK_g,	   spawn,	   SHCMD("gimp") },
	{ Mod1Mask,	        	XK_f,	   spawn,	   SHCMD("st -e ranger") },
        { MODKEY|ControlMask,		XK_q,	   spawn,	   SHCMD("systemctl suspend") },
	{ MODKEY|ControlMask|Mod1Mask,	XK_r,	   spawn,	   SHCMD("systemctl reboot") },
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,          rotatestack,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          rotatestack,            {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_Return,     zoom,                   {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,              Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};
