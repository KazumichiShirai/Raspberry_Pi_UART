/*
 * Functions to communcate with mbed via UART
 * author : Kazumichi Shirai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include "./uart.h"

int initializeComMbed(int *fd)
{
     if(initializeUART(fd) < 0){
	  fprintf(stderr, "Can't initizalize UART to communicate with mbed\n");
	  return -1;
     }
     
     return 1;
}

void closeComMbed(int fd)
{
     closeUART(fd);
     close(fd);
}

int recvDataMbed(int fd, char recv_buf[], int buf_size)
{
    return recvDataUART(fd, recv_buf, buf_size);
}

