/*
 * Functions to use UART
 */
int initializeUART(int *fd);
void closeUART(int fd);
int recvDataUART(int fd, char recv_buf[], int buf_size);
