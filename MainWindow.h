#ifndef CLUB_H
#define CLUB_H

#include <QMainWindow>
#include"liaison.h"
namespace Ui {
class Club;
}

class Club : public QMainWindow
{
    Q_OBJECT

public:
    explicit Club(QWidget *parent = nullptr);
    ~Club();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Club *ui;
     liaison *L;
};

#endif // CLUB_H
