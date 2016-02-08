#ifndef RESTLISTMODEL_H
#define RESTLISTMODEL_H

#include <QJsonDocument>
#include <QtQml>

#include "baserestlistmodel.h"

class QNetworkReply;

class JsonRestListModel : public BaseRestListModel
{
    Q_OBJECT
public:
    explicit JsonRestListModel(QObject *parent = 0);

public slots:
    void fetchMoreFinished();
    void fetchDetailFinished();

private:
    QJsonDocument getJSONDocument(QByteArray bytes);
};

#endif // RESTLISTMODEL_H
