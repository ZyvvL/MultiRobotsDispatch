#include "ros/ros.h"
#include "std_msgs/String.h"
#include "test1/robot_info.h"
#include "QList"

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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "node3");
    ros::NodeHandle nh;

    //ros::Publisher Info_pub = nh.advertise<test1::robot_info>("Robot_Info", 1000);
    ros::Publisher Info_pub = nh.advertise<std_msgs::String>("Robot_Info", 1000);

    ros::Rate loop_rate(50);
    int i;
#if 0
    test1::robot_info msg;
    msg.Control_State = Start;
    msg.Route_Serial = 1;
    msg.Robot_State = Paused;
    msg.Robot_Position = 0;
    msg.Task_Type = Go;
    msg.Robot_Serial = 513;
#endif
    int Route_Serial =0;
    int Robot_Position = 0;
    int Robot_Serial = 24065;
    std_msgs::String msg;
    std::stringstream ss;
    ss<<Robot_Serial<<" ";
    ss<<Start<<" ";
    ss<<Paused<<" ";
    ss<<Go<<" ";
    ss<<Route_Serial<<" ";
    ss<<Robot_Position<<" ";
    msg.data = ss.str();

    while (ros::ok())
    {
        Info_pub.publish(msg);
        ros::spinOnce();
        i = i+1;
        if(i > 50)
        {
            Robot_Position++;
            if(Robot_Position == 10)
                Robot_Position = 0;
            i=0;
            ss.clear();
            ss.str("");
            ss<<Robot_Serial<<" ";
            ss<<Start<<" ";
            ss<<Paused<<" ";
            ss<<Go<<" ";
            ss<<Route_Serial<<" ";
            ss<<Robot_Position<<" ";
            msg.data = ss.str();
        }
        loop_rate.sleep();
    }

    return 0;
}
