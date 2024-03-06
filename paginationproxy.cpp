#include "paginationproxy.h"

PaginationProxy::PaginationProxy(QObject *parent)
    : QSortFilterProxyModel{parent},
    currentPage{0},
    sizePage{5},
    acceptedCount{0},
    skippedCount{0},
    request{" "}
{}

void PaginationProxy::search(QString request)
{
    this->request = request;
    qDebug("search");
    if(acceptedCount < sizePage)
    {
        setCurrentPage(0);
    }
    acceptedCount = 0;
    skippedCount = 0;
    setFilterRegularExpression(request);
}

void PaginationProxy::prevPage()
{
    if(currentPage != 0)
    {
        currentPage--;
    }
    qDebug("prev_page");
    search(request);
}

void PaginationProxy::nextPage()
{
    currentPage++;
    qDebug("next_page");
    search(request);
}

void PaginationProxy::setCurrentPage(int page)
{
    currentPage = page;
}

bool PaginationProxy::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index{ sourceModel()->index(source_row, 0, source_parent) };
    if( !index.data().toString().contains(filterRegularExpression()) )
    {
        return false;
    }
    if( skippedCount < currentPage * sizePage )
    {
        skippedCount++;
        return false;
    }
    if( skippedCount >= currentPage * sizePage )
    {
        if( acceptedCount < sizePage )
        {
            acceptedCount++;
            qDebug("accepted +");
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
