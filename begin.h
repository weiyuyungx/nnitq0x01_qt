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
     void trysend(QStringList path);

signals:
     void send_00(QStringList);
     void send_01(QStringList);
     void send_02(QStringList);
     void send_03(QStringList);
     void send_04(QStringList);
     void send_05(QStringList);
     void send_06(QStringList);
     void send_07(QStringList);


public slots:
     void acceptmission(QStringList,int ,int);




};
