#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpSocket *tcpsocket ;
    QList<QString> messageList; // 存储服务端发送的未接收消息
    QString str1;


public slots:
    void connected_Slot();
    void readyRead_Slot();
    void disconnectedSlot();
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void on_disconnectButton_clicked();

private slots:
    void on_fanhui_clicked();

    void on_display_history_jilu_clicked();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
