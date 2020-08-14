import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        objectName: "textObject"
        id: text1
        x: 168
        y: 157
        width: 169
        height: 75
        text: qsTr("Text")
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 1
        font.pixelSize: 12
         anchors.centerIn: parent
    }
}
