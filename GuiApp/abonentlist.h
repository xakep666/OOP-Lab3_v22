#ifndef ABONENTLIST_H
#define ABONENTLIST_H

#include <QComboBox>

class AbonentList : public QComboBox
{
    Q_OBJECT
public:
    explicit AbonentList(QWidget *parent = 0);
signals:

public slots:
    void Update();
};

#endif // ABONENTLIST_H
