import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        radius: 10
        border.width: 5
        border.color: "#b9ff72"
        anchors.fill: parent

        Image {
            id: image
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent
            source: "image://videocapture/0"
        }
        ///*
        Timer {
            property int cnt: 0
            interval: 32
            running: true
            repeat: true
            onTriggered: {
                if (image.status === Image.Ready) {
                    image.source = "image://VideoCapture/" + cnt
                    cnt++
                }
            }
        }
        //*/
    }
}
