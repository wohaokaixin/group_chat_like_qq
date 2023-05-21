#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "denglu.h"
#include<QDataStream>
#include<QColorDialog>
#include<QFileDialog>
#include <QMessageBox>
#include "denglu_jiemian.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    str1 =Denglu_jiemian::get_username;
    ui->my_name->setText(str1);


    tcpsocket = new QTcpSocket(this);
    QString str_my_IP = tcpsocket->peerAddress().toString();//客户端IP
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
   connect(ui->zhiti, &QFontComboBox::currentFontChanged, this, [=](const QFont &font){
       //设置全局字体
       QFont f = ui->input_kuang->font();
       f.setFamily(font.family());
       ui->input_kuang->setFont(f);
       ui->jieshou_kuang->setFont(f);
       ui->input_kuang->setFocus();
   });
   //字体大小
   void (QComboBox:: *sizeBtn)(const QString &text) = &QComboBox::currentTextChanged;
   connect(ui->ziti_size, sizeBtn, this, [=](const QString &text){
       QFont f = ui->input_kuang->font();
       f.setPointSize(text.toDouble());
       ui->input_kuang->setFont(f);
       ui->jieshou_kuang->setFont(f);
       ui->input_kuang->setFocus();
   });
   //加粗
   connect(ui->jiacu, &QToolButton::clicked, this, [=](bool checked){
       //是否按下
       QFont f = ui->input_kuang->font();
       f.setBold(checked);
       ui->input_kuang->setFont(f);
       ui->jieshou_kuang->setFont(f);
   });
   //倾斜
   connect(ui->xieti, &QToolButton::clicked, this, [=](bool checked){
       QFont f = ui->input_kuang->font();
       f.setItalic(checked);
       ui->input_kuang->setFont(f);
       ui->jieshou_kuang->setFont(f);
       ui->input_kuang->setFocus();
   });
   //下划线
   connect(ui->xiahuaxian, &QToolButton::clicked, this, [=](bool checked){
       QFont f = ui->input_kuang->font();
       f.setUnderline(checked);
       ui->input_kuang->setFont(f);
       ui->jieshou_kuang->setFont(f);
       ui->input_kuang->setFocus();
   });
   //清空
   connect(ui->qingkong, &QToolButton::clicked, this, [=](){
       ui->jieshou_kuang->clear();
   });
   //字体颜色
   connect(ui->color, &QToolButton::clicked, this, [=](){
       QColor color = QColorDialog::getColor(color, this);
       ui->input_kuang->setTextColor(color);

       QTextCursor cursor = ui->jieshou_kuang->textCursor();
           // 创建一个 QTextCharFormat 对象，并设置颜色
           QTextCharFormat format;
           format.setForeground(QBrush(color));
           // 在 QTextCursor 处插入文本，同时设置格式
           cursor.insertText(" ", format);
           ui->jieshou_kuang->setTextCursor(cursor); // 将光标移到文本末尾

   });


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
    ui->textEdit->append(QString("已连接至 %1 %2").arg(tcpsocket->peerAddress().toString()).arg(tcpsocket->peerPort()));
}
void MainWindow::readyRead_Slot()
{
    QString message = QString("%1").arg(QString(tcpsocket->readAll()));

    if (!message.contains("历史消息"))//如果不包含，就是正常消息
    {
        ui->jieshou_kuang->appendPlainText(message);
    }
    else //否则就是历史消息，存入链表
    {
        QStringList messageList = message.split("\r\n");//因为服务端返回的是一行一行的文本，所以需要使用 split 方法按照 "\r\n" 对文本进行分割
        for (auto it = messageList.begin(); it != messageList.end(); ++it)
        {
            if (!(*it).isEmpty())
            {
                this->messageList.append(*it);//
            }
        }
    }




}

void MainWindow::disconnectedSlot()
{
    ui->textEdit->append("与服务器断开连接");
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
    QString str_message = QString("有一条来自")+str1+QString("的信息： ")+message;
    tcpsocket->write(str_message.toUtf8());
    ui->input_kuang->clear();

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


void MainWindow::on_display_history_jilu_clicked()
{

    //读取链表里的消息
    for (auto it = messageList.begin(); it != messageList.end(); ++it)
    {
        ui->jieshou_kuang->appendPlainText(*it); // 将所有历史消息输出到客户端界面中
    }
}

