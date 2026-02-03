#include "editor.h"

static void open_response(GObject *s, GAsyncResult *r, gpointer d)
{
    GFile *file;
    char *contents;
    gsize length;
    t_editor *editor;

    editor = (t_editor *)d;
    file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(s), r, NULL);
    if (!file)
        return ;
    if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL))
    {
        if (g_utf8_validate(contents, length, NULL))
            gtk_text_buffer_set_text(editor->buffer, contents, -1);
        g_free(contents);
        if (editor->file)
            g_object_unref(editor->file);
        editor->file = file;
    }
    else
        g_object_unref(file);
}

void on_open_clicked(GtkWidget *button, gpointer user_data)
{
    GtkFileDialog *dialog;
    t_editor *editor;

    (void)button;
    editor = (t_editor *)user_data;
    dialog = gtk_file_dialog_new();
    gtk_file_dialog_open(dialog, GTK_WINDOW(editor->window), NULL,
        open_response, editor);
    g_object_unref(dialog);
}

static void save_as_response(GObject *s, GAsyncResult *r, gpointer d)
{
    GtkFileDialog *dialog;
    GFile *file;
    GtkTextIter start;
    GtkTextIter end;
    char *text;
    t_editor *editor;

    dialog = GTK_FILE_DIALOG(s);
    editor = (t_editor *)d;
    file = gtk_file_dialog_save_finish(dialog, r, NULL);
    if (file)
    {
        gtk_text_buffer_get_bounds(editor->buffer, &start, &end);
        text = gtk_text_buffer_get_text(editor->buffer, &start, &end, FALSE);
        char *path = g_file_get_path(file);
        g_file_set_contents(path, text, -1, NULL);
        g_free(path);
        g_free(text);
        if (editor->file)
            g_object_unref(editor->file);
        editor->file = file;
    }
}

void on_save_as_clicked(GtkWidget *button, gpointer user_data)
{
    GtkFileDialog *dialog;
    t_editor *editor;

    (void)button;
    editor = (t_editor *)user_data;
    dialog = gtk_file_dialog_new();
    gtk_file_dialog_save(dialog, GTK_WINDOW(editor->window), NULL,
        save_as_response, editor);
    g_object_unref(dialog);
}

void on_save_clicked(GtkWidget *button, gpointer user_data)
{
    t_editor *editor;
    GtkTextIter start;
    GtkTextIter end;
    char *text;

    editor = (t_editor *)user_data;
    if (editor->file)
    {
        gtk_text_buffer_get_bounds(editor->buffer, &start, &end);
        text = gtk_text_buffer_get_text(editor->buffer, &start, &end, FALSE);
        char *path = g_file_get_path(editor->file);
        g_file_set_contents(path, text, -1, NULL);
        g_free(path);
        g_free(text);
    }
    else
        on_save_as_clicked(button, user_data);
}
