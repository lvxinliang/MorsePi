#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define KEY_VALUE	0X01020304
#define MSG_SIZE	128
#define MSG_TYPE	1

void process_msg(char *msg);

typedef struct _mesg_buff_	{
	long mtype;
	char minfo[MSG_SIZE];
}msgbuf_st;

int main(int argc, char **argv)
{
	int msgid;
	msgbuf_st msgbuf;

	if (-1 == (msgid = msgget(KEY_VALUE, IPC_CREAT | 0666)))
		ERROR_EXIT("msgget");

	msgbuf.mtype = MSG_TYPE;
	strcpy(msgbuf.minfo, "helloworld");
#if 0
	if (-1 == (msgsnd(msgid, &msgbuf, sizeof(msgbuf_st) - sizeof(long), 0)))
		ERROR_EXIT("msgsnd");
#else
//	memset(&msgbuf, 0, sizeof(msgbuf));
	while(1) {
		if (-1 == msgrcv(msgid, &msgbuf, sizeof(msgbuf_st) - sizeof(long), msgbuf.mtype, 0))
			ERROR_EXIT("msgrcv");

		process_msg(msgbuf.minfo);
	}
#endif

	return 0;
}

void process_msg(char *msg)
{
		printf("info:%s\n", msg);
}
