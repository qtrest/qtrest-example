import QtQuick 2.6
import QtQuick.Controls 2.0


Rectangle {
    //anchors.fill: parent

    property var parentItem: stackView.get(stackView.depth-2, StackView.DontLoad)
    property var categoriesModel
    property var loadingStatus: categoriesModel.loadingStatus

    property string titleText: qsTr("Search")

    Image {
        id: background
        source: "qrc:/images/bgvar1.png"
        fillMode: Image.Tile
        anchors.fill: parent
    }

    ListView {
        id: listView
        anchors.fill: parent

        model: categoriesModel

        delegate: ItemDelegate {
            width: parent.width
            text: model.categoryName
            highlighted: ListView.isCurrentItem
            onClicked: {
                parentItem.setCategory(model.categoryName, model.categoryIdentifier)
                stackView.pop()
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }
}
