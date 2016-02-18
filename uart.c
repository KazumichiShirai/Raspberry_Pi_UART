/*
 * Functions to use UART
 */
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "./uart.h"
 
//Raspberry Pi Port Setting
#define SERIAL_PORT "/dev/ttyAMA0" 
#define BAUDRATE B19200

//Size to read UART buffer
#define READ_MAX_SIZE (255)
static struct termios oldtio; //save original termios setting

int initializeUART(int *fd)
{
     /* fd : File descriptor */
     struct termios newtio;
         
     if(!(*fd = open(SERIAL_PORT, O_RDWR))){ //Open device
       fprintf(stderr, "Can't open UART device\n");
       return -1;
     }
     ioctl(*fd, TCGETS, &oldtio);       /* Save current serial setting in oldtio*/
 
     bzero(&newtio, sizeof(newtio));
     newtio = oldtio;                  /* Copy current serial setting */

     newtio.c_cflag = (BAUDRATE | CS8 | CLOCAL | CREAD | CSTOPB);
     newtio.c_iflag = (IGNPAR); //Ignore frame error and parity error
     newtio.c_oflag = 0;
     newtio.c_lflag = 0; /* Disable canonical mode */
 
     ioctl(*fd, TCSETS, &newtio);       /* Set new serial setting */

     return 1;
}

void closeUART(int fd)
{
     ioctl(fd, TCSETS, &oldtio);       //Recovery serial setting
     close(fd);
}

int recvDataUART(int fd, char recv_buf[], int buf_size)
{
     int size;
     char tmp_recv_buf[READ_MAX_SIZE];
     int i;

     size = read(fd, tmp_recv_buf, READ_MAX_SIZE);
     if(size < 0){
       fprintf(stderr, "Return value from read()is error, %s, %d\n",__FILE__, __LINE__);
       return -1;
     }

     if(size > buf_size){
       fprintf(stderr, "Data size is larger than buf_size, %s, %d\n",__FILE__, __LINE__);
       return -1;
     }

     for(i=0;i<size;i++){
       recv_buf[i] = tmp_recv_buf[i];
     }

     return size;
}
