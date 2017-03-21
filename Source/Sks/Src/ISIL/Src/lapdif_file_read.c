

#include <stdio.h>
#include <string.h>
#include <../Inc/lapd_adaptation_layer.h>
#include <../Inc/lapdif_handler.h>
#include <../Inc/lapd_trace.h>

#define MAX 96
extern struct conf_data CONF_DATA[];

int GetTEI(int ts1)
{
    struct conf_data *cfgdata;
    int i;

    for(i=0; i<MAX; i++)
    {
       cfgdata = &CONF_DATA[i];
       if(cfgdata->ts == ts1)
       {
           return cfgdata->appTei;
       }
    }
    return 0;
}

int GetTIMESLOT(int tei1, int sapi1)
{
    struct conf_data *cfgdata;
    int i;
 
    for(i=0; i<MAX; i++)
    {
       cfgdata = &CONF_DATA[i];
       if( (cfgdata->appTei == tei1) && ((cfgdata->sapi1 == sapi1) || (cfgdata->sapi2 == sapi1)) )
       {
           return cfgdata->ts;
       }
    }
    return 0;
}




#ifdef ADAX_block 

#include <stdio.h>
#include <string.h>

#define MAXLINE 80

extern int APPTEI[];
extern int LAPDTEI[];
extern int port[];
extern int SAPI1[];
extern int SAPI2[];
extern int TIMESLOT[];

int readfile()
{
    char line[MAXLINE];
    int temp=0,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0;
    char *str;
    FILE *fp;
    int i = 0;

    fp = fopen("../config/lapd.conf","r");
    if (fp)
    {
        printf("\nLAPD ADAX_block Configuration File opened successfully\n");
    }
    else
    {
        printf("Could not open the LAPD ADAX_block file\n");
        return -1;
    }
    
   while(!feof(fp))
   {
       fgets(line,sizeof(line),fp);
       if (line[0] == '#')
       {
          // This is to ignore the comments   
       }
       else
       {
           sscanf(line,"%d %d %d %d %d %d",&temp,&temp1,&temp2,&temp3,&temp4,&temp5);
           LAPDTEI[i] = temp;
           APPTEI[i] = temp1;
           SAPI1[i] = temp2;
           SAPI2[i] = temp3;
           port[i] = temp4;
           TIMESLOT[i] = temp5;
           i++;
       }
    }

    fclose(fp);
    return 0;
}

#endif // ADAX_block
