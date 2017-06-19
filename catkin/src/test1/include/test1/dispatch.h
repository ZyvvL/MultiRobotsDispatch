#ifndef DISPATCH_H
#define DISPATCH_H

#include <QByteArray>
#include <QVector>
#include <QList>
#include <map>
#include <QPoint>
#include "maps.h"
#include "socketthread.h"

class tcp_server;

class DisPatch
{
public:
    DisPatch(tcp_server* server, Maps *maps);
    ~DisPatch();

public:
    bool OccupyDetect();     //Take Up conflict detection
    bool AvoidanceDetect();  //detection function
    ZYVVFIFO<socketThread::RobotDispatchInfo,100> *DisPatch_Info; //调度信息表
private:
    void MapsDataGen();        //地图数据生成
    bool DisPatchInfoGen();        //生成调度数据
    void AddItem2Maps(socketThread::RobotInfo* ptr,quint16 itemtype,qint16 s_pos,quint16 g_pos);   //add PointItem to MapList : s_pos means the position of robotself ;
                                                                                                   //g_pos means the global position in map
    Maps::PointItem *IsItemInList(Maps::PointItem * item,QList<Maps::PointItem*> *itemlist);       //判断是否在pointitem列表中
    int IsItemInList(Maps::PointItem * item,ZYVVULIST<Maps::PointItem,10> *itemlist);              //判断是否在pointitem列表中
    //外部引用
    tcp_server *my_server;                                //tcp服务器指针
    Maps *maps;                                           //地图服务指针
};

#endif // DISPATCH_H
