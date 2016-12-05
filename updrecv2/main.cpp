//
//  main.cpp
//  updrecv2
//
//  Created by junpengzhang on 12/5/16.
//  Copyright © 2016 junpengzhang. All rights reserved.
//

#include <iostream>
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
#include<netdb.h>

#define GET_MAX 1024



int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int sock = 0; /* 套接字 */
    socklen_t addr_len; /* 发送端的地址长度，用于 recvfrom */
    char mess[15];
    char get_mess[GET_MAX]; /* 后续版本使用 */
    struct sockaddr_in host_v4; /* IPv4 地址 */
    struct sockaddr_in6 host_v6; /* IPv6 地址 */
    struct addrinfo easy_to_use; /* 用于设定要获取的信息以及如何获取信息 */
    struct addrinfo *result;  /* 用于存储得到的信息(需要注意内存泄露) */
    struct addrinfo * p;
    
    /* 准备信息 */
    memset(&easy_to_use, 0, sizeof easy_to_use);
    easy_to_use.ai_family = AF_UNSPEC; /* 告诉接口，我现在还不知道地址类型 */
    easy_to_use.ai_flags = AI_PASSIVE; /* 告诉接口，稍后“你”帮我填写我没明确指定的信息 */
    easy_to_use.ai_socktype = SOCK_DGRAM; /* UDP 的套接字 */
    /* 其余位都为 0 */
    
    /* 使用 getaddrinfo 接口 */
    getaddrinfo(NULL, argv[1], &easy_to_use, &result); /* argv[1] 中存放字符串形式的 端口号 */
    
    /* 创建套接字，此处会产生两种写法，但更保险，可靠的写法是如此 */
    /* 旧式方法
     * sock = socket(PF_INET, SOCK_DGRAM, 0);
     */
    /* 把IP 和 端口号信息绑定在套接字上 */
    /* 旧式方法
     * memset(&recv_host, 0, sizeof(recv_host));
     * recv_host.sin_family = AF_INET;
     * recv_host.sin_addr.s_addr = htonl(INADDR_ANY);/ /接收任意的IP *
    * recv_host.sin_port = htons(6000); // 使用6000 端口号
    * bind(sock, (struct sockaddr *)&recv_host, sizeof(recv_host));
    */
    
    for(p = result; p != NULL; p = p->ai_next) /* 该语法需要开启 -std=gnu99 标准*/
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(sock == -1)
            continue;
        if(bind(sock, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sock);
            continue;
        }
        break; /* 如果能执行到此，证明建立套接字成功，套接字绑定成功，故不必再尝试。 */
    }
    
    /* 进入接收信息的状态 */
    //recvfrom(sock, mess, 15, 0, (struct sockaddr *)&send_host, &addr_len);
    switch(p->ai_socktype)
    {
        case AF_INET :
            addr_len = sizeof(host_v4);
            recvfrom(sock, mess, 15, 0, (struct sockaddr *)&host_v4, &addr_len);
            break;
        case AF_INET6:
            addr_len = sizeof(host_v6);
            recvfrom(sock, mess, 15, 0, (struct sockaddr *)&host_v6, &addr_len);
            break;
        default:
            break;
    }
    freeaddrinfo(result); /* 释放这个空间，由getaddrinfo分配的 */
    /* 接收完成，关闭套接字 */
    close(sock);
    return 0;
}
