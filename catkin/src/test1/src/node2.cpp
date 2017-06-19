#include <ros/ros.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QByteArray>
#include <unistd.h>
#include "tcp_client.h"
#include "QDebug"
#include <stdio.h>
#include "std_msgs/String.h"

//global
ros::Publisher robot_pub;
ros::Subscriber robot_sub;
bool isRosInit;
//#define IP_ADDR "192.168.2.110"
#define IP_ADDR "127.0.0.1"

void ROS_Init(int argc, char **argv,int robot_serial,tcp_client *client)
{
    char node_name[10];
    sprintf(node_name,"cient_node%d",robot_serial);
    ros::init(argc, argv,node_name);
    ros::NodeHandle Ros_Node;

    cout<<"Hello World! robot: "<<robot_serial<<"\r\n";
    //init ROS topic
    //robot_pub = Ros_Node.advertise<test1::robot_dispatch>("Dispatch_Info",1000);     //advetise dispatch info
    robot_pub = Ros_Node.advertise<std_msgs::String >("Dispatch_Info",1000);     //advetise dispatch info
    //receive robot info
    robot_sub = Ros_Node.subscribe("Robot_Info",1000,&tcp_client::messageCallBack2,client);


}

int main(int argc, char **argv)
{
    isRosInit = false;

    tcp_client *client = new tcp_client;
    while(client->Open_Client(IP_ADDR) == false)
    {
        cout<<"client Open failed\r\n";
        sleep(1);
    }
    cout<<"client Open success\r\n";



    //ros::Rate loop_rate(10);   //10 hz

    while(1)
    {
        //tcp detect
        if(client->isConnected == false)
        {
            cout<<"The connection is disconnected\r\n";
            isRosInit == false;
            while(client->Open_Client(IP_ADDR) == false)
            {
                cout<<"client connect failed";
                sleep(1);
            }
            cout<<"client connect success";
        }

        //read dispatch info and preocess
        tcp_client::RobotDispatchInfo rinfo;
        //add lock
        pthread_mutex_lock(&(client->DispatchInfo_mutex));
        if(client->Dispatch_Fifo.isEmpty() == false)
        {
            client->Dispatch_Fifo.takeFirst(rinfo);
            if(1)//if(rinfo.Robot_Serial == client->Robot_Info.Robot_Serial)
            {
                client->Robot_Info.Robot_Serial = rinfo.Robot_Serial;
                client->Robot_Info.Robot_Priority = client->Robot_Info.Robot_Serial;

                if(isRosInit == false)
                {
                    ROS_Init(argc,argv,client->Robot_Info.Robot_Serial,client);
                    isRosInit = true;
                    //continue;
                }
                if(client->Robot_Info.control == tcp_client::Start)     //只在启动条件下更新指令
                {
                    if(rinfo.Instruct != tcp_client::InNone)
                    {

                        if(rinfo.Instruct == tcp_client::Pause)
                            client->Robot_Info.PausePos = rinfo.Task.taskval.PausePos;
                        client->Robot_Info.Instruct = rinfo.Instruct;

                        if(isRosInit == true)
                        {
                            //advertise dispatch topic to robot
#if 0
                            test1::robot_dispatch msg;
                            msg.Instruct = client->Robot_Info.Instruct;
                            msg.PausePosition = client->Robot_Info.PausePos;
                            msg.Robot_Serial  = client->Robot_Info.Robot_Serial;
#endif
                            std_msgs::String msg;
                            std::stringstream ss;
                            ss<<client->Robot_Info.Instruct<<" ";
                            ss<<client->Robot_Info.PausePos<<" ";
                            ss<<client->Robot_Info.Robot_Serial<<" ";
                            msg.data = ss.str();
                            robot_pub.publish(msg);
                        }

                    }
                }
            }
        }
        pthread_mutex_unlock(&(client->DispatchInfo_mutex));

        //Send robot info to server
        client->SendRobotInfo();
        //print robot info
#if 1
        if(client->isRevMsg == true)
        {
            cout<<"robot_serial "<<client->Robot_Info.Robot_Serial;
            switch(client->Robot_Info.Robot_State)
            {
            case 0:
                cout<<"  robot_state: Moving";
                break;
            case 1:
                cout<<"  robot_state: Paused";
                break;
            case 2:
                cout<<"  robot_state: Done";
                break;
            default:
                cout<<"  robot_state: Error";
                break;

            }
            cout<<"  route_serial: "<<client->Robot_Info.Route_Serial;
            cout<<"  robot_position: "<<client->Robot_Info.Robot_Pos;
            switch(client->Robot_Info.Task.tasktype)
            {
            case 0:
                cout<<"  task_type: Run";
                break;
            case 1:
                cout<<"  task_type: Wait";
                break;
            default:
                cout<<"  task_type: Error";
                break;
            }
            switch(client->Robot_Info.Instruct)
            {
            case 0:
                cout<<"  Instruct: Move";
                break;
            case 1:
                cout<<"  Instruct: Pause";
                break;
            default:
                cout<<"  Instruct: Error";
                break;
            }

            cout<<"\r\n";
            client->isRevMsg = false;
        }
        else
        {
            cout<<"No robot_info received!\r\n";
        }
#endif
        if(isRosInit == true)
        {
            //ros msg callback preocess
            ros::spinOnce();
        }
        //loop_rate.sleep();
        usleep(100000);
    }


    return 0;
}
