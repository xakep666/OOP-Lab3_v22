#include "linktablewidget.h"
#include "linktabledialog.h"
#include "networkservice.h"
LinkTableWidget::LinkTableWidget(QWidget *parent) : QListWidget(parent)
{
    //get index
    if (auto dialogwindow = dynamic_cast<LinkTableDialog *>(parent)) {
        serverindex = dialogwindow->getIndex();
        //render all items
        auto table = NetworkService::Application::getInstance()[serverindex].showTable();
        std::for_each(table.begin(),table.end(),[this](const std::string &str){
            addItem(new QListWidgetItem(str.c_str()));
        });
    }
}

