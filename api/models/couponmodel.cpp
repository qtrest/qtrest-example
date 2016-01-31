#include "couponmodel.h"
#include "api/apimanager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

CouponModel::CouponModel(QObject *parent) : QAbstractListModel(parent), m_sort("-id"), m_perPage(20), currentReply(NULL),m_currentPage(0)
{
    setLoadingStatus(LoadingStatus::Idle);
    connect(&couponapi,SIGNAL(getCouponFinished(QJsonDocument, QNetworkReply *)), this, SLOT(updateFinished(QJsonDocument, QNetworkReply *)));
}

void CouponModel::updateFinished(QJsonDocument json, QNetworkReply *reply)
{
    qDebug() << "updateFinished";

    if (this->loadingStatus() == LoadingStatus::Idle) {
        return;
    }

    //TODO check is reply for me

    //update headers data
    this->setCurrentPage(reply->rawHeader("X-Pagination-Current-Page").toInt());
    this->setTotalCount(reply->rawHeader("X-Pagination-Total-Count").toInt());
    this->setPageCount(reply->rawHeader("X-Pagination-Page-Count").toInt());
    reply->deleteLater();

    QJsonArray jsonArray = json.array();

    //prepare vars
    int insertFrom = rowCount();
    int insertCount = rowCount()+jsonArray.count()-1;

    if (this->loadingStatus() == LoadingStatus::FullReloadProcessing) {
        int removeCount = rowCount()-1;
        if (removeCount < 0) { removeCount = 0; }
        beginResetModel();
        m_items.clear();
        insertFrom = rowCount();
        insertCount = jsonArray.count()-1;
        endResetModel();
    }

    beginInsertRows(this->index(rowCount(), 0), insertFrom, insertCount);

    //http://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        CouponItem item;
        item.id = obj["id"].toString();
        item.title = obj["title"].toString();
        item.mainImageLink = obj["mainImageLink"].toString();

        QDateTime timestamp;
        timestamp.setTime_t(obj["createTimestamp"].toInt());
        //item.createDate = timestamp.toString("dd.MM.yyyy");
        item.createDate = QDateTime::fromString(obj["createTimestamp"].toString(), "yyyy-MM-dd hh:mm:ss").date();
        //qDebug() << item.createDate.toString() << obj["createTimestamp"].toString();
        item.createTimestamp = obj["createTimestamp"].toInt();

        item.boughtCount = obj["boughtCount"].toString();
        //qDebug() << obj["boughtCount"].toInt() << obj["boughtCount"].toString();
        item.cityId = obj["cityId"].toInt();
        item.cityName = obj["cityName"].toString();

        item.shortDescription = obj["shortDescription"].toString();

        m_items.append(item);
    }

    endInsertRows();

    qDebug() << m_items.count() << rowCount() << jsonArray.count() << jsonArray.size() << insertFrom << insertCount;

    setLoadingStatus(LoadingStatus::Idle);

    emit countChanged();
}

bool CouponModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (currentPage() < totalCount()) {
        return true;
    } else {
        return false;
    }
}

void CouponModel::fetchMore(const QModelIndex &parent)
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

    currentReply = couponapi.getCoupon(sort(), perPage(), currentPage(), filters());
}

void CouponModel::reload()
{
    setLoadingStatus(LoadingStatus::RequestToReload);
    this->fetchMore(QModelIndex());
}

QVariant CouponModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) {
        qDebug() << "Row not found" << index.row();
        return QVariant();
    }

    CouponItem item = m_items.at(index.row());

    switch (role) {
    case IdRole:
        return item.id;
        break;
    case TitleRole:
        return item.title;
        break;
    case MainImageLinkRole:
        return item.mainImageLink;
        break;
    case CityNameRole:
        return item.cityName;
        break;
    case BoughtCountRole:
        return item.boughtCount;
        break;
    case CreateDateRole:
        return item.createDate.toString("dd.MM.yyyy");
        break;
    case ShortDescriptionRole:
        return item.shortDescription;
        break;
    default:
        return QVariant();
        break;
    }
}

QHash<int, QByteArray> CouponModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[TitleRole] = "title";
    roles[MainImageLinkRole] = "mainImageLink";
    roles[CreateDateRole] = "createDate";
    roles[BoughtCountRole] = "boughtCount";
    roles[CityNameRole] = "cityName";
    roles[ShortDescriptionRole] = "shortDescription";
    return roles;
}

int CouponModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

int CouponModel::count() const { return m_items.count(); }
