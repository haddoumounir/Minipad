#ifndef EDITOR_H
# define EDITOR_H

# include <gtk/gtk.h>

typedef struct s_editor {
    GtkWidget *window;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    GFile *file;
    GtkWidget *status_label;
} t_editor;

void activate(GtkApplication *app, gpointer user_data);
void on_open_clicked(GtkWidget *button, gpointer user_data);
void on_save_clicked(GtkWidget *button, gpointer user_data);
void on_save_as_clicked(GtkWidget *button, gpointer user_data);
void on_mark_set(GtkTextBuffer *b, GtkTextIter *i, GtkTextMark *m, gpointer d);

#endif
