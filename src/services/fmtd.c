#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdarg.h>
#include <syslog.h>

void respond(char *fmt,...);

int vul(void)
{
  char tmp[1024];
  char buf[1024];
  int len = 0;

  syslog(LOG_ERR, "vul() -> tmp = 0x%x buf = 0x%x\n", tmp, buf); 

  while(1) {

    memset(buf, 0, sizeof(buf));
    memset(tmp, 0, sizeof(tmp));
    if ( (len = read(0, buf, sizeof(buf))) <= 0 ) {
      syslog(LOG_ERR, "vul() -> error while reading input buf [%s] (%d)",
	     buf, len);
      exit(-1);
    } /*
	else
	syslog(LOG_INFO, "vul() -> read %d bytes", len);
      */
    if (!strncmp(buf, "quit", 4)) {
      respond("bye bye ...\n");
      return 0;
    }
    snprintf(tmp, sizeof(tmp)-1, buf);
    respond("%s", tmp);

  }
}

void respond(char *fmt,...)
{
  va_list va;
  char buf[1024];
  int len = 0;

  va_start(va,fmt);
  vsnprintf(buf,sizeof(buf),fmt,va);
  va_end(va);
  len = write(STDOUT_FILENO,buf,strlen(buf));
  /* syslog(LOG_INFO, "respond() -> write %d bytes", len); */
}


int main()
{
  struct sockaddr_in sin;
  int i,len = sizeof(struct sockaddr_in);
  char login[16];
  char passwd[1024];
  openlog("fmtd", LOG_NDELAY | LOG_PID, LOG_LOCAL0);

  /* get login */
  memset(login, 0, sizeof(login));
  respond("login: ");
  if ( (len = read(0, login, sizeof(login))) <= 0 ) {
    syslog(LOG_ERR, "login -> error while reading login [%s] (%d)",
	   login, len);
    exit(-1);
  } else
    syslog(LOG_INFO, "login -> read login [%s] (%d) bytes", login, len);

  /* get passwd */
  memset(passwd, 0, sizeof(passwd));
  respond("password: ");
  if ( (len = read(0, passwd, sizeof(passwd))) <= 0 ) {
    syslog(LOG_ERR, "passwd -> error while reading passwd [%s] (%d)",
	   passwd, len);
    exit(-1);
  } else
    syslog(LOG_INFO, "passwd -> read passwd [%x] (%d) bytes", passwd, len);

  /* let's run ... */
  vul();
  return 0;
}
