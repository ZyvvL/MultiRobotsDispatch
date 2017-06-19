#include "socketthread.h"
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <QByteArray>
#include <linux/types.h>
#include <asm/byteorder.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

socketThread::socketThread()
{
    isConnected = true;
    pthread_mutex_init(&DispatchInfo_mutex,NULL);


}

socketThread::~socketThread()
{
    pthread_mutex_destroy(&DispatchInfo_mutex);
}

void socketThread::run()
{
    int recv_len = 0;
    char recv_buf[1024] = "";   // 接收缓冲区

    IN_ADDR addr;
    addr.S_un.S_addr = client_addr.sin_addr.s_addr;
    this->Robot_Info->Robot_Serial = addr.S_un.S_un_b.s_b4 + (ntohs(client_addr.sin_port)%100)*256;
    this->Robot_Info->Robot_Priority = this->Robot_Info->Robot_Serial;
    this->IsException = false;

    while(1)
    {
        if((recv_len = recv(connfd, recv_buf, sizeof(recv_buf), 0)) > 0)
        {
            QByteArray array = QByteArray(recv_buf,recv_len);
            RobotInfo *RInfo = (RobotInfo*)array.data();
            if((RInfo->ECC_Front == ECC_FRONT)&&(RInfo->ECC_Back == ECC_BACK))
            {
                char char_1 = 1;
                if(this->PackREevCnt.isFull() == false)
                    this->PackREevCnt.append(char_1);
                else
                {
                    this->PackREevCnt.removeFirst();
                    this->PackREevCnt.append(char_1);
                }

                //this->Robot_Info->Robot_Per = RInfo->Robot_Per;
                this->Robot_Info->Robot_Pos = RInfo->Robot_Pos;
                //this->Robot_Info->Robot_Priority = RInfo->Robot_Priority;
                this->Robot_Info->Robot_State = RInfo->Robot_State;
                this->Robot_Info->Route_Serial = RInfo->Route_Serial;
                //this->Robot_Info->Robot_Serial = RInfo->Robot_Serial;
                this->Robot_Info->Task = RInfo->Task;
                //this->Robot_Info->PauseCNT = RInfo->PauseCNT;
                //this->Robot_Info->RunningCnt = RInfo->RunningCnt;
                this->Robot_Info->PausePos = RInfo->PausePos;
                this->Robot_Info->Instruct = RInfo->Instruct;
                this->Robot_Info->control = RInfo->control;
                //printf("RunningCnt %d\r\n",RInfo->Route_Serial);
                //printf("RunningCnt2 %d\r\n",Robot_Info->Robot_Serial);
            }
            else
            {
                char char_0 = 0;
                if(this->PackREevCnt.isFull() == false)
                    this->PackREevCnt.append(char_0);
                else
                {
                    this->PackREevCnt.removeFirst();
                    this->PackREevCnt.append(char_0);
                }
            }

        }
        else
        {
            struct tcp_info info;
            int len = sizeof(info);
            getsockopt(this->connfd, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
            if ((info.tcpi_state == TCP_ESTABLISHED))
            {

            }
            else
            {
                break;
            }
        }
        //add mutex
        int ret = pthread_mutex_trylock(&DispatchInfo_mutex);
        if(ret == 0)
        {
            if(this->Dispatch_Fifo.isEmpty() == false)
            {
                QByteArray arr;
                RobotDispatchInfo RDInfo;
                this->Dispatch_Fifo.takeFirst(RDInfo);
                //if(RDInfo.Instruct == Stop)
                    //RobotData_Init();
                RDInfo.ECC_Front = ECC_FRONT;
                RDInfo.ECC_Back = ECC_BACK;
                arr.resize(sizeof((RDInfo)));  //设置发送数据大小
                memcpy(arr.data(),&RDInfo,sizeof((RDInfo)));  //拷贝数据到arr
                send(this->connfd,arr.data(),sizeof((RDInfo)),0);
            }
            pthread_mutex_unlock(&DispatchInfo_mutex);
        }


    }
    close(connfd);  //关闭已连接套接字
    isConnected = false;
}

// calculate the quality of network
double socketThread::CalPackQuality()
{
    double LossPer;
    double LossCnt;
    for(size_t i=0; i < PackREevCnt.size();i++)
    {
        char temp;
        PackREevCnt.value(temp,i);
        if(temp == 0)
            LossCnt++;
    }
    LossPer = LossCnt/PackREevCnt.size();
    return LossPer;
}
