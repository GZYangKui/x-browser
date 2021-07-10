//
// Created by yangkui on 2021/7/9.
//

#ifndef X_LITE_NOTE_H
#define X_LITE_NOTE_H

#include "common.h"
#include <gtk/gtk.h>

typedef struct {
    int16 id;
    char *name;
    char *icon;
} NoteItem;

extern GtkWidget *note_widget();


#endif //X_LITE_NOTE_H
