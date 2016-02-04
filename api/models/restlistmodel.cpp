#include "restlistmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

RESTListModel::RESTListModel(QObject *parent) : QAbstractListModel(parent), m_sort("-id"), m_perPage(20), currentReply(NULL), m_currentPage(0), m_roleNamesIndex(0)
{
    setLoadingStatus(LoadingStatus::Idle);
    connect(&couponapi,SIGNAL(getCouponFinished(QJsonDocument, QNetworkReply *)), this, SLOT(updateFinished(QJsonDocument, QNetworkReply *)));
    connect(&couponapi,SIGNAL(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)), this, SLOT(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)));
}

void RESTListModel::updateFinished(QJsonDocument json, QNetworkReply *reply)
{
    qDebug() << "updateFinished";

    if (this->loadingStatus() == LoadingStatus::Idle) {
        return;
    }

    //TODO check is reply for me

    updateHeadersData(reply);

    QJsonArray jsonArray = json.array();

    //prepare vars
    int insertFrom = rowCount();
    int insertCount = rowCount()+jsonArray.count()-1;

    //check if we need to full reload
    if (this->loadingStatus() == LoadingStatus::FullReloadProcessing) {
        beginResetModel();

        m_items.clear();
        insertFrom = rowCount();
        insertCount = jsonArray.count()-1;

        endResetModel();
    }

    //append rows to model
    beginInsertRows(this->index(rowCount(), 0), insertFrom, insertCount);

    //http://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        QVariantMap item = processItem(obj.toVariantMap());

        m_items.append(item);
    }

    //get all role names
    if (rowCount() > 0) {
        QStringList keys = m_items[0].keys();

        foreach (QString key, keys) {
            m_roleNamesIndex++;
            m_roleNames[m_roleNamesIndex] = QByteArray().append(key);
        }
    }

    endInsertRows();

    setLoadingStatus(LoadingStatus::Idle);

    emit countChanged();
}

bool RESTListModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (currentPage() < totalCount()) {
        return true;
    } else {
        return false;
    }
}

void RESTListModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)

    if (loadingStatus() != LoadingStatus::Idle && loadingStatus() != LoadingStatus::RequestToReload) {
        return;
    }

    qDebug() << "fetchMore";

    if (loadingStatus() == LoadingStatus::RequestToReload) {
        setCurrentPage(0);
        setLoadingStatus(LoadingStatus::FullReloadProcessing);
    } else {
        setLoadingStatus(LoadingStatus::LoadMoreProcessing);
    }

    int nextPage = currentPage()+1;
    setCurrentPage(nextPage);

    fetchMoreHelper(parent);
}

void RESTListModel::reload()
{
    setLoadingStatus(LoadingStatus::RequestToReload);
    this->fetchMore(QModelIndex());
}

void RESTListModel::replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString)
{
    Q_UNUSED(reply)
    setLoadingErrorCode(error);
    setLoadingErrorString(errorString);
    setLoadingStatus(LoadingStatus::Error);
}

QVariant RESTListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) {
        qDebug() << "Row not found" << index.row();
        return QVariant();
    }

    QVariantMap item = m_items.at(index.row());
    return item.value(m_roleNames[role]);
}

QHash<int, QByteArray> RESTListModel::roleNames() const
{
    return m_roleNames;
}

void RESTListModel::updateHeadersData(QNetworkReply *reply)
{
    //update headers data
    this->setCurrentPage(reply->rawHeader("X-Pagination-Current-Page").toInt());
    this->setTotalCount(reply->rawHeader("X-Pagination-Total-Count").toInt());
    this->setPageCount(reply->rawHeader("X-Pagination-Page-Count").toInt());
    reply->deleteLater();
}

int RESTListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

int RESTListModel::count() const { return m_items.count(); }
