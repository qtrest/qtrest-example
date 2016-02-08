#include "jsonrestlistmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include "detailsmodel.h"

JsonRestListModel::JsonRestListModel(QObject *parent) : BaseRestListModel(parent)
{
    setAccept("application/json");
}

void JsonRestListModel::fetchMoreFinished()
{
    qDebug() << "fetchMoreFinished";

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (api.checkReplyIsError(reply) || !reply->isFinished()) {
        return;
    }

    if (this->loadingStatus() == LoadingStatus::Idle) {
        return;
    }

    QJsonDocument json = getJSONDocument(reply->readAll());

    //TODO check is reply for me

    updateHeadersData(reply);

    QJsonArray jsonArray = json.array();

    //prepare vars
    int insertFrom = rowCount();
    int insertCount = rowCount()+jsonArray.count()-1;

    //check if we need to full reload
    if (this->loadingStatus() == LoadingStatus::FullReloadProcessing) {
        clearForReload();
        insertFrom = rowCount();
        insertCount = jsonArray.count()-1;
    }

    //append rows to model
    beginInsertRows(this->index(rowCount(), 0), insertFrom, insertCount);

    //http://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        Item item = createItem(obj.toVariantMap());

        append(item);
    }

    //get all role names
    generateRoleNames();

    endInsertRows();

    detailsModel()->setSourceModel(this);

    setLoadingStatus(LoadingStatus::Idle);

    emit countChanged();
}

void JsonRestListModel::fetchDetailFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (api.checkReplyIsError(reply) || !reply->isFinished()) {
        return;
    }

    if (this->loadingStatus() == LoadingStatus::Idle) {
        return;
    }

    QJsonDocument json = getJSONDocument(reply->readAll());

    QJsonObject obj = json.object();

    updateItem(obj.toVariantMap());

    detailsModel()->setSourceModel(this);
}

QJsonDocument JsonRestListModel::getJSONDocument(QByteArray bytes)
{
    QString str = QString::fromUtf8(bytes.data(), bytes.size());

    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << parseError.errorString();
    }

    return document;
}
