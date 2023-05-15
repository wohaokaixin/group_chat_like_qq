#include "denglu.h"
#include "ui_denglu.h"
#include "mainwindow.h"
#include "denglu_jiemian.h"
#include <QStackedWidget>
#include <QPushButton>
denglu::denglu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::denglu)
{
    ui->setupUi(this);

    //设置标题和图标
    this -> setWindowIcon(QIcon("://images/qq.png"));
    this -> setWindowTitle("聊天系统");

    QString str1 =Denglu_jiemian::get_username;
    qDebug()<<str1;
    if(str1 == "波风水门")
    {
        ui->stackedWidget1_1->setCurrentIndex(0);//page1_1
        ui->stackedWidget4_1->hide();
        ui->stcakedWidget_new->hide();
    }
    else if(str1 =="漩涡鸣人")
    {
        ui->stackedWidget1_1->setCurrentIndex(1);//page1_1
        ui->stackedWidget4_1->hide();
        ui->stcakedWidget_new->hide();
    }
    else if(str1 =="宇智波佐助")
    {
        ui->stackedWidget4_1->setCurrentIndex(0);//page1_1
        ui->stackedWidget1_1->hide();
        ui->stcakedWidget_new->hide();
    }
    else if(str1 =="千手纲手")
    {
        ui->stackedWidget4_1->setCurrentIndex(1);//page2_1
        ui->stackedWidget1_1->hide();
        ui->stcakedWidget_new->hide();
    }
    else
    {
        ui->stackedWidget4_1->hide();
        ui->stackedWidget1_1->hide();
    }


    connect(ui->qunliao_3,SIGNAL(clicked()),this,SLOT(on_qunliao_2_clicked()));
    connect(ui->qunliao_4,SIGNAL(clicked()),this,SLOT(on_qunliao_2_clicked()));
    connect(ui->qunliao_5,SIGNAL(clicked()),this,SLOT(on_qunliao_2_clicked()));

    connect(ui->zuozhu_3,SIGNAL(clicked()),this,SLOT(on_zuozhu_2_clicked()));
    connect(ui->gangshou_3,SIGNAL(clicked()),this,SLOT(on_gangshou_2_clicked()));
    connect(ui->mingren_4,SIGNAL(clicked()),this,SLOT(on_mingren_2_clicked()));
    connect(ui->zuozhu_4,SIGNAL(clicked()),this,SLOT(on_zuozhu_2_clicked()));
    connect(ui->mingren_5,SIGNAL(clicked()),this,SLOT(on_mingren_2_clicked()));
    connect(ui->gangshou_5,SIGNAL(clicked()),this,SLOT(on_gangshou_2_clicked()));
}

denglu::~denglu()
{
    delete ui;
}

QString denglu::str ="a";
void denglu::on_qunliao_2_clicked()
{
    str ="qunliao";
    MainWindow* m1 = new MainWindow();
//    m1 ->setGeometry(this->geometry());
    m1 ->show();
    this ->close();
}

void denglu::on_mingren_2_clicked()
{
    str ="mingren";
    MainWindow* m1 = new MainWindow();
//    m1 ->setGeometry(this->geometry());
    m1 ->show();
    this ->close();
}

void denglu::on_zuozhu_2_clicked()
{
    str ="zuozhu";
    MainWindow* m1 = new MainWindow();
//    m1 ->setGeometry(this->geometry());
    m1 ->show();
    this ->close();
}

void denglu::on_gangshou_2_clicked()
{
    str ="gangshou";
    MainWindow* m1 = new MainWindow();
//    m1 ->setGeometry(this->geometry());
    m1 ->show();
    this ->close();
}




