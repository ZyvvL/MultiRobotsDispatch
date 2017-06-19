#include "thread.h"

int Thread::start()
{
        if(pthread_create(&pid,NULL,start_thread,(void *)this) != 0)                 //创建一个线程(必须是全局函数)
        {
            return -1;
        }
        return 0;
}

void* Thread::start_thread(void *arg) //静态成员函数只能访问静态变量或静态函数，通过传递this指针进行调用
{
    Thread *ptr = (Thread *)arg;
    ptr->run();                                                                                                //线程的实体是run
}
