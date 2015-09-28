#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <wiringPi.h>

#define ERROR_EXIT(_errmsg_)	error(EXIT_FAILURE, errno, _errmsg_)

#define KEY_VALUE	0X01020304
#define MSG_SIZE	128
#define MSG_TYPE	1
#define GPIO0 0
#define GPIO7 7
#define GPIO8 10
#define LED0 0
#define LED1 7
#define BUZZ 10

#define UNIT_DELAY 100000
int long_delay = UNIT_DELAY * 3;
int short_delay = UNIT_DELAY * 1;

void process_msg(char *msg);

typedef struct _mesg_buff_	{
	long mtype;
	char minfo[MSG_SIZE];
}msgbuf_st;

void gpio_setup()
{
	wiringPiSetup();
	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);
	pinMode(BUZZ, OUTPUT);
	digitalWrite(LED0, HIGH);
	digitalWrite(LED1, HIGH);
	digitalWrite(BUZZ, LOW);
}

void gpio_cleanup()
{

}

int main(int argc, char **argv)
{
	int msgid;
	msgbuf_st msgbuf;

	if (-1 == (msgid = msgget(KEY_VALUE, IPC_CREAT | 0666)))
		ERROR_EXIT("msgget");

	gpio_setup();

	msgbuf.mtype = MSG_TYPE;
	while(1) {
		if (-1 == msgrcv(msgid, &msgbuf, sizeof(msgbuf_st) - sizeof(long), msgbuf.mtype, 0))
			ERROR_EXIT("msgrcv");

		printf("Recv message:%s\n", msgbuf.minfo);
		process_msg(msgbuf.minfo);
	}
	gpio_cleanup();

	return 0;
}

char *get_symbol(char ch)
{
	if (ch == 'A' || ch == 'a')
		return ".-";
	else if (ch == 'B' || ch == 'b')
		return "-...";
	else if (ch == 'C' || ch == 'c')
		return "-.-.";
	else if (ch == 'D' || ch == 'd')
		return "-..";
	else if (ch == 'E' || ch == 'e')
		return ".";
	else if (ch == 'F' || ch == 'f')
		return "..-.";
	else if (ch == 'G' || ch == 'g')
		return "--.";
	else if (ch == 'H' || ch == 'h')
		return "....";
	else if (ch == 'I' || ch == 'i')
		return "..";
	else if (ch == 'J' || ch == 'j')
		return ".---";
	else if (ch == 'K' || ch == 'k')
		return "-.-";
	else if (ch == 'L' || ch == 'l')
		return ".-..";
	else if (ch == 'M' || ch == 'm')
		return "--";
	else if (ch == 'N' || ch == 'n')
		return "-.";
	else if (ch == 'O' || ch == 'o')
		return "---";
	else if (ch == 'P' || ch == 'p')
		return ".--.";
	else if (ch == 'Q' || ch == 'q')
		return "--.-";
	else if (ch == 'R' || ch == 'r')
		return ".-.";
	else if (ch == 'S' || ch == 's')
		return "...";
	else if (ch == 'T' || ch == 't')
		return "-";
	else if (ch == 'U' || ch == 'u')
		return "..-";
	else if (ch == 'V' || ch == 'v')
		return "...-";
	else if (ch == 'W' || ch == 'w')
		return ".--";
	else if (ch == 'X' || ch == 'x')
		return "-..-";
	else if (ch == 'Y' || ch == 'y')
		return "-.--";
	else if (ch == 'Z' || ch == 'z')
		return "--..";
	else if (ch == '0')
		return "-----";
	else if (ch == ',')
		return "--..--";
	else if (ch == '1')
		return ".----";
	else if (ch == '.')
		return ".-.-.-";
	else if (ch == '2')
		return "..---";
	else if (ch == '?')
		return "..--..";
	else if (ch == '3')
		return "...--";
	else if (ch == ';')
		return "-.-.-.";
	else if (ch == '4')
		return "....-";
	else if (ch == ':')
		return "---...";
	else if (ch == '5')
		return ".....";
	else if (ch == '\'')
		return ".----.";
	else if (ch == '6')
		return "-....";
	else if (ch == '-')
		return "-....-";
	else if (ch == '7')
		return "--...";
	else if (ch == '/')
		return "-..-.";
	else if (ch == '8')
		return "---..";
	else if (ch == '(')
		return "-.--.-";
	else if (ch == '9')
		return "----.";
	else if (ch == ')')
		return "-.--.-";
	else if (ch == ' ')
		return " ";
	else if (ch == '-')
		return "..--.-";
	return " ";
}

void process_symbol(char ch)
{

    digitalWrite (BUZZ, HIGH);
    digitalWrite (LED0, LOW);
    digitalWrite (LED1, LOW);

	if (ch == '-')
		usleep(long_delay);
	else
		usleep(short_delay);

    digitalWrite (BUZZ, LOW);
    digitalWrite (LED0, HIGH);
    digitalWrite (LED1, HIGH);
}

void process_msg(char *msg)
{
	int i = 0;
	int j = 0;
	int delay = 0;
	char tmp = '\0';
	char sy = '\0';
	char *symbol = NULL;
	for(i = 0; i < strlen(msg); i++)
	{
		tmp = msg[i];
		symbol = get_symbol(tmp);
		if (tmp == ' ')
		{
			delay = 6 * UNIT_DELAY;
		}
		else
		{
			printf("%c = ", tmp);
			fflush(stdout);
			for(j = 0; j < strlen(symbol); j++)
			{
				sy = symbol[j];
				printf("%c", sy);
				fflush(stdout);
				process_symbol(sy);
				usleep(short_delay);
			}
			delay = 2 * UNIT_DELAY;
		}
		usleep(delay);
		printf("\n");
	}
}
