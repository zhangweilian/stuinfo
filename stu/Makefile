CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi add1.cgi	mod1.cgi del1.cgi stu.cgi teacher.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
				cp *.cgi /usr/lib/cgi-bin/sx
				cp stu.html /usr/lib/cgi-bin/sx
				cp teacher.html /usr/lib/cgi-bin/sx
