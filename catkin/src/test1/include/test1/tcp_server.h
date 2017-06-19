#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <QList>
#include "zyvvfifo.h"
#include "socketthread.h"

class tcp_server
{
public:
    tcp_server();
    ~tcp_server();
    int recv_msg();
    int Open_Server();
    bool SendRobotInstruct(socketThread::RobotDispatchInfo &info);
    void BoardRobotInstruct(socketThread::RobotDispatchInfo &info);
private:
    //static void *client_fun(void *arg);
    //static void * test(void *arg);
    static void* server_fun(void* arg);
    static void* condetect_fun(void* arg);
    int server_sockfd;//服务器端套接字
    //int client_sockfd;//客户端套接字
    struct sockaddr_in my_addr;   //服务器网络地址结构体
    //struct sockaddr_in remote_addr; //客户端网络地址结构体
public:
    QList<socketThread*>  *ThreadList;
    pthread_t server_thread_id;
    pthread_t condetect_thread_id;
};

#endif // TCP_SERVER_H
