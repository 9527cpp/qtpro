#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QComboBox>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QProgressBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    //ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(3);

    QStringList headers;
    headers<<"FilePath"<<"Size"<<"Status";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setVisible(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->setShowGrid(true);
/*
    QGridLayout * mainLayout = new QGridLayout(this);
    mainLayout->setRowStretch(0,3);
    mainLayout->setRowStretch(1,1);
    wDraw = new QWidget(this);
    mainLayout->addWidget(wDraw);
    QPushButton * btn = new QPushButton(QString("draw"),this);
    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    mainLayout->addWidget(btn,1,0);
    image = new QImage(this->size(), QImage::Format_ARGB32_Premultiplied);//能划线但不能贴图
    //image = new QImage();// 能贴图但画不出线
    image->fill(QColor(0, 0, 0, 0));
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(drawPicture()));
    // 绘制不规则窗体
    //setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
*/
    pool = new QThreadPool();
    pool->setMaxThreadCount(4);
}


void Widget::drawPicture()
{
/*
    QPainter painter;
    painter.begin(image);
    painter.drawLine(0,0,100,100);
    //image->load("alphafill.png");
    painter.end();
    this->update();
*/
}

void Widget::mousePressEvent(QMouseEvent *ev)
{
    /*
    if(ev->button() == Qt::LeftButton)
    {
        qDebug()<<"LeftButton press"<<endl;
    }
    else if(ev->button() == Qt::RightButton)
    {
        qDebug()<<"RightButton press"<<endl;
    }
    else if(ev->button() == Qt::MiddleButton)
    {
        qDebug()<<"MiddleButton press"<<endl;
    }
    qDebug()<<ev->pos()<<endl;*/
}

void Widget::paintEvent(QPaintEvent* ev)
{
    /*
    QPainter painter;
    painter.begin(this);

    painter.drawImage(0, 0, *image);
    painter.end();*/
}


void Widget::choseFile()
{
    QStringList FileNames = QFileDialog::getOpenFileNames(0,"choseFile",".");
    fileListCtl = this->findChild<QTableWidget*>("tableWidget");
    QStringList::iterator itr = FileNames.begin();

    QLineEdit * folderCtl = this->findChild<QLineEdit*>("lineEdit");
    folderCtl->clear();
    for(int i = fileListCtl->rowCount();i > 0;i--)
    {
        fileListCtl->removeRow(0);
    }
    if(FileNames.size()>0){
        QFileInfo f(FileNames[0]);
        folderCtl->setText(f.path());
        for(int i = 0;itr!=FileNames.end();itr++,i++)
        {
            int rowcount = fileListCtl->rowCount();
            QFileInfo f(*itr);
            fileListCtl->insertRow(rowcount);
            fileListCtl->setItem(rowcount,0,new QTableWidgetItem(*itr));
            fileListCtl->setItem(rowcount,1,new QTableWidgetItem(QString::number(f.size())));
            fileListCtl->setItem(rowcount,2,new QTableWidgetItem("0%"));
            //fileListCtl->setCellWidget(rowcount,1,new QProgressBar());
        }
    }
}


#define EVENT_UPDATE_PROCESS (QEvent::User+1)

bool Widget::event(QEvent *event)
{
    switch(event->type())
    {
        case EVENT_UPDATE_PROCESS:
        {
            MyEvent* pEvent = (MyEvent*)event;
            //qDebug()<<"line:"<<pEvent->GetLine()<<"val:"<<pEvent->GetVal()<<endl;
            fileListCtl->setItem(pEvent->GetLine(),2,new QTableWidgetItem(QString::number(pEvent->GetVal())+"%"));

            return 0;
        }
        break;
    }
    return QWidget::event(event);
}


typedef void (*CALLBACK)(int,int);
extern void process(std::string strFileName,int line,CALLBACK cb);



void Widget::start()
{
    QTableWidget * fileListCtl = this->findChild<QTableWidget*>("tableWidget");
    Task::widget = this;

    for(int i = 0;i<fileListCtl->rowCount();i++)
    {
        pool->start(new Task(fileListCtl->item(i,0)->text(),i));
    }
}

Widget::~Widget()
{
    delete ui;
}


QWidget *Task::widget = NULL;

Task::Task(QString FileName,int JobId)
{
    this->FileName = FileName;
    this->JobId = JobId;
}

Task::~Task()
{

}

void upDataProcess(int val,int line)
{
    MyEvent me(QEvent::Type(EVENT_UPDATE_PROCESS));
    me.SetVal(val);
    me.SetLine(line);
    QApplication::postEvent(Task::widget, new MyEvent(me));
}

void Task::run()
{
    qDebug()<<"Thread:"<<QThread::currentThreadId()<<"process:"<<FileName<<endl;
    process(FileName.toStdString(),this->JobId,upDataProcess);//// callback
}
