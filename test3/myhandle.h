#ifndef MYHANDLE_H
#define MYHANDLE_H

/// 这个类加了Q_OBJECT宏的话 必须放在头文件中
/// 否则moc会报 找不到元对象 的错
/// 并且放在头文件后 注意 要删除工程下的构建目录再重新构建
/// 否则creator里怎么清除重新构建都是不行的(依然会报错)
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTimer>

class MyHandle:public QObject
{
    Q_OBJECT
public slots:
    void timeFunc()
    {
        qDebug()<<i++<<endl;
    }

    void run()
    {
    #if 0
        int i = 0;
         while(1)
         {
             qDebug()<<i++<<endl;
             QThread::sleep(1);
         }
    #else
        i = 0;
        QTimer* timer = new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(timeFunc()));
        timer->start(1000);
    #endif
    }
private:
    int i;
};

#endif // MYHANDLE_H
