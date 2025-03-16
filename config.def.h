/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaMono Nerd Font:size=20" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#77002e";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
	"slstatus", NULL,
	"sh", "-c", "feh --randomize --bg-fill ~/wp/*", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,             NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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
static const char *launcher[] = { "rofi", "-show", "drun", NULL };
static const char *terminal[] = { "alacritty", NULL };

#include "movestack.c"

static const Key keys[] = {
	/* modifier                                          key                             function        argument */
	{ MODKEY,                                            XK_BackSpace,                   spawn,          {.v = launcher } },
	{ MODKEY,                                            XK_Return,                      spawn,          {.v = terminal } },
	{ MODKEY,                                            XK_Escape,                      togglebar,      {0} },
	{ MODKEY,                                            XK_k,                           focusstack,     {.i = +1 } },
	{ MODKEY,                                            XK_j,                           focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,                                  XK_k,                           movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,                                  XK_j,                           movestack,      {.i = -1 } },
	{ MODKEY,                                            XK_h,                           setmfact,       {.f = -0.05} },
	{ MODKEY,                                            XK_l,                           setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,                                  XK_l,                           setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,                                  XK_h,                           setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,                                  XK_o,                           setcfact,       {.f =  0.00} },
	{ MODKEY,                                            XK_Tab,                         view,           {0} },
	{ MODKEY,                                            XK_q,                           zoom,           {0} },
	{ MODKEY,                                            XK_f,                           killclient,     {0} },
	{ MODKEY,                                            XK_t,                           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                                            XK_y,                           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                                            XK_u,                           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                                            XK_comma,                       focusmon,       {.i = -1 } },
	{ MODKEY,                                            XK_period,                      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,                                  XK_comma,                       tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,                                  XK_period,                      tagmon,         {.i = +1 } },
	TAGKEYS(                                             XK_1,                                           0)
	TAGKEYS(                                             XK_2,                                           1)
	TAGKEYS(                                             XK_3,                                           2)
	TAGKEYS(                                             XK_4,                                           3)
	TAGKEYS(                                             XK_5,                                           4)
	{ MODKEY|ControlMask|ShiftMask,                      XK_BackSpace,                   quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("alacritty -e alsamixer") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
