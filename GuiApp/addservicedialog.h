#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class AddServiceDialog;
}

class AddServiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddServiceDialog(QWidget *parent = 0,ulong serveraddr = 0);
    ~AddServiceDialog();

signals:
    void UpdateLinkTableSignal();
protected slots:
    void on_recvToggle_post_clicked();

    void on_sendToggle_post_clicked();

    void on_recvToggle_files_clicked();

    void on_sendToggle_files_clicked();

    void on_buttonBox_rejected();

    virtual void on_buttonBox_clicked(QAbstractButton *button);

    virtual void on_buttonBox_accepted();

    void on_abonentEdit_textChanged(const QString &arg1);

    void on_sendrecvEdit_post_textChanged(const QString &arg1);

    void on_sendrecvEdit_files_textChanged(const QString &arg1);

    void on_destEdit_net_textChanged(const QString &arg1);

    void on_addPost_toggled(bool checked);

    void on_addFiles_toggled(bool checked);

    void on_addNet_toggled(bool checked);

protected:
    Ui::AddServiceDialog *ui;
    ulong serveraddr;
};

#endif // ADDSERVICEDIALOG_H
