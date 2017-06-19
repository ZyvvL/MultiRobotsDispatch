#include "tcp_server.h"
#include <string.h>
#include <fcntl.h>
#include "maps.h"
#define foreach Q_FOREACH

tcp_server::tcp_server()
{
    memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零
    my_addr.sin_family=AF_INET; //设置为IP通信
    my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上
    my_addr.sin_port=htons(8050); //服务器端口号

    ThreadList = new QList<socketThread*>;
    /*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error");
    }


    /*将套接字绑定到服务器的网络地址上*/
    if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
    {
        perror("bind error");
    }

    /*监听连接请求--监听队列长度为50*/
    if(listen(server_sockfd,50)<0)
    {
        perror("listen error");
    };
}

tcp_server::~tcp_server()
{
    foreach(socketThread *pvar,*(this->ThreadList)) {
       delete pvar->Robot_Info;
    }
    //qDeleteAll(*(this->ThreadList));
    this->ThreadList->clear();
    delete ThreadList;
}

void* tcp_server::server_fun(void *arg)
{
    tcp_server* server_ptr = (tcp_server*)arg;
    int sin_size;
    int connfd;

    sin_size=sizeof(struct sockaddr_in);

    printf("Waiting client...\n");

    while(1)
    {
        char cli_ip[INET_ADDRSTRLEN] = "";     // 用于保存客户端IP地址
        struct sockaddr_in client_addr;        // 用于保存客户端地址
        socklen_t cliaddr_len = sizeof(client_addr);   // 必须初始化!!!

        //获得一个已经建立的连接
        connfd = accept(server_ptr->server_sockfd, (struct sockaddr*)&client_addr, &cliaddr_len);
        if(connfd < 0)
        {
            perror("accept this time");
            continue;
        }

        // 打印客户端的 ip 和端口
        inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
        printf("----------------------------------------------\n");
        printf("client ip=%s,port=%d\n", cli_ip,ntohs(client_addr.sin_port));
        if(connfd > 0)
        {
            int flags = fcntl(connfd, F_GETFL, 0);
            fcntl(connfd, F_SETFL, flags|O_NONBLOCK);
            //由于同一个进程内的所有线程共享内存和变量，因此在传递参数时需作特殊处理，值传递。


            socketThread *thread=new socketThread;
            thread->connfd = connfd;
            thread->Robot_Info = new socketThread::RobotInfo;
            thread->Dispatch_Fifo.clear();
            thread->client_addr = client_addr;
            server_ptr->ThreadList->append(thread);
            thread->start();

            //pthread_create(&thread_id, NULL, client_fun,(void *)thread);  //创建线程
            //pthread_detach(thread_id); // 线程分离，结束时自动回收资源
        }

    }

    close(server_ptr->server_sockfd);
}

void* tcp_server::condetect_fun(void *arg)
{
    tcp_server* server_ptr = (tcp_server*)arg;
    while(1)
    {
        //delete the unconnected thread
        QList<socketThread*>::Iterator it;
        for(it = server_ptr->ThreadList->begin();it != server_ptr->ThreadList->end();)
        {
            socketThread* thread = *it;
            if(thread->isConnected == true)
            {
                it++;
            }
            else
            {
                delete thread->Robot_Info;
                delete thread;
                it = server_ptr->ThreadList->erase(it);
                printf("client unconnected...\n");
            }
        }
    }

}

int tcp_server::Open_Server()
{
    pthread_create(&(this->condetect_thread_id), NULL, condetect_fun,(void *)this);
    pthread_create(&(this->server_thread_id), NULL, server_fun,(void *)this);
}

bool tcp_server::SendRobotInstruct(socketThread::RobotDispatchInfo &info)
{
    for(quint16 i=0; i < ThreadList->size();i++)
    {
        if(ThreadList->at(i)->Robot_Info->Robot_Serial == info.Robot_Serial)
        {
             //add lock
             pthread_mutex_lock(&(ThreadList->at(i)->DispatchInfo_mutex));
             if(ThreadList->at(i)->Dispatch_Fifo.isFull() == false)
                ThreadList->at(i)->Dispatch_Fifo.append(info);
             pthread_mutex_unlock(&(ThreadList->at(i)->DispatchInfo_mutex));
             return true;
        }
    }

    return false;
}


void tcp_server::BoardRobotInstruct(socketThread::RobotDispatchInfo &info)
{
    for(quint16 i=0; i < ThreadList->size();i++)
    {
         //add lock
         pthread_mutex_lock(&(ThreadList->at(i)->DispatchInfo_mutex));
         info.Robot_Serial = ThreadList->at(i)->Robot_Info->Robot_Serial;
         if(ThreadList->at(i)->Dispatch_Fifo.isFull() == false)
         ThreadList->at(i)->Dispatch_Fifo.append(info);
         pthread_mutex_unlock(&(ThreadList->at(i)->DispatchInfo_mutex));
    }
}
