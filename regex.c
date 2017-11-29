/*
 * GetDir.c
 *
 *  Created on: 2017年11月29日
 *      Author: jiaobing
 */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
char path[20]="D:/Cadence/aa";

void regexpress(char *pathread)
{

	char ch;
	int k=0,z=0;
     char bigbg[1024]="";
    char *fread;
    fread = (char *)malloc(102400);
	int status,i;
	int cflags =REG_EXTENDED;
    regmatch_t pmatch[1024];
    char  nmatch[1024];
    regex_t reg;
    const char *patten ="markdown-body+.+br";
    FILE *pfwrite = fopen("D:/Cadence/http.txt","a");
    FILE *pfread = fopen(pathread,"r+");
    while (ch!=EOF)
    {
        ch=fgetc(pfread);
    	fread[k]=ch;
    	k++;
    }
    fclose(pfread);
    const char *ptr = fread;
    regcomp(&reg,patten,cflags);
    while(strlen(ptr)>0)
    {
    	memset(pmatch,0,sizeof(pmatch));
    status = regexec(&reg,ptr,(size_t)1024,pmatch,0);
    if(status == REG_NOMATCH)
    	{
    	printf("no Match\n");
    	    break;
    	}
    else if(status == 0)
    {
    	printf("Match:\n");
        int len =pmatch[0].rm_eo-pmatch[0].rm_so;
    	memcpy(bigbg,ptr+pmatch[0].rm_so,len);
    	bigbg[len]='\0';
        printf("%s\n",bigbg);
        //fseek(pfwrite,0,SEEK_END);
        fputs(bigbg,pfwrite);
        fputs(" \n",pfwrite);
    	ptr = ptr+pmatch[0].rm_so+len;
     }
    }
    fclose(pfwrite);
    sleep(10);
    regfree(&reg);
    free(fread);
    //return 0;

}

int main()
{
	DIR *dp;
	char **ptr = NULL;
	ptr = (char **)malloc(100);
    char *fullname;
    fullname = (char *)malloc(100);
	int k=0,i=0;
	struct stat st;
    struct  dirent *dirp;
    if((dp = opendir(path)) == NULL)
    {
    	perror("DP");
    }
   while((dirp = readdir(dp)) != NULL)
   {
	   if(!strcmp(dirp->d_name,".") || ! strcmp(dirp->d_name,".."))  //为防止陷入死循环，必须判断返回目录
	   {
	    continue;
	   }
	  // printf("%s\n",dirp->d_name);
	   sprintf(fullname,"%s/%s",path,dirp->d_name);
	   ptr[k] =fullname ;
	   fullname = (char *)malloc(100);

	   k++;
   }
  for(i=0;i<=k;i++)
 {
    regexpress(ptr[i]);
   // k--;
   }
}


