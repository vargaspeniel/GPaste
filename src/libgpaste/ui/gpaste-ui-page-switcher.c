/*
 * This file is part of GPaste.
 *
 * Copyright (c) 2010-2016, Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 */

#include <gpaste-ui-page-switcher.h>

struct _GPasteUiPageSwitcher
{
    GtkBox parent_instance;
};

typedef struct
{
    gboolean tmp;
} GPasteUiPageSwitcherPrivate;

G_PASTE_DEFINE_TYPE_WITH_PRIVATE (UiPageSwitcher, ui_page_switcher, GTK_TYPE_BOX)

static void
g_paste_ui_page_switcher_dispose (GObject *object)
{
    GPasteUiPageSwitcherPrivate *priv = g_paste_ui_page_switcher_get_instance_private (G_PASTE_UI_PAGE_SWITCHER (object));

    G_OBJECT_CLASS (g_paste_ui_page_switcher_parent_class)->dispose (object);
}

static void
g_paste_ui_page_switcher_class_init (GPasteUiPageSwitcherClass *klass)
{
    G_OBJECT_CLASS (klass)->dispose = g_paste_ui_page_switcher_dispose;
}

static void
g_paste_ui_page_switcher_init (GPasteUiPageSwitcher *self)
{
    GtkWidget *widget = GTK_WIDGET (self);

    //gtk_widget_set_tooltip_text (widget, _("Track clipboard changes"));
    gtk_widget_set_valign (widget, GTK_ALIGN_CENTER);
}

/**
 * g_paste_ui_page_switcher_new:
 *
 * Create a new instance of #GPasteUiPageSwitcher
 *
 * Returns: a newly allocated #GPasteUiPageSwitcher
 *          free it with g_object_unref
 */
G_PASTE_VISIBLE GtkWidget *
g_paste_ui_page_switcher_new (void)
{
    GtkWidget *self = gtk_widget_new (G_PASTE_TYPE_UI_PAGE_SWITCHER, NULL);
    GPasteUiPageSwitcherPrivate *priv = g_paste_ui_page_switcher_get_instance_private (G_PASTE_UI_PAGE_SWITCHER (self));

    return self;
}
