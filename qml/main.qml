import QtQuick 2.6
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0

import "includes" as I
import ru.forsk.adctl 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 800

    //    width: 360
    //    height: 520

    title: qsTr("Skid.KZ")


    //           [Controls]
    //           Style=Material

    //           [Material]
    //           Primary=BlueGrey
    //           Accent=BlueGrey
    //           Theme=Dark


    Settings {
        id: settings
        property string style: "Material"
        property int spacing: utils.mm(1)
        property int bottomPadding: utils.mm(2)
        property int topPadding: utils.mm(2)
        property int busyIndicatorSize: 40
    }

    //Component.onCompleted: console.log(settings.spacing, settings.bottomPadding, settings.topPadding, settings.busyIndicatorSize )

    header: ToolBar {
        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {
                id: menuBtn
                label: Image {
                    anchors.centerIn: parent
                    source: stackView.depth > 1 ? awesome.iconLink( "chevronleft", {}, "mdpi" ) : awesome.iconLink( "bars", {}, "mdpi" )
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
            }
        }
    }

    AdCtl {
        id: adCtl

        //manage enabled components
        adMobBannerEnabled: false
        adMobIinterstitialEnabled: false
        gAnalyticsEnabled: true

        //set ids
        adMobBannerId: "ca-app-pub-7212327600726803/5192183680"
        gAnalyticsId: "UA-67543404-5"

        //Start positions for banners.
        adMobBannerPosition: Qt.point(0,-500)

        onAdMobBannerShowed: {
            adMobBannerPosition = Qt.point((root.width - adCtl.adMobBannerWidth) * 0.5,
                                           (root.height - adCtl.adMobBannerHeight))
            adCtl.showAdMobBanner()
        }

        //When all variables are setted, we can to initialize our code
        Component.onCompleted: {
            adCtl.init()
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
    }

    onClosing: {
        if (stackView.depth > 1) {
            stackView.pop()
            close.accepted = false
        }
    }
}
