#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define SINGLENUM 10
struct restore
{
	int a[3];

}x,y;

void GetDir()
{
    int count;
struct stat statbuf;
if (!S_ISDIR(statbuf->st_mode))
       {

       }

}













struct restore serachdir ( char* path)
{
	  int count=0,lenth=0;
	 char txtname[128];
	FILE *fp, *fp1;
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
    if((fp1 = fopen("D:/testing/testing1.txt","w+")) == NULL)
    {
            printf("this is kong");


    }
   while((dirp = readdir(dp)) != NULL)
   {

         // if(dirp->d_type)

	     int size = strlen(dirp->d_name);
      if(strcmp((dirp ->d_name + (size-4)), ".mp3") != 0)  /*关键是这句:dirp->d_name + (size - 4) dirp->d_name是一个字符指针,假如现在有 "abc.mp3",dirp->d_name则指向'a',dirp->d_name+1指向'b'...,那么此时size=strlen("abc.mp3")=7,dirp->d_name+(7-4)=dirp->d_name+3,dirp->d_name+3指向'.',此时dirp->d_name+3指向字符串".mp3".然后就去跟常量字符串".mp3"比较,如果不相同就执行下一次循环*/
            continue;
    /*  if((++count) > SINGLENUM )
      {
    	  fclose(fp);
    	  sprintf(txtname, "D:/testing/testing1.txt");
    	  if((fp =fopen(txtname,"w+")) == NULL)
    	  {
              printf("this ti ff");
    	  }

    	  count =1;
      }  */

      fputs(path,fp);
      fputs("D:/Cadence/test/",fp1);
      fputs(dirp->d_name,fp);
      fputs(dirp->d_name,fp1);
      fputs("  ",fp);
      fputs("  ",fp1);
      lenth += strlen(dirp->d_name) ;
      count ++;
   }
   fclose(fp);
   fclose(fp1);
   closedir(dp);
   int stringlenth = lenth+count;
   x.a[0]=count;
   x.a[1]=stringlenth;

   return x;

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
  void ReaddirAndCopy(char *path1, char *path2, int count)  //path1读取目录，path2为写入目录，count为读取文件数目；
  {
	     int i = 0 ,j;

	 	char fileread[40]= " ";
	 	char filewrite[40]= " ";
	  FILE *pfread ,*pfread1;
	  pfread = fopen(path1,"r");
	  pfread1 = fopen(path2,"r");
	  for(j=0;j<count;j++){
	  char ch="",ch1="";
	     i=0;
	 	while(ch != ' ')  //判断一个地址结束的标志空格
	 	{

	 	   ch=fgetc(pfread);
	        if (ch != ' ')
	        {

	     	   fileread[i]=ch;   //读到的地址不能有空格
	     	   	        i++;
	        }

	 	       // fputs(fileread,stderr);
	 	}
	 	fseek(pfread,1,SEEK_CUR);  //偏移流文件指针位置到下一个文件名
	 	 i=0;
	 		while(ch1 != ' ')
	 		{

	 		   ch1=fgetc(pfread1);
	 		   if (ch1 != ' ')
	 		        {

	 		        filewrite[i]=ch1;

	 		        i++;
	 		        }


	 		       // fputs(fileread,stderr);
	 		}
	 		 fseek(pfread1,1,SEEK_CUR);
	        fputs(fileread,stderr);
	        fputs(filewrite,stderr);
	 		CopyFile(fileread,filewrite);

	  }
	  sleep(100);
	 	fclose(pfread);
		fclose(pfread1);
     //   fputs(fileread,stderr);
      //  fputs(filewrite,stderr);
        // sleep(100);

  }


int main(void)
 {
    int count ;
  char a[20];
  char path1[40]="D:/testing/testing.txt";
  char path2[40]="D:/testing/testing1.txt";
  char path[20] = "D:/Cadence/aa/";
  struct restore y=serachdir (path);
  //收索目录
	printf("%d\n",y.a[0]);  //a[0]得到字符串中空格数目count
	printf("%d\n",y.a[1]);   //a[1]得到字符串长度stringlenth
   count=y.a[0];
	//fputs(a,stderr);
	//sleep(100);
		//fclose(pfread);

	ReaddirAndCopy(path1,path2,count);

	//fclose(pfread);



	//printf("%s",ret);

   /* printf("input the readfile");
    scanf("%s",fileread);
    printf("intput the writefile");
    scanf("%s",filewrite);*/
  // CopyFile(fileread,filewrite);


}














