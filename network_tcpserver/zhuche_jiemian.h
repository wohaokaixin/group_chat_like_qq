#ifndef ZHUCHE_JIEMIAN_H
#define ZHUCHE_JIEMIAN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class Zhuche_jiemian;
}

class Zhuche_jiemian : public QWidget
{
    Q_OBJECT

public:
    explicit Zhuche_jiemian(QWidget *parent = nullptr);
    ~Zhuche_jiemian();

private slots:
    void on_pushButton_3_clicked();

    void on_goback_denglu_clicked();

private:
    Ui::Zhuche_jiemian *ui;
    QSqlDatabase db222;
};

#endif // ZHUCHE_JIEMIAN_H
