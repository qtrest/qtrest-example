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
    void fetchMoreFinished(QJsonDocument json, QNetworkReply *reply);
};

#endif // RESTLISTMODEL_H
