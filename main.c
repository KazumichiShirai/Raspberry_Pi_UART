#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include "./com_mbed.h"

#define MAX_EVENTS (10)

int registerFdToEpoll(struct epoll_event *ev, int epollfd, int fd)
{
     /* register socket to epoll */
     ev->events = EPOLLIN;
     ev->data.fd = fd;
     if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, ev) == -1) {
	  fprintf(stderr, "fail epoll_ctl\n");
	  return -1;
     }
     return 1;
}

void main( void )
{
     struct epoll_event ev;
     struct epoll_event events[MAX_EVENTS];
     int epollfd, nfds;
     int mbed_fd; // file descriptor for UART to communicate with mbed
     char recv_buf[255] = {};
     int len;
     int i;

     initializeUART(&mbed_fd);
     if((epollfd = epoll_create1(0)) < 0)
     {
	  fprintf(stderr, "can't creare epoll\n");
	  return;
     }

     /* register Fd to epoll */
     registerFdToEpoll(&ev, epollfd, mbed_fd);

     while(1){
       nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
	  if (nfds == -1) {
	       fprintf(stderr, "err : epoll wait");
	       return;
	  }

	  for (i = 0; i < nfds; i++) {
               /** Receive Data From Mbed **/
	      if(events[i].data.fd == mbed_fd) {
		  len = recvDataMbed(mbed_fd, recv_buf, (sizeof (recv_buf)/sizeof(recv_buf[0])));
	      }

	  }
     }
     closeUART(mbed_fd);
}
