#include "denglu_jiemian.h"
#include "zhuche_jiemian.h"
#include "ui_denglu_jiemian.h"
#include "tcpserver.h"

Denglu_jiemian::Denglu_jiemian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Denglu_jiemian)
{
    ui->setupUi(this);
    static bool isFirst = true;
    //以下是防止内存泄漏
//    if(isFirst) {
//            db = QSqlDatabase::addDatabase("QMYSQL","first");	//指定了连接名
//            isFirst = false;
//        } else if(QSqlDatabase::contains("first")) {
//            db = QSqlDatabase::database("first");
//        }

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("db_for_qq_server");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setPassword("zxcvbnm123");
    db.setUserName("root");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"连接成功";
    }
    else
    {
        qDebug()<<"连接失败"<<db.lastError().text();
    }

}

Denglu_jiemian::~Denglu_jiemian()
{
    delete ui;
}

void Denglu_jiemian::on_login_clicked()
{
    QString username = ui->user_name->text();
    QString password = ui->password->text();


    if(username == "" || password == "")
    {
        QMessageBox::warning(this,tr("警告"),tr("用户名和密码不能为空！"),QMessageBox::Yes);
        return;
    }

    //查询用户信息，判断用户名和密码是否正确
    QSqlQuery query1;
    QString sql1 = "SELECT username, pwd FROM login_information WHERE username = ? AND pwd = ?";
    query1.prepare(sql1);
    query1.addBindValue(username);
    query1.addBindValue(password);
    bool b =query1.exec();

    QString sql2 ="select * from login_information";

 //   bool b =query1.exec(sql2);



    if(!b)
    {
        qDebug() << "Query user failed";
        return;
    }

        if(query1.next())
        {
            //如果用户名和密码正确，则进入主窗口，否则提示用户名或密码错误
            QMessageBox::information(this,tr("信息"),tr("登录成功！"),QMessageBox::Yes);


                TcpServer* t1 = new TcpServer();
            //    t1->setGeometry(this->geometry());
                t1->show();

        }
        else
        {
            QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误！"),QMessageBox::Yes);
        }
        //以下只能登录一次以后删除，要用连接池实现
//        db.close();
//        QSqlDatabase::removeDatabase(db.connectionName());
}


void Denglu_jiemian::on_pushButton_3_clicked()//进入注册界面按钮
{

    db.close();
    QSqlDatabase::removeDatabase(db.connectionName());
    Zhuche_jiemian* zhuce1 =new Zhuche_jiemian();
    zhuce1->setGeometry(this->geometry());
    zhuce1->show();

    this ->close();
}


void Denglu_jiemian::on_exit_clicked()
{
    this->close();
}

