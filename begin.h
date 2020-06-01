#ifndef BEGIN_H
#define BEGIN_H
#endif // begin


#include <QObject>
#include<QString>
#include<QDateTime>
#include<QStringList>
#include<QThread>
class begin : public QObject
{
    Q_OBJECT
    QString base_dir;
    int file_num;
    int empty_dir;
    int running_mission;
    int thread_num;


public:
    explicit begin(QObject *parent = 0);
     void  gogogo();
     void  out();
     qint64 begin_time;
     int total_i;
     void trysend(QString path);

signals:
     void send_00(QString);
     void send_01(QString);
     void send_02(QString);
     void send_03(QString);

public slots:
     void acceptmission(QStringList,int ,int,QString);



};
