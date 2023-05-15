#include "zhuche_jiemian.h"
#include "ui_zhuche_jiemian.h"
#include "denglu_jiemian.h"
Zhuche_jiemian::Zhuche_jiemian(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zhuche_jiemian)
{
    ui->setupUi(this);

    static bool isFirst = true;
//    if(isFirst) {
//            db222 = QSqlDatabase::addDatabase("QMYSQL","second");	//指定了连接名
//            isFirst = false;
//        } else if(QSqlDatabase::contains("second")) {
//            db222 = QSqlDatabase::database("second");
//        }
    db222 = QSqlDatabase::addDatabase("QMYSQL");
    db222.setDatabaseName("db_for_qq");
    db222.setHostName("127.0.0.1");
    db222.setPort(3306);
    db222.setPassword("zxcvbnm123");
    db222.setUserName("root");
    if(!db222.open())
        {
            qDebug() << "Open database failed";
            return;
        }
}

Zhuche_jiemian::~Zhuche_jiemian()
{
    delete ui;
}

void Zhuche_jiemian::on_pushButton_3_clicked()//点击注册
{
    QString username = ui->user_name_zhuce->text();
        QString password = ui->password_zhuce->text();
       QString repassword = ui->repassword_zhuce->text();

        if(username == "" || password == ""|| repassword == "")
        {
            QMessageBox::warning(this,tr("警告"),tr("用户名、密码和确认密码不能为空！"),QMessageBox::Yes);
            return;
        }

        if(password != repassword)
        {
            QMessageBox::warning(this,tr("警告"),tr("两次输入的密码不一致！"),QMessageBox::Yes);
            return;
        }

        //查询用户信息，判断用户名是否已经存在
        QSqlQuery query1;
        QString sql1 = "SELECT username, pwd FROM login_information WHERE username = ? AND pwd = ?";
        query1.prepare(sql1);
        query1.addBindValue(username);
        query1.addBindValue(password);
        bool b =query1.exec();

        if(!b)
        {
            qDebug() << "Query user failed";
            return;
        }



        if(query1.next())
        {
            QMessageBox::warning(this,tr("警告"),tr("用户名已经存在，请重新输入！"),QMessageBox::Yes);
        }
        else
        {
            //插入新用户到数据库中
            QSqlQuery query2;
            QString sql2 = "insert into login_information(username,pwd) values(?,?)";
            query2.prepare(sql2);
            query2.addBindValue(username);
            query2.addBindValue(password);
            b = query2.exec();

            if(!b)
            {
                qDebug() << "Insert user failed";
                return;
            }
            else
            {
                QMessageBox::information(this,tr("信息"),tr("注册成功！"),QMessageBox::Yes);
            }

//            db222.close();
//            QSqlDatabase::removeDatabase(db222.connectionName());

        }
}


void Zhuche_jiemian::on_goback_denglu_clicked()
{

    db222.close();
    QSqlDatabase::removeDatabase(db222.connectionName());
    Denglu_jiemian* denglu1 =new Denglu_jiemian;
    denglu1->setGeometry(this->geometry());
    denglu1->show();

    this->close();
}

