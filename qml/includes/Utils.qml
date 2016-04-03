import QtQuick 2.4
import QtQuick.Window 2.2

Item {
    property int defaultWidth: 800
    property int defaultHeight: 480
    readonly property double scaleFactorPercent: Math.min(Math.min(root.width, root.height) / defaultHeight, Math.max(root.width, root.height) / defaultWidth);
    readonly property int scaleFactor: Screen.logicalPixelDensity;

    function dp(val) { return Math.floor(val ) } //millimeters
    function mm(val) { return Math.floor(val) } //millimeters
    function pt(val) { return Math.floor(val) } //points (dp)
    function pct(val) { return Math.floor(val) } //percents

    function getRandomInt(min, max) {
      return Math.floor(Math.random() * (max - min)) + min;
    }
}
