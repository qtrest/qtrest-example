#include "jsonrestlistmodel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

JsonRestListModel::JsonRestListModel(QObject *parent) : BaseRestListModel(parent)
{

}

void JsonRestListModel::fetchMoreFinished(QJsonDocument json, QNetworkReply *reply)
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
        clearForReload();
        insertFrom = rowCount();
        insertCount = jsonArray.count()-1;
    }

    //append rows to model
    beginInsertRows(this->index(rowCount(), 0), insertFrom, insertCount);

    //http://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();

        Item item = getItem(obj.toVariantMap());

        append(item);
    }

    //get all role names
    generateRoleNames();

    endInsertRows();

    setLoadingStatus(LoadingStatus::Idle);

    emit countChanged();
}
