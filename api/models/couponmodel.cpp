#include "couponmodel.h"
#include "api/apimanager.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

CouponModel::CouponModel(QObject *parent) : QAbstractListModel(parent)
{
    connect(&couponapi,SIGNAL(getCouponFinished(QJsonDocument)), this, SLOT(updateFinished(QJsonDocument)));
}

void CouponModel::update()
{
    currentReply = couponapi.getCoupon("-id");
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

        m_items.append(item);
    }

    endInsertRows();

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
    return roles;
}

int CouponModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}
