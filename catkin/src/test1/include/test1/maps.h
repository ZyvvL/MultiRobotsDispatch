#ifndef MAPS_H
#define MAPS_H

#include <QList>
#include <QVector>
#include <QPoint>
#include <map>
#include "socketthread.h"
#include "zyvvulist.h"

class Maps
{
public:
    Maps();
    ~Maps();
    enum PointType{Free,Route,Block};   //地图点类型

    typedef struct pointitem{          //地图点结构
        socketThread::RobotInfo* robot_info;     //机器人信息结构指针
        qint16  pos;                             //预测点或占据点相对位置
    }PointItem;

    typedef struct pointinfo{
        ZYVVULIST<PointItem,10> *OccupyItem;          //占据点队列    ten robots max
        ZYVVULIST<PointItem,10> *PredictItem;         //预测点队列
    }PointInfo;

private:

    template <class T>
    int getArrayLen(T& array)
    {
      return (sizeof(array) / sizeof(array[0]));
    }

    template<size_t size>
    void AddP2R(int (&node)[size])
    {
        QList<QPoint *> *route = new QList<QPoint *>;

       int node_size = getArrayLen(node);
       for(int i=0; i< node_size; i++)
       {
           int node_serial = node[i];
           int node_x = node_serial/map_height;
           int node_y = node_serial%map_height;
           route->append(new QPoint(node_x,node_y));
       }

       this->Route_List->append(route);
    }

    QList<QPoint*>* MakeRouteFunc(QList<QPoint*>* routep);   //路径生成函数
    void SetUp_RobotTask();      //创建任务队列
    void SetUp_RouteList();      //创建路径表 适用于qt仿真
    void SetUp_RouteList2();     //创建路径表 用于建立实际路径

public:
    quint16 map_width;      //地图尺寸
    quint16 map_height;
    QList<QList<QPoint*>*> *Route_List;  //路径数据
    map<int,QList<QPoint> > *Route_map;

    QList<PointInfo*> *Map_List;         //地图数据
    QList<QList<socketThread::RobotTask*>*>  *Robot_Task;      //任务队列
    void SetMapSize(quint16 width,quint16 height);
    void ClearMapData();   //清除地图数据
    void MapListInit();
    void SetUp_RouteList3(vector<int> &route);
};

#endif // MAPS_H
