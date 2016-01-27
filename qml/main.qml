import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import ru.forsk.coupons 1.0
import "includes" as I
import ru.forsk.adctl 1.0
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 800
    title: qsTr("Skid.KZ")

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                iconSource: awesome.iconLink( "beer", "xxhdpi" )
            }
        }
    }

    AdCtl {
        id: adCtl

        //manage enabled components
        adMobBannerEnabled: true
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

    CouponModel {
        id: coupons;
        sort: "-id"
        perPage: 50
        Component.onCompleted: update()
    }

    Image {
        id: background
        source: "qrc:/images/bgvar1.png"
        fillMode: Image.Tile
        anchors.fill: parent
    }

    StackView {
        id: stack
        initialItem: couponsList
        anchors.fill: parent

        Component {
            id: couponsList

            CouponsList {
                anchors.fill: parent
            }
        }
    }
}
