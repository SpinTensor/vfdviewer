dist_data_DATA = vfdviewer.glade

bin_PROGRAMS = vfdviewer

vfdviewer_SOURCES = vfdviewer.c \
		    paths.c \
		    mpi_types.c \
		    vfd_header_IO.c \
		    vfd_stacks_IO.c \
		    vfd_samples_IO.c \
		    vfd.c

vfdviewer_CPPFLAGS = @GTK_CFLAGS@ -D_DEBUG -Wall -Wextra -Wpedantic
vfdviewer_CFLAGS = -g
vfdviewer_LDFLAGS = @GTK_LIBS@ -rdynamic
