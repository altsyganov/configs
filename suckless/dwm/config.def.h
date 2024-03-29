#define TERM "alacritty"
#define SCRIPTS_HOME "$HOME/.local/bin/"
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 25;        /* gaps between windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */

static const char *fonts[]          = { "xft:FiraCode Nerd Font:style=Retina,Regular:size=18:antialias=true:hinting=true" };
static const char dmenufont[]       = "xft:FiraCode Nerd Font:style=Retina,Regular:size=18";
static const char background[]      = "#1E1E2E";
static const char foreground[]      = "#D9E0EE";
static const char magenta[]         = "#F5C2E7";
static const char cyan[]            = "#96CDFB";
static const char yellow[]          = "#FAE3B0";
static const char red[]             = "#F28FAD";

/* static const char *colors[][8]      = {
	*   fg         bg         border   *
	{ foreground, background, background },
	{ background, magenta,    magenta },
	{ background, cyan,       cyan },
	{ background, yellow,     yellow },
	{ background, red,        red },
}; */
static const char norm_fg[] = "#a89984";
static const char norm_bg[] = "#282828";
static const char norm_border[] = "#928374";

static const char sel_fg[] = "#282828";
static const char sel_bg[] = "#a790d5";
static const char sel_border[] = "#a89984";

static const char urg_fg[] = "#a89984";
static const char urg_bg[] = "#a790d5";
static const char urg_border[] = "#b8bb26";

static const char title_fg[] = "#b8bb26";
static const char title_bg[] = "#3A3A3A";

static const char col_borderbar[]   = "#75715e";


static const char *colors[][3]      = {
    /*               fg           bg         border                         */
     { norm_fg,     norm_bg,   norm_border }, // unfocused wins
     { sel_fg,      sel_bg,    sel_border },  // the focused win
     { urg_fg,      urg_bg,    urg_border },
     { title_fg,   title_bg,  norm_border },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *alttags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance   title  tags mask   isfloating   isterminal noswallow monitor */
	{ "Gnome-screenshot", NULL, "Screenshot", 0,          1,           0,         1,       -1 },
	{ "Galculator",       NULL, "galculator", 0,          1,           0,         1,       -1 },
	{ "mpv",              NULL,     NULL,  	  0,          1,           0,         1,       -1 },
	{ TERM,               NULL,     NULL,     0,          0,           1,         0,       -1 },

};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { TERM, NULL };

// custom commands
//
// audio
static const char *increase_vol_cmd[] = { SCRIPTS_HOME"pulsevolume", "--increase", NULL };
static const char *decrease_vol_cmd[] = { SCRIPTS_HOME"pulsevolume", "--decrease", NULL };
static const char *toggle_mute_cmd[] = { SCRIPTS_HOME"pulsevolume", "--mute", NULL };
static const char *pause_cmd[] = { "mpc", "toggle", NULL };
static const char *next_song_cmd[] = { "mpc", "next", NULL };
static const char *previous_song_cmd[] = { "mpc", "prev", NULL };
static const char *inc_mpd_vol[] = { "mpc", "volume", "+10", NULL };
static const char *dec_mpd_vol[] = { "mpc", "volume", "-10", NULL };
static const char *clear_mpd_list[] = { "mpc", "clear", NULL };

// launchers
static const char *open_browser_cmd[] = { "firefox", NULL };
static const char *open_vim_cmd[] = { TERM, "-e", "nvim", NULL };
static const char *open_ncmpcpp_cmd[] = { TERM, "-e", "ncmpcpp", NULL };
static const char *screenshot_cmd[] = { "mate-screenshot", "-a", NULL };
static const char *open_htop_cmd[] = { TERM, "-e", "htop", NULL };
static const char *open_fm_cmd[] = { TERM, "-e", "lf", NULL };
static const char *sys_upgrade[] = { SCRIPTS_HOME"upgrade", NULL };
static const char *open_calculator[] = { "galculator", NULL };

// dmenu
static const char *passmenucmd[] = { "passmenu", "--type", NULL };
static const char *logoutcmd[] = { "slock", NULL };
static const char *projects_menu_cmd[] = { SCRIPTS_HOME"dmenu_projects", NULL };
static const char *web_menu_cmd[] = { SCRIPTS_HOME"dmenu_web", NULL };
static const char *musicmenu[] = { SCRIPTS_HOME"dmenu_mpd", NULL };
static const char *monitors[] = { SCRIPTS_HOME"monitors", NULL };

// change xkeymap
static const char *changexmap[] = { SCRIPTS_HOME"changexmap", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_a,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ ControlMask|ShiftMask,        XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_slash,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_minus,  togglefullscr,  {0} },
	{ MODKEY|ShiftMask, 		XK_s, 	   togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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

	// CUSTOM KEYS
	// launchers
	{ MODKEY,                       XK_n,      spawn,          {.v = open_browser_cmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = open_vim_cmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = open_ncmpcpp_cmd } },	
	{ MODKEY,                       XK_p,      spawn,          {.v = screenshot_cmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = open_htop_cmd } },
	{ MODKEY,                       XK_f,      spawn,          {.v = open_fm_cmd } },
	{ MODKEY,                       XK_u,      spawn,          {.v = sys_upgrade } },
	{ MODKEY,                       XK_c,      spawn,          {.v = open_calculator } },

	// dmenu
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = passmenucmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          {.v = logoutcmd } },	
	{ MODKEY,                       XK_d,      spawn,          {.v = projects_menu_cmd } },	
	{ MODKEY,                       XK_b,      spawn,          {.v = web_menu_cmd } },	
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = musicmenu } },	
	
	// audio
	{ ControlMask|Mod1Mask,         XK_k,      spawn,          {.v = increase_vol_cmd } },
	{ ControlMask|Mod1Mask,         XK_j,      spawn,          {.v = decrease_vol_cmd } },
	{ ControlMask|Mod1Mask,         XK_m,      spawn,          {.v = toggle_mute_cmd } },
	{ ControlMask|Mod1Mask,         XK_p,      spawn,          {.v = pause_cmd } },
	{ ControlMask|Mod1Mask,         XK_l,      spawn,          {.v = next_song_cmd } },
	{ ControlMask|Mod1Mask,         XK_h,      spawn,          {.v = previous_song_cmd } },
	{ ControlMask|Mod1Mask,         XK_equal,  spawn,          {.v = inc_mpd_vol } },
	{ ControlMask|Mod1Mask,         XK_minus,  spawn,          {.v = dec_mpd_vol } },
	{ ControlMask|Mod1Mask,         XK_c,      spawn,          {.v = clear_mpd_list } },

	// etc
	{ ControlMask|Mod1Mask,         XK_x,      spawn,          {.v = changexmap } },
	{ ControlMask|Mod1Mask,         XK_d,      spawn,          {.v = monitors } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

