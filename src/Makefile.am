# install directory for glade file
# without specific choice it is
# $(prefix)/share/vfdviewer/
vfdview_dir = $(pkgdatadir)
vfdview__DATA = vfdviewer.glade

noinst_LTLIBRARIES = libvfd.la \
		     libvgtk.la \
		     libvutils.la

bin_PROGRAMS = vfdviewer

vfdviewer_SOURCES = vfdviewer.c
vfdviewer_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
vfdviewer_LDFLAGS = @GTK_LIBS@ -rdynamic -lm
vfdviewer_LDADD = libvfd.la \
		  libvgtk.la \
		  libvutils.la
# external libraries
vfdviewer_LDADD += ${top_builddir}/external/libslope.la \
		   ${top_builddir}/external/libtinyexpr.la

libvutils_la_SOURCES = mpi_types.c \
		       v_timer.c \
		       hashing.c
libvutils_la_CFLAGS = -g -Wall -Wextra -Wpedantic

libvfd_la_SOURCES = vfd_header.c \
		    vfd_hwc_header.c \
		    vfd_stacks.c \
		    vfd_samples.c \
		    vfd_fcalls.c \
		    vfd_msgreg.c \
		    vfd_statistics.c \
		    vfd_sort.c \
		    vfd_list.c \
		    vfd_load.c
libvfd_la_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic


libvgtk_la_SOURCES = vgtk_handles.c \
		     vgtk_builder.c \
		     vgtk_main_window.c \
		     vgtk_main_menu_bar.c \
		     vgtk_open_file_dialog.c \
		     vgtk_about_dialog.c \
		     vgtk_stack_treeview.c \
		     vgtk_stack_tree_searchentry.c \
		     vgtk_stack_tree_toolbar.c \
		     vgtk_main_view.c \
		     vgtk_main_view_gtkstack.c \
		     vgtk_main_stacktimeline.c \
		     vgtk_stacktimeline_spinner.c \
		     vgtk_stacktimeline_checkbuttons.c \
		     vgtk_stacktimeline_cursorpos_labels.c \
		     vgtk_stacktimeline_hscrollbar.c \
		     vgtk_stacktimeline_entry.c \
		     vgtk_main_comm_matrix.c \
		     vgtk_comm_matrix_grid.c \
		     vgtk_comm_matrix.c \
		     vgtk_comm_matrix_legend.c \
		     vgtk_comm_matrix_mode_switcher.c \
		     vgtk_comm_matrix_update_bw.c \
		     vgtk_comm_matrix_update_size.c \
		     vgtk_comm_matrix_update_count.c \
		     vgtk_comm_matrix_cursorpos_labels.c \
		     vgtk_colors.c \
		     vgtk_surfaces.c
libvgtk_la_CPPFLAGS= -D_DATADIR=$(pkgdatadir)
libvgtk_la_CFLAGS = @GTK_CFLAGS@ -g -Wall -Wextra -Wpedantic
libvgtk_la_LDFLAGS = @GTK_LIBS@ -lm
