#include <ros/ros.h>
#include "tcp_server.h"
#include "test1/hello.h"
#include "test1/robot_info.h"
#include "test1/server.h"
#include "std_msgs/String.h"
#include "sstream"
#include <QList>
#include "maps.h"
#include "dispatch.h"
#include "QDebug"
#include <stdio.h>
#include <std_msgs/UInt16MultiArray.h>

#define foreach Q_FOREACH

bool IsRevOk = false;
vector<int> Route_Data;

bool isDispatch = false;
#if 0
void  messageCallBack(const test1::server::ConstPtr& msg)
{
    if(msg->IsStart == 1)
    {
        isDispatch = true;
    }
    else
    {
        isDispatch = false;
    }
}
#endif

void  messageCallBack(const std_msgs::String::ConstPtr& msg)
{
    std::string str = msg->data.c_str();
    if(str == "Start")
    {
        isDispatch = true;
        //cout<<"Start \r\n";
    }
    else if(str == "Stop")
    {
        isDispatch = false;
        //cout<<"Stop \r\n";
    }
}

void  RouteRevCallBack(const std_msgs::UInt16MultiArray::ConstPtr& msg)
{
    int arraysize = msg->layout.dim[0].size;
    Route_Data.clear();
    Route_Data.reserve(arraysize);
    for(int i=0; i < arraysize;i++)
    {
        Route_Data.push_back(msg->data[i]);

    }
    IsRevOk = true;
}

void PrintRobotInfo(tcp_server *server)
{
    if(server->ThreadList->isEmpty() == false)
    {
        QList<socketThread*>::iterator it;
        for(it=server->ThreadList->begin();it != server->ThreadList->end();it++)
        {
            socketThread::RobotInfo *robot_info = (*it)->Robot_Info;
            cout<<"robot_serial:"<<robot_info->Robot_Serial;
            switch(robot_info->Robot_State)
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
            cout<<"  route_serial: "<<robot_info->Route_Serial;
            cout<<"  robot_position: "<<robot_info->Robot_Pos;
            switch(robot_info->Task.tasktype)
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

            switch(robot_info->Instruct)
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
        }
    }
}

int main(int argc, char **argv)
{
    //地图构建
    Maps *maps = new Maps;
    maps->SetMapSize(20,20);       //设置地图大小
    maps->MapListInit();           //地图数据初始化

  ros::init(argc, argv, "node1");
  ros::NodeHandle Ros_Node;

  ROS_INFO("Hello world! node 1");

  tcp_server *server = new tcp_server;
  server->Open_Server();
  ROS_INFO("server Open");

  //request route date
  ros::Publisher routeReq_pub = Ros_Node.advertise<std_msgs::String >("Route_Request",1000);
  ros::Subscriber routeRev_sub = Ros_Node.subscribe("Route_Data",10,&RouteRevCallBack);

  ROS_INFO("Req Route");
  for(int i=0; i< 4;)
  {
      std_msgs::String msg;
      std::stringstream ss;
      ss<<"RouteReq "<<i;
      msg.data = ss.str();

      IsRevOk = false;
      while(IsRevOk == false)
      {
          routeReq_pub.publish(msg);
          ros::spinOnce();
      }

       ROS_INFO("Rev Ok");
      if(Route_Data[0] == i)
      {

         maps->SetUp_RouteList3(Route_Data);
         i++;
      }

  }

  ROS_INFO("Req Route End");

  ros::Subscriber robot_sub = Ros_Node.subscribe("server",10,&messageCallBack);
  ros::Rate loop_rate(10);

  QList<socketThread*>::iterator it;
  while(ros::ok())
  {
      //print the info of robot

      PrintRobotInfo(server);
      if(isDispatch)
      {
          DisPatch *dispatch = new DisPatch(server,maps);
          if(dispatch->AvoidanceDetect() == false)
          {
              isDispatch = false;
              ROS_INFO("Game Over!!");
          }
          else
          {
              while(dispatch->DisPatch_Info->isEmpty() == false)
              {
                  socketThread::RobotDispatchInfo dispatch_info;
                  dispatch->DisPatch_Info->takeFirst(dispatch_info);
                  server->SendRobotInstruct(dispatch_info);
                  qDebug("Ins %d  %d ",dispatch_info.Instruct,dispatch_info.Robot_Serial);
              }
          }
          delete dispatch;
      }
      else
      {
          socketThread::RobotDispatchInfo dispatch_info;
          dispatch_info.ECC_Back = ECC_BACK;
          dispatch_info.ECC_Front = ECC_FRONT;
          dispatch_info.Instruct = socketThread::InNone;
          server->BoardRobotInstruct(dispatch_info);
      }

      ros::spinOnce();
      loop_rate.sleep();
  }

  delete server;
  delete maps;
  return 0;

}
