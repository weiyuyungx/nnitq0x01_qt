#ifndef TASK_H
#define TASK_H
#endif
#include<QString>
#include<QStringList>
#include<QDir>
#include<QFileInfo>
class task : public QObject
{
    Q_OBJECT

public:
    task();

signals:
     void finishmission(QStringList ,int ,int );

public slots:
     void receive(QStringList);
};


