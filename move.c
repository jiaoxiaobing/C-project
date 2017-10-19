#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SINGLENUM 10
void serachdir ( char* path)
{
	 unsigned int count=0;
	 char txtname[128];
	FILE *fp;
	DIR *dp;
    struct dirent *dirp;
    if((dp = opendir(path)) == NULL)
    {
    	  perror("DP");
    }
    if((fp = fopen("D:/testing/testing.txt","w+")) == NULL)
    {
            printf("this is kong");


    }
   while((dirp = readdir(dp)) != NULL)
   {
	     int size = strlen(dirp->d_name);
      if(strcmp((dirp ->d_name + (size-4)), ".mp3") != 0)  /*关键是这句:dirp->d_name + (size - 4) dirp->d_name是一个字符指针,假如现在有 "abc.mp3",dirp->d_name则指向'a',dirp->d_name+1指向'b'...,那么此时size=strlen("abc.mp3")=7,dirp->d_name+(7-4)=dirp->d_name+3,dirp->d_name+3指向'.',此时dirp->d_name+3指向字符串".mp3".然后就去跟常量字符串".mp3"比较,如果不相同就执行下一次循环*/
            continue;
      if((++count) > SINGLENUM )
      {
    	  fclose(fp);
    	  sprintf(txtname, "D:/testing/testing1.txt");
    	  if((fp =fopen(txtname,"w+")) == NULL)
    	  {
              printf("this ti ff");
    	  }

    	  count =1;
      }
      fputs(path,fp);
      fputs(dirp->d_name,fp);
      fputs("  ",fp);

   }
   fclose(fp);
   closedir(dp);

}




long CopyFile(const char* file_1, const char* file_2)
{
	FILE *pfRead = fopen(file_1,"r+");
	FILE *pfWrite = fopen(file_2,"w+");
	if (pfRead == NULL || pfWrite == NULL)
	{
	       fclose(pfRead);
	        fclose(pfWrite);
	        return -1;
	}
long bytesCount = 0;
int arrLen =1024;
char bufArr[arrLen];
int copiedLen;
int elementSize =sizeof(bufArr[0]);
do{
	copiedLen = 0;
	copiedLen = fread(bufArr,elementSize,arrLen,pfRead);
	fwrite(bufArr,elementSize,copiedLen,pfWrite);
    bytesCount +=copiedLen*elementSize;
   }while(copiedLen == arrLen);
          fclose(pfRead);
	        fclose(pfWrite);
   return bytesCount;
}

int main(void)
 {
     int i = 0 ;
     int ch;
     FILE *pfread;
	char fileread[40]= "D:/Cadence/aa/a1.mp3", filewrite[40] = "D:/Cadence/test/";
/*	char path[20] = "D:/Cadence/aa/";
	serachdir (path);
	pfread = fopen("D:/testing/testing.txt","r");
	while(ch != ' ')
	{

	   ch=fgetc(pfread);

	        fileread[i]=ch;
	        i++;
	       // fputs(fileread,stderr);
	}

	//fputs(fileread,stderr);
	//sleep(100);*/
	 CopyFile(fileread,filewrite);

		//fclose(pfread);



	//printf("%s",ret);

   /* printf("input the readfile");
    scanf("%s",fileread);
    printf("intput the writefile");
    scanf("%s",filewrite);*/
  // CopyFile(fileread,filewrite);


}

