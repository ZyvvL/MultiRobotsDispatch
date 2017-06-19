#include <ros/ros.h>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <std_msgs/String.h>
#include <std_msgs/UInt16MultiArray.h>

bool IsPubRoute;
int  Pub_RouteSerial;

using namespace std;

std::vector<std::string> split(const  std::string& s, const std::string& delim)
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

void  RouteReqCallBack(const std_msgs::String::ConstPtr& msg)
{
    std::string str = msg->data.c_str();
    vector<string> str_vector =  split(str," ");
    if(str_vector[0] == "RouteReq")
    {
        Pub_RouteSerial = stoi(str_vector[1]);

        IsPubRoute = true;
    }

}

int main(int argc, char **argv)
{
    IsPubRoute = false;
    ros::init(argc, argv, "node5");
    ros::NodeHandle nh;

    //request route date
    ros::Publisher routeReq_pub = nh.advertise<std_msgs::UInt16MultiArray>("Route_Data",1000);
    ros::Subscriber routeRev_sub = nh.subscribe("Route_Request",10,&RouteReqCallBack);

    //init route map
    map<int,vector<int> > Route_map;
    vector<int> route1;
    route1.clear();
    route1.reserve(20);
    route1.push_back(0);
    route1.push_back(1);
    route1.push_back(2);
    route1.push_back(3);
    route1.push_back(4);
    route1.push_back(5);
    route1.push_back(6);
    route1.push_back(7);
    route1.push_back(8);
    route1.push_back(9);
    route1.push_back(10);

    vector<int> route2;
    route2.clear();
    route2.reserve(20);
    route2.push_back(1);
    route2.push_back(11);
    route2.push_back(12);
    route2.push_back(13);
    route2.push_back(14);
    route2.push_back(15);
    route2.push_back(6);
    route2.push_back(17);
    route2.push_back(18);
    route2.push_back(19);
    route2.push_back(20);

    vector<int> route3;
    route3.clear();
    route3.reserve(20);
    route3.push_back(2);
    route3.push_back(21);
    route3.push_back(22);
    route3.push_back(23);
    route3.push_back(24);
    route3.push_back(15);
    route3.push_back(26);
    route3.push_back(27);
    route3.push_back(28);
    route3.push_back(29);
    route3.push_back(30);

    vector<int> route4;
    route4.clear();
    route4.reserve(20);
    route4.push_back(3);
    route4.push_back(31);
    route4.push_back(12);
    route4.push_back(33);
    route4.push_back(34);
    route4.push_back(35);
    route4.push_back(36);
    route4.push_back(17);
    route4.push_back(38);
    route4.push_back(39);
    route4.push_back(40);

    Route_map[0] = route1;
    Route_map[1] = route2;
    Route_map[2] = route3;
    Route_map[3] = route4;

    ros::Rate loop_rate(50);
    while(1)
    {
        if(IsPubRoute == true)
        {
            vector<int> route = Route_map[Pub_RouteSerial];
            std_msgs::UInt16MultiArray m;
            m.layout.dim.push_back(std_msgs::MultiArrayDimension());
            m.layout.dim[0].size = route.size();
            m.layout.dim[0].stride = 1;
            m.layout.dim[0].label = "bla";

            m.data.resize(route.size());
            for(int i=0;i< route.size();i++)
            {
                m.data[i] = route[i];
            }

            routeReq_pub.publish(m);
            ros::spinOnce();
            //routeReq_pub(msg);
            IsPubRoute = false;
        }

        ros::spinOnce();
        loop_rate.sleep();

    }

}
