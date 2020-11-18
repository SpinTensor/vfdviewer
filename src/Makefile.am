dist_data_DATA = vfdviewer.glade

bin_PROGRAMS = vfdviewer

vfdviewer_SOURCES = vfdviewer.c \
		    paths.c \
		    vfd_header_IO.c \
		    vfd_IO.c
vfdviewer_CPPFLAGS = @GTK_CFLAGS@ -D_DEBUG -Wall -Wextra -Wpedantic
vfdviewer_CFLAGS = -g
vfdviewer_LDFLAGS = @GTK_LIBS@ -rdynamic
