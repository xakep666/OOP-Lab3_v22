#ifndef LINKTABLEDIALOG_H
#define LINKTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class LinkTableDialog;
}

class LinkTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkTableDialog(QWidget *parent = 0);
    explicit LinkTableDialog(QWidget *parent = 0,uint index=0);
    uint getIndex() const;
    ~LinkTableDialog();

private:
    Ui::LinkTableDialog *ui;
    uint index;
};

#endif // LINKTABLEDIALOG_H
