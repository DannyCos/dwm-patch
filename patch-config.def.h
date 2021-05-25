--- config.def.h.orig	2019-02-02 12:55:28.000000000 +0000
+++ config.def.h	2021-05-17 21:17:00.676409000 +0100
@@ -5,6 +5,7 @@
 static const unsigned int snap      = 32;       /* snap pixel */
 static const int showbar            = 1;        /* 0 means no bar */
 static const int topbar             = 1;        /* 0 means bottom bar */
+static const int focusonwheel       = 0;
 static const char *fonts[]          = { "monospace:size=10" };
 static const char dmenufont[]       = "monospace:size=10";
 static const char col_gray1[]       = "#222222";
@@ -28,7 +29,6 @@
 	 */
 	/* class      instance    title       tags mask     isfloating   monitor */
 	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
-	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
 };
 
 /* layout(s) */
@@ -44,7 +44,7 @@
 };
 
 /* key definitions */
-#define MODKEY Mod1Mask
+#define MODKEY Mod4Mask
 #define TAGKEYS(KEY,TAG) \
 	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
 	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
@@ -57,8 +57,12 @@
 /* commands */
 static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
 static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
-static const char *termcmd[]  = { "st", NULL };
+static const char *termcmd[]  = { "alacritty", NULL };
+static const char *incrvol[] = { "mixer", "vol", "+1:+1", NULL};
+static const char *decrvol[] = { "mixer", "vol", "-1:-1", NULL};
 
+#define XK_XF86AudioLowerVolume 0x1008ff11
+#define XK_XF86AudioRaiseVolume 0x1008ff13
 static Key keys[] = {
 	/* modifier                     key        function        argument */
 	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
@@ -94,6 +98,8 @@
 	TAGKEYS(                        XK_8,                      7)
 	TAGKEYS(                        XK_9,                      8)
 	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
+	{ 0x0,                          XK_XF86AudioRaiseVolume,    spawn,           {.v = incrvol } },
+	{ 0x0,                          XK_XF86AudioLowerVolume,    spawn,           {.v = decrvol } },
 };
 
 /* button definitions */
