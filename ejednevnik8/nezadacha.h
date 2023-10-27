#ifndef NEZADACHA_H
#define NEZADACHA_H

#include <QDialog>

namespace Ui {
class nezadacha;
}

class nezadacha : public QDialog
{
    Q_OBJECT

public:
    explicit nezadacha(QWidget *parent = nullptr);
    ~nezadacha();
    QString textovik;
    bool zakril = false;
    QString vnutritextovika;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::nezadacha *ui;
};

#endif // NEZADACHA_H
