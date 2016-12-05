//
//  main.cpp
//  udptestsend2
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
    int sock;
    const char* mess = "Hello Server!";
    char get_mess[GET_MAX]; /* 后续版本使用 */
    struct sockaddr_storage recv_host; /* - struct sockaddr_in recv_host; */
    struct addrinfo tmp, *result;
    struct addrinfo *p;
    socklen_t addr_len;
    
    /* 获取对端的信息 */
    memset(&tmp, 0, sizeof tmp);
    tmp.ai_family = AF_UNSPEC;
    tmp.ai_flags = AI_PASSIVE;
    tmp.ai_socktype = SOCK_DGRAM;
    getaddrinfo(argv[1], argv[2], &tmp, &result); /* argv[1] 代表对端的 IP地址， argv[2] 代表对端的 端口号 */
    
    /* 创建套接字 */
    for(p = result; p != NULL; p = p->ai_next)
    {
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol); /* - sock = socket(PF_INET, SOCK_DGRAM, 0); */
        if(sock == -1)
            continue;
        /* 此处少了绑定 bind 函数，因为作为发送端不需要讲对端的信息 绑定 到创建的套接字上。 */
        break; /* 找到就可以退出了，当然也有可能没找到，那么此时 p 的值一定是 NULL */
    }
    if(p == NULL)
    {
        /* 错误处理 */
    }
    /* -// 设定对端信息
     memset(&recv_host, 0, sizeof(recv_host));
     recv_host.sin_family = AF_INET;
     recv_host.sin_addr.s_addr = inet_addr("127.0.0.1");
     recv_host.sin_port = htons(6000);
     */
    
    /* 发送信息 */
    /* 在此处，发送端的IP地址和端口号等各类信息，随着这个函数的调用，自动绑定在了套接字上 */
    sendto(sock, mess, strlen(mess), 0, p->ai_addr, p->ai_addrlen);
    /* 完成，关闭 */
    freeaddrinfo(result); /* 实际上这个函数应该在使用完 result 的地方就予以调用 */
    close(sock);
    return 0;
}
