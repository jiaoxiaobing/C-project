/*
 * test.c
 *
 *  Created on: 2017年11月19日
 *      Author: jiaobing
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <locale.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define bzero(p, s) memset(p, 0, s)
#define USERAGENT "Wget/1.10.2"
#define ACCEPT "*/*"
#define ACCEPTLANGUAGE "zh-cn,zh;q=0.5"
#define ACCEPTENCODING "gzip,deflate"
#define ACCEPTCHARSET "gb2312,utf-8;q=0.7,*;q=0.7"
#define KEEPALIVE "300"
#define CONNECTION "keep-alive"
#define CONTENTTYPE "application/x-www-form-urlencoded"

#define MAXFILENAME 14
#define DEBUG 1

typedef struct webnode
{
	char * host;                 /* 网页所在的主机 */
	int    port;                 /* 网络服务器所使用的端口 */
	char *  dir;                 /* 网页所在的目录 */
	char * page;                 /* 网页文件名 */
	char * file;                 /* 本地保存的文件名 */
	char IsHandled;              /* 是否处理过 */
	struct webnode * brother;    /* 兄弟节点链表指针 */
	struct webnode * child;      /* 子节点链表指针 */
} WEBNODE;


struct sockaddr_in  server_addr;
int sockfd = 0, dsend = 0, totalsend = 0, nbytes = 0, reqn = 0, i = 0, j = 0, ret = 0;
struct hostent *host;
char request[409600] = "", buffer[1024] = "", httpheader[1024] = "";
int FileNumber = 0;
char e[2] = "@/";
WEBNODE * NodeHeader, * NodeTail, * NodeCurr;
char * mapped_mem;
WEBNODE * NewNode;
int GetLocalAgent(char * UserAgent, char * Accept, char * AcceptLanguage, char * AcceptEncoding, char * AcceptCharset, char * KeepAlive, char * Connection, char * ContentType);
void HandleInitNode(WEBNODE * node);
void HandOneNode(WEBNODE * node);
void DoOnce();
void DoneWithList(int flag);
void ConnectWeb(void);
void SendRequest(void);
void ReceiveResponse(void);



/**************************************************************
功能：设置 HTTP 协议头内容的一些固定值
***************************************************************/
int GetLocalAgent(char * UserAgent, char * Accept, char * AcceptLanguage, char * AcceptEncoding, char * AcceptCharset, char * KeepAlive, char * Connection, char * ContentType)
{
	memcpy(UserAgent, USERAGENT, strlen(USERAGENT));
	memcpy(Accept, ACCEPT, strlen(ACCEPT));
	memcpy(AcceptLanguage, ACCEPTLANGUAGE, strlen(ACCEPTLANGUAGE));
	memcpy(AcceptEncoding, ACCEPTENCODING, strlen(ACCEPTENCODING));
	memcpy(AcceptCharset, ACCEPTCHARSET, strlen(ACCEPTCHARSET));
	memcpy(KeepAlive, KEEPALIVE, strlen(KEEPALIVE));
	memcpy(Connection, CONNECTION, strlen(CONNECTION));
	memcpy(ContentType, CONTENTTYPE, strlen(CONTENTTYPE));
	return 0;
}

void HandleInitNode(WEBNODE * node)
{
	WEBNODE * CurrentNode = 0;
	CurrentNode = node->brother;
	if(CurrentNode)
	{
		while(CurrentNode)
		{
			if(CurrentNode->IsHandled == 0)
			{
				HandOneNode(CurrentNode);
				if(DEBUG)
				{
					fprintf(stdout, "\nDisplay.%5d:", FileNumber);
				//	DisplayNode(CurrentNode); /* display every node */
				}
			}
			CurrentNode = CurrentNode->brother;
		}// while
	}
}

void HandOneNode(WEBNODE * node)
{
	char UserAgent[1024] = "",
		Accept[1024] = "",
		AcceptLanguage[1024] = "",
		AcceptEncoding[1024] = "",
		AcceptCharset[1024] = "",
		KeepAlive[1024] = "",
		Connection[1024] = "",
		ContentType[1024] = "";

	NodeCurr = node;
	if((host=gethostbyname(NodeCurr->host))==NULL) /* get ip address by domain */
	{
		if(DEBUG)  fprintf(stderr,"\tGethostname '%s' error, %s\n", NodeCurr->host, strerror(errno));
		exit(1);
	}
	GetLocalAgent(UserAgent, Accept, AcceptLanguage, AcceptEncoding, AcceptCharset, KeepAlive, Connection, ContentType); /* Get client browser information */

	if(strcmp(NodeCurr->dir, "/"))
		sprintf(request, "GET /%s/%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nAccept: %s\r\nConnection: %s\r\n\r\n", NodeCurr->dir, strcmp(NodeCurr->page, "@")?NodeCurr->page:"", NodeCurr->host, UserAgent, Accept, Connection);
	else
		sprintf(request, "GET %s%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\nAccept: %s\r\nConnection: %s\r\n\r\n", NodeCurr->dir, strcmp(NodeCurr->page, "@")?NodeCurr->page:"", NodeCurr->host, UserAgent, Accept, Connection);

	DoneWithList(1);
}

void DoneWithList(int flag)
{
	if(flag) fprintf(stdout, "\tRequest.%d is:\n%s", ++reqn, request);

	DoOnce();

	if(flag) fprintf(stdout, "\n\tThe following is the response header:\n%s", httpheader);
}

void DoOnce()
{
	/* send and receive */
	ConnectWeb(); /* connect to the web server */

	/* send a request */
	SendRequest();

	/* receive a response message from web server */
	ReceiveResponse();

	close(sockfd); /* because HTTP protocol do something one connection, so I can close it after receiving */
}

void ConnectWeb(void)
{
	/* connect to web server */
  	/* create a socket descriptor */
	if((sockfd=socket(PF_INET,SOCK_STREAM,0))==-1)
	{
		fprintf(stderr,"\tSocket Error:%s\a\n",strerror(errno));
		exit(1);
	}

	/* bind address */
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(NodeCurr->port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);

	/* connect to the server */
	if(connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "\tConnect Error:%s\a\n", strerror(errno));
		exit(1);
	}
}

void SendRequest(void)
{
	/* send my http-request to web server */
	dsend = 0;totalsend = 0;
	nbytes=strlen(request);
	while(totalsend < nbytes)
	{
		dsend = write(sockfd, request + totalsend, nbytes - totalsend);
		if(dsend==-1)  {fprintf(stderr, "\tsend error!%s\n", strerror(errno));exit(0);}
		totalsend+=dsend;
		fprintf(stdout, "\n\tRequest.%d %d bytes send OK!\n", reqn, totalsend);
	}
}

void ReceiveResponse(void)
{
	/* get response from web server */
	fd_set writefds;
	struct timeval tival;
	int retry = 0;
	FILE * localfp = NULL;

	i=0; j = 0;
	__ReCeive:
	FD_ZERO(&writefds);
	tival.tv_sec = 10;
	tival.tv_usec = 0;
	if(sockfd > 0) FD_SET(sockfd, &writefds);
	else {fprintf(stderr, "\n\tError, socket is negative!\n"); exit(0);}

	ret = select(sockfd + 1,&writefds, NULL, NULL, &tival);
	if(ret ==0 )
	{
		if(retry++ < 10) goto __ReCeive;
	}
	if(ret <= 0) {fprintf(stderr, "\n\tError while receiving!\n"); exit(0);}

	if(FD_ISSET(sockfd, &writefds))
	{
		memset(buffer, 0, 1024);
		memset(httpheader, 0, 1024);
		if((localfp = fopen(NodeCurr->file, "w")) == NULL) {if(DEBUG) fprintf(stderr, "create file '%s' error\n", NodeCurr->file); return;}
		/* receive data from web server */
		while((nbytes=read(sockfd,buffer,1))==1)
		{
			if(i < 4)
			{
				/* 获取 HTTP 消息头 */
					if(buffer[0] == '\r' || buffer[0] == '\n')  i++;
					else i = 0;
			 		memcpy(httpheader + j, buffer, 1); j++;
			}
			else
			{
				/* 获取 HTTP 消息体 */
					fprintf(localfp, "%c", buffer[0]); /* print content on the screen */
					i++;
			}//else
		}//while
		fclose(localfp);
	}//if(FD_ISSET(sockfd, &writefds))
}



/**************************************************************
功能：从字符串 src 中分析出网站地址和端口，并得到文件和目录
***************************************************************/
void GetMemory(char ** myanchor, int len)
{
	if(!(*myanchor))
		(*myanchor) = (char *)malloc(len + 1);
	else
		(*myanchor) = (char *)realloc((void *)(*myanchor), len + 1);
	memset((*myanchor), 0, len + 1);
}

/**************************************************************
功能：在字符串 s 里搜索 x 字符，并设置指针 d 指向该位置
***************************************************************/
void Rstrchr(char * s, int x, char ** d)
{
	int len = strlen(s) - 1;
	while(len >= 0)
	{
		if(x == s[len]) {(*d) = s + len; return;}
		len--;
	}
	(*d) = 0;
}

int GetHost(char *src, char ** web, char ** file, int * port, char ** dir)
{
	char * pA, * pB, * pC;
	int len;

	*port = 0;
	if(!(*src))
	{
		return -1;
	}
	pA = src;
	printf("%s\n",src);
	if(!strncmp(pA, "http://", strlen("http://")))  pA = src+strlen("http://");
	else
		{printf("%s\n",pA);
	printf("%s","3232r434r");
		return 1; }
	pB = strchr(pA, '/');
	if(pB)
	{
		len = strlen(pA) - strlen(pB);
		GetMemory(web, len);
		memcpy((*web), pA, len);
		if(*(pB+1))
		{
			Rstrchr(pB + 1, '/', &pC);
			if(pC) len = strlen(pB + 1) - strlen(pC);
			else len = 0;
			if(len > 0)
			{
				GetMemory(dir, len);
				memcpy((*dir), pB + 1, len);

				if(pC + 1)
				{
					len = strlen(pC + 1);
					GetMemory(file, len);
					memcpy((*file), pC + 1, len);
				}
				else
				{
					len = 1;
					GetMemory(file, len);
					memcpy((*file), e, len);
				}// else
			}// if(len > 0)
			else
			{
				len = 1;
				GetMemory(dir, len);
				memcpy((*dir), e + 1, len);

				len = strlen(pB + 1);
				GetMemory(file, len);
				memcpy((*file), pB + 1, len);
			}// else
		}// if(*(pB+1))
		else
		{
			len = 1;
			GetMemory(dir, len);
			memcpy((*dir), e + 1, len);

			len = 1;
			GetMemory(file, len);
			memcpy((*file), e, len);
		}// else
	}// if(pB)
	else
	{
		len = strlen(pA);
		GetMemory(web, len);
		memcpy((*web), pA, strlen(pA));
		len = 1;
		GetMemory(dir, len);
		memcpy((*dir), e + 1, len);
		len = 1;
		GetMemory(file, len);
		memcpy((*file), e, len);
	}// else

	pA = strchr((*web), ':');
	if(pA)  *port = atoi(pA + 1);
	else *port = 80;

	return 0;
}
/**************************************************************
功能：处理单个节点信息
*********************************************************/
void AddInitNode(char * Host, char * Page, int Port, char * Dir)
{

	char filename[ MAXFILENAME + 1] = "";

	if(NodeHeader == NULL) {
	   NodeHeader = (WEBNODE *)malloc(sizeof(WEBNODE));
	   NodeHeader -> brother = NULL;
	   NodeTail = NodeHeader;
	printf("jiaobing111");
	}
	//else NodeTail->brother = NewNode = (WEBNODE *)malloc(sizeof(WEBNODE));
	NewNode = (WEBNODE *)malloc(sizeof(WEBNODE));
	memset(NewNode, 0, sizeof(WEBNODE));
	NewNode->host = (char *)malloc(strlen(Host) + 1);  //这里的NewNode->host是指向host这个指针的地址
	memset(NewNode->host, 0, strlen(Host) + 1);
	NewNode->page = (char *)malloc(strlen(Page) + 1);
	memset(NewNode->page, 0, strlen(Page) + 1);
	NewNode->dir = (char *)malloc(strlen(Dir) + 1);
	memset(NewNode->dir, 0, strlen(Dir) + 1);
	NewNode->file = (char *)malloc(MAXFILENAME + 1);
	memset(NewNode->file, 0, MAXFILENAME + 1);
	strcpy(NewNode->host, Host);
	strcpy(NewNode->page, Page);
	strcpy(NewNode->dir, Dir);
	sprintf(filename, "file%05d.html", FileNumber++);
	strcpy(NewNode->file, filename);
	NewNode->port = Port;
	NewNode->IsHandled = 0;
	NewNode->brother = 0;
	NewNode->child = 0;
	NodeTail->brother = NewNode;
	NodeTail = NewNode;
	NodeTail->brother = NULL;
}
/**************************************************************
功能：显示年有节点信息
***************************************************************/
void DisplayNode(WEBNODE * NodeHeader)
{
	WEBNODE * TempNode;
	TempNode = NodeHeader->brother;
	printf("\n");
	while(TempNode)
	{
		if(!strcmp(TempNode->dir, "/"))
		printf("\t%s:%d%s%s => %s %d\n", TempNode->host, TempNode->port, TempNode->dir, strcmp(TempNode->page, "@")?TempNode->page:"", TempNode->file, TempNode->IsHandled);
		else
			printf("\t%s:%d/%s/%s => %s %d\n", TempNode->host, TempNode->port, TempNode->dir, strcmp(TempNode->page, "@")?TempNode->page:"", TempNode->file, TempNode->IsHandled);
		TempNode = TempNode->brother;
	}// while

	/*TempNode = NodeHeader;
	while(TempNode)
	{
		if(TempNode->child)
			DisplayNode(TempNode->child);
		TempNode = TempNode->brother;
	}// while
*/
}


int main( )
{
	char **agrv =NULL;
	 agrv = (char **)malloc(100);
	 agrv[1]= "http://ask.csdn.net/questions/205116";
	 agrv[2]= "http://blog.csdn.net/angelo_yz/article/details/4083379";
	 printf("%s\n",agrv[1]);
	int WebPort;
	char * WebHost = 0, * PageAddress = 0, * WebDir = 0;

	//if(argc < 2) {if(DEBUG) printf( "Command error, you should input like this:\n\t%s WebPageAddress1 WebPageAddress2 WebPageAddress3 ...", argv[0]); exit(0);}

	NodeHeader = NodeTail = NodeCurr = 0;

	for(i = 1; i < 3; i++)
	{
		ret = GetHost(agrv[i], &WebHost, &PageAddress, &WebPort, &WebDir); /* Get web page info */
		if(ret) {if(DEBUG)  printf("GetHost error from %s\n", agrv[i]) ; exit(0);}
		AddInitNode(WebHost, PageAddress, WebPort, WebDir); /* add this page to chain */
	}
	free(WebHost); free(PageAddress);free(WebDir);free(agrv);
	if(DEBUG)
	{
		printf("\nDisplay.%5d:", FileNumber);
		DisplayNode(NodeHeader); /* display every node */
	}
	HandleInitNode(NodeHeader);
	 sleep(10);
	return 0;
}


















