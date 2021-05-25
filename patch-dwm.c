--- dwm.c.orig	2021-05-17 21:03:41.755149000 +0100
+++ dwm.c	2021-05-17 21:04:20.311598000 +0100
@@ -163,7 +163,6 @@
 static Monitor *dirtomon(int dir);
 static void drawbar(Monitor *m);
 static void drawbars(void);
-static void enternotify(XEvent *e);
 static void expose(XEvent *e);
 static void focus(Client *c);
 static void focusin(XEvent *e);
@@ -181,7 +180,6 @@
 static void mappingnotify(XEvent *e);
 static void maprequest(XEvent *e);
 static void monocle(Monitor *m);
-static void motionnotify(XEvent *e);
 static void movemouse(const Arg *arg);
 static Client *nexttiled(Client *c);
 static void pop(Client *);
@@ -249,13 +247,11 @@
 	[ConfigureRequest] = configurerequest,
 	[ConfigureNotify] = configurenotify,
 	[DestroyNotify] = destroynotify,
-	[EnterNotify] = enternotify,
 	[Expose] = expose,
 	[FocusIn] = focusin,
 	[KeyPress] = keypress,
 	[MappingNotify] = mappingnotify,
 	[MapRequest] = maprequest,
-	[MotionNotify] = motionnotify,
 	[PropertyNotify] = propertynotify,
 	[UnmapNotify] = unmapnotify
 };
@@ -424,7 +420,8 @@
 
 	click = ClkRootWin;
 	/* focus monitor if necessary */
-	if ((m = wintomon(ev->window)) && m != selmon) {
+	if ((m = wintomon(ev->window)) && m != selmon
+	    && (focusonwheel || (ev->button != Button4 && ev->button != Button5))) {
 		unfocus(selmon->sel, 1);
 		selmon = m;
 		focus(NULL);
@@ -444,8 +441,8 @@
 		else
 			click = ClkWinTitle;
 	} else if ((c = wintoclient(ev->window))) {
-		focus(c);
-		restack(selmon);
+		if (focusonwheel || (ev->button != Button4 && ev->button != Button5))
+			focus(c);
 		XAllowEvents(dpy, ReplayPointer, CurrentTime);
 		click = ClkClientWin;
 	}
@@ -752,25 +749,6 @@
 }
 
 void
-enternotify(XEvent *e)
-{
-	Client *c;
-	Monitor *m;
-	XCrossingEvent *ev = &e->xcrossing;
-
-	if ((ev->mode != NotifyNormal || ev->detail == NotifyInferior) && ev->window != root)
-		return;
-	c = wintoclient(ev->window);
-	m = c ? c->mon : wintomon(ev->window);
-	if (m != selmon) {
-		unfocus(selmon->sel, 1);
-		selmon = m;
-	} else if (!c || c == selmon->sel)
-		return;
-	focus(c);
-}
-
-void
 expose(XEvent *e)
 {
 	Monitor *m;
@@ -1113,23 +1091,6 @@
 		snprintf(m->ltsymbol, sizeof m->ltsymbol, "[%d]", n);
 	for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
 		resize(c, m->wx, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, 0);
-}
-
-void
-motionnotify(XEvent *e)
-{
-	static Monitor *mon = NULL;
-	Monitor *m;
-	XMotionEvent *ev = &e->xmotion;
-
-	if (ev->window != root)
-		return;
-	if ((m = recttomon(ev->x_root, ev->y_root, 1, 1)) != mon && mon) {
-		unfocus(selmon->sel, 1);
-		selmon = m;
-		focus(NULL);
-	}
-	mon = m;
 }
 
 void
