import QtQuick 2.5
import QtQuick.Dialogs 1.2
import "includes" as I
import ru.forsk.adctl 1.0
import QtQuick.Layouts 1.2
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 800
    title: qsTr("Skid.KZ")

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
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id: menuBtn
                label: Image {
                    anchors.centerIn: parent
                    source: awesome.iconLink( "bars", "xxhdpi" )
                }
                onClicked: drawer.open()
            }

            Label {
                id: titleLabel
                text: "Skid.KZ"
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
            width: Math.min(root.width, root.height) / 3 * 2
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
                            titleLabel.text = model.title
                            stackView.replace(model.source)
                        }
                        drawer.close()
                    }
                }

                model: ListModel {
                    ListElement { title: "Actual"; source: "qrc:/ActualCouponsList.qml" }
                    ListElement { title: "Archive"; source: "qrc:/ArchiveCouponsList.qml" }
                    ListElement { title: "Statistics"; source: "qrc:/Statistics.qml" }
                    ListElement { title: "About"; source: "qrc:/About.qml" }
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
}
