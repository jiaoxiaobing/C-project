/*
 * findstring.c
 *
 *  Created on: 2017-11-15
 *      Author: jWX451217
 */
#include <stdio.h>
 #include <sys/types.h>
 #include <regex.h>
#include <string.h>
 #include <dirent.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/stat.h>

int main()
{

	char ch;
	int k=0,z=0;
	char fread[1024]="",bigbg[1024]="",bigbg1[1024]="";

	int status,i;
	int cflags =REG_EXTENDED;
    regmatch_t pmatch[1024];
    char  nmatch[1024];
    regex_t reg;
    const char *patten ="[<div id=""user-content-markdown_content]+.+NA";
    FILE *pfwrite = fopen("D:/Cadence/http.txt","w+");
    FILE *pfread = fopen("D:/Cadence/sss.txt","r+");

    const char *ptr = pfread;
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
       fputs(bigbg,pfwrite);
        fputs(" ",pfwrite);
    	ptr = ptr+pmatch[0].rm_so+len;
     }
    }
    fclose(pfwrite);
    sleep(10);
    regfree(&reg);
    return 0;


}
