/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#include "/home/andreas/.config/dwm/themes/nord.h"

/* appearance */
static const unsigned int borderpx       = 2;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappih         = 5;  /* horiz inner gap between windows */
static const unsigned int gappiv         = 5;  /* vert inner gap between windows */
static const unsigned int gappoh         = 5;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 5;  /* vert outer gap between windows and screen edge */
static const int smartgaps_fact          = 1;   /* gap factor when there is only one client; 0 = no gaps, 3 = 3x outer gaps */
static const char autostartblocksh[]     = "autostart_blocking.sh";
static const char autostartsh[]          = "autostart.sh";
static const char dwmdir[]               = "dwm";
static const char localshare[]           = ".local/share";
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */
static const int statusmon               = -1;
static const int horizpadbar             = 2;   /* horizontal padding for statusbar */
static const int vertpadbar              = 6;   /* vertical padding for statusbar */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int showsystray             = 1;   /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype              = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype            = INDICATOR_NONE;
static int floatindicatortype            = INDICATOR_TOP_LEFT_SQUARE;
static const char *fonts[]               = { "Noto Sans:Bold:size=10:antialias=true:autohint=true",
                                             "FontAwesome:size:11:antialias=true:autohint=true"
                                                             };
static const char dmenufont[]            = "Noto Sans:Bold:size=10:antialias=true";

static char *colors[][ColCount] = {
	/*                       fg                bg                border                float */
	[SchemeNorm]         = { normfgcolor,      normbgcolor,      normbordercolor,      normfloatcolor },
	[SchemeSel]          = { selfgcolor,       selbgcolor,       selbordercolor,       selfloatcolor },
	[SchemeTitleNorm]    = { titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor },
	[SchemeTitleSel]     = { titleselfgcolor,  titleselbgcolor,  titleselbordercolor,  titleselfloatcolor },
	[SchemeTagsNorm]     = { tagsnormfgcolor,  tagsnormbgcolor,  tagsnormbordercolor,  tagsnormfloatcolor },
	[SchemeTagsSel]      = { tagsselfgcolor,   tagsselbgcolor,   tagsselbordercolor,   tagsselfloatcolor },
	[SchemeHidNorm]      = { hidnormfgcolor,   hidnormbgcolor,   c000000,              c000000 },
	[SchemeHidSel]       = { hidselfgcolor,    hidselbgcolor,    c000000,              c000000 },
	[SchemeUrg]          = { urgfgcolor,       urgbgcolor,       urgbordercolor,       urgfloatcolor },
};

/*const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };*/
const char *spcmd1[] = {"kitty", "-t", "spterm", "--class", "spterm", NULL };
const char *spcmd2[] = {"kitty", "-t", "spvol", "--class", "spvol", "-e", "pulsemixer", NULL };
const char *spcmd3[] = {"kitty", "-t", "spfm", "--class", "spfm", "-e", "ranger", NULL };
const char *spcmd4[] = {"kitty", "-t", "spht", "--class", "spht", "-e", "htop", NULL };
static Sp scratchpads[] = {
   /* name          cmd  */
   {"spterm",      spcmd1},
   {"spvol",       spcmd2},
   {"spfm",        spcmd3},
   {"spht",        spcmd4}, 
};

static char *tagicons[][NUMTAGS] = {
    [DEFAULT_TAGS]        = { "", "", "", "", "", "" },
    [ALTERNATIVE_TAGS]    = { "A", "B", "C", "D", "E", "F" },
    [ALT_TAGS_DECORATION] = { "<1>", "<2>", "<3>", "<4>", "<5>", "<6>" },
};


static const Rule rules[] = {
	RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
	RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
	RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
	RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
	RULE(.class = "zoom", .tags = 1 << 4, .isfloating = 1)
	RULE(.class = "wine", .tags = 1 << 1, .isfloating = 1)
	RULE(.class = "Galculator", .tags = 1, .isfloating = 1)
	RULE(.class = "Grsync", .tags = 1, .isfloating = 1)
/*	RULE(.class = "Firefox", .tags = 1 << 1) */
	RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
	RULE(.instance = "spvol", .tags = SPTAG(1), .isfloating = 1)
	RULE(.instance = "spfm", .tags = SPTAG(2), .isfloating = 1)
	RULE(.instance = "spht", .tags = SPTAG(3), .isfloating = 1)
};

static const BarRule barrules[] = {
	/* monitor   bar    alignment         widthfunc                drawfunc                clickfunc                name */
	{ -1,        0,     BAR_ALIGN_LEFT,   width_tags,              draw_tags,              click_tags,              "tags" },
	{  0,        0,     BAR_ALIGN_RIGHT,  width_systray,           draw_systray,           click_systray,           "systray" },
	{ -1,        0,     BAR_ALIGN_LEFT,   width_ltsymbol,          draw_ltsymbol,          click_ltsymbol,          "layout" },
	{ statusmon, 0,     BAR_ALIGN_RIGHT,  width_status2d,          draw_status2d,          click_status2d,          "status2d" },
	{ -1,        0,     BAR_ALIGN_NONE,   width_wintitle,          draw_wintitle,          click_wintitle,          "wintitle" },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */



static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ NULL,       NULL },
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,              KEY,      tagnextmon,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask|ShiftMask,    KEY,      tagprevmon,     {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

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
static const char *termcmd[]  = { "kitty", NULL };
/*static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *brightnessup[] = { "xbacklight", "-inc", "5", NULL };
static const char *brightnessdown[] = { "xbacklight", "-dec", "5", NULL }; */


static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_p,          spawn,                  {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,                  SHCMD("kitty -e fish") },
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_j,          rotatestack,            {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_k,          rotatestack,            {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,             {.i = -1 } },
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,                       XK_Return,     zoom,                   {0} },
	{ MODKEY|Mod1Mask,              XK_u,          incrgaps,               {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,          incrgaps,               {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,          incrigaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,          incrigaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,          incrogaps,              {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,          incrogaps,              {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,          incrihgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,          incrihgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,          incrivgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,          incrivgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,          incrohgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,          incrohgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,          incrovgaps,             {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,          incrovgaps,             {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,          togglegaps,             {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,          defaultgaps,            {0} },
	{ MODKEY,                       XK_Tab,        view,                   {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} },
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,          quit,                   {1} },
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,          setlayout,              {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,      setlayout,              {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY,                       XK_z,      togglescratch,          {.ui = 0 } },
	{ MODKEY|ControlMask,           XK_z,      setscratch,             {.ui = 0 } },
	{ MODKEY|ShiftMask,             XK_z,      removescratch,          {.ui = 0 } },
	{ MODKEY,                       XK_y,      togglescratch,          {.ui = 1 } },
	{ MODKEY|ControlMask,           XK_y,      setscratch,             {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_y,      removescratch,          {.ui = 1 } },
	{ MODKEY,                       XK_r,      togglescratch,          {.ui = 2 } },
	{ MODKEY|ControlMask,           XK_r,      setscratch,             {.ui = 2 } },
	{ MODKEY|ShiftMask,             XK_r,      removescratch,          {.ui = 2 } },
	{ MODKEY,                       XK_s,      togglescratch,          {.ui = 3 } },
	{ MODKEY|ControlMask,           XK_s,      setscratch,             {.ui = 3 } },
	{ MODKEY|ShiftMask,             XK_s,      removescratch,          {.ui = 3 } },
	{ MODKEY,                       XK_0,          view,                   {.ui = ~SPTAGMASK } },
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~SPTAGMASK } },
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,      cyclelayout,            {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,            {.i = +1 } },
/*	{ MODKEY|Mod1Mask,              XK_space,      spawn,          CMD("rofi -modi drun -show drun -show-icons") }, */
    { MODKEY|ShiftMask,              XK_i,          spawn,          CMD("qutebrowser") },
    { MODKEY|ShiftMask,              XK_g,          spawn,          CMD("geany") },
    { MODKEY|ShiftMask,              XK_b,          spawn,          CMD("chromium") },
    { MODKEY|ShiftMask,              XK_y,          spawn,          CMD("freetube") },
    { MODKEY|ShiftMask,              XK_z,          spawn,          CMD("zoom") },
    { MODKEY|ShiftMask,              XK_n,          spawn,          CMD("nitrogen") },
    { MODKEY|ShiftMask,              XK_p,          spawn,          CMD("pavucontrol") },
    { MODKEY|ShiftMask,              XK_o,          spawn,          CMD("libreoffice") },
    { MODKEY|ShiftMask,              XK_e,          spawn,          CMD("claws-mail") },
    { MODKEY|ShiftMask,              XK_l,          spawn,          CMD("lxsession-logout") },
    { MODKEY|ShiftMask,              XK_s,          spawn,          CMD("tabbed -c surf -e") },
    { MODKEY|ShiftMask,              XK_f,          spawn,          CMD("pcmanfm") },
    { MODKEY|Mod1Mask,               XK_x,          spawn,          CMD("slock") },
    { MODKEY,			     XK_s,	    spawn,	    SHCMD("scrot") },
    { MODKEY,			     XK_r,	    spawn,	    CMD("synapse") },
    { Mod1Mask,                      XK_g,          spawn,	    CMD("gimp") },
    { Mod1Mask,                      XK_f,          spawn,	    SHCMD("kitty -e ranger") },
    { MODKEY|ControlMask|ShiftMask,  XK_s,          spawn,          SHCMD("scrot -s") },
    { MODKEY|ControlMask,	     XK_q,          spawn,	    SHCMD("systemctl suspend") },
    { MODKEY|ControlMask|Mod1Mask,   XK_r,          spawn,          SHCMD("systemctl reboot") },


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



