#ifndef LINKTABLEWIDGET_H
#define LINKTABLEWIDGET_H

#include <QListWidget>

class LinkTableWidget : public QListWidget
{
    Q_OBJECT
private:
    uint serverindex;
public:
    explicit LinkTableWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // LINKTABLEWIDGET_H
