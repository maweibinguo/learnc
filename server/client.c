#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(int argc, char ** argv)
{
    assert(argc > 1);
    argv++;
    char msg[255];
    while(*argv != NULL) {
        char delemiter[] = " ";
        strcat(msg, strcat(delemiter,*argv));
        argv++;
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) {
        perror("wrong 1");
        exit(EXIT_FAILURE);
    }
     
    //配置信息
    struct sockaddr_in addr_info;
    bzero(&addr_info, sizeof(addr_info));
    addr_info.sin_family = AF_INET;
    addr_info.sin_port = htons(4433);

    struct in_addr ip_addr;
    ip_addr.s_addr = inet_addr("127.0.0.1");
    addr_info.sin_addr = ip_addr;
    int conn_result = connect(server_socket, (struct sockaddr *)&addr_info, sizeof(struct sockaddr));
    if(conn_result < 0) {
        perror("wrong two");
        exit(EXIT_FAILURE);
    }

    //发送数据
    int send_res = send(server_socket, msg, strlen(msg), 0);
    if(send_res < 0) {
        perror("wrong three");
        exit(EXIT_FAILURE);
    } else {
        printf("\n had send : %s\n", msg);
    }

    char buffer[255] = {0};
    int recv_result = recv(server_socket, buffer, 255, 0);
    if(recv_result < 0) {
        perror("wrong 5");
        exit(EXIT_FAILURE);
    } else {
        printf("\n had receive : %s \n\n", buffer);
    }

}
