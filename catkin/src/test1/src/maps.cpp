#include "maps.h"
#include "stdio.h"
#include <iostream>
//#include "qglobal.h"
#define foreach Q_FOREACH

Maps::Maps()
{
    this->Route_List = new  QList<QList< QPoint*>*>;
    this->Map_List = new QList<PointInfo*>;
    this->Robot_Task = new QList<QList<socketThread::RobotTask*>*>;
    this->Route_map = new map<int,QList<QPoint> >;
    this->Route_map->clear();
}

Maps::~Maps()
{
    //析构路径数据
    QList<QList< QPoint*>*>::Iterator it_route1;
    for(it_route1 = Route_List->begin();it_route1 != Route_List->end();it_route1++)
    {
        QList< QPoint*>* pvar = *it_route1;
        QList< QPoint*>::Iterator it_route2;
        for(it_route2=pvar->begin();it_route2 != pvar->end();it_route2++)
        {
            QPoint* var = *it_route2;
            delete var;
        }
        pvar->clear();
    }
    Route_List->clear();
    delete Route_List;

    QList<QList<socketThread::RobotTask*>*>::iterator it_task1;
    for(it_task1=Robot_Task->begin();it_task1 !=Robot_Task->end();it_task1++)
    {
        QList<socketThread::RobotTask*>* pvar = *it_task1;
        QList<socketThread::RobotTask*>::iterator it_task2;
        for(it_task2=pvar->begin();it_task2 != pvar->end();it_task2++)
        {
            socketThread::RobotTask* var= *it_task2;
            delete var;
        }
        pvar->clear();
    }
    Robot_Task->clear();
    delete Robot_Task;

    //析构地图数据
    QList<PointInfo*>::iterator it_map;
    for(it_map=Map_List->begin();it_map != Map_List->end();it_map++)
    {
        PointInfo* pvar = *it_map;
        delete pvar->OccupyItem;
        delete pvar->PredictItem;
    }
    Map_List->clear();
    delete Map_List;

    delete Route_map;
}

void Maps::SetMapSize(quint16 width, quint16 height)
{
    this->map_width = width;
    this->map_height = height;
}


QList<QPoint *> *Maps::MakeRouteFunc(QList<QPoint *> *routep)
{
    if(routep->size() > 1)   //至少两个点
    {
        QList<QPoint*> *rou = new QList<QPoint*>;
        QPoint pointpre = QPoint(routep->at(0)->x(),routep->at(0)->y());
        rou->append(new QPoint(pointpre.x(),pointpre.y()));
        QPoint pointnext = QPoint(0,0);
        for(qint16 i=1; i < (routep->size());i++)
        {
            pointnext.setX(routep->at(i)->x());
            pointnext.setY(routep->at(i)->y());

            while(1)
            {
                qint16 dim = abs(pointnext.x() - pointpre.x()) + abs(pointnext.y() - pointpre.y());
                if(dim == 1)   //找到相邻点
                {
                    rou->append(new QPoint(pointnext.x(),pointnext.y()));
                    pointpre.setX(pointnext.x());
                    pointpre.setY(pointnext.y());
                    break;
                }
                else
                {
                    if(pointnext.x() == pointpre.x())
                    {
                        if(pointnext.y() > pointpre.y())
                        {
                            pointpre.setY(pointpre.y() + 1);
                        }
                        else
                        {
                            pointpre.setY(pointpre.y() - 1);
                        }
                        rou->append(new QPoint(pointpre.x(),pointpre.y()));
                    }
                    else if(pointnext.y() == pointpre.y())
                    {
                        if(pointnext.x() > pointpre.x())
                        {
                            pointpre.setX(pointpre.x() + 1);
                        }
                        else
                        {
                            pointpre.setX(pointpre.x() - 1);
                        }
                        rou->append(new QPoint(pointpre.x(),pointpre.y()));
                    }
                    else
                    {
                        //qDebug()<<"路径点数据错误";
                        //释放内存
                        foreach (QPoint* var, *rou) {
                            delete var;
                        }
                        rou->clear();
                        delete rou;

                        return nullptr;
                    }

                }
            }
        }
        return rou;

    }
    else
    {
        return nullptr;
    }
}

void Maps::SetUp_RouteList()
{
    QList<QPoint *> *route0 = new QList<QPoint *>;
    route0->append(new QPoint(0,0));    
    route0->append(new QPoint(10,0));
    route0->append(new QPoint(10,10));
    route0->append(new QPoint(15,10));
    route0->append(new QPoint(15,13));
    this->Route_List->append(MakeRouteFunc(route0));

    QList<QPoint *> *route1 = new QList<QPoint *>;
    route1->append(new QPoint(0,19));
    route1->append(new QPoint(0,10));
    route1->append(new QPoint(10,10));
    route1->append(new QPoint(15,10));
    route1->append(new QPoint(15,15));
    this->Route_List->append(MakeRouteFunc(route1));

    QList<QPoint *> *route2 = new QList<QPoint *>;
    route2->append(new QPoint(19,10));
    route2->append(new QPoint(10,10));
    route2->append(new QPoint(10,0));
    route2->append(new QPoint(0,0));
    this->Route_List->append(MakeRouteFunc(route2));


    QList<QPoint *> *route3 = new QList<QPoint *>;
    route3->append(new QPoint(19,0));
    route3->append(new QPoint(10,0));
    route3->append(new QPoint(10,18));
    this->Route_List->append(MakeRouteFunc(route3));

}

void Maps::SetUp_RouteList2()
{
    int m_route0[] = {0,1,2,3,4,5,6,7,8,9};
     AddP2R(m_route0);

    int m_route1[] = {10,11,12,13,4,15,16,17,18,19};
     AddP2R(m_route1);

    int m_route2[] = {20,21,22,3,4,5,26,27,28,29};
      AddP2R(m_route2);

    int m_route3[] = {30,1,32,33,34,35,63,7,8,39};
      AddP2R(m_route3);
}


void Maps::SetUp_RouteList3(vector<int> &route)
{
    QList<QPoint> route_list;
    route_list.clear();

   int route_num = route[0];
   int route_size = route.size();
   route_list.reserve(route_size);

   for(int i=1; i< route_size; i++)
   {
       int node_serial = route[i];
       int node_x = node_serial/map_height;
       int node_y = node_serial%map_height;
       route_list.append(QPoint(node_x,node_y));
   }

   std::cout<<"route num "<<route_size;
   map<int,QList<QPoint> >::iterator it = this->Route_map->find(route_num);
   if(it == this->Route_map->end())
   {
       std::pair< std::map< int,QList<QPoint>  >::iterator,bool > ret;
       ret = this->Route_map->insert(map<int,QList<QPoint> >::value_type(route_num,route_list));
       if( ret.second ){
           std::cout<<"success1"<<std::endl;
       }
       else{
           std::cout<<"failed1"<<std::endl;
       }
   }
   else
   {
       std::pair< std::map< int,QList<QPoint>  >::iterator,bool > ret;
       this->Route_map->erase(route_num);
       this->Route_map->insert(map<int,QList<QPoint> >::value_type(route_num,route_list));
       ret = this->Route_map->insert(map<int,QList<QPoint> >::value_type(route_num,route_list));
       if( ret.second ){
           std::cout<<"success2"<<std::endl;
       }
       else{
           std::cout<<"failed2"<<std::endl;
       }
   }

}

void Maps::SetUp_RobotTask()
{

    //********************任务0******************/
    QList<socketThread::RobotTask*> *task0 = new QList<socketThread::RobotTask*>;

    socketThread::RobotTask* task0_0 = new socketThread::RobotTask;
    task0_0->tasktype = socketThread::Go;
    task0_0->taskval.Route_Serial = 0;
    task0->append(task0_0);

    socketThread::RobotTask* task0_1 = new socketThread::RobotTask;
    task0_1->tasktype = socketThread::Wait;
    task0_1->taskval.Wait_Cnt = 100;
    task0->append(task0_1);
    Robot_Task->append(task0);

    //********************任务1******************/
    QList<socketThread::RobotTask*> *task1 = new QList<socketThread::RobotTask*>;

    socketThread::RobotTask* task1_0 = new socketThread::RobotTask;
    task1_0->tasktype = socketThread::Go;
    task1_0->taskval.Route_Serial = 1;
    task1->append(task1_0);

    socketThread::RobotTask* task1_1 = new socketThread::RobotTask;
    task1_1->tasktype = socketThread::Wait;
    task1_1->taskval.Wait_Cnt = 100;
    task1->append(task1_1);
    Robot_Task->append(task1);

    //********************任务2******************/
    QList<socketThread::RobotTask*> *task2 = new QList<socketThread::RobotTask*>;

    socketThread::RobotTask* task2_0 = new socketThread::RobotTask;
    task2_0->tasktype = socketThread::Go;
    task2_0->taskval.Route_Serial = 2;
    task2->append(task2_0);

    socketThread::RobotTask* task2_1 = new socketThread::RobotTask;
    task2_1->tasktype = socketThread::Wait;
    task2_1->taskval.Wait_Cnt = 100;
    task2->append(task2_1);
    Robot_Task->append(task2);

    //********************任务3******************/
    QList<socketThread::RobotTask*> *task3 = new QList<socketThread::RobotTask*>;

    socketThread::RobotTask* task3_0 = new socketThread::RobotTask;
    task3_0->tasktype = socketThread::Go;
    task3_0->taskval.Route_Serial = 3;
    task3->append(task3_0);

    socketThread::RobotTask* task3_1 = new socketThread::RobotTask;
    task3_1->tasktype = socketThread::Wait;
    task3_1->taskval.Wait_Cnt = 100;
    task3->append(task3_1);
    Robot_Task->append(task3);
}


void Maps::ClearMapData()
{
    QList<PointInfo*>::iterator it_map;
    for(it_map=Map_List->begin();it_map != Map_List->end();it_map++)
    {
        PointInfo* pvar = *it_map;
        pvar->OccupyItem->clear();
        pvar->PredictItem->clear();
    }
}

//初始化地图
void Maps::MapListInit()
{
    for(quint16 i =0; i < this->map_height;i++)
        for(quint16 j=0; j< this->map_width; j++)
        {
            PointInfo *pinfo = new PointInfo;
            ZYVVULIST<PointItem,10> *pitemoccu = new ZYVVULIST<PointItem,10>;
            ZYVVULIST<PointItem,10> *pitempred = new ZYVVULIST<PointItem,10>;

            pinfo->OccupyItem = pitemoccu;
            pinfo->PredictItem = pitempred;
            Map_List->append(pinfo);
        }
#if 1
    //SetUp_RouteList2();
#else
    SetUp_RouteList();
#endif
    //SetUp_RobotTask();
}

