TOPDIR := $(shell pwd)
CC = gcc
CXX= g++
STRIP = strip

DESTDIR = /var/www/
WEBDIR = morse/
INSTALL = install
MAKE = make
TARGET = cgi app

export TOPDIR
export DESTDIR
export WEBDIR
export INSTALL

all:$(TARGET)

cgi:
	$(MAKE) -C $(TOPDIR)/cgi/

app:
	$(MAKE) -C $(TOPDIR)/app/

install:$(TARGET)
	cp -a $(TOPDIR)/morse/ $(DESTDIR)
	$(MAKE) install -C $(TOPDIR)/cgi/
	$(MAKE) install -C $(TOPDIR)/app/

clean:
	$(MAKE) clean -C $(TOPDIR)/cgi/
	$(MAKE) clean -C $(TOPDIR)/app/

uninstall:
	-rm -rf $(DESTDIR)$(WEBDIR)

.PHONY:all clean install uninstall $(TARGET)
