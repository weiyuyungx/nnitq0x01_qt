#ifndef TASK_H
#define TASK_H
#endif


#include<QString>
#include<QStringList>
#include<QDir>
class task : public QObject
{
    Q_OBJECT

public:
    task();

signals:
     void finishmission(QStringList ,int ,int ,QString);
     void getit(int);

public slots:
     void receive(QString);


};


