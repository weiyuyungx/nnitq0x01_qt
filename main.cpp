#include <QCoreApplication>
#include<begin.h>
#include <windows.h>
#include<qdebug.h>
#include<QString>
#include<QDateTime>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    begin* bg = new begin();
    bg->gogogo();

    return a.exec();
}
