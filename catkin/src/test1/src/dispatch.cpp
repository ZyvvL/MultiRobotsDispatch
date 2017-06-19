#include "dispatch.h"
//#include "myserver.h"
#include "tcp_server.h"
#include "QDebug"
#include "ros/ros.h"

#define foreach Q_FOREACH

DisPatch::DisPatch(tcp_server* server,Maps *maps)
{
    this->my_server = server;
    this->maps = maps;
    this->DisPatch_Info = new ZYVVFIFO<socketThread::RobotDispatchInfo,100>;

}

DisPatch::~DisPatch()
{
    this->DisPatch_Info->clear();
    delete DisPatch_Info;
}


void DisPatch::MapsDataGen()
{
      QList<socketThread*>::iterator it;
      for(it = my_server->ThreadList->begin();it != my_server->ThreadList->end();it++)
      {
         socketThread* var = *it;
         var->IsException = false;
        if((var->Robot_Info->Robot_State == socketThread::Done)||(var->Robot_Info->Task.tasktype == socketThread::Wait))
        {
            //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
            QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径
            quint16 rpos1 = route.at(var->Robot_Info->Robot_Pos).x() + (route.at(var->Robot_Info->Robot_Pos).y())*maps->map_width;   //获取maps坐标位置
            AddItem2Maps(var->Robot_Info,0,1,rpos1);
            return;
        }
        if(var->Robot_Info->Instruct == socketThread::Move)
        {
            if(var->Robot_Info->Robot_State == socketThread::Moving)
            {
                //添加占据点数据到地图
                //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
                QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径
                quint16 rpos1 = route.at(var->Robot_Info->Robot_Pos).x() + (route.at(var->Robot_Info->Robot_Pos).y())*maps->map_width;   //获取maps坐标位置
                AddItem2Maps(var->Robot_Info,0,1,rpos1);

                if(var->Robot_Info->Robot_Pos < (route.size() - 1))   //若不是最后一点
                {
                    quint16 rpos0 = route.at(var->Robot_Info->Robot_Pos + 1).x() + (route.at(var->Robot_Info->Robot_Pos + 1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,0,rpos0);
                }

                if(var->Robot_Info->Robot_Pos > 0)                  //若不是第一点
                {
                    quint16 rpos2 = route.at(var->Robot_Info->Robot_Pos - 1).x() + (route.at(var->Robot_Info->Robot_Pos - 1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,2,rpos2);
                }

                //填充预测点到地图
                if(var->Robot_Info->Robot_Pos < (route.size() - 2))
                    for(quint16 i = (var->Robot_Info->Robot_Pos + 2);i < route.size();i++)
                    {
                        quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                        int s_pos = i- (var->Robot_Info->Robot_Pos + 2);
                        AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                    }

            }
            else  if(var->Robot_Info->Robot_State == socketThread::Paused) //Paused 占用3点
            {
                //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
                QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径路径

                quint16 rpos2 = route.at(var->Robot_Info->Robot_Pos).x() + (route.at(var->Robot_Info->Robot_Pos).y())*maps->map_width;   //获取maps坐标位置
                AddItem2Maps(var->Robot_Info,0,2,rpos2);

                if(var->Robot_Info->Robot_Pos <= (route.size() - 4))   //保证四个点
                {
                    quint16 rpos0 = route.at(var->Robot_Info->Robot_Pos + 2).x() + (route.at(var->Robot_Info->Robot_Pos + 2).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,0,rpos0);

                    quint16 rpos1 = route.at(var->Robot_Info->Robot_Pos + 1).x() + (route.at(var->Robot_Info->Robot_Pos + 1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,1,rpos1);

                    //填充预测点到地图
                    for(quint16 i = (var->Robot_Info->Robot_Pos + 3);i < route.size();i++)
                    {
                        quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位
                        int s_pos = i- (var->Robot_Info->Robot_Pos + 3);
                        AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                    }

                }
                else
                {
                    qDebug()<<"Paused -- Move Error!";
                    var->IsException = true;
                    socketThread::RobotDispatchInfo dispatch_info;
                    dispatch_info.control = socketThread::CoNone;
                    dispatch_info.Robot_Serial = var->Robot_Info->Robot_Serial;
                    dispatch_info.Instruct = socketThread::Pause;
                    dispatch_info.Task.taskval.PausePos = var->Robot_Info->Robot_Pos;
                    this->DisPatch_Info->append( dispatch_info);
                }

            }else
            {
                qDebug()<<"Move_Instruct Error!";
            }
        }
        else
        {
            if(var->Robot_Info->Robot_State == socketThread::Moving)
            {
                //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
                QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径

                quint16 rpos1 = route.at(var->Robot_Info->Robot_Pos).x() + (route.at(var->Robot_Info->Robot_Pos).y())*maps->map_width;   //获取maps坐标位置 当前的点
                AddItem2Maps(var->Robot_Info,0,1,rpos1);

                if((var->Robot_Info->PausePos - var->Robot_Info->Robot_Pos) == 1)  //暂停点超前一点
                {
                    quint16 rpos0 = route.at(var->Robot_Info->Robot_Pos + 1).x() + (route.at(var->Robot_Info->Robot_Pos + 1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,0,rpos0);

                    //填充预测点到地图
                    if(var->Robot_Info->Robot_Pos < (route.size() - 2))
                        for(quint16 i = (var->Robot_Info->Robot_Pos + 2);i < route.size();i++)
                        {
                            quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                            int s_pos = i- (var->Robot_Info->Robot_Pos + 2);
                            AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                        }

                }
                else if(var->Robot_Info->PausePos == var->Robot_Info->Robot_Pos)
                {
                    //填充预测点到地图
                    if(var->Robot_Info->Robot_Pos < (route.size() - 1))
                        for(quint16 i = (var->Robot_Info->Robot_Pos + 1);i < route.size();i++)
                        {
                            quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                            int s_pos = i- (var->Robot_Info->Robot_Pos + 1);
                            AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                        }
                }
                else
                {
                    qDebug("PausePos Error! Pause - Moving %d -- %d",var->Robot_Info->Robot_Pos,var->Robot_Info->PausePos);
                    var->IsException = true;
                    socketThread::RobotDispatchInfo dispatch_info;
                    dispatch_info.control = socketThread::CoNone;
                    dispatch_info.Robot_Serial = var->Robot_Info->Robot_Serial;
                    dispatch_info.Instruct = socketThread::Pause;
                    dispatch_info.Task.taskval.PausePos = var->Robot_Info->Robot_Pos;
                    this->DisPatch_Info->append( dispatch_info);
                }

                if(var->Robot_Info->Robot_Pos > 0)                  //若不是第一点
                {
                    quint16 rpos2 = route.at(var->Robot_Info->Robot_Pos - 1).x() + (route.at(var->Robot_Info->Robot_Pos - 1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,2,rpos2);
                }


            }
            else   //Paused
            {
                //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
                QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径S

                quint16 rpos2 = route.at(var->Robot_Info->Robot_Pos).x() + (route.at(var->Robot_Info->Robot_Pos).y())*maps->map_width;   //获取maps坐标位置
                AddItem2Maps(var->Robot_Info,0,2,rpos2);

                //若有其他占据点
                if((var->Robot_Info->PausePos - var->Robot_Info->Robot_Pos) == 1)
                {
                    quint16 rpos0 = route.at(var->Robot_Info->Robot_Pos+1).x() + (route.at(var->Robot_Info->Robot_Pos+1).y())*maps->map_width;   //获取maps坐标位置
                    AddItem2Maps(var->Robot_Info,0,0,rpos0);

                    //填充预测点到地图
                    if(var->Robot_Info->Robot_Pos < (route.size() - 2))
                        for(quint16 i = (var->Robot_Info->Robot_Pos + 2);i < route.size();i++)
                        {
                            quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                            int s_pos = i- (var->Robot_Info->Robot_Pos + 2);
                            AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                         }
                    //qDebug()<<"Pause - Paused -1";
                }else if((var->Robot_Info->PausePos - var->Robot_Info->Robot_Pos) == 0)
                    {
                        //填充预测点到地图
                        if(var->Robot_Info->Robot_Pos < (route.size() - 1))
                        for(quint16 i = (var->Robot_Info->Robot_Pos + 1);i < route.size();i++)
                        {
                            quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                            int s_pos = i- (var->Robot_Info->Robot_Pos + 1);
                            AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                        }
                        //qDebug()<<"Pause - Paused -2";
                }else if((var->Robot_Info->PausePos - var->Robot_Info->Robot_Pos) == 2)
                    {
                        quint16 rpos0 = route.at(var->Robot_Info->Robot_Pos+2).x() + (route.at(var->Robot_Info->Robot_Pos+2).y())*maps->map_width;   //获取maps坐标位置
                        AddItem2Maps(var->Robot_Info,0,0,rpos0);

                        quint16 rpos1 = route.at(var->Robot_Info->Robot_Pos+1).x() + (route.at(var->Robot_Info->Robot_Pos+1).y())*maps->map_width;   //获取maps坐标位置
                        AddItem2Maps(var->Robot_Info,0,1,rpos1);

                        //填充预测点到地图
                        if(var->Robot_Info->Robot_Pos < (route.size() - 3))
                        for(quint16 i = (var->Robot_Info->Robot_Pos + 3);i < route.size();i++)
                        {
                            quint16 ppos = route.at(i).x() + (route.at(i).y())*maps->map_width;   //获取maps坐标位置
                            int s_pos = i- (var->Robot_Info->Robot_Pos + 3);
                            AddItem2Maps(var->Robot_Info,1,s_pos,ppos);
                        }
                        //qDebug()<<"Pause - Paused -3";
                }
                    else {
                        qDebug()<<"PausePos Error! Pause - Paused";
                        var->IsException = true;
                        socketThread::RobotDispatchInfo dispatch_info;
                        dispatch_info.control = socketThread::CoNone;
                        dispatch_info.Robot_Serial = var->Robot_Info->Robot_Serial;
                        dispatch_info.Instruct = socketThread::Pause;
                        dispatch_info.Task.taskval.PausePos = var->Robot_Info->Robot_Pos;
                        this->DisPatch_Info->append( dispatch_info);
                    }

                }

            }
    }

}


bool DisPatch::OccupyDetect()
{
    QList<Maps::PointInfo*>::iterator it;
    for(it = maps->Map_List->begin();it != maps->Map_List->end();it++)
    {
        Maps::PointInfo* pvar = *it;
        if(pvar->OccupyItem->size() > 1)
        {
            //qDebug("占据点发送冲突 -- %d",i);
            Maps::PointItem item;
            for(int j=0; j< pvar->OccupyItem->size();j++)
            {
                pvar->OccupyItem->Value(item,j);
                qDebug("占据点：%d",item.robot_info->Robot_Serial);
            }

            return false;
        }
    }
    return true;

}

bool DisPatch::DisPatchInfoGen()
{
    bool IsError = false;
    QList<socketThread*>::iterator it;
    for(it=my_server->ThreadList->begin();it != my_server->ThreadList->end();it++)
    {
           socketThread* var = *it;
           if(var->IsException == true)
               continue;
           //QList<QPoint*> *route = maps->Route_List->at(var->Robot_Info->Route_Serial);  //获取路径
           QList<QPoint> route = maps->Route_map->at(var->Robot_Info->Route_Serial);      //获取路径

           qint16 FirsrtPredP = -1;        //第一个预测点位置
           quint16 LastOccupyP;            //最后一个占据点位置
           ZYVVULIST<Maps::PointItem,10> collisionlist;         //预测点冲突列表
           ZYVVULIST<Maps::PointItem,10> collisison_dislist;     //预测点冲突列表
           bool IsPause = false;
           socketThread::RobotDispatchInfo dispatch_info;
           dispatch_info.control = socketThread::CoNone;
           dispatch_info.Robot_Serial = var->Robot_Info->Robot_Serial;
           Maps::PointInfo* Fp_point_info;    //第一个预测点信息
           qDebug("Disp_Serial: %d",dispatch_info.Robot_Serial);
           //获取第一个预测点
           if(var->Robot_Info->Instruct == socketThread::Move)
           {
                if(var->Robot_Info->Robot_State == socketThread::Moving)
                {
                    if(var->Robot_Info->Robot_Pos >= (route.size() - 2))    //最后两点 无预测点
                    {
                        FirsrtPredP = -1;
                        LastOccupyP = route.size() -1;
                        qDebug()<<"FirsrtPredP 1";
                    }
                    else
                    {
                        FirsrtPredP = var->Robot_Info->Robot_Pos + 2;
                        LastOccupyP = FirsrtPredP -1;
                        qDebug()<<"FirsrtPredP 2";
                    }
                }
                else
                {
                    if(var->Robot_Info->Robot_Pos >= (route.size() - 3))
                    {
                        FirsrtPredP = -1;
                        LastOccupyP = route.size() - 1;
                        qDebug()<<"FirsrtPredP 3";
                    }
                    else
                    {
                        FirsrtPredP = var->Robot_Info->Robot_Pos + 3;
                        LastOccupyP = FirsrtPredP -1;
                        qDebug()<<"FirsrtPredP 4";
                    }

                }
           }
           else
           {
               if(var->Robot_Info->Robot_State == socketThread::Moving)
               {
                    if(var->Robot_Info->PausePos < (route.size() -1))
                    {
                        FirsrtPredP = var->Robot_Info->PausePos + 1;
                        LastOccupyP = FirsrtPredP -1;
                        qDebug()<<"FirsrtPredP 5";
                    }
                    else
                    {
                        FirsrtPredP = -1;
                        LastOccupyP = var->Robot_Info->PausePos;
                        qDebug()<<"FirsrtPredP 6";
                    }
               }
               else
               {
                   if(var->Robot_Info->PausePos < (route.size() -1))
                   {
                       FirsrtPredP = var->Robot_Info->PausePos + 1;
                       LastOccupyP = FirsrtPredP -1;
                       qDebug()<<"FirsrtPredP 7";
                   }
                   else
                   {
                       FirsrtPredP = -1;
                       LastOccupyP = var->Robot_Info->PausePos;
                       qDebug()<<"FirsrtPredP 8";
                   }
               }
           }

           if(FirsrtPredP < 0)   //若没有预测点 则 Pause
           {
                dispatch_info.Instruct = socketThread::Pause;
                dispatch_info.Task.taskval.PausePos = LastOccupyP;
                qDebug()<<"Pause 7__"<<dispatch_info.Task.taskval.PausePos;

           }
           else
           {
                Fp_point_info = this->maps->Map_List->at(route.at(FirsrtPredP).x() + route.at(FirsrtPredP).y()*maps->map_width);
                if(Fp_point_info->OccupyItem->isEmpty() == false)   //预测点被占 则 pause
                {
                    dispatch_info.Instruct = socketThread::Pause;
                    dispatch_info.Task.taskval.PausePos = LastOccupyP;
                    qDebug()<<"Pause 6";
                }
                else if(Fp_point_info->PredictItem->size() == 1)   //没有其他预测点占用
                {
                    if(var->Robot_Info->Robot_State == socketThread::Moving)
                    {
                        if(FirsrtPredP >= (var->Robot_Info->Robot_Pos + 2))
                        {
                             dispatch_info.Instruct = socketThread::Move;
                             qDebug()<<"Move 1";
                        }
                        else
                        {
                            dispatch_info.Instruct = socketThread::Pause;
                            dispatch_info.Task.taskval.PausePos = FirsrtPredP;
                            qDebug()<<"Pause 5";
                        }
                    }
                    else   //paused
                    {
                        if(FirsrtPredP >= (var->Robot_Info->Robot_Pos + 3))
                        {
                             dispatch_info.Instruct = socketThread::Move;
                             qDebug()<<"Move 2";
                        }
                        else
                        {
                            dispatch_info.Instruct = socketThread::Pause;
                            dispatch_info.Task.taskval.PausePos = FirsrtPredP;
                            qDebug()<<"Pause 4";
                        }
                    }
                }
                else   //预测点冲突处理
                {

                    //复制冲突的预测点数据 本点除外
                    for(quint16 j =0; j < Fp_point_info->PredictItem->size();j++)
                    {
                        Maps::PointItem item;
                        Fp_point_info->PredictItem->Value(item,j);
                        if(item.robot_info->Robot_Serial != var->Robot_Info->Robot_Serial)
                        {
                            Maps::PointItem pf;
                            pf.robot_info = item.robot_info;
                            pf.pos = item.pos;
                            collisison_dislist.append(pf);
                        }
                    }

                    for(quint16 i= FirsrtPredP+1; i < route.size();i++)
                    {
                        Maps::PointInfo *ptemp = this->maps->Map_List->at(route.at(i).x() + route.at(i).y()*maps->map_width);
                        for(int q=0; q < collisison_dislist.size();q++)
                        {
                            //获取冲突点数据
                            Maps::PointItem collItem;
                            collisison_dislist.Value(collItem,q);

                            //判断var是否在占据点中
                            if(IsItemInList(&collItem,ptemp->OccupyItem) != -1)  //若冲突点与占据点冲突
                            {
                                Maps::PointInfo *qtemp = this->maps->Map_List->at(route.at(LastOccupyP).x() + route.at(LastOccupyP).y()*maps->map_width);  //获取最后占据点信息
                                if(IsItemInList(&collItem,qtemp->OccupyItem) != -1)   //占据点冲突 调度失败
                                {
                                    IsError = true;
                                }

                                //更新列表数据
                                collItem.pos = -1;
                                collisison_dislist.Update(collItem,q);

                                //复制列表所有数据
                                for(int u =0; u < collisison_dislist.size();u++)
                                {
                                    Maps::PointItem reItem;
                                    collisison_dislist.Value(reItem,u);
                                    collisionlist.append(reItem);
                                }
                                //清空列表
                                collisison_dislist.clear();
                                break;

                            }
                            else
                            {
                                 int item_num = IsItemInList(&collItem,ptemp->PredictItem);
                                 if(item_num == -1)
                                 {
                                     collisionlist.append(collItem);
                                     collisison_dislist.RemoveAt(q);
                                 }
                                 else   //记录冲突预测点的最小距离值
                                 {
                                    Maps::PointItem ppoint;
                                    ptemp->PredictItem->Value(ppoint,item_num);
                                    if(ppoint.pos < collItem.pos)
                                        collItem.pos = ppoint.pos;

                                    collisison_dislist.Update(ppoint,q);
                                 }

                            }
                            if(collisison_dislist.isEmpty() == true)
                                break;

                        }
                        if(collisison_dislist.isEmpty() == true)
                            break;
                     }

                  //释放内存  //查询距离列表 判断是否为最短
                  for(int g =0; g< collisionlist.size();g++)
                  {
                      Maps::PointItem yvar;
                      collisionlist.Value(yvar,g);

                      if(IsPause == false)
                      {
                          if(yvar.pos > 0)
                              IsPause = false;
                          else if(yvar.pos == -1)   //预测点被占据
                              IsPause = true;
                          else                       //预测点0位置冲突
                          {
                            Maps::PointInfo *qtemp = this->maps->Map_List->at(route.at(LastOccupyP).x() + route.at(LastOccupyP).y()*maps->map_width);  //获取最后占据点信息
                            if(IsItemInList(&yvar,qtemp->OccupyItem) != -1)
                            {
                                if(yvar.robot_info->Robot_Priority > var->Robot_Info->Robot_Priority)       //优先级较小时 则 暂停
                                    IsPause = true;
                                else if(yvar.robot_info->Robot_Priority < var->Robot_Info->Robot_Priority)
                                    IsPause = false;
                                else
                                {
                                    if(yvar.robot_info->Robot_Serial > var->Robot_Info->Robot_Serial)
                                        IsPause = true;
                                    else
                                        IsPause = false;
                                }
                            }
                            else
                            {
                                 IsPause = false;
                            }

                          }
                      }
                      else{;}
                  }

                  collisionlist.clear();

                  if(IsPause == true)
                  {
                      dispatch_info.Instruct = socketThread::Pause;
                      dispatch_info.Task.taskval.PausePos = LastOccupyP;
                      qDebug()<<"Pause 3";
                  }
                  else
                  {
                      if(var->Robot_Info->Robot_State == socketThread::Moving)
                      {
                          if(FirsrtPredP >= (var->Robot_Info->Robot_Pos + 2))
                          {
                               dispatch_info.Instruct = socketThread::Move;
                          }
                          else
                          {
                              dispatch_info.Instruct = socketThread::Pause;
                              dispatch_info.Task.taskval.PausePos = FirsrtPredP;
                              qDebug()<<"Pause 2";
                          }
                      }
                      else   //paused
                      {
                          if(FirsrtPredP >= (var->Robot_Info->Robot_Pos + 3))
                          {
                               dispatch_info.Instruct = socketThread::Move;
                          }
                          else
                          {
                              dispatch_info.Instruct = socketThread::Pause;
                              dispatch_info.Task.taskval.PausePos = FirsrtPredP;
                              qDebug()<<"Pause 1";
                          }
                      }
                   }

                }
           }
          this->DisPatch_Info->append( dispatch_info);
    }

    if(IsError == false)
        return true;
    else
        return false;
}


Maps::PointItem *DisPatch::IsItemInList(Maps::PointItem *item, QList<Maps::PointItem *> *itemlist)
{
    QList<Maps::PointItem*>::iterator it;
    for(it=itemlist->begin();it != itemlist->end();it++)
    {
         Maps::PointItem* var = *it;
        if(item->robot_info->Robot_Serial == var->robot_info->Robot_Serial)
            return var;
    }

    return nullptr;
}

int DisPatch::IsItemInList(Maps::PointItem *item, ZYVVULIST<Maps::PointItem,10> *itemlist)
{
    Maps::PointItem pitem;
    for(int i=0; i< itemlist->size(); i++)
    {
        itemlist->Value(pitem,i);
        if(pitem.robot_info->Robot_Serial == item->robot_info->Robot_Serial)
            return i;
    }
    return -1;
}

bool DisPatch::AvoidanceDetect()
{
    this->maps->ClearMapData();   //清除地图数据
    this->MapsDataGen();    //生成地图数据
    if(OccupyDetect() == false)
        return false;
    if(DisPatchInfoGen() == false)
        return false;
    return true;
}

void DisPatch::AddItem2Maps(socketThread::RobotInfo *ptr, quint16 itemtype, qint16 s_pos, quint16 g_pos)
{
    Maps::PointItem pitem;
    pitem.robot_info = ptr;
    pitem.pos = s_pos;
    if(itemtype == 0)
        maps->Map_List->at(g_pos)->OccupyItem->append(pitem);
    else
        maps->Map_List->at(g_pos)->PredictItem->append(pitem);
}

