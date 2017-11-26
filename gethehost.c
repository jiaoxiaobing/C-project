/*
 * ftpclient.c
 *
 *  Created on: 2017年11月6日
 *      Author: jiaobing
 */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
void gethehost(char **arv,int *j);
int main()
{
  char **agrv = NULL;
  agrv = (char **)malloc(100);
  int j=0,i=0;
  gethehost(agrv,&j);
  printf("%d\n",j);

	  printf("%s\n",agrv);


sleep(10);

}

void gethehost(char **arv,int *j)
{
	 arv = (char **)malloc(100);
	char tempres[1024];
	char ch;
 FILE *pfread;
 int i=0;
 pfread= fopen("D:/Cadence/http.txt","r+");
 while(ch != '+')
 {
	  ch = fgetc(pfread);
	  if(ch!='\n')
	  {tempres[i] = ch;
	     i++;

		 }
     else
	  {
		    arv[*j]=tempres;
   	    printf("%s\n",arv[*j]);
		  memset(tempres,0,1024);
		  (*j)++;
		  i=0;
	  }

 }

}













