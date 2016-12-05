//
//  main.cpp
//  udptest
//
//  Created by junpengzhang on 12/5/16.
//  Copyright © 2016 junpengzhang. All rights reserved.
//

#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<unistd.h>


//udp接收

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int sock; /* 套接字 */
    socklen_t addr_len; /* 发送端的地址长度，用于 recvfrom */
    char mess[15];
    //char get_mess[GET_MAX]; /* 后续版本使用 */
    struct sockaddr_in recv_host, send_host;
    
    /* 创建套接字 */
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    
    /* 把IP 和 端口号信息绑定在套接字上 */
    memset(&recv_host, 0, sizeof(recv_host));
    recv_host.sin_family = AF_INET;
    recv_host.sin_addr.s_addr = htonl(INADDR_ANY);/* 接收任意的IP */
    recv_host.sin_port = htons(6000); /* 使用6000 端口号 */
    bind(sock, (struct sockaddr *)&recv_host, sizeof(recv_host));
    
#if 0
    /* 进入接收信息的状态 */
    recvfrom(sock, mess, 15, 0, (struct sockaddr *)&send_host, &addr_len);
#else//常时间连接
    /* 前方一致， 添加额外的 struct sockaddr_in send_host; 并添加循环，构造收发的现象*/
    while(1)
    {
        size_t read_len = 0;
        char sent_mess[15] = "Hello Sender!"; /* 用于发送的信息 */
        sendto(sock, mess, strlen(sent_mess), 0, (struct sockaddr *)&recv_host, sizeof(recv_host));
        read_len = recvfrom(sock, mess, 15, 0, (struct sockaddr *)&send_host, &addr_len)
        mess[read_len-1] = '\0';
        printf("In Sever like Host Recvive From other Host : %s\n", mess);
    }
    /* 后方高度一致 */
    /*
     * 之所以只在接收端使用 connect 的原因，便在于我们模拟的是 客户端-服务器 的模型，而服务器的各项信息是不会随意变更的
     * 但是 客户端就不同了，可能由于 ISP(Internet Server Provider) 的原因，你的IP地址不可能总是固定的，所以只能
     * 保证 在客户端 部分注册了 服务器 的各类信息，而不能在 服务器端 注册 客户端 的信息。
     * 当然也有例外，例如你就想这个软件作为私密软件，仅供两个人使用， 且你有固定的 IP地址，那么你可以两边都connect，但是
     * 一定要注意，只要有一点信息变动，这个软件就可能无法正常的收发信息了。
     */
    
#endif
    /* 接收完成，关闭套接字 */
    close(sock);
    return 0;
}
