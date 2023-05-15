#ifndef DENGLU_JIEMIAN_H
#define DENGLU_JIEMIAN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>



namespace Ui {
class Denglu_jiemian;
}

class Denglu_jiemian : public QWidget
{
    Q_OBJECT

public:
    explicit Denglu_jiemian(QWidget *parent = nullptr);
    ~Denglu_jiemian();
    void func();

private slots:
    void on_login_clicked();

    void on_pushButton_3_clicked();

    void on_exit_clicked();

private:
    Ui::Denglu_jiemian *ui;
    QSqlDatabase db;
};

#endif // DENGLU_JIEMIAN_H
