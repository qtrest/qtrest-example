#ifndef RESTLISTMODEL_H
#define RESTLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QtQml>
#include "api/apimanager.h"

class QNetworkReply;

class JsonRestListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit JsonRestListModel(QObject *parent = 0);

    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString sort READ sort WRITE setSort NOTIFY sortChanged)
    Q_PROPERTY(int perPage READ perPage WRITE setPerPage NOTIFY perPageChanged)
    Q_PROPERTY(int currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(int totalCount READ totalCount WRITE setTotalCount NOTIFY totalCountChanged)
    Q_PROPERTY(int pageCount READ pageCount WRITE setPageCount NOTIFY pageCountChanged)
    Q_PROPERTY(LoadingStatus loadingStatus READ loadingStatus WRITE setLoadingStatus NOTIFY loadingStatusChanged)
    Q_PROPERTY(QVariantMap filters READ filters WRITE setFilters NOTIFY filtersChanged)
    Q_PROPERTY(QString loadingErrorString READ loadingErrorString WRITE setLoadingErrorString NOTIFY loadingErrorStringChanged)
    Q_PROPERTY(QNetworkReply::NetworkError loadingErrorCode READ loadingErrorCode WRITE setLoadingErrorCode NOTIFY loadingErrorCodeChanged)

    Q_ENUMS(LoadingStatus)

    enum LoadingStatus {
        Idle,
        RequestToReload,
        FullReloadProcessing,
        LoadMoreProcessing,
        Error
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

    int currentPage() const
    {
        return m_currentPage;
    }

    int totalCount() const
    {
        return m_totalCount;
    }

    int pageCount() const
    {
        return m_pageCount;
    }

    LoadingStatus loadingStatus() const
    {
        return m_loadingStatus;
    }

    QVariantMap filters() const
    {
        return m_filters;
    }

    QString loadingErrorString() const
    {
        return m_loadingErrorString;
    }

    QNetworkReply::NetworkError loadingErrorCode() const
    {
        return m_loadingErrorCode;
    }

signals:
    void countChanged();

    void sortChanged(QString sort);

    void perPageChanged(int perPage);

    void currentPageChanged(int currentPage);

    void totalCountChanged(int totalCount);

    void pageCountChanged(int pageCount);

    void loadingStatusChanged(LoadingStatus loadingStatus);

    void filtersChanged(QVariantMap filters);

    void loadingErrorStringChanged(QString loadingErrorString);

    void loadingErrorCodeChanged(QNetworkReply::NetworkError loadingErrorCode);

public slots:
    void fetchMoreFinished(QJsonDocument json, QNetworkReply *reply);
    bool canFetchMore(const QModelIndex &parent) const;
    void fetchMore(const QModelIndex &parent);
    void reload();

    void replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString);

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

    void setLoadingStatus(LoadingStatus loadingStatus)
    {
        if (m_loadingStatus == loadingStatus)
            return;

        m_loadingStatus = loadingStatus;
        emit loadingStatusChanged(loadingStatus);
    }

    void setFilters(QVariantMap filters)
    {
        if (m_filters == filters)
            return;

        m_filters = filters;
        emit filtersChanged(filters);
    }

    void setLoadingErrorString(QString loadingErrorString)
    {
        if (m_loadingErrorString == loadingErrorString)
            return;

        m_loadingErrorString = loadingErrorString;
        emit loadingErrorStringChanged(loadingErrorString);
    }

    void setLoadingErrorCode(QNetworkReply::NetworkError loadingErrorCode)
    {
        if (m_loadingErrorCode == loadingErrorCode)
            return;

        m_loadingErrorCode = loadingErrorCode;
        emit loadingErrorCodeChanged(loadingErrorCode);
    }

protected slots:
    void setCurrentPage(int currentPage)
    {
        if (m_currentPage == currentPage)
            return;

        m_currentPage = currentPage;
        emit currentPageChanged(currentPage);
    }

    void setTotalCount(int totalCount)
    {
        if (m_totalCount == totalCount)
            return;

        m_totalCount = totalCount;
        emit totalCountChanged(totalCount);
    }

    void setPageCount(int pageCount)
    {
        if (m_pageCount == pageCount)
            return;

        m_pageCount = pageCount;
        emit pageCountChanged(pageCount);
    }

protected:
    virtual void fetchMoreData(const QModelIndex &parent) = 0;
    virtual QVariantMap processItem(QVariantMap item) = 0;

    QHash<int, QByteArray> roleNames() const;
    QNetworkReply *currentReply;
private:
    void updateHeadersData(QNetworkReply *reply);

    QString m_sort;
    int m_perPage;
    int m_currentPage;
    int m_totalCount;
    int m_pageCount;
    LoadingStatus m_loadingStatus;
    QVariantMap m_filters;
    QString m_loadingErrorString;
    QNetworkReply::NetworkError m_loadingErrorCode;

    //second chance
    QHash<int, QByteArray> m_roleNames;
    int m_roleNamesIndex;
    QList<QVariantMap> m_items;
};

#endif // RESTLISTMODEL_H

