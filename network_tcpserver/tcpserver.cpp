#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>

TcpServer::TcpServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    tcpserver = new QTcpServer(this);
    tcpsocket = new QTcpSocket(this);//这里的socket是接收客户端的socket,这里只能接收一个客户端
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(newConnection_Slot()));//当有新客户端连接到tcp服务器时，调用newConnection_Slot()
}

void TcpServer::newConnection_Slot()
{
    clientSocket = tcpserver->nextPendingConnection();//新连接的客户端套接字
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead_Slot()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    //添加客户端套接字到列表中
    clientSockets.append(clientSocket);
    ui->textEdit->append(QString("有一个新的客户端已连接: %1").arg(clientSocket->peerAddress().toString()));


    //
    for (auto it = messageList.begin(); it != messageList.end();it++)
    {
        QPair<QTcpSocket*, QString> message = *it;

        QString str1 =QString("历史消息： ")+message.second+QString("\n");


        clientSocket->write(str1.toUtf8());
        //  it = messageList.erase(it);


    }
}
void TcpServer::readyRead_Slot(){//读取客户端套接字缓冲区的所有内容，然后把这些内容显示在服务器的接收框上

    clientSocket = qobject_cast<QTcpSocket*>(sender());//用于获取当前客户端的QTcpSocket对象，并将其存储到clientSocket变量中
    QString message = QString("%1").arg(QString(clientSocket->readAll()));

    if(clientSocket)


    ui->plainTextEdit->appendPlainText(message);

    messageList.append(qMakePair(clientSocket, message));//把这个客户端的消息写入消息列表，假设a发送“你好”，b发送“我很好”,内容就是“你好”，“我很好”

    //转发消息给所有客户端
    for (int i = 0; i < clientSockets.size(); i++)
    {
        QTcpSocket *receiverSocket = clientSockets.at(i);

        receiverSocket->write(message.toUtf8());
    }

}
//新增

void TcpServer::disconnectedSlot()
{
    clientSocket = qobject_cast<QTcpSocket*>(sender());//将发送信号的对象转换成 QTcpSocket* 类型

    ui->textEdit->append(QString("客户端连接：%1").arg(clientSocket->peerAddress().toString()));

    //从客户端套接字列表中删除该套接字
    clientSockets.removeOne(clientSocket);
    clientSocket->deleteLater();

}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::on_startButton_clicked()
{
    quint16 port = ui->portEdit->text().toUInt();
    if (tcpserver->listen(QHostAddress::Any, port))
    {
        ui->textEdit->append(QString("服务器开始监听端口%1").arg(port));
    }
    else
    {
        ui->textEdit->append(QString("监听失败！").arg(tcpserver->errorString()));
    }
}
