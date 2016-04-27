import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0

import com.github.qtrestexample.skidkzapi 1.0
import com.github.qtrest.jsonrestlistmodel 1.0
import com.github.qtrest.pagination 1.0
import com.github.qtrest.requests 1.0

import "includes" as I

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 800

    title: qsTr("Skid.KZ")

    property string searchSource: "qrc:/Search.qml"

    SkidKZApi {
        id: skidKZApi

        baseUrl: "http://api.skid.kz"

        authTokenHeader: "Authorization"
        authToken: "Bearer 8aef452ee3b32466209535b96d456b06"

        Component.onCompleted: console.log("completed!");
    }

    JsonRestListModel {
        id: categoriesRestModel
        api: skidKZApi

        idField: 'id'

        requests {
            get: "/v1/categories"
        }

        sort: ['categoryName']

        pagination {
            policy: Pagination.PageNumber
            perPage: 20
            currentPageHeader: "X-Pagination-Current-Page"
            totalCountHeader: "X-Pagination-Total-Count"
            pageCountHeader: "X-Pagination-Page-Count"
        }

        Component.onCompleted: { console.log(pagination.perPage); reload(); }
    }

    Settings {
        id: settings
        property string style: "Material"
        property int spacing: utils.mm(1)
        property int bottomPadding: utils.mm(2)
        property int topPadding: utils.mm(2)
        property int busyIndicatorSize: 40
    }

    header: ToolBar {
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                id: menuBtn
                label: Image {
                    anchors.centerIn: parent
                    source: stackView.depth > 1 ? awesome.iconLink( "chevronleft", {}, "mdpi" )
                                                : awesome.iconLink( "bars", {}, "mdpi" )
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: titleLabel
                text: "Skid.KZ - " + stackView.currentItem.titleText
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            Item {
                width: menuBtn.width
                height: width

                ToolButton {
                    id: searchBtn
                    visible: stackView.depth == 1
                    label: Image {
                        anchors.centerIn: parent
                        source: awesome.iconLink( "search", {}, "mdpi" )
                    }
                    onClicked: {
                        if (stackView.depth > 1) {
                            stackView.pop()
                        } else {
                            stackView.push(searchSource, {categoriesModel: categoriesRestModel})
                        }
                    }
                }

                Item {
                    visible: stackView.depth > 1
                    width: menuBtn.width
                    height: width
                }
            }
        }
    }

    I.Utils { id: utils }

    Image {
        id: background
        source: "qrc:/images/bgvar1.png"
        fillMode: Image.Tile
        anchors.fill: parent
    }

    Drawer {
        id: drawer

        Pane {
            padding: 0
            width: Math.min(root.width, root.height) * 0.8
            height: root.height

            ListView {
                id: listView
                currentIndex: -1
                anchors.fill: parent

                delegate: ItemDelegate {
                    width: parent.width
                    text: model.title
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        if (listView.currentIndex != index) {
                            listView.currentIndex = index
                            stackView.replace(model.source)
                        }
                        drawer.close()
                    }
                }

                model: ListModel {
                    ListElement { title: qsTr("Actual"); source: "qrc:/ActualCouponsList.qml" }
                    ListElement { title: qsTr("Archive"); source: "qrc:/ArchiveCouponsList.qml" }
                    ListElement { title: qsTr("Statistics"); source: "qrc:/Statistics.qml" }
                    ListElement { title: qsTr("About"); source: "qrc:/About.qml" }
                }

                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }
        onClicked: close()
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: ActualCouponsList {
            anchors.fill: parent
        }

        pushEnter: Transition {
            XAnimator { from: root.width; to: 0; duration: 200; easing.type: Easing.OutCubic }
        }

        pushExit: Transition {
            XAnimator { from: 0; to: -root.width; duration: 200; easing.type: Easing.OutCubic }
        }

        popEnter: Transition {
            XAnimator { from: -root.width; to: 0; duration: 200; easing.type: Easing.OutCubic }
        }

        popExit: Transition {
            XAnimator { from: 0; to: root.width; duration: 200; easing.type: Easing.OutCubic }
        }

        replaceEnter: Transition {
            XAnimator { from: root.width; to: 0; duration: 200; easing.type: Easing.OutCubic }
        }

        replaceExit: Transition {
            XAnimator { from: 0; to: -root.width; duration: 200; easing.type: Easing.OutCubic }
        }
    }

    onClosing: {
        if (stackView.depth > 1) {
            stackView.pop()
            close.accepted = false
        }
    }
}
