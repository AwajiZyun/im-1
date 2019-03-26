import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
    id: registWindow
    width: 300
    height: 470
    modality: Qt.ApplicationModal
    flags: Qt.FramelessWindowHint | Qt.Window

    Rectangle{
        id: rect
        anchors.fill: parent
        radius: 5
        color: "#ebebeb"
        MouseArea {
            id: mouseMoveWindowArea
            anchors.fill: parent
            property int dx
            property int dy
            onPressed: {
                dx = mouseX
                dy = mouseY
            }
            onPositionChanged: {
              registWindow.x += mouseX - dx
              registWindow.y += mouseY - dy
            }
        }

        Image{
            id: backgroundImg
            x: 0
            y: 0
            width: parent.width
            height: 45
            smooth: true
            source: "/image/LoginBG.png"
        }

        Button{
            id: btnClose
            x: 268
            y: 10
            width: 25
            height: 25
            style: ButtonStyle{
                label: Image {
                    anchors.fill: parent
                    source: control.hovered ? (control.pressed ? "/image/close_down.png" : "/image/close_hover.png") : "/image/close_normal.png"
                    fillMode: Image.PreserveAspectFit
                }
                background: Rectangle{
                    color: "transparent"
                }
                padding {
                    left: 0
                    right: 0
                    top: 0
                    bottom: 0
                }
            }
            onClicked: {
                registWindow.close()
            }
        }

        Image{
            id: headIconImg
            x: 113
            y: 60
            width: 95
            height: 95
            source: "/image/HeadMale.png"
        }

        Label{
            x: 25
            y: 170
            width: 70
            height: 30
            text: qsTr("昵称")
            horizontalAlignment: Text.AlignRight
            font.pointSize: 11
            verticalAlignment: Text.AlignVCenter
            color: "#a8a8a8"
        }

        Label{
            x: 25
            y: 210
            width: 70
            height: 30
            text: qsTr("ID")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            color: "#a8a8a8"
        }

        Label{
            x: 25
            y: 250
            width: 70
            height: 30
            text: qsTr("邮箱")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            color: "#a8a8a8"
        }

        Label{
            x: 25
            y: 290
            width: 70
            height: 30
            text: qsTr("性别")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            color: "#a8a8a8"
        }

        Label{
            x: 25
            y: 330
            width: 70
            height: 30
            text: qsTr("密码")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            color: "#a8a8a8"
        }

        Label{
            x: 25
            y: 370
            width: 70
            height: 30
            text: qsTr("密码确认")
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
            color: "#a8a8a8"
        }

        TextField{
            id: nickNameText
            x: 110
            y: 170
            width: 130
            height: 30
        }

        TextField{
            id: idText
            x: 110
            y: 210
            width: 130
            height: 30
            readOnly: true
        }

        TextField{
            id: mailAddressText
            x: 110
            y: 250
            width: 130
            height: 30
        }

        ComboBox{
            id: sexCombo
            x: 110
            y: 290
            width: 130
            height: 30
            currentIndex: 0
            model: ListModel {
                id: cbItems
                ListElement { text: qsTr("男"); color: "#a8a8a8" }
                ListElement { text: qsTr("女"); color: "#a8a8a8" }
                ListElement { text: qsTr("其他"); color: "#a8a8a8" }
            }
        }

        TextField{
            id: passwordText
            x: 110
            y: 330
            width: 130
            height: 30
            echoMode: TextInput.Password
        }

        TextField{
            id: passwordConfirmText
            x: 110
            y: 370
            width: 130
            height: 30
            echoMode: TextInput.Password
        }

        Button{
            id: registBtn
            x: 110
            y: 418
            width: 120
            height: 30
            text: qsTr("保  存")
            style: ButtonStyle {
                label: Text {
                    renderType: Text.NativeRendering
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "fixed"
                    font.pointSize: 10
                    color: "#ffffff"
                    text: control.text
                }
                background: Rectangle{
                    radius: 5
                    color: control.hovered ? (control.pressed ? "#098cbc" : "#3cc3f5") : "#00a3fe"
                }
            }
        }
    }
}
