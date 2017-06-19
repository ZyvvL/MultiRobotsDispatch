#include "tcp_client.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QByteArray>
#include <unistd.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <fcntl.h>


tcp_client::tcp_client()
{

    //数据初始化
    Robot_Info.ECC_Front = ECC_FRONT;
    Robot_Info.ECC_Back  = ECC_BACK;
    Robot_Info.Task.tasktype = Wait;        //.. .
    Robot_Info.Task.taskval.Wait_Cnt = 0;
    Robot_Info.Robot_Serial = 0;            //..
    Robot_Info.Route_Serial = 0;            //.. .
    Robot_Info.Robot_Priority = 0;          //..
    Robot_Info.Robot_Per = 100;
    Robot_Info.Robot_Pos = 0;               //.. .
    Robot_Info.Robot_State = Done;          //.. .
    Robot_Info.PauseCNT = 0;
    Robot_Info.RunningCnt = 0;
    Robot_Info.control = Stop;              //.. .
    Robot_Info.Instruct = Pause;            //..
    Robot_Info.PausePos = 0;                //..

    isConnected = false;
    isRevMsg = false;
    pthread_mutex_init(&DispatchInfo_mutex,NULL);
}

tcp_client::~tcp_client()
{
    close(client_sockfd);
}

bool tcp_client::Open_Client(char *IP_Addr)
{
    //int len;
    struct sockaddr_in remote_addr; //服务器端网络地址结构体
    //char buf[BUFSIZ];  //数据传送的缓冲区
    char cli_ip[INET_ADDRSTRLEN] = "";
    memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零
    remote_addr.sin_family=AF_INET; //设置为IP通信
    remote_addr.sin_addr.s_addr=inet_addr(IP_Addr);//服务器IP地址
    remote_addr.sin_port=htons(8050); //服务器端口号

    /*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
    if((client_sockfd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket error");
        return false;
    }

    /*将套接字绑定到服务器的网络地址上*/
    if(connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0)
    {
        perror("connect error");
        return false;
    }
    //printf("connected to server\n");

    int flags = fcntl(client_sockfd, F_GETFL, 0);
    fcntl(client_sockfd, F_SETFL, flags|O_NONBLOCK);

    //set robot_seial and poriority

    isConnected = true;

    //open thread to rev
    pthread_create(&(this->client_thread_id), NULL, client_fun,(void *)this);
    return true;
}

#if 1
void  tcp_client::messageCallBack(const test1::robot_info::ConstPtr& msg)
{
    //read robot info from topic
    if(msg->Robot_Serial == this->Robot_Info.Robot_Serial)
    {
        switch(msg->Control_State)
        {
        case 0:
            this->Robot_Info.control = Start;
            break;
        case 1:
            this->Robot_Info.control = Stop;
            break;
        default:
            break;
        }

        switch(msg->Robot_State)
        {
        case 0:
            this->Robot_Info.Robot_State = Moving;
            break;
        case 1:
            this->Robot_Info.Robot_State = Paused;
            break;
        case 2:
            this->Robot_Info.Robot_State = Done;
            break;
        default:
            break;
        }
        switch(msg->Task_Type)
        {
        case 0:
            this->Robot_Info.Task.tasktype = Go;
            break;
        case 1:
            this->Robot_Info.Task.tasktype = Wait;
            break;
        case 2:
            this->Robot_Info.Task.tasktype = TaNone;
            break;
        default:
            break;
        }

        this->Robot_Info.Route_Serial = msg->Route_Serial;

        this->Robot_Info.Robot_Pos = msg->Robot_Position;

        this->isRevMsg = true;
    }

}
#endif

std::vector<std::string> tcp_client::split(const  std::string& s, const std::string& delim)
{
    std::vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    if (delim_len == 0) return elems;
    while (pos < len)
    {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0)
        {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

void  tcp_client::messageCallBack2(const std_msgs::String::ConstPtr& msg)
{

    string str = msg->data.c_str();

    vector<string> str_vector =  split(str," ");
    //read robot info from topic
    if(stoi(str_vector[0]) == this->Robot_Info.Robot_Serial)
    {
        switch(stoi(str_vector[1]))
        {
        case 0:
            this->Robot_Info.control = Start;
            break;
        case 1:
            this->Robot_Info.control = Stop;
            break;
        default:
            break;
        }

        switch(stoi(str_vector[2]))
        {
        case 0:
            this->Robot_Info.Robot_State = Moving;
            break;
        case 1:
            this->Robot_Info.Robot_State = Paused;
            break;
        case 2:
            this->Robot_Info.Robot_State = Done;
            break;
        default:
            break;
        }
        switch(stoi(str_vector[3]))
        {
        case 0:
            this->Robot_Info.Task.tasktype = Go;
            break;
        case 1:
            this->Robot_Info.Task.tasktype = Wait;
            break;
        case 2:
            this->Robot_Info.Task.tasktype = TaNone;
            break;
        default:
            break;
        }

        this->Robot_Info.Route_Serial = stoi(str_vector[4]);

        this->Robot_Info.Robot_Pos = stoi(str_vector[5]);

        this->isRevMsg = true;
    }

}

void tcp_client::SendRobotInfo()
{
    QByteArray arr;
    arr.resize(sizeof(this->Robot_Info));  //设置发送数据大小
    memcpy(arr.data(),&(this->Robot_Info),sizeof(this->Robot_Info));  //拷贝数据到arr
    send(client_sockfd,arr.data(),sizeof((Robot_Info)),0);
}

void* tcp_client::client_fun(void *arg)
{
    int recv_len = 0;
    char recv_buf[1024] = "";   // 接收缓冲区

    tcp_client *client = (tcp_client*)arg;
    while(1)
    {
        if((recv_len = recv(client->client_sockfd, recv_buf, sizeof(recv_buf), 0)) > 0)
        {
            QByteArray array = QByteArray(recv_buf,recv_len);
            RobotDispatchInfo *RDInfo = (RobotDispatchInfo*)array.data();
            if((RDInfo->ECC_Front == ECC_FRONT)&&(RDInfo->ECC_Back == ECC_BACK))
            {
                char char_1 = 1;
                if(client->PackREevCnt.isFull() == false)
                    client->PackREevCnt.append(char_1);
                else
                {
                    client->PackREevCnt.removeFirst();
                    client->PackREevCnt.append(char_1);
                }

                pthread_mutex_lock(&(client->DispatchInfo_mutex));
                //add lock
                if(client->Dispatch_Fifo.isFull() == false)
                {
                    client->Dispatch_Fifo.append(*RDInfo);
                }
                pthread_mutex_unlock(&(client->DispatchInfo_mutex));

                //print the robot serial
#if 0
                RobotDispatchInfo info0;
                client->Dispatch_Fifo.valueLast(info0);
                qDebug("Robot_serial: %d",info0.Robot_Serial);
#endif
            }else
            {
                char char_0 = 0;
                if(client->PackREevCnt.isFull() == false)
                    client->PackREevCnt.append(char_0);
                else
                {
                    client->PackREevCnt.removeFirst();
                    client->PackREevCnt.append(char_0);
                }
            }

        }
        else
        {
            struct tcp_info info;
            int len = sizeof(info);
            getsockopt(client->client_sockfd, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
            if ((info.tcpi_state == TCP_ESTABLISHED))
            {

            }
            else
            {
                break;
            }
        }
    }

    client->isConnected = false;
    printf("unconnected !");
}

// calculate the quality of network
double tcp_client::CalPackQuality()
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
