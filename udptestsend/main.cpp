//
//  main.cpp
//  udptestsend
//
//  Created by junpengzhang on 12/5/16.
//  Copyright © 2016 junpengzhang. All rights reserved.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>

#define GET_MAX 1024

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int sock;
    const char* mess = "Hello Server!";
    char get_mess[GET_MAX]; /* 后续版本使用 */
    struct sockaddr_in recv_host;
    socklen_t addr_len;
    /* 创建套接字 */
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    /* 绑定 */
    memset(&recv_host, 0, sizeof(recv_host));
    recv_host.sin_family = AF_INET;
    recv_host.sin_addr.s_addr = inet_addr("127.0.0.1");
    recv_host.sin_port = htons(6000);
    /* 发送信息 */
    /* 在此处，发送端的IP地址和端口号等各类信息，随着这个函数的调用，自动绑定在了套接字上 */
#if 0
    sendto(sock, mess, strlen(mess), 0, (struct sockaddr *)&recv_host, sizeof(recv_host));
#else//常时间连接
    /* 前方高度一致，将 bind函数替换为 */
    connect(sock, (struct sockaddr *)&recv_host, sizeof(recv_host));
    // 将对方的 IP地址和 端口号信息 注册进UDP的套接字中)
    while(1) /* 循环的发送和接收信息 */
    {
        size_t read_len = 0;
        /* 原先使用的 sendto 函数，先择改为使用 write 函数， Windows平台为 send 函数 */
        write(sock, mess, strlen(mess));      /* send(sock, mess, strlen(mess), 0) FOR Windows Platform */
        read_len = read(sock, get_mess, GET_MAX-1); /* recv(sock, mess, strlen(mess)-1, 0) FOR Windows Platform */
        get_mess[read_len-1] = '\0';
        printf("In Client like Host Recvive From Other Host : %s\n", get_mess);
    }
    /* 后方高度一致 */
#endif
    /* 完成，关闭 */
    close(sock);
    return 0;
}
