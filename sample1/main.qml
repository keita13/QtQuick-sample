import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Sample1")

    Text {
        id: text1
        x: 17
        y: 8
        width: 222
        height: 69
        text: qsTr("Sample1")
        font.pixelSize: 40
    }

    Button {
        id: button
        x: 17
        y: 220
        text: qsTr("Button")
    }

    CheckBox {
        id: checkBox
        x: 17
        y: 284
        text: qsTr("Check Box")
    }

    ColumnLayout {
        id: columnLayout
        x: 185
        y: 220
        width: 194
        height: 100

        RadioButton {
            id: radioButton
            text: qsTr("Radio Button")
            clip: false
            spacing: 6
            checkable: true
            transformOrigin: Item.Center

        }

        RadioButton {
            id: radioButton1
            text: qsTr("Radio Button")
        }
    }

    Switch {
        id: switch1
        x: 372
        y: 220
        text: qsTr("Switch")
    }

    Rectangle {
        id: rectangle
        color: "#ffffff"
        radius: 18
        border.width: 3
        anchors.right: parent.right
        anchors.rightMargin: 43
        anchors.left: parent.left
        anchors.leftMargin: 43
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 293
        anchors.top: parent.top
        anchors.topMargin: 78
        border.color: "#ff2424"

        TextArea {
            id: textArea
            text: qsTr("Text Area")
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            anchors.topMargin: 10
            anchors.fill: parent
        }
    }

    Dial {
        id: dial
        x: 413
        y: 284
    }
}
