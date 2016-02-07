#include "baserestlistmodel.h"

BaseRestListModel::BaseRestListModel(QObject *parent) : QAbstractListModel(parent), m_sort("-id"), m_perPage(20), currentReply(NULL), m_currentPage(0), m_roleNamesIndex(0)
{
    setLoadingStatus(LoadingStatus::Idle);
    connect(&apimanager,SIGNAL(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)), this, SLOT(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)));
}

void BaseRestListModel::reload()
{
    setLoadingStatus(LoadingStatus::RequestToReload);
    this->fetchMore(QModelIndex());
}

bool BaseRestListModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (currentPage() < totalCount()) {
        return true;
    } else {
        return false;
    }
}

void BaseRestListModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)

    qDebug() << "fetchMore";

    switch (loadingStatus()) {
    case LoadingStatus::RequestToReload:
        setCurrentPage(0);
        setLoadingStatus(LoadingStatus::FullReloadProcessing);
        break;
    case LoadingStatus::Idle:
        setLoadingStatus(LoadingStatus::LoadMoreProcessing);
        break;
    default:
        return;
        break;
    }

    int nextPage = currentPage()+1;
    setCurrentPage(nextPage);

    fetchMoreImpl(parent);
}

void BaseRestListModel::replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString)
{
    Q_UNUSED(reply)
    setLoadingErrorCode(error);
    setLoadingErrorString(errorString);
    setLoadingStatus(LoadingStatus::Error);
}

Item BaseRestListModel::getItem(QVariantMap value)
{
    return Item(preProcessItem(value));
}

QVariant BaseRestListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) {
        qDebug() << "Row not found" << index.row();
        return QVariant();
    }

    Item item = m_items.at(index.row());
    return item.value(m_roleNames[role]);
}

QHash<int, QByteArray> BaseRestListModel::roleNames() const
{
    return m_roleNames;
}

void BaseRestListModel::updateHeadersData(QNetworkReply *reply)
{
    //update headers data
    this->setCurrentPage(reply->rawHeader("X-Pagination-Current-Page").toInt());
    this->setTotalCount(reply->rawHeader("X-Pagination-Total-Count").toInt());
    this->setPageCount(reply->rawHeader("X-Pagination-Page-Count").toInt());
    reply->deleteLater();
}

void BaseRestListModel::clearForReload()
{
    beginResetModel();

    m_items.clear();

    endResetModel();
}

void BaseRestListModel::append(Item item)
{
    m_items.append(item);
}

void BaseRestListModel::generateRoleNames()
{
    if (rowCount() > 0) {
        QStringList keys = m_items[0].keys();

        foreach (QString key, keys) {
            m_roleNamesIndex++;
            m_roleNames[m_roleNamesIndex] = QByteArray().append(key);
        }
    }
}

int BaseRestListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

int BaseRestListModel::count() const { return m_items.count(); }
