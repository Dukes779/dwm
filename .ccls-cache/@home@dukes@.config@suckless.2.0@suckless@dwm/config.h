/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx        = 1;        /* border pixel of windows */
static const unsigned int snap            = 32;       /* snap pixel */
static const unsigned int gappih          = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv          = 7;       /* vert inner gap between windows */
static const unsigned int gappoh          = 7;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov          = 7;       /* vert outer gap between windows and screen edge */
static const unsigned int colorfultitle   = 1;       /* 0 means title use SchemeTitle and SchemeTitleFloat */
static const unsigned int colorfultag     = 1;       /* 0 means use SchemeSel for selected tag */
static       int smartgaps                = 0;
static const int swallowfloating          = 0;        /* 1 means swallow floating windows by default */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
static const int user_bh                  = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]                = { "Shure Tech Mono Nerd Font:size=10"};
static const char dmenufont[]             = "Shure Tech Mono Nerd Font:size=10";
static const char col_gray1[]             = "#0B0716";
static const char col_gray2[]             = "#a6e3a1";
static const char col_gray3[]             = "#6E6C7E";
static const char col_gray4[]             = "#cdd6f4";
static const char cyan[]                  = "#E8A2AF" ;
#include "themes/catppuccin.h" 
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = {col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, cyan,  cyan  },

       /* The Beginning of something */
    [SchemeTag]        = { col_gray1 ,        col_gray1,    col_gray1},
    [SchemeTag1]       = { black ,            col_gray1,    col_gray1},
    [SchemeTag2]       = { gray2,             col_gray1,    col_gray1},
    [SchemeTag3]       = { gray3,             col_gray1,    col_gray1},
    [SchemeTag4]       = { gray4,             col_gray1,    col_gray1},
    [SchemeTag5]       = { blue,              col_gray1,    col_gray1},
	[SchemeTag6]       = { green,             col_gray1,    col_gray1},
	[SchemeTag7]       = { red ,              col_gray1,    col_gray1},
	[SchemeTag8]       = { orange,            col_gray1,    col_gray1},
	[SchemeTag9]       = { yellow,            col_gray1,    col_gray1},
	[SchemeLayout]     = { gray3,             col_gray1,    col_gray1},
	[SchemeTitle]      = { yellow ,           col_gray1,    col_gray1},
	[SchemeTitleFloat] = { col_gray2,         col_gray1,    col_gray1},
	[SchemeTitle1]     = { col_gray1,            cyan,      col_gray1},
	[SchemeTitle2]     = { col_gray1,            cyan,      col_gray1},
    [SchemeTitle3]     = { col_gray1,            cyan,      col_gray1},
    [SchemeTitle4]     = { col_gray1,            cyan,      col_gray1},
    [SchemeTitle5]     = { col_gray1,            cyan,      col_gray1},
	[SchemeTitle6]     = { col_gray1,            cyan,      col_gray1},
	[SchemeTitle7]     = { col_gray1,            cyan,      col_gray1},
	[SchemeTitle8]     = { col_gray1,            cyan,      col_gray1},
	[SchemeTitle9]     = { col_gray1,            cyan,      col_gray1},
};

static const int tagschemes[] = { SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5, SchemeTag6, SchemeTag7, SchemeTag8, SchemeTag9 };
static const int titleschemes[] = { SchemeTitle1, SchemeTitle2, SchemeTitle3, SchemeTitle4, SchemeTitle5, SchemeTitle6, SchemeTitle7, SchemeTitle8, SchemeTitle9 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const char *tagsel[][2] = {
	{ "#F5C2E7", "#0B0716" },
	{ "#DDB6F2", "#0B0716" },
	{ "#C9CBFF", "#0B0716" },
	{ "#F28FAD", "#0B0716" },
	{ "#F2CDCD", "#0B0716" },
	{ "#ABE9B3", "#0B0716" },
	{ "#F2CDCD", "#0B0716" },
	{ "#F28FAD", "#0B0716" },
	{ "#DDB6F2", "#0B0716" },
};

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",             NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox",          NULL,     NULL,           2,         0,          0,          -1,        -1 },
	{ "St",               NULL,     NULL,           1,         0,          1,           0,        -1 },
	{ NULL,               NULL,    "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
	{ "Pavucontrol",      NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "Arandr",           NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lxappearance",     NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Leafpad",          NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "discord",          NULL,     NULL,           4,         0,          0,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
/*	{ "TTT",      bstack },   */
/*	{ "[@]",      spiral },   */
/*	{ "[\\]",     dwindle },  */	
/*	{ "[D]",      deck    },  */
	{ "[M]",      monocle },  
	{ "|M|",      centeredmaster },
/*	{ ">M>",      centeredfloatingmaster }, */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]   = { "st", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd }  },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("pcmanfm") },
    { MODKEY,                       XK_p,      spawn,          SHCMD("~/Documents/Scripts/lock.sh" ) },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_I,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
/*  { MODKEY,                       XK_x,      setlayout,      {.v = &layouts[]}  }, */
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
/*	{ MODKEY|ControlMask,           XK_x,      setlayout,      {.v = &layouts[5]} }, */
/*	{ MODKEY|ControlMask,           XK_a,      setlayout,      {.v = &layouts[6]} }, */
/*	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[7]} }, */
/*	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[8]} }, */
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_u,      togglecolorfultag,   {0} },
	{ MODKEY|ShiftMask,             XK_u,      togglecolorfultitle, {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn, SHCMD(" pamixer -d 5 --allow-boost && dunstify -h string:x-dunst-stack-tag:volume volume: $(pamixer --get-volume)%") },
	{ 0,                            XF86XK_AudioMute,          spawn, SHCMD(" pamixer -t && dunstify -h string:x-dunst-stack-tag:mute mute: $(pamixer --get-mute)!") },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn, SHCMD("pamixer -i 5 --allow-boost && dunstify -h string:x-dunst-stack-tag:volume volume: $(pamixer --get-volume)%") },
	{ 0,                            XF86XK_AudioPlay,          spawn, SHCMD("playerctl play-pause") },
	{ 0,                            XF86XK_AudioPrev,          spawn, SHCMD("playerctl previous") },
	{ 0,                            XF86XK_AudioNext,          spawn, SHCMD("playerctl next") },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn, SHCMD("xbacklight -inc 10") },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn, SHCMD("xbacklight -dec 10") },
	/* { 0,                            XK_Print,                  spawn, SHCMD("flameshot full -p ~/Pictures/Screenshots") }, */
	{ MODKEY|Mod4Mask,              XK_Y,      incrgaps,       {.i = +1 } },
	{ 0,                            XK_Print,                  spawn, SHCMD("awesome-flameshot") },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_e,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_O,      defaultgaps,    {0} },
	{ MODKEY,                       XK_r,      togglesmartgaps,{0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

