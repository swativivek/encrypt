#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"

#include "dev/button-sensor.h"

#include "dev/leds.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*---------------------------------------------------------------------------*/
PROCESS(example_abc_process, "ABC example");
AUTOSTART_PROCESSES(&example_abc_process);
/*---------------------------------------------------------------------------*/
static void
abc_recv(struct abc_conn *c)
{
  char *str;
  str= (char *) packetbuf_dataptr();
  printf("abc message received '%s'\n", str);
}

//static void tostring(char [], int);
//static int toint(char []);
static void tostringnum(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
 
/*static int toint(char str[])
{
    int len = strlen(str);
    int i, num = 0;
 
    for (i = 0; i < len; i++)
    {
        num = num + ((str[len - (i + 1)] - '0') * pow(10, i));
    }
 
   return num;
}*/
static void ToStringdbl(char * outStr, int length, double val)
{

    _snprintf(outStr,length,"%f",val);

}

static const struct abc_callbacks abc_call = {abc_recv};
static struct abc_conn abc;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_abc_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(abc_close(&abc);)

  PROCESS_BEGIN();

  abc_open(&abc, 128, &abc_call); 

  while(1) {

    /* Delay 2-4 seconds */
    etimer_set(&et, CLOCK_SECOND * 2 + random_rand() % (CLOCK_SECOND * 2));

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    

    int dt;
    int n;
    int g;
    int r;
    double sqn;
    sqn = n*n;
    dt=random_rand()%100;
    r=random_rand()%100;
    n=77;
    g=5652;
    double c;
    double t1= fmod(pow(g,dt),sqn);
    double t2= fmod(pow(r,n),sqn);
    c=fmod((t1*t2),sqn);
    //srand(100);
    char str[10];
    //r=random_rand()%100;
    //tostringnum(str,c);
    ToStringdbl(str,20,c);	
    packetbuf_copyfrom(str, 20);
    abc_send(&abc);
    printf("message sent %d and ciphertext %E\n",dt,c);
    //free(str);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
