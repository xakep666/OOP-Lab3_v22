#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Exit_triggered();

    void on_OpenFile_triggered();

    void on_SaveFile_triggered();

    void on_addserver_clicked();

    void on_removeServer_clicked();

    void on_linktableShow_clicked();

    void on_abonentInfo_clicked();

    void on_editServer_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
