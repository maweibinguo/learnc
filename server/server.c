#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
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

    //绑定@todo不能直接使用结构体么
    int bind_result = bind(server_socket, (struct sockaddr*)&addr_info, sizeof(struct sockaddr));
    if(bind_result < 0) {
        perror("wrong 2");
        exit(EXIT_FAILURE);
    }

    //监听
    int listen_result = listen(server_socket, 1);
    if(listen_result < 0) {
        perror("wrong 3");
        exit(EXIT_FAILURE);
    }

    int number = 0;
    while(1) {
        number++;
        //接收数据
        struct sockaddr_in remote_com;
        int length = sizeof(struct sockaddr);
        int client_socket = accept(server_socket, (struct sockaddr *)&remote_com, &length);
        if(client_socket < 0) {
            perror("wrong 4");
            exit(EXIT_FAILURE);
        }

        char buffer[255] = {'\0'};
        printf("addr : %d\n", buffer);
        int recv_result = recv(client_socket, buffer, 255, 0);
        if(recv_result < 0) {
            perror("wrong 5");
            exit(EXIT_FAILURE);
        } else {
            printf("\nhad get msg : %s\n", buffer);
        }

        //返回数据
        int send_result = send(client_socket, buffer, strlen(buffer), 0);
        if(send_result < 0) {
            perror("wrong 6");
            exit(EXIT_FAILURE);
        } else {
            printf("\nmsg %s had sent {%d}\n\n", buffer, number);
        }
    }

    close(server_socket);
}
