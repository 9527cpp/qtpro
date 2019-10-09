#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include "myhandle.h"



class MyThread : public QThread
{
public:
    void run()//这里的run 是覆盖QThread方法
    {
        int i = 0;

        while(1)
        {
            qDebug()<<i++<<endl;
            sleep(1);
        }
    }

};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MyThread t;
    t.start();

    QThread tt;
    MyHandle h;
    const QMetaObject * obj = h.metaObject();
    qDebug()<<obj->className()<<endl;
    qDebug()<<obj->methodCount()<<endl;
    h.moveToThread(&tt);
    QObject::connect(&tt,SIGNAL(started()),&h,SLOT(run()));
    tt.start();

    /*添加一行注释*/

    return a.exec();
}
