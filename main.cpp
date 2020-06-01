#include <QCoreApplication>
#include<begin.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    begin* bg = new begin();
    bg->gogogo();




    return a.exec();
}
