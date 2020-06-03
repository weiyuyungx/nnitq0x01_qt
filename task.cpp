#include "task.h"
#include<qdebug.h>
#include<QString>
#include<QThread>
#include<QDir>
#include<QFileInfo>
#include <windows.h>
task::task()
{

}

//接收信号
//@path 目录list
void task::receive(QStringList paths)
{
    int file_num = 0;
    int empty_dir = 0;
    QStringList new_list = QStringList();


    int paths_size = paths.size();


    for(int i =0;i<paths_size;i++)
    {
        QString path = paths.at(i);


        QDir* dir = new  QDir(path);

        dir->setFilter(QDir::Files | QDir::Dirs| QDir::NoDotAndDotDot );

       QFileInfoList file = dir->entryInfoList();

       int size = file.size();


       if (size == 0)
       {
          empty_dir ++;
       }
       else
       {
             for(int j =0;j<size;j++)
             {

                QFileInfo one = file.at(j);

                if (one.isFile() || one.isSymLink())
                {
                   file_num ++;
                }
                else
                {
                    //new_list.append(one.filePath());

                    //再找一层


                            QDir* sondir = new  QDir(one.filePath());

                            sondir->setFilter(QDir::Files | QDir::Dirs| QDir::NoDotAndDotDot );

                           QFileInfoList sonfile = sondir->entryInfoList();

                           int sonsize = sonfile.size();

                           if (sonsize == 0)
                           {
                              empty_dir ++;
                           }
                           else
                           {
                               for(int k =0;k<sonsize;k++)
                               {

                                  QFileInfo sonone = sonfile.at(k);

                                  if (sonone.isFile() || sonone.isSymLink())
                                  {
                                     file_num ++;
                                  }
                                  else
                                  {
                                       new_list.append(sonone.filePath());
                                  }
                               }
                           }





                    //再找一层ned
                }
             }
       }

    }//end for


    //发信号
    emit finishmission(new_list ,empty_dir ,file_num );
}






