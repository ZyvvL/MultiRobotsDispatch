#ifndef ZYVVULIST_H
#define ZYVVULIST_H


#include<stdint.h>
#include<stdio.h>
#include<algorithm>
#include<QVector>


template<class T,int len> class ZYVVULIST
{

public:
    uint16_t ItemNum;      //存在的元素个数

    typedef struct itemstruct{
        T t;
        int16_t pre;
        int16_t next;
    }ItemStruct;
private:
    uint16_t FirstPtr;     //第一个元素位置
    uint16_t LastPtr;      //最后一个元素后的位置
    uint16_t ListLen;      //列表长度

    QVector<ItemStruct> *ItemList;

public:
    ZYVVULIST()
    {
        this->ListLen = len;
        this->ItemList = new QVector<ItemStruct>;
        this->ItemList->resize(this->ListLen + 1);   //设置列表大小
        for(uint16_t i =1; i < (this->ListLen +1);i++)
        {
            (*(this->ItemList))[i].pre = -1;
            (*(this->ItemList))[i].next = -1;
        }
        (*(this->ItemList))[0].pre = 0;
        (*(this->ItemList))[0].next = 0;
        this->FirstPtr = 0;
        this->LastPtr = 0;
        this->ItemNum = 0;
    }

    ~ZYVVULIST()
    {
        this->ItemList->clear();
        delete this->ItemList;
    }

    bool append(T &item)
    {
        if(this->isFull() == false)
        {
            //获取一个空元素
            for(uint16_t i =1; i < (this->ListLen +1);i++)
            {
                ItemStruct &var = (*(this->ItemList))[i];
                if((var.pre == -1)&&(var.next == -1))
                {
                    if(this->LastPtr == 0)  //空列表
                    {
                        this->FirstPtr = i;
                        //(*(this->ItemList))[this->LastPtr].pre = i;
                    }
                    (*(this->ItemList))[i].pre = this->LastPtr;
                    (*(this->ItemList))[i].next = 0;
                    (*(this->ItemList))[i].t = item;
                    (*(this->ItemList))[this->LastPtr].next = i;
                    this->LastPtr = i;
                    this->ItemNum++;
                    break;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool RemoveAt(uint16_t i)
    {
        if(this->ItemNum > i)
        {
            uint16_t dirnum = this->FirstPtr;
            for(uint16_t j=0; j< i;j++)                    //find the obj node
            {
                dirnum = this->ItemList->at(dirnum).next;
            }

            uint16_t dir_pre = ((*(this->ItemList))[dirnum].pre);
            uint16_t dir_next = ((*(this->ItemList))[dirnum].next);

            if(dirnum == this->FirstPtr)  //if remove the first node,reset FisrtPtr
            {
                this->FirstPtr = dir_next;
            }

            (*(this->ItemList))[dir_pre].next = dir_next;
            (*(this->ItemList))[dir_next].pre = dir_pre;
            (*(this->ItemList))[dirnum].pre = -1;
            (*(this->ItemList))[dirnum].next = -1;
            this->ItemNum--;

            return true;
        }
        else
        {
            return false;
        }
    }

    bool Value(T &item,uint16_t i)
    {
        if(this->ItemNum > i)
        {
            uint16_t dirnum = this->FirstPtr;
            for(uint16_t j=0; j< i;j++)
            {
                dirnum = this->ItemList->at(dirnum).next;
            }

            item = ((*(this->ItemList)))[dirnum].t;
            return true;
        }
        else
        {
            return false;
        }
    }
    void clear()
    {
        for(uint16_t i =1; i < (this->ListLen +1);i++)
        {
            (*(this->ItemList))[i].pre = -1;
            (*(this->ItemList))[i].next = -1;
        }
        (*(this->ItemList))[0].pre = 0;
        (*(this->ItemList))[0].next = 0;
        this->FirstPtr = 0;
        this->LastPtr = 0;
        this->ItemNum = 0;
    }

    bool isEmpty()
    {
        ItemStruct var = (*(this->ItemList))[0];   //get root node
        if(var.next !=0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool isFull()
    {
        bool temp = true;
        for(uint16_t i =1; i < (this->ListLen +1);i++)
        {
            ItemStruct var = (*(this->ItemList))[i];
            if((var.pre == -1)&&(var.next == -1))
            {
                temp = false;
                break;
            }
        }

        return temp;
    }

    int size()
    {
        return this->ItemNum;
    }

    //更新列表数据
    bool Update(T &item,uint16_t i)
    {
        if(this->ItemNum > i)
        {
            uint16_t dirnum = this->FirstPtr;
            for(uint16_t j=0; j< i;j++)
            {
                dirnum = this->ItemList->at(dirnum).next;
            }

            ((*(this->ItemList)))[dirnum].t = item;
            return true;
        }
        else
        {
            return false;
        }
    }
};


#endif // ZYVVULIST_H
