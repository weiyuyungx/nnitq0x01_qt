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
    this->thread_num = 4; //4个线程最合适
    this->total_i =0;

    //初始化线程与任务
    for(int i =0 ; i < this->thread_num;i ++)
    {
        task* tk = new task();

        //完成任务时的信号
        QObject::connect(tk, SIGNAL(finishmission(QStringList,int ,int,QString)), this, SLOT(acceptmission(QStringList,int ,int,QString)));


        //发送新任务时的信号
        if (i == 0)
        {
           QObject::connect(this, SIGNAL(send_00(QString)), tk, SLOT(receive(QString)));
        }
        else if (i == 1)
        {
           QObject::connect(this, SIGNAL(send_01(QString)), tk, SLOT(receive(QString)));
        }
        else if (i == 2)
        {
           QObject::connect(this, SIGNAL(send_02(QString)), tk, SLOT(receive(QString)));
        }
        else if (i == 3)
        {
           QObject::connect(this, SIGNAL(send_03(QString)), tk, SLOT(receive(QString)));
        }

        QThread* pthread = new QThread();

        tk->moveToThread(pthread);
        pthread->start();

    }


    //执行第一个任务
    this->trysend(base_dir);

}

void begin:: acceptmission(QStringList files , int empty_dir ,int file_num ,QString dir)
{
    this->running_mission--;  //回来一个任务

    this->empty_dir += empty_dir;
    this->file_num += file_num;

    int size = files.size();

    if (size > 0)
    {
        //有货的目录
        for(int i = 0 ;i < size;i ++)
        {
           QString at_i =  files.at(i);

           if (at_i == "." || at_i == "..")
           {
               continue;
           }
           this->trysend(QString("%1/%2").arg(dir).arg(at_i));
        }
    }

   // qDebug() << QString("running_mission:%1").arg(this->running_mission);
   // qDebug() << QString("dir:%1").arg(dir);


    //结束条件
     this->out();

}

void begin:: out()
{
  //  qDebug() << QString("file_num:%1").arg(this->file_num);

    if (this->running_mission <= 0)
    {
        qint64 end_time = QDateTime::currentMSecsSinceEpoch();

        float useing_time = (end_time - this->begin_time) ;//单位毫秒


        qDebug() << QString("path:%1").arg(this->base_dir);
        qDebug() << QString("file_num:%1").arg(this->file_num);

        qDebug() << QString("empty_dir:%1").arg(this->empty_dir);

        qDebug() << QString("useing_time:%1 (s)").arg(QString::number(useing_time/1000,'f',3));

        qDebug() << QString("speed:%1 (f/s)").arg((int)((this->empty_dir + this->file_num)*1000/(useing_time)) );
    }
}


//尝试一个发送
void begin::trysend(QString path)
{
    this->running_mission++;
    this->total_i ++;

    int index = this->total_i % this->thread_num; //轮询

    if (index == 0)
    {
        emit send_00(path);
    }
    else if (index == 1)
    {
        emit send_01(path);
    }
    else if (index == 2)
    {
        emit send_02(path);
    }
    else if (index == 3)
    {
      emit send_03(path);
    }

}
