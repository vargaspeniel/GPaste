/*
 * This file is part of GPaste.
 *
 * Copyright (c) 2010-2016, Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 */

#include <gpaste-ui-page.h>

struct _GPasteUiPage
{
    GtkButton parent_instance;
};

typedef struct
{
    guint64 page;
} GPasteUiPagePrivate;

G_PASTE_DEFINE_TYPE_WITH_PRIVATE (UiPage, ui_page, GTK_TYPE_BUTTON)

enum
{
    SWITCH,

    LAST_SIGNAL
};

static guint64 signals[LAST_SIGNAL] = { 0 };

static gboolean
g_paste_ui_page_button_press_event (GtkWidget      *widget,
                                    GdkEventButton *event G_GNUC_UNUSED)
{
    const GPasteUiPagePrivate *priv = _g_paste_ui_page_get_instance_private (G_PASTE_UI_PAGE (widget));

    g_signal_emit (widget, signals[SWITCH], 0, priv->page, NULL);

    return GDK_EVENT_STOP;
}

static void
g_paste_ui_page_class_init (GPasteUiPageClass *klass)
{
    GTK_WIDGET_CLASS (klass)->button_press_event = g_paste_ui_page_button_press_event;

    /**
     * GPasteUiPage::switch:
     * @ui_page: the object on which the signal was emitted
     * @page: the page we switched to
     *
     * The "switch" signal is emitted when the user wants to
     * switch to a new page
     */
    signals[SWITCH] = g_signal_new ("switch",
                                    G_PASTE_TYPE_UI_PAGE,
                                    G_SIGNAL_RUN_LAST,
                                    0, /* class offset */
                                    NULL, /* accumulator */
                                    NULL, /* accumulator data */
                                    g_cclosure_marshal_generic,
                                    G_TYPE_NONE,
                                    1, /* number of params */
                                    G_TYPE_UINT64);
}

static void
g_paste_ui_page_init (GPasteUiPage *self)
{
    gtk_widget_set_valign (GTK_WIDGET (self), GTK_ALIGN_CENTER);
}

G_PASTE_VISIBLE void
g_paste_ui_page_set_active (GPasteUiPage *self,
                            gboolean      active)
{
    g_return_if_fail (G_PASTE_IS_UI_PAGE (self));

    GPasteUiPagePrivate *priv = g_paste_ui_page_get_instance_private (G_PASTE_UI_PAGE (self));
    GtkLabel *label = GTK_LABEL (gtk_bin_get_child (GTK_BIN (self)));
    g_autofree gchar *text = g_strdup_printf ("%" G_GUINT64_FORMAT, priv->page);

    if (active)
    {
        g_autofree gchar *markup = g_markup_printf_escaped ("<b>%s</b>", text);

        gtk_label_set_markup (label, markup);
        //add_style_pseudo_class('active');
    }
    else
    {
        gtk_label_set_text (label, text);
        //remove_style_pseudo_class('active');
    }
}

/**
 * g_paste_ui_page_new:
 * @page: the page we're currently pointing to
 *
 * Create a new instance of #GPasteUiPage
 *
 * Returns: a newly allocated #GPasteUiPage
 *          free it with g_object_unref
 */
G_PASTE_VISIBLE GtkWidget *
g_paste_ui_page_new (guint64 page)
{
    g_autofree gchar *label = g_strdup_printf ("%" G_GUINT64_FORMAT, page);
    g_autofree gchar *tooltip = g_strdup_printf ("%s %" G_GUINT64_FORMAT, _("Page"), page);

    GtkWidget *self = gtk_widget_new (G_PASTE_TYPE_UI_PAGE,
                                      "label", label,
                                      NULL);
    GPasteUiPagePrivate *priv = g_paste_ui_page_get_instance_private (G_PASTE_UI_PAGE (self));

    priv->page = page;

    gtk_widget_set_tooltip_text (self, tooltip);

    return self;
}
