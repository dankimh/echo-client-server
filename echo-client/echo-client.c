#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 1024 //max input buffer size

void * send_msg(void * arg); //send message to server(for sender)
void * recv_msg(void * arg); //receive message from server(for receiver)
void usage();
//void error_handling(char *msg);

char msg[BUF_SIZE]; //message buffer
int main(int argc, char *argv[])
{
//client socket descriptor and server address structure
    int sock;
    struct sockaddr_in serv_addr;

//thread id for sender&receiver and thread return value(pthread_join)
    pthread_t snd_thread, rcv_thread;

    int str_len,ch=0;

    //argv error handling
    if (argc != 3) {
        usage();
        exit(1);
    }

    //IPv4, TCP socket create
    sock = socket(PF_INET, SOCK_STREAM,0);

    //server address information initialization
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    //connect request
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
    pthread_detach(rcv_thread);

    while(1){
        fgets(msg, BUF_SIZE, stdin);
        int len=write(sock, msg, strlen(msg));
        if(len == 0 || len == -1){
            fprintf(stderr, "sending error\n");
            break;
        }
    }

    //client socket connection close
    close(sock);
    return 0;
}

void usage(){
    printf("syntax : echo-client <ip> <port>\nample : echo-client 192.168.10.2 1234\n");
    return;
}

void* recv_msg(void* arg){

    //client's file descriptor
    int sock = *((int*)arg);
    char name_msg[BUF_SIZE];
    int str_len;

    while (1) {

    //read buffer from server
        str_len = read(sock, name_msg ,BUF_SIZE-1);
        if(str_len == -1 || str_len == 0){
            fprintf(stderr, "failed to recv\n");
            break;
        }
        //if message sent from server
        name_msg[str_len] = '\0';
        fputs(name_msg, stdout);
    }

    //socket close
    close(sock);
    return NULL;
}

//error handling
/*void error_handling(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}*/
