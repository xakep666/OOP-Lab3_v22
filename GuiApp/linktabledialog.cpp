#include "linktabledialog.h"
#include "ui_linktabledialog.h"
#include "networkservice.h"
LinkTableDialog::LinkTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkTableDialog)
{
    ui->setupUi(this);
}

LinkTableDialog::LinkTableDialog(QWidget *parent, uint _index) :
    QDialog(parent),
    ui(new Ui::LinkTableDialog),
    index(_index)
{
    auto server = NetworkService::Application::getInstance()[index];
    ui->setupUi(this);
    setWindowTitle(tr("Таблица связи для сервера: ")+
                   tr(server.getName().c_str())+
                   tr(" (")+
                   tr(NetworkService::LongIPtoString(server.getAddress()).c_str())+
                   tr(")"));
}

uint LinkTableDialog::getIndex() const
{
    return index;
}

LinkTableDialog::~LinkTableDialog()
{
    delete ui;
}
