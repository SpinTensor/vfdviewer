dist_data_DATA = vfdviewer.glade

noinst_LTLIBRARIES = libvfd.la \
		     libvgtk.la


bin_PROGRAMS = vfdviewer

vfdviewer_SOURCES = vfdviewer.c \
		    paths.c \
		    mpi_types.c
vfdviewer_CPPFLAGS = -D_DEBUG
vfdviewer_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
vfdviewer_LDFLAGS = @GTK_LIBS@ -rdynamic 
vfdviewer_LDADD = libvfd.la \
		  libvgtk.la


libvfd_la_SOURCES = vfd_header.c \
		    vfd_stacks.c \
		    vfd_samples.c \
		    vfd_list.c
libvfd_la_CPPFLAGS = -D_DEBUG
libvfd_la_CFLAGS = -g -Wall -Wextra -Wpedantic


libvgtk_la_SOURCES = vgtk_builder.c \
		     vgtk_main_window.c \
		     vgtk_main_menu_bar.c \
		     vgtk_open_file_dialog.c \
		     vgtk_about_dialog.c \
		     vgtk_stack_treeview.c \
		     vgtk_stack_tree_toolbar.c
libvgtk_la_CPPFLAGS = -D_DEBUG
libvgtk_la_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
libvgtk_la_LDFLAGS = @GTK_LIBS@
