#include "widget.h"

#include <QApplication>
#include <QtSql>
#include <QSqlQueryModel>

#include"paginationproxy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    if(!db.open())
    {
        qDebug("error connect db");
        return a.exec();
    }

    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery("SELECT title FROM movies ORDER BY title ASC", db);
    if (model->lastError().isValid())
    {
        qDebug() << model->lastError();
        return a.exec();
    }

    PaginationProxy* proxy = new PaginationProxy;
    proxy->setSourceModel(model);

    w.view->setModel(proxy);
    QThread model_thread;

    model->moveToThread(&model_thread);
    proxy->moveToThread(&model_thread);

    QObject::connect(w.search_button, &QPushButton::clicked, &w, &Widget::beginSearch);
    QObject::connect(&w, &Widget::setCurrentPage, proxy, &PaginationProxy::setCurrentPage);
    QObject::connect(&w, &Widget::search, proxy, &PaginationProxy::search);
    QObject::connect(w.prev_button, &QPushButton::clicked, proxy, &PaginationProxy::prevPage);
    QObject::connect(w.next_button, &QPushButton::clicked, proxy, &PaginationProxy::nextPage);

    model_thread.start();

    int result = a.exec();

    model_thread.quit();
    model_thread.wait();

    return result;
}
