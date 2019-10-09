#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QPicture>
#include <QImage>
#include <QMouseEvent>
#include <QThreadPool>
#include <QTableWidget>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void drawPicture();
    void paintEvent(QPaintEvent* ev);
    void choseFile();
    void start();
protected:
    bool event(QEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::Widget *ui;
    QWidget * wDraw;
    QImage * image;
    QThreadPool *pool;
    QTableWidget * fileListCtl;
};


class MyEvent:public QEvent
{
public:
    MyEvent(QEvent::Type type):QEvent(type){}
    ~MyEvent(){}
    void SetVal(int nVal){mVal = nVal;}
    void SetLine(int nLine){mLine = nLine;}
    int GetVal(){return mVal;}
    int GetLine(){return mLine;}
private:
    int mVal;
    int mLine;
};

class Task:public QObject,public QRunnable
{
    Q_OBJECT
public:
    Task(QString FileName,int JobId);
    ~Task();
    friend void upDataProcess();
protected:
    void run();
private:
    QString FileName;
    int JobId;
public:
    static QWidget * widget;
};

#endif // WIDGET_H
