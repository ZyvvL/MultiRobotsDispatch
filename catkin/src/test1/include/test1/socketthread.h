#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H
#include <QList>
#include "zyvvfifo.h"
#include "thread.h"
//#include <sys/socket.h>
#include <arpa/inet.h>

class socketThread:public Thread
{
public:
#define ECC_FRONT 12345
#define ECC_BACK  9876

    socketThread();
    ~socketThread();
    enum RobotState{Moving,Paused,Done};                 //机器人状态
    enum RobotInstruct{Move,Pause,InNone};          //机器人指令
    enum RobotControl{Start,Stop,Suspend,Resume,Ready,Addtask,CoNone};  //机器人控制
    enum RobotTaskType{Go,Wait,TaNone};      //机器人任务类型

    typedef struct robottask{
        RobotTaskType tasktype;       //任务类型
        union {
        quint16 Route_Serial;         //路径编号
        quint16 Wait_Cnt;             //停留时间
        quint16 PausePos;
        }taskval;

    }RobotTask;

    typedef struct robotinfo{
        quint16 ECC_Front;
        quint16 Robot_Serial;           //机器人编号
        quint16 Route_Serial;           //路径编号
        RobotTask Task;
        quint16 Robot_Priority;         //机器人优先级
        quint16 Robot_Pos;               //机器人位置(路径表中的索引)
        float Robot_Per;             //机器人位置百分比
        RobotState Robot_State;        //机器人运行状态
        quint16 PauseCNT;            //被迫暂停次数
        quint16 RunningCnt;          //运行总时间计数
        RobotInstruct Instruct;         //机器人指令
        RobotControl control;
        quint16 PausePos;
        quint16 ECC_Back;
    }RobotInfo;


    typedef struct robotdispatchinfo{
        quint16 ECC_Front;
        quint16 Robot_Serial;           //机器人编号
        RobotTask   Task;
        RobotInstruct Instruct;         //机器人指令
        RobotControl control;
        quint16     ECC_Back;
    }RobotDispatchInfo;

    typedef struct in_addr{
        union{
            struct{unsigned char s_b1,s_b2,s_b3,s_b4;} S_un_b;
            struct{unsigned short s_w1,s_w2;} S_un_w;
            unsigned long S_addr;
        } S_un;
    }IN_ADDR;

    struct sockaddr_in client_addr;    //ip and port
    RobotInfo *Robot_Info;
    ZYVVFIFO<RobotDispatchInfo,50> Dispatch_Fifo;
    int connfd;
    bool isConnected;
    pthread_mutex_t DispatchInfo_mutex;

    bool IsException;

public:
    void run();
private:
    ZYVVFIFO<char,200> PackREevCnt;
    double CalPackQuality();
};

#endif // SOCKETTHREAD_H
