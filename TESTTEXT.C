	#include <stdio.h>
	#include <dirent.h>
	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/stat.h>

void cutthetext(char *path,char *path2)
{
	int z=0,j,y,i,h,st=0;
	FILE *pfread,*pfwrite;;
	char s[1024],a[1024];
	pfread = fopen(path,"r+");
	pfwrite= fopen(path2,"w+");
	while((fgets(s,1024,pfread))!=NULL)
	{	printf("%s",s);
			  z=0;
			for(i=0;i<150;i++)
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
			 memset(a,0,1024);
			 printf("%s\n","wepirwermd122555");
			   st=0;
			}
			fputs(a,pfwrite);

 }
          fclose(pfread);
           fclose(pfwrite);

}
typedef struct DTSCOUNT
{
	 char DTS[20];
	 char ddesc[200];
	 char people[30];
	char fileld[15];
	 char de[20];
	 int linre;
	 char serv[4];
	 char anysl[200];
}dts1;
void sort(char *path)
{
	
	dts1 *d;
	int i;
	FILE *fread,*fwrite;
	char s[1024];
	char path3[40]="D:/Cadence/test/sort.txt";
	fread = fopen(path,"r+");
	fwrite = fopen(path3,"w+");
	for(i=0;i<=7;i++)
	{
	  fgets(s,1024,fread);
	  switch (i) {
	    case 0 : strcpy(,s);   break;
	    case 1 : strcpy(d->ddesc,s);   break;
	    case 2 : strcpy(d->people,s);   break;
	    case 3 : strcpy(d->fileld,s);   break;
	    case 4 : strcpy(d->de,s);   break;
	    case 5 : strcpy(d->linre,s);   break;
	    case 6 : strcpy(d->serv,s);   break;
	    case 7 : strcpy(d->anysl,s);   break;
	     }

	}
	fputs(d->DTS,fwrite);
	fputs("   ",fwrite);
	fputs(d->ddesc,fwrite);
	close(fread);
	close(fwrite);

}
	void main(void)
	{
		char path[40]="D:/Cadence/test/dtstest.txt" ;
		char path2[40]="D:/Cadence/test/dts.txt" ;
		//cutthetext(path,path2);
		sort(path2);
 }









