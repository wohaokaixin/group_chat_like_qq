#include "tcpserver.h"
#include "ui_tcpserver.h"

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
    clientSocket = tcpserver->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readyRead_Slot()));
    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    //添加客户端套接字到列表中
    clientSockets.append(clientSocket);
    ui->textEdit->append(QString("有一个新的客户端已连接: %1").arg(clientSocket->peerAddress().toString()));
}
void TcpServer::readyRead_Slot(){//读取客户端套接字缓冲区的所有内容，然后把这些内容显示在服务器的接收框上

    clientSocket = qobject_cast<QTcpSocket*>(sender());
    QString message = QString("New message from%1 %2 %3").arg(clientSocket->peerAddress().toString()).arg(clientSocket->peerPort()).arg(QString(clientSocket->readAll()));

    ui->plainTextEdit->appendPlainText(message);

    //转发消息给所有客户端（除了发送者）
    for (int i = 0; i < clientSockets.size(); i++)
    {
        QTcpSocket *receiverSocket = clientSockets.at(i);
//        if (receiverSocket != clientSocket)
//        {
//            receiverSocket->write(message.toUtf8());
//        }
        receiverSocket->write(message.toUtf8());
    }

}
//新增

void TcpServer::disconnectedSlot()
{
    QTcpSocket clientSocket = qobject_cast<QTcpSocket>(sender());

    ui->textEdit->append(QString("Client disconnected:1").arg(clientSocket.peerAddress().toString()));

//从客户端套接字列表中删除该套接字
//clientSockets.removeOne(clientSocket);
//QList<QTcpSocket*>::const_iterator it = std::find_if(clientSockets.constBegin(), clientSockets.constEnd(),
//                                                     [=](const QTcpSocket* socket) { return socket == clientSocket; });
//if (it != clientSockets.constEnd()) {
//    clientSockets.removeOne(*it);
//}
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
        ui->textEdit->append(QString("Server started, listening on port1").arg(port));
    }
    else
    {
        ui->textEdit->append(QString("Failed to start server:1").arg(tcpserver->errorString()));
    }
}
