/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 6;        /* gap pixel between windows */
static const unsigned int systraypinning  = 0;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;  /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 5;  /* systray spacing */
static const int systraypinningfailfirst  = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;  /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NF:size=9", "Font Awesome:size=9" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#20242d";
static const char col_gray2[]       = "#4c4f56";
static const char col_gray3[]       = "#62656c";
static const char col_gray4[]       = "#B3B8C3";
static const char col_cyan[]        = "#b04b57";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { " ", " ", " ", " ", " ", " ", " ", " ", " " };
/* static const char *tags[] = { "", "", "", "", "", "", "", "", "" }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
	{ "Firefox",   NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Emacs",     NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Alacritty", NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Pcmanfm",   NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Calibre",   NULL,       NULL,       1 << 5,       0,           -1 },
	{ "Steam",     NULL,       NULL,       1 << 6,       0,           -1 },
	{ "Spotify",   NULL,       NULL,       1 << 7,       0,           -1 },
	{ "mpv",       NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "< >",      NULL }, /* no layout function means floating behavior */
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "shiftview.c"
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD("/usr/bin/firefox --private-window") },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("emacsclient -c -a 'emacs'") },
	{ MODKEY,                       XK_a,      spawn,          SHCMD("emacsclient -c -a 'emacs' --eval '(dired nil)'") },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("pcmanfm") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("rofi -m 1 -show drun") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("rofi -m 1 -show window") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("rofi -m 1 -show power-menu -modi power-menu:~/.config/rofi/modules/rofi-power-menu") },
	{ MODKEY,                       XK_space,  togglebar,      {0} },
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_l,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_k,      shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_j,      shiftview,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,      setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_k,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_Tab,    setlayout,      {0} },
	{ MODKEY,                       XK_z,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_x,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_x,      tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	/* { MODKEY,                       XK_Return, zoom,           {0} }, */
	/* { MODKEY,                       XK_Tab,    view,           {0} }, */
	/* { MODKEY,                       XK_0,      view,           {.ui = ~0 } }, */
	/* { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } }, */
	/* { MODKEY,                       XK_s,      spawn,          {.v = dmenucmd } }, */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

static const char *const autostart[] = {
	"dwmblocks", NULL,
	"/usr/bin/emacs", "--daemon", NULL,
	"nm-applet", NULL,
	"picom", "-b", NULL,
	"dunst", NULL,
	"brightnessctl", "set 60%", NULL,
	NULL
};
