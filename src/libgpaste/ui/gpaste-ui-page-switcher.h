/*
 * This file is part of GPaste.
 *
 * Copyright (c) 2010-2016, Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 */

#if !defined (__G_PASTE_H_INSIDE__) && !defined (G_PASTE_COMPILATION)
#error "Only <gpaste.h> can be included directly."
#endif

#ifndef __G_PASTE_UI_PAGE_SWITCHER_H__
#define __G_PASTE_UI_PAGE_SWITCHER_H__

#include <gpaste-macros.h>

G_BEGIN_DECLS

#define G_PASTE_TYPE_UI_PAGE_SWITCHER (g_paste_ui_page_switcher_get_type ())

G_PASTE_FINAL_TYPE (UiPageSwitcher, ui_page_switcher, UI_PAGE_SWITCHER, GtkBox)

GtkWidget *g_paste_ui_page_switcher_new (void);

G_END_DECLS

#endif /*__G_PASTE_UI_PAGE_SWITCHER_H__*/
