#ifndef ABONENTSERVICES_H
#define ABONENTSERVICES_H

#include <QDialog>

namespace Ui {
class AbonentServices;
}

class AbonentServices : public QDialog
{
    Q_OBJECT

public:
    explicit AbonentServices(QWidget *parent = 0,ulong abonentIP = 0);
    ~AbonentServices();

private slots:
    void on_closeButton_clicked();

private:
    Ui::AbonentServices *ui;
    ulong abonentIP;
};

#endif // ABONENTSERVICES_H
