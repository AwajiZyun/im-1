import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle {
    x: 0
    y: 0
    width: parent.width
    height: parent.height
    Rectangle{
        x: 0
        y: 0
        width: 200
        height: parent.height
        color: "gray"
        Text {
            anchors.centerIn: parent
            text: qsTr("Not")
        }
    }
    Rectangle{
        x: 200
        y: 0
        width: parent.width - 200
        height: parent.height
        color: "white"
        Text {
            anchors.centerIn: parent
            text: qsTr("Ready")
        }
    }
}
