import QtQuick 2.6
import QtQuick.Controls 2.0

Rectangle {
    id: searchPage
    //anchors.fill: parent

    property var parentItem: stackView.get(stackView.depth-2, StackView.DontLoad)
    property var categoriesModel
    property string searchCategoriesSource: "qrc:/SearchCategories.qml"

    property var loadingStatus: categoriesModel.loadingStatus

    property string titleText: qsTr("Search")

    property string categoryIdentifier
    property string categoryName

    function setCategory(catNm, categoryId)
    {
        categoryIdentifier = categoryId
        categoryName = catNm
        categoryBtn.text = catNm
    }

    Image {
        id: background
        source: "qrc:/images/bgvar1.png"
        fillMode: Image.Tile
        anchors.fill: parent
    }

    Column {
        anchors.centerIn: parent
        Button {
            id: categoryBtn
            text: qsTr("Select category...")
            onClicked: stackView.push(searchCategoriesSource, {categoriesModel: categoriesRestModel})
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: searchBtn
            text: qsTr("Search")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                parentItem.filter({'sourceServiceCategories': categoryIdentifier})
                stackView.pop()
            }
        }
    }
}
