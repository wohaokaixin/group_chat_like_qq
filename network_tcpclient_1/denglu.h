#ifndef DENGLU_H
#define DENGLU_H

#include <QWidget>

namespace Ui {
class denglu;
}

class denglu : public QWidget
{
    Q_OBJECT

public:
    explicit denglu(QWidget *parent = nullptr);
    ~denglu();
    QString static str;

private slots:
    void on_qunliao_2_clicked();
    void on_mingren_2_clicked();
    void on_zuozhu_2_clicked();
    void on_gangshou_2_clicked();



private:
    Ui::denglu *ui;
};

#endif // DENGLU_H
