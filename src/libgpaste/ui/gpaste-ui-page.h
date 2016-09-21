/*
 * This file is part of GPaste.
 *
 * Copyright (c) 2010-2016, Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 */

#if !defined (__G_PASTE_H_INSIDE__) && !defined (G_PASTE_COMPILATION)
#error "Only <gpaste.h> can be included directly."
#endif

#ifndef __G_PASTE_UI_PAGE_H__
#define __G_PASTE_UI_PAGE_H__

#include <gpaste-macros.h>

G_BEGIN_DECLS

#define G_PASTE_TYPE_UI_PAGE (g_paste_ui_page_get_type ())

G_PASTE_FINAL_TYPE (UiPage, ui_page, UI_PAGE, GtkButton)

void g_paste_ui_page_set_active (GPasteUiPage *self,
                                 gboolean      active);

GtkWidget *g_paste_ui_page_new (guint64 page);

G_END_DECLS

#endif /*__G_PASTE_UI_PAGE_H__*/
