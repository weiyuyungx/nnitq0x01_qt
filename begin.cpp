#include "begin.h"
#include<QDir>
#include<QStringList>
#include<QFileInfo>
#include<QDebug>
#include<task.h>
#include<QObject>
#include<QString>
#include<QThreadPool>
#include<QThread>
#include<QFileInfo>
begin::begin(QObject *parent) : QObject(parent)
{

}

void begin::gogogo()
{
    //初始化数据
     this->begin_time = QDateTime::currentMSecsSinceEpoch();

    this->base_dir = "C:/";
    this->file_num = 0;
    this->empty_dir = 0;
    this->running_mission = 0;
    this->thread_num = 4; //线程数。4个最合适(最多只能写8)
    this->total_i =0;

    //初始化线程与任务
    for(int i =0 ; i < this->thread_num;i ++)
    {
        task* tk = new task();

        //完成任务时的信号(新的)
        QObject::connect(tk, SIGNAL(finishmission(QStringList,int ,int)), this, SLOT(acceptmission(QStringList,int ,int)));


        //发送新任务时的信号
        if (i == 0)
        {
           QObject::connect(this, SIGNAL(send_00(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 1)
        {
           QObject::connect(this, SIGNAL(send_01(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 2)
        {
           QObject::connect(this, SIGNAL(send_02(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 3)
        {
           QObject::connect(this, SIGNAL(send_03(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 4)
        {
           QObject::connect(this, SIGNAL(send_04(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 5)
        {
           QObject::connect(this, SIGNAL(send_05(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 6)
        {
           QObject::connect(this, SIGNAL(send_06(QStringList)), tk, SLOT(receive(QStringList)));
        }
        else if (i == 7)  //最多8个，再多没意义
        {
           QObject::connect(this, SIGNAL(send_07(QStringList)), tk, SLOT(receive(QStringList)));
        }

        //把任务移到一条线程上
        QThread* pthread = new QThread();
        tk->moveToThread(pthread);


       // SetThreadAffinityMask(pthread,2^i);

        pthread->start();

    }


    //执行第一个任务
    QStringList basepaths = QStringList();
    basepaths.append(this->base_dir);
    this->trysend(basepaths);

}

//接收完成一个任务信号
void begin:: acceptmission(QStringList paths , int empty_dir ,int file_num)
{
    this->running_mission--;  //回来一个任务

    this->empty_dir += empty_dir;
    this->file_num += file_num;


    if (paths.size() > 0)
    {
        emit this->trysend(paths);
    }

    this->out();
}



//判断结束
void begin:: out()
{
  //  qDebug() << QString("file_num:%1").arg(this->file_num);

    if (this->running_mission <= 0)
    {
        qint64 end_time = QDateTime::currentMSecsSinceEpoch();

        float useing_time = (end_time - this->begin_time) ;//单位毫秒


         qDebug() << QString("----------------------------------------");
        qDebug() << QString("path:%1").arg(this->base_dir);
        qDebug() << QString("file_num:%1").arg(this->file_num);

        qDebug() << QString("empty_dir:%1").arg(this->empty_dir);

        qDebug() << QString("useing_time:%1 (s)").arg(QString::number(useing_time/1000,'f',3));

        qDebug() << QString("speed:%1 (f/s)").arg((int)((this->empty_dir + this->file_num)*1000/(useing_time)) );
    }
}


//准备一个发送
void begin::trysend(QStringList paths)
{
    this->running_mission++;
    this->total_i ++;

    int index = this->total_i % this->thread_num; //轮询

    if (index == 0)
    {
        emit send_00(paths);
    }
    else if (index == 1)
    {
        emit send_01(paths);
    }
    else if (index == 2)
    {
        emit send_02(paths);
    }
    else if (index == 3)
    {
      emit send_03(paths);
    }
    else if (index == 4)
    {
      emit send_04(paths);
    }
    else if (index == 5)
    {
      emit send_05(paths);
    }
    else if (index == 6)
    {
      emit send_06(paths);
    }
    else if (index == 7)
    {
      emit send_07(paths);
    }
}
