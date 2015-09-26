#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

#define KEY_VALUE	0X01020304
#define MSG_SIZE	128
#define MSG_TYPE	1
#define REDIRECT_INDEX "<script>window.setTimeout(\"location.href = 'http://%s/morse/index.html'\", %d);</script>\n"

void goto_index();

typedef struct _mesg_buff_	{
	long mtype;
	char minfo[MSG_SIZE];
}msgbuf_st;

int main(int argc, char *argv[])
{
	int msgid;
	msgbuf_st msgbuf;
	char *info=NULL;
	char info_str[MSG_SIZE];
	int lenstr = 0;
	
	if (-1 == (msgid = msgget(KEY_VALUE, IPC_CREAT | 0666)))
		goto_index(0);

	printf("Content-type: text/html; charset=utf-8\n\n");
	printf("\n\n");
	printf("请稍后... </br>");
	lenstr = atoi(getenv("CONTENT_LENGTH"));
	info = (char *)malloc( lenstr + 1);
	fread(info, 1, lenstr, stdin);
	sscanf(info, "info=%s", info_str);
	free(info);

	msgbuf.mtype = MSG_TYPE;
	strcpy(msgbuf.minfo, info_str);

	if (-1 == (msgsnd(msgid, &msgbuf, sizeof(msgbuf_st) - sizeof(long), 0)))
		goto_index(0);

	printf("发送内容为: %s.<br><br>", info_str); 
	goto_index(1000);
	return 0;
}

void goto_index(int delay)
{
	char *local_addr = NULL;
	char dest[256] = {0};
	local_addr = get_local_addr();
	sprintf(dest, REDIRECT_INDEX, local_addr, delay);
	printf("%s", dest);
}
