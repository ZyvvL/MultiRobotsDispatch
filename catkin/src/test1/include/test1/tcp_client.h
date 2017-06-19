#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include <qglobal.h>
#include "ros/ros.h"
#include "zyvvfifo.h"
#include "test1/hello.h"
#include "test1/robot_info.h"
#include "test1/robot_dispatch.h"
#include "queue"
 #include "std_msgs/String.h"
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>

class tcp_client
{
public:
#define ECC_FRONT 12345
#define ECC_BACK  9876

    tcp_client();
    ~tcp_client();
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
        quint16 Route_Serial;          //路径编号
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
        quint16 ECC_Back;
    }RobotDispatchInfo;

    //ros::NodeHandle Ros_Node;

    void SendRobotInfo();
    bool Open_Client(char* IP_Addr);
    void messageCallBack(const test1::robot_info::ConstPtr& msg);
    void messageCallBack2(const std_msgs::String::ConstPtr& msg);
    std::vector<std::string> split(const  std::string& s, const std::string& delim);
    ZYVVFIFO<RobotDispatchInfo,50> Dispatch_Fifo;   // dispatch info receive cache
    RobotInfo Robot_Info;         //机器人运动信息
    bool isConnected;
    pthread_mutex_t DispatchInfo_mutex;
    bool isRevMsg;                 //receive robot_info.msg flag
private:

    void Tcp_Process();
    static void* client_fun(void* arg);
    double CalPackQuality();
    ros::Publisher robot_pub;
    ros::Subscriber robot_sub;
    int client_sockfd;
    pthread_t client_thread_id;
    ZYVVFIFO<char,200> PackREevCnt;

};

#endif // TCP_CLIENT_H
