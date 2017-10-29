/*
 * mystart.c
 *
 *  Created on: 2017年10月26日
 *      Author: jiaoxiaobing
 */
	#include <stdio.h>
	#include <dirent.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/stat.h>

void cutthetext(char *path,char *path2)
{
	int z=0,j,y,i,h,st=0;
	FILE *pfread,*pfwrite;
	char s[1024],a[1024];
	if ((pfread = fopen(path,"r+")) == NULL)
	{

		printf("%s\n","the path is error");
		sleep(10);
	}

	pfwrite= fopen(path2,"w+");
	while((fgets(s,1024,pfread))!=NULL)
	{	printf("%s",s);

			  z=0;
			for(i=0;i<1024;i++)
			{
			   printf("%s\n","1111111111");
				if(s[i] == ':')
				{
				j=i;
				printf("%d\n",j);
				printf("%s\n","ewqqww");
				}
				if(s[i]== '\0')
				{
				y =i;
				printf("%d",y);
				printf("%s\n","wwwwwww");

						  break;
						   }
				/*if(s[i]== '\n')
				{
					printf("%s\n","hhhhh");
					h =i;
					break;
					}		*/

	         }
			for(i=(j+1);i<=y;i++)
			{
				a[z]= s[i];
				  z++;
			}
			printf(a);

			//fseek(pfwrite,y,SEEK_CUR);
			//getch();
			st++;
			printf("%d\n",st);

			if(st==9)
			{
			 strcpy(a," ");
			 printf("%s\n","wepirwermd122555");
			   st=0;
			}
			fputs(a,pfwrite);

 }
          fclose(pfread);
           fclose(pfwrite);

}
typedef struct{
	 char DTS[1024];
	 char ddesc[1024];
	 char people[1024];
	char fileld[1024];
	 char de[1024];
	 char linre[1024];
	 char serv[1024];
	 char anysl[1024];
}dts1;
void removeCRchar( char *p)
{
  int   i =0;
  while((*(p+i))!= '\r')
  {i++;
  }
 *(p+i) = '\0';

}


void sort(char *path)
{
	dts1 dts;
	//dts1 *d;
	char *p;
	int i,len,j;
	FILE *fread,*fwrite;
	char s[1024];
	  p=s;
	char path3[40]="D:/Cadence/test/sort.txt";
	fread = fopen(path,"r+");
	fwrite = fopen(path3,"w+");

	// fpos_t home;
	while( p !=NULL)
	{

	for(i=0;i<=7;i++)
	{
	 // fgets(s,1024,fread);
	p= fgets(s,1024,fread);
		// removeCRchar(s);
	int j=0;
	for(j=0;j<1024;j++)
	{
		if (s[j]== '\r')
		{

			s[j]='\0';
			break;
		}

	}
	/*while(s[j]!='\r')
		j++;
	s[j]='\0';*/
		 printf("%s",s);

	  switch (i) {
	    case 0 : strcpy(dts.DTS,s);   break;
	    case 1 : strcpy(dts.ddesc,s);   break;
	    case 2 : strcpy(dts.people,s);   break;
	    case 3 : strcpy(dts.fileld,s);   break;
	    case 4 : strcpy(dts.de,s);    break;
	    case 5 : strcpy(dts.linre,s);   break;
	   case 6 : strcpy(dts.serv,s);   break;
	 case 7 : strcpy(dts.anysl,s);   break;
	  }

	}

	fputs(dts.DTS,fwrite);
	fputs("     ",fwrite);
	fputs(dts.ddesc,fwrite);
	fputs("     ",fwrite);
	fputs(dts.people,fwrite);
	fputs("     ",fwrite);
	fputs(dts.fileld,fwrite);
	fputs("     ",fwrite);
	fputs(dts.de,fwrite);
	fputs("     ",fwrite);
	fputs(dts.linre,fwrite);
	fputs("  ",fwrite);
	fputs(dts.serv,fwrite);
	fputs("    ",fwrite);
	fputs(dts.anysl,fwrite);
	fputc('\r',fwrite);
	//fputs(a,fwrite);

	}

	fclose(fread);
	fclose(fwrite);

}
	void main(void)
	{
		char path[40]="D:/Cadence/test/testtext.txt" ;
		char path2[40]="D:/Cadence/test/dts.txt" ;
	   cutthetext(path,path2);
		 sort(path2);
 }











