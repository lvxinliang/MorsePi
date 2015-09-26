CC = gcc
CXX= g++
STRIP = strip

CFLAGS= -fPIC -Wall -O2 -I.
LDFLAGS=
CGI_DIR = cgi-bin/

CGI_SRCS = execute.c utils.c
CGI_OBJS = $(patsubst %.c, %.o, $(CGI_SRCS))
TARGET= execute.cgi

all:$(TARGET)

execute.cgi: $(CGI_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

install:
	$(INSTALL) -d $(DESTDIR)$(WEBDIR)$(CGI_DIR)
	$(INSTALL) -m 755 -s --strip-program=$(STRIP) $(TARGET) $(DESTDIR)$(WEBDIR)$(CGI_DIR)

clean:
	-rm -f $(CGI_OBJS) $(TARGET)

.PHONY:all clean install uninstall $(TARGET)
