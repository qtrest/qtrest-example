#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>

class CouponModel;
class QNetworkReply;

class CouponItem
{
private:
    QString id;
    QString title;
    QString mainImageLink;
    friend CouponModel;
};

class CouponModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CouponModel(QObject *parent = 0);

    enum CouponRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        MainImageLinkRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

public slots:
    void update();
    void updateFinished(QJsonDocument json);

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<CouponItem> m_items;
    QNetworkReply *currentReply;
};

#endif // COUPONMODEL_H

