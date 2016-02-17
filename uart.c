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
