#include "task.h"
#include<qdebug.h>
#include<QString>
#include<QThread>
#include<QDir>
#include<QFileInfo>
task::task()
{
}

//接收信号
//@path 可能是目录，文件，链接
void task::receive(QString path)
{
    int file_num = 0;
    int empty_dir = 0;
    QStringList new_list = QStringList();


   QFileInfo* myfile = new  QFileInfo(path);


   if (myfile->isFile())
   {
       file_num ++;
   }
   else if( myfile->isSymLink())
   {
       file_num ++;
   }
   else
   {

       QDir dir(path);
       QStringList files = dir.entryList();

       int size = files.size();

       if (size < 0)
       {
           file_num ++;
       }
       else if (size == 2)
       {
           empty_dir ++;
       }
       else
       {
           new_list = files;
       }
   }
   emit finishmission(new_list,empty_dir ,file_num ,path);
}





