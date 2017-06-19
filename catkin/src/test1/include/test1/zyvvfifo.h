#ifndef ZYVVFIFO_H
#define ZYVVFIFO_H

#include<stdint.h>
#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

template<class T,int len> class ZYVVFIFO
{
public:
    ZYVVFIFO();

    ~ZYVVFIFO();
    bool append(T &item);
    bool takeFirst(T &item);
    bool removeFirst();
    bool value(T &item,uint16_t i);
    bool valueFirst(T &item);
    bool valueLast(T &item);
    void clear();         //清除所有元素
    bool isEmpty();
    bool isFull();
    size_t size();        //return the size of fifo mem
    uint16_t ItemNum;      //存在的元素个数
private:
    uint16_t FirstPtr;     //第一个元素位置
    uint16_t LastPtr;      //最后一个元素后的位置
    uint16_t ListLen;      //列表长度 （实际创建 ListLen +1个元素）

    vector<T> *ItemList;

};


template<class T,int len>
ZYVVFIFO<T,len>::ZYVVFIFO()
{

    this->ListLen = len;
    this->ItemList = new vector<T>;
    this->ItemList->resize(this->ListLen + 1);   //设置列表大小
    this->FirstPtr = 0;
    this->LastPtr = 0;
    this->ItemNum = 0;

}


template<class T,int len>
ZYVVFIFO<T,len>::~ZYVVFIFO()
{
    this->ItemList->clear();
    delete this->ItemList;
}

template<class T,int len>
bool ZYVVFIFO<T,len>::append(T &item)
{
    if(this->isFull() == false)
    {
        (*(this->ItemList))[this->LastPtr] = item;
        this->ItemNum++;
        this->LastPtr = (this->LastPtr + 1)%(this->ListLen + 1);
        return true;
    }
    else
    {
        return false;
    }

}


template<class T,int len>
bool ZYVVFIFO<T,len>::takeFirst(T &item)
{
    if(this->isEmpty() == false)
    {
        item = (*(this->ItemList))[this->FirstPtr];
        this->FirstPtr = (this->FirstPtr + 1)%(this->ListLen + 1);  //移除第一项
        this->ItemNum--;
        return true;
    }
    else
    {
        return false;
    }
}

template<class T,int len>
bool ZYVVFIFO<T,len>::value(T &item, uint16_t i)
{
    if(i <= this->ItemNum)
    {
        item = (*(this->ItemList))[i];
        return true;
    }
    else
    {
        return false;
    }
}

template<class T,int len>
bool ZYVVFIFO<T,len>::valueFirst(T &item)
{
    if(this->isEmpty() == false)
    {
        item = (*(this->ItemList))[this->FirstPtr];
        return true;
    }
    else
    {
        return false;
    }
}

template<class T,int len>
bool ZYVVFIFO<T,len>::valueLast(T &item)
{
    if(this->isEmpty() == false)
    {
        item = (*(this->ItemList))[(this->LastPtr + this->ListLen)%(this->ListLen + 1)];
        return true;
    }
    else
    {
        return false;
    }
}


template<class T,int len>
bool ZYVVFIFO<T,len>::removeFirst()
{
    if(this->isEmpty() == false)
    {
        this->FirstPtr = (this->FirstPtr + 1)%(this->ListLen + 1);  //移除第一项
        this->ItemNum--;
        return true;
    }
    else
    {
        return false;
    }
}



template<class T,int len>
bool ZYVVFIFO<T,len>::isEmpty()
{
    if(this->FirstPtr == this->LastPtr)
    {
        this->ItemNum = 0;
        return true;
    }
    else
    {
        return false;
    }
}

template<class T,int len>
bool ZYVVFIFO<T,len>::isFull()
{
    if(((this->LastPtr + 1)%(this->ListLen + 1)) == this->FirstPtr)
    {
        this->ItemNum = this->ListLen;
        return true;
    }
    else
    {
        return false;
    }
}


template<class T,int len>
void ZYVVFIFO<T,len>::clear()
{
    this->FirstPtr = 0;
    this->LastPtr = 0;
    this->ItemNum = 0;
}

template<class T,int len>
size_t ZYVVFIFO<T,len>::size()
{
    return this->ItemNum;
}

#endif // ZYVVFIFO_H
