#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class TcpServer;
}

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    QList<QTcpSocket*> clientSockets;
    QTcpSocket* clientSocket;
    QList<QPair<QTcpSocket*, QString>> messageList;//这个列表用于存储一个消息队列，其中每个消息由一个QTcpSocket和一个QString组成。群聊消息队列

private slots:
    void newConnection_Slot();
    void readyRead_Slot();

    void disconnectedSlot();

    void on_startButton_clicked();

private:
    Ui::TcpServer *ui;
};

#endif // TCPSERVER_H
