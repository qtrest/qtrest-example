#ifndef COUPONMODEL_H
#define COUPONMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QDate>

class CouponModel;
class QNetworkReply;

class CouponItem
{
private:
    QString id;
    QString title;
    QString mainImageLink;
    QString createTimestamp;
    QDate createDate;
    int sourceServiceId;
    QString sourceServiceName;
    QString boughtCount;
    int cityId;
    QString cityName;
    QString pageLink;
    bool isArchive;
    friend CouponModel;
};

class CouponModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CouponModel(QObject *parent = 0);

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString sort READ sort WRITE setSort NOTIFY sortChanged)
    Q_PROPERTY(int perPage READ perPage WRITE setPerPage NOTIFY perPageChanged)

    enum CouponRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        MainImageLinkRole,
        CreateTimestampRole,
        CreateDateRole,
        SourceServiceNameRole,
        CityNameRole,
        BoughtCountRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    int count() const;

    QString sort() const
    {
        return m_sort;
    }

    int perPage() const
    {
        return m_perPage;
    }

signals:
    void countChanged();

    void sortChanged(QString sort);

    void perPageChanged(int perPage);

public slots:
    void update();
    void updateFinished(QJsonDocument json);

    void setSort(QString sort)
    {
        if (m_sort == sort)
            return;

        m_sort = sort;
        emit sortChanged(sort);
    }

    void setPerPage(int perPage)
    {
        if (m_perPage == perPage)
            return;

        m_perPage = perPage;
        emit perPageChanged(perPage);
    }

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<CouponItem> m_items;
    QNetworkReply *currentReply;
    QString m_sort;
    int m_perPage;
};

#endif // COUPONMODEL_H

