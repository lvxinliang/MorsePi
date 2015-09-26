CC = gcc
CXX= g++
STRIP = strip

CFLAGS= -fPIC -Wall -O2 -I.
LDFLAGS=

APP_SRCS = morsed.c
APP_OBJS = $(patsubst %.c, %.o, $(APP_SRCS))
TARGET= morsed

all:$(TARGET)

morsed: $(APP_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

install:
	$(INSTALL) -m 755 -s --strip-program=$(STRIP) $(TARGET) /usr/bin/

clean:
	-rm -f  $(APP_OBJS) $(TARGET)

.PHONY:all clean install uninstall $(TARGET)
