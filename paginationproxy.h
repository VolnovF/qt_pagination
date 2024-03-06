#ifndef PAGINATIONPROXY_H
#define PAGINATIONPROXY_H

#include <QSortFilterProxyModel>

class PaginationProxy : public QSortFilterProxyModel
{
private:
    int currentPage;
    int sizePage;
    mutable int acceptedCount;
    mutable int skippedCount;
    QString request;
public:
    explicit PaginationProxy(QObject *parent = nullptr);
public slots:
    void search(QString request);
    void prevPage();
    void nextPage();
    void setCurrentPage(int page);
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // PAGINATIONPROXY_H
