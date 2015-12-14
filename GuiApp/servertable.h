#ifndef SERVERTABLE_H
#define SERVERTABLE_H

#include <QWidget>
#include <QTableWidget>

class ServerTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit ServerTable(QWidget *parent = 0);

signals:

public slots:
    void UpdateTable();
    void AddLastItem();
    void UpdateItem(uint index,ulong newip,QString &newname,uint newcostpermin,uint newcostpermb);
};

#endif // SERVERTABLE_H
