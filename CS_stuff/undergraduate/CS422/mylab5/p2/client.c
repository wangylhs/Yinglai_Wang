#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"ws2_32.lib")

#define BLOCK 4096


void main(int argc, char** argv){
	if (argc != 5)
	{
		printf("usage: <IP address> <Port number> <file-path> <filename>\n");
		exit(1);
	}

	WSADATA wsaData;                 /* Structure for WinSock setup communication */
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}

	//variables used to build connection with server
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	char recbuf[BLOCK];
	memset(recbuf, 0, BLOCK);
	int port = atoi(argv[2]);
	const char* invalid = "INVALID REQUEST";
	const char* end = "END ACK";
	LPVOID lpMsgBuf;
	//create connection
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
	servaddr.sin_port = htons(port);
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	//send file path to server
	n = send(sockfd, argv[3], strlen(argv[3]), 0);
	//program exit if error on write
	if (n<0){
		perror("error reading from socket");
		exit(1);
	}
	//start receiving if send succeed
	if (n == strlen(argv[3])){
		//prepare to download file
		//int outfd = open(argv[4], O_WRONLY | O_CREAT, 0644);    //create file
		HANDLE outfd = CreateFile(argv[4], FILE_WRITE_DATA, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		int a;
		//write received message into file
		while ((n = recv(sockfd, recbuf, BLOCK, 0))>0){
			if (strcmp(recbuf, invalid) == 0){
				printf("%s\n", invalid);
				exit(0);
			}
			else if (strncmp(recbuf, end, strlen(end)) == 0){
				printf("file download completed.\n");
				exit(0);
			}
			else{
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR)&lpMsgBuf,
					0,
					NULL);
				n = WriteFile(outfd, &recbuf, sizeof recbuf, &a, NULL);
			}
			memset(recbuf, 0, BLOCK);
		}
		CloseHandle(outfd);

		closesocket(sockfd);
		//clean up winsock
		WSACleanup();
		exit(0);
	}

}