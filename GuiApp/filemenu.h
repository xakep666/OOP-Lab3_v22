#ifndef MENU_H
#define MENU_H

#include <QMenu>

class FileMenu : public QMenu
{
    Q_OBJECT
public:
    explicit FileMenu(QWidget *parent = 0);

signals:
    void UpdateTableSignal();
public slots:
};

#endif // MENU_H
