#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define SINGLENUM 10
int serachdir ( char* path)
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
      if(strcmp((dirp ->d_name + (size-4)), ".mp3") != 0)  /*�ؼ������:dirp->d_name + (size - 4) dirp->d_name��һ���ַ�ָ��,���������� "abc.mp3",dirp->d_name��ָ��'a',dirp->d_name+1ָ��'b'...,��ô��ʱsize=strlen("abc.mp3")=7,dirp->d_name+(7-4)=dirp->d_name+3,dirp->d_name+3ָ��'.',��ʱdirp->d_name+3ָ���ַ���".mp3".Ȼ���ȥ�������ַ���".mp3"�Ƚ�,�������ͬ��ִ����һ��ѭ��*/
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
      fputs(dirp->d_name,fp);
      fputs("  ",fp);
   }
   fclose(fp);
   closedir(dp);
   return 0;

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
     long ret;
     //  FILE *pfread, *pfwrite;
	char fileread[20], filewrite[20];
	char path[20] = "d:/Cadence";
	serachdir (path);
   /* printf("input the readfile");
    scanf("%s",fileread);
    printf("intput the writefile");
    scanf("%s",filewrite);*/
  //CopyFile(fileread,filewrite);


}

