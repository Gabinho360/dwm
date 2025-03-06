/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "MesloLGS Nerd Font Mono:size=16" };

static const char normborder[]      = "#3B4252"; 
static const char normbkg[]         = "#2E3440"; 
static const char normtext[]        = "#D8DEE9"; 
static const char selborder[]       = "#434C5E"; 
static const char selbkg[]          = "#434C5E"; 
static const char seltext[]         = "#ECEFF4"; 

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normtext, normbkg, normborder },
	[SchemeSel]  = { seltext, selbkg,  selborder  },
};

static const char *const autostart[] = {
        "sh", "-c", "feh --randomize --bg-fill ~/dwm/wallpapers/*", NULL,
        "slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "󰊖", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                      instance  title                 tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",                NULL,     NULL,                 0,         0,          1,          0,         0 },
	{ "Thunar",                   NULL,     NULL,                 0,         1,          0,          0,         0 },
	{ "steam",                    NULL,     NULL,                 0,         1,          0,          0,         0 },
	{ "pavucontrol",              NULL,     NULL,                 0,         1,          0,          0,         0 },
	{ NULL,                       NULL,     "Event Tester",       0,         0,          0,          1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c"

static const Key keys[] = {
	/* modifier                                    key                   function        argument */
	{ MODKEY,                                      XK_BackSpace,         spawn,          {.v = dmenucmd } },
	{ MODKEY,                                      XK_Return,            spawn,          {.v = termcmd } },
	{ MODKEY,                                      XK_k,                 focusstack,     {.i = +1 } },
	{ MODKEY,                                      XK_j,                 focusstack,     {.i = -1 } },
	{ MODKEY,                                      XK_i,                 incnmaster,     {.i = +1 } },
	{ MODKEY,                                      XK_d,                 incnmaster,     {.i = -1 } },
	{ MODKEY,                                      XK_h,                 setmfact,       {.f = -0.05} },
	{ MODKEY,                                      XK_l,                 setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,                            XK_k,                 movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,                            XK_j,                 movestack,      {.i = -1 } },
	{ MODKEY,                                      XK_f,                 killclient,     {0} },
	{ MODKEY,                                      XK_e,                 setlayout,      {.v = &layouts[0]} }, //tile
	{ MODKEY,                                      XK_q,                 setlayout,      {.v = &layouts[2]} }, //monocle
	{ MODKEY,                                      XK_0,                 view,           {.ui = ~0 } },
	{ MODKEY,                                      XK_comma,             focusmon,       {.i = -1 } }, //unused
	{ MODKEY,                                      XK_period,            focusmon,       {.i = +1 } }, //unused
	{ MODKEY|ShiftMask,                            XK_comma,             tagmon,         {.i = -1 } }, //unused
	{ MODKEY|ShiftMask,                            XK_period,            tagmon,         {.i = +1 } }, //unused
	TAGKEYS(                                       XK_1,                 0)
	TAGKEYS(                                       XK_2,                 1)
	TAGKEYS(                                       XK_3,                 2)
	TAGKEYS(                                       XK_4,                 3)
	TAGKEYS(                                       XK_5,                 4)
	{ MODKEY|ControlMask|ShiftMask,                XK_BackSpace,         quit,           {0} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask         button          function        argument */
	{ ClkWinTitle,          0,                 Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                 Button2,        spawn,          SHCMD("pavucontrol") },
	{ ClkClientWin,         MODKEY,            Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,            Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,            Button3,        resizemouse,    {0} },
        { ClkClientWin,         MODKEY,            Button4,        setcfact,       {.f = +0.25} }, // aumenta
	{ ClkClientWin,         MODKEY,            Button5,        setcfact,       {.f = -0.25} }, // diminui
	{ ClkTagBar,            0,                 Button1,        view,           {0} },
	{ ClkTagBar,            0,                 Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,            Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,            Button3,        toggletag,      {0} },
};
