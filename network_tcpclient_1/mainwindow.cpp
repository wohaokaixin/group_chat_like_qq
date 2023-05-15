#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "denglu.h"
#include<QDataStream>
#include<QColorDialog>
#include<QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpsocket = new QTcpSocket(this);
    connect(tcpsocket,SIGNAL(connected()),this,SLOT(connected_Slot()));//当TCP套接字连接到远程服务器以后（当然这里是客户端的套接字），调用connected_Slot()
    connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));//当客户端的套接字收到远程主机发送的消息时，把消息存在缓冲区，并发出 readyRead() 信号，调用readyRead_Slot()
    connect(tcpsocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

    if(denglu::str =="qunliao")
    {
        ui->stackedWidget_2->setCurrentIndex(1);
        ui->stackedWidget->hide();
    }
    else if(denglu::str =="mingren")
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_2->hide();
    }
    else if(denglu::str =="gangshou")
    {
        ui->stackedWidget_2->setCurrentIndex(0);
        ui->stackedWidget->hide();
    }
    else if(denglu::str =="zuozhu")
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget_2->hide();
    }

   //字体
   connect(ui->zhiti,&QFontComboBox::currentFontChanged,this,[=](const QFont &font){
       //设置全局字体
       ui->input_kuang->setFontFamily(font.toString());
       ui->input_kuang->setFocus();
   });

   //字体大小
   void (QComboBox:: *sizeBtn)(const QString &text)=&QComboBox::currentTextChanged;
   connect(ui->ziti_size,sizeBtn,this,[=](const QString &text){
       ui->input_kuang->setFontPointSize(text.toDouble());
        ui->input_kuang->setFocus();
   });

   //加粗
   connect(ui->jiacu,&QToolButton::clicked,this,[=](bool checked){
       //是否按下
       if(checked){
          ui->input_kuang->setFontWeight(QFont::Bold);
       }else{
           ui->input_kuang->setFontWeight(QFont::Normal);
       }
   });

   //倾斜
   connect(ui->xieti,&QToolButton::clicked,this,[=](bool checked){
       ui->input_kuang->setFontItalic(checked);
       ui->input_kuang->setFocus();
   });

   //下划线
   connect(ui->xiahuaxian,&QToolButton::clicked,this,[=](bool checked){
       ui->input_kuang->setFontUnderline(checked);
       ui->input_kuang->setFocus();
   });

    //清空
   connect(ui->qingkong,&QToolButton::clicked,this,[=](){
       ui->jieshou_kuang->clear();
   });

   //字体颜色
   connect(ui->color,&QToolButton::clicked,this,[=](){
       QColor color=QColorDialog::getColor(color,this);
        ui->input_kuang->setTextColor(color);
   });

   //保存聊天记录
   connect(ui->save,&QToolButton::clicked,this,[=](){
       if(ui->jieshou_kuang->toPlainText().isEmpty()){
           QMessageBox::warning(this,"警告","保存内容不能为空");
           return;
       }
       //获取保存文件绝对路径/文件名(窗口标题,文件名,类型)
       QString fileName=QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
       if(!fileName.isEmpty()){
           QFile file(fileName);
           file.open(QIODevice::WriteOnly|QFile::Text);
           QTextStream stream(&file);
           stream<<ui->jieshou_kuang->toPlainText();
           file.close();
       }
   });
}


void MainWindow::connected_Slot()
{
    ui->textEdit->append(QString("Connected to server at %1 %2").arg(tcpsocket->peerAddress().toString()).arg(tcpsocket->peerPort()));
}
void MainWindow::readyRead_Slot()
{
    QString message = QString("%1").arg(QString(tcpsocket->readAll()));
    ui->jieshou_kuang->appendPlainText(message);
}

void MainWindow::disconnectedSlot()
{
    ui->textEdit->append("Disconnected from server");
}

void MainWindow::on_connectButton_clicked()
{
    QString hostName = ui->hostEdit->text();
    quint16 port = ui->portEdit->text().toUInt();
    tcpsocket->connectToHost(hostName, port);
}


void MainWindow::on_sendButton_clicked()
{
    QString message = ui->input_kuang->toPlainText();
    tcpsocket->write(message.toUtf8());
}

void MainWindow::on_disconnectButton_clicked()
{
    tcpsocket->disconnectFromHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fanhui_clicked()
{
    denglu* d1 =new denglu();
    d1 ->setGeometry(this->geometry());
    d1 ->show();
    this ->close();
}

