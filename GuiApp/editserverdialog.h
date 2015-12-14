#ifndef EDITSERVERDIALOG_H
#define EDITSERVERDIALOG_H

#include "addserverdialog.h"
class EditServerDialog : public AddServerDialog
{
    Q_OBJECT
public:
    explicit EditServerDialog(QWidget *parent=0,uint index=0);

signals:
    void UpdateItemSignal(uint index,ulong newaddress,QString &newname,uint newcostpermin,uint newcostpermb);

private slots:
    void on_buttonBox_accepted();

private:
    uint index;
};

#endif // EDITSERVERDIALOG_H
