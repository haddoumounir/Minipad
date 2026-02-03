#include "editor.h"

static void setup_buttons(t_editor *e, GtkWidget *header)
{
    GtkWidget *btn;

    btn = gtk_button_new_with_label("Open");
    g_signal_connect(btn, "clicked", G_CALLBACK(on_open_clicked), e);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn);
    btn = gtk_button_new_with_label("Save");
    g_signal_connect(btn, "clicked", G_CALLBACK(on_save_clicked), e);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn);
    btn = gtk_button_new_with_label("Save As");
    g_signal_connect(btn, "clicked", G_CALLBACK(on_save_as_clicked), e);
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), btn);
}

static void on_destroy(GtkWidget *widget, gpointer data)
{
    t_editor *editor;

    (void)widget;
    editor = (t_editor *)data;
    if (editor->file)
        g_object_unref(editor->file);
    g_free(editor);
}

void on_mark_set(GtkTextBuffer *b, GtkTextIter *i, GtkTextMark *m, gpointer d)
{
    t_editor *e;
    char buf[64];
    int row;
    int col;

    (void)i;
    e = (t_editor *)d;
    if (m != gtk_text_buffer_get_insert(b))
        return ;
    gtk_text_buffer_get_iter_at_mark(b, i, m);
    row = gtk_text_iter_get_line(i) + 1;
    col = gtk_text_iter_get_line_offset(i);
    snprintf(buf, 64, "Line: %d, Col: %d", row, col);
    gtk_label_set_text(GTK_LABEL(e->status_label), buf);
}

void activate(GtkApplication *app, gpointer user_data)
{
    t_editor *e;
    GtkWidget *box;
    GtkWidget *scrolled;
    GtkWidget *header;

    (void)user_data;
    e = g_malloc(sizeof(t_editor));
    e->window = gtk_application_window_new(app);
    e->file = NULL;
    gtk_window_set_default_size(GTK_WINDOW(e->window), 800, 600);
    header = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(e->window), header);
    setup_buttons(e, header);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(e->window), box);
    scrolled = gtk_scrolled_window_new();
    gtk_box_append(GTK_BOX(box), scrolled);
    gtk_widget_set_vexpand(scrolled, TRUE);
    e->text_view = gtk_text_view_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), e->text_view);
    e->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(e->text_view));
    e->status_label = gtk_label_new("Line: 1, Col: 0");
    gtk_box_append(GTK_BOX(box), e->status_label);
    gtk_widget_set_halign(e->status_label, GTK_ALIGN_END);
    g_signal_connect(e->buffer, "mark-set", G_CALLBACK(on_mark_set), e);
    g_signal_connect(e->window, "destroy", G_CALLBACK(on_destroy), e);
    gtk_window_present(GTK_WINDOW(e->window));
}
