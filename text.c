/*
 * testtext.c
 *
 *  Created on: 2017年10月24日
 *      Author: jiaobing
 */
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void main(void)
{
   FILE *fread;
   int i=0,z=0,j,k;
   char s[1024],a[100];
   char path[40]="D:/Cadence/test/testtext.txt";
   fread = fopen(path,"r+");
   fgets(s,1000,fread);

	   for(i=0;i<=(strlen(s)+1);i++)
	   {
		   printf("%d",s[i]);
		 if(s[i]= ':')
		 {
			 j=i;
			 printf("%s","get the j");
		 }
		 if(s[i]= '\0')
		 {
			 k=i;
			 printf("%s","get the k");
		 }

	   }

	   for(i=j;i<=k;i++)
	   {
		   a[z]=s[i];
		   z++;

	   }
	   printf(a);
	 //sleep(10);





}

