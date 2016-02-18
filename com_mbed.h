/*
 * Functions to communication with Mbed
 */
int initializeComMbed(int *fd);
void closeComMbed(int fd);
int recvDataMbed(int fd, char recv_buf[], int buf_size);
