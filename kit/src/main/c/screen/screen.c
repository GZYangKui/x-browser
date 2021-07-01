//
// Created by yangkui on 2021/6/28.
//
#include "screen.h"
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

// Target brightness between 0.0 and 1.0
#define BRIGHTNESS 0.5

void c_brightness() {
    Display *dpy;
    static Atom backlight;
    int screen = 0, o = 0;
    Window root;
    XRRScreenResources *resources;
    RROutput output;
    XRRPropertyInfo *info;
    double min, max;
    long value;

    dpy = XOpenDisplay(NULL);
    backlight = XInternAtom(dpy, "Backlight", True);
    root = RootWindow(dpy, screen);
    resources = XRRGetScreenResources(dpy, root);
    output = resources->outputs[o];
    info = XRRQueryOutputProperty(dpy, output, backlight);
    min = info->values[0];
    max = info->values[1];
    XFree(info); // Don't need this anymore
    XRRFreeScreenResources(resources); // or this

    value = BRIGHTNESS * (max - min) + min;

    XRRChangeOutputProperty(dpy, output, backlight, XA_INTEGER,
                            32, PropModeReplace, (unsigned char *) &value, 1);
    XFlush(dpy);
    XSync(dpy, False);
}
