#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
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
/*
 * QMainWindow 有自己的布局 menuBar ToolBar statuBar 所以在QMainWindow上直接添加Layout会出错(需要借助QWidget 然后通过QWidget去添加QLayout)
 * QWidget QDialog 只是一个页面 可以添加QLayout
*/


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    //去掉默认ui
    //ui->setupUi(this);
    QMenuBar * menuBar = this->menuBar();
    QMenu * fileMenu =new QMenu("文件",menuBar);
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(QIcon("res/alphafill.png"),"文件1",this,SLOT(update()));
    fileMenu->addAction(QIcon("res/alphafill.png"),"文件2",this,SLOT(update()));
    QMenu * openMenu =new QMenu("新建(&N)");
    fileMenu->addMenu(openMenu);
    openMenu->addAction(QIcon("res/alphafill.png"),"新建",this,SLOT(update()));
    menuBar->addSeparator();

    QMenu * editMenu =new QMenu("edit(&E)",menuBar);
    menuBar->addMenu(editMenu);
    editMenu->addAction(QIcon("res/btn_next.png"),"menu/edit",this,SLOT(update()));


    QWidget * widget = new QWidget(this);
    this->setCentralWidget(widget);

    QGridLayout *main = new QGridLayout(widget);// 如果是QWidget的话 直接用this作为参数

    QHBoxLayout *up = new QHBoxLayout();
    QGridLayout *bottom = new QGridLayout();
    le = new QLineEdit("this is a test");
    up->addWidget(le);

    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<3;j++)
        {
            QPushButton *btn = new QPushButton(QString::number(i*3+j));
            /*
             信号的参数个数大于等于槽函数参数的个数
             并且信号参数的类型与槽函数参数的类型一致(相当于槽参数是信号参数的子集)
            */
            connect(btn,SIGNAL(clicked()),this,SLOT(update()));
            bottom->addWidget(btn,i,j);
        }
    }

    QCheckBox * cb = new QCheckBox;
    bottom->addWidget(cb,4,0);
    connect(cb,SIGNAL(stateChanged(int)),this,SLOT(update()));

    main->addLayout(up,0,0);
    main->addLayout(bottom,1,0);
}

void MainWindow::update()
{
    QPushButton * btn = qobject_cast<QPushButton *>(sender());
    if(btn)
    {
        le->setText(btn->text());
    }
    QCheckBox * cb = qobject_cast<QCheckBox *>(sender());
    if(cb)
    {
        le->setText(QString::number((int)(cb->checkState())));
    }
    QAction *ac = qobject_cast<QAction *>(sender());
    if(ac)
    {
        le->setText(ac->text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
