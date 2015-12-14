#ifndef EDITSERVICEDIALOG_H
#define EDITSERVICEDIALOG_H

#include "addservicedialog.h"

class EditServiceDialog : public AddServiceDialog
{
    Q_OBJECT
public:
    explicit EditServiceDialog(QWidget *parent = 0,ulong serveraddr=0,uint index=0);

signals:

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    uint index;
    void _rewrite();
};

#endif // EDITSERVICEDIALOG_H
