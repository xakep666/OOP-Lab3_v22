#ifndef ADDSERVERDIALOG_H
#define ADDSERVERDIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class AddServerDialog;
}

class AddServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddServerDialog(QWidget *parent = 0);
    ~AddServerDialog();

signals:
    void AddLastItemSignal();

private slots:
    void on_buttonBox_rejected();

    virtual void on_buttonBox_accepted();

    virtual void on_buttonBox_clicked(QAbstractButton *button);

    void on_ipEdit_textChanged(const QString &arg1);

protected:
    Ui::AddServerDialog *ui;
};

#endif // ADDSERVERDIALOG_H
