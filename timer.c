/*
 * time.c
 *
 *  Created on: 2017年10月29日
 *      Author: jiaobing
 */

#include"stdio.h"
#include"stdlib.h"
#include<windows.h>//ShellExecute函数的头文件
#include <shellapi.h>
#include<sys/time.h>

int main()
{
	 struct  timeval    tv;
	 struct  timezone   tz;
	 struct tm* ptm;
     char time_string[40];
     long milliseconds;
     /* 获得日期时间，并转化为 struct tm。 */
     while(1)
     {  gettimeofday(&tv,&tz);
     ptm = localtime (&tv.tv_sec);

     strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
     milliseconds = tv.tv_usec / 1000;
     /* 以秒为单位打印格式化后的时间日期，小数点后为毫秒。*/
     printf ("%s.%03ld\n", time_string, milliseconds);

/*     printf("tvs_sec:%d\n",tv.tv_sec);
     printf("tv_usec:%d\n",tv.tv_usec);
     printf("tz_minuteswest:%d\n",tz.tz_minuteswest);
     printf("tz_dsttime:%d\n",tz.tz_dsttime);*/
     }

	char function[]="E:/Users/jiaobing/eclipse-workspace/mystart/Debug/mystart.exe";
	int aa;
	//ShellExecute(NULL,"open",function,NULL,NULL,SW_SHOWNORMAL);
	// aa=system(function);
	//sprintf("aa = %d\n",aa);//system函数有返回值：成功返回1，失败返回0；1时，代表程序已经打开。
	printf("Please waiting for.......");

	return 1;

}
