#include "couponmodel.h"
#include "api/apimanager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

CouponModel::CouponModel(QObject *parent) : QAbstractListModel(parent), m_sort("-id"), m_perPage(20)
{
    connect(&couponapi,SIGNAL(getCouponFinished(QJsonDocument)), this, SLOT(updateFinished(QJsonDocument)));
}

void CouponModel::update()
{
    currentReply = couponapi.getCoupon(sort(), perPage());
}

void CouponModel::updateFinished(QJsonDocument json)
{
    qDebug() << "updateFinished";

//    if (!reply || ) {
//        qDebug() << "reply is null or ";
//        return;
//    }

    m_items.clear();

    QJsonArray jsonArray = json.array();

    beginInsertRows(QModelIndex(), rowCount(), jsonArray.count());

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

        m_items.append(item);
    }

    endInsertRows();

    emit countChanged();

    qDebug() << rowCount() << jsonArray.count();
}

QVariant CouponModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count())
        return QVariant();

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
    return roles;
}

int CouponModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

int CouponModel::count() const { return m_items.size(); }
