import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import Qt.IM.Network 1.0

ApplicationWindow {
    id: loginWindow
    visible: true
    width: 432
    height: 332
    title: qsTr("IM")
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.WindowSystemMenuHint| Qt.WindowMinimizeButtonHint| Qt.Window

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
              loginWindow.x += mouseX - dx
              loginWindow.y += mouseY - dy
            }
        }

        Image {
            id: backgroundImg
            x: 0
            y: 0
            width: parent.width
            height: 183
            smooth: true
            source: "/image/LoginBG.png"
        }

        Image {
            id: logoImg
            x: 135
            y: 45
            width: 180
            height: 80
            //fillMode: Image.TileHorizontally
            smooth: true
            source: "/image/Logo.png"
        }

        Button{
            id: btnMenu
            x: 350
            y: 12
            width: 25
            height: 25
            style: ButtonStyle{
                label: Image {
                    source: control.hovered ? (control.pressed ? "/image/menu_down.png" : "/image/menu_hover.png") : "/image/menu_normal.png"
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
        }

        Button{
            id: btnMin
            x: 375
            y: 12
            width: 25
            height: 25
            style: ButtonStyle{
                label: Image {
                    source: control.hovered ? (control.pressed ? "/image/min_down.png" : "/image/min_hover.png") : "/image/min_normal.png"
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
                loginWindow.showMinimized()
            }
        }

        Button{
            id: btnClose
            x: 400
            y: 12
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
                loginWindow.close()
            }
        }

        Image{
            id: imgHead
            x: 40
            y: 197
            width: 85
            height: 85
            smooth: true
            source: "/image/HeadMale.png"
        }

        ComboBox{
            id: comboUsrID
            x: 136
            y: 196
            width: 192
            height: 30
            editable: true
            model: ListModel {
                id: cbItems
                ListElement { text: "500001"; }
            }
        }

        TextField{
            id: textFieldUsrPwd
            x: 136
            y: 226
            width: 192
            height: 30
            echoMode: TextInput.Password
        }

        CheckBox{
            id: checkSavePwd
            x: 136
            y: 263
            width: 100
            height: 18
            text: qsTr("记住密码")
            style: CheckBoxStyle{
                label: Text {
                    horizontalAlignment: Text.AlignLeft
                    font.family: "fixed"
                    font.pointSize: 10
                    color: "#919191"
                    text: control.text
                }
            }
        }

        CheckBox{
            id: checkAutoLogin
            x: 260
            y: 263
            width: 100
            height: 18
            text: qsTr("自动登录")
            style: CheckBoxStyle{
                label: Text {
                    horizontalAlignment: Text.AlignLeft
                    font.family: "fixed"
                    font.pointSize: 10
                    color: "#919191"
                    text: control.text
                }
            }
        }

        Button{
            id: btnLogin
            x: 136
            y: 288
            width: 195
            height: 30
            text: qsTr("登  录")
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
                    color: control.enabled ? (control.hovered ? (control.pressed ? "#098cbc" : "#3cc3f5") : "#00a3fe") : "#cccccc"
                }
            }
            onClicked: {
                btnLogin.enabled = false;
                NetApi.start("193.112.95.23", 10090);
                NetApi.sendLoginRequest(comboUsrID.editText, textFieldUsrPwd.text)
            }
            Connections{
                target: NetApi
                onSignalLoginResponse:{
                    btnLogin.enabled = true;
                    if(arguments[0] === 0){
                        console.log("login OK ");
                        var component = Qt.createComponent("/WindowMain.qml")
                        var window    = component.createObject()
                        loginWindow.visible = false
                        window.show()
                    }
                    else{
                        console.log("login NG：" + arguments[1]);
                        NetApi.stop();
                    }
                }
                onSignalError:{
                    btnLogin.enabled = true;
                    console.log("login NG：" + arguments[0]);
                    NetApi.stop();
                }
            }
        }

        Button{
            id: btnRegist
            x: 340
            y: 200
            width: 60
            height: 24
            text: qsTr("注册账号")
            Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
            style: ButtonStyle {
                label: Text {
                    renderType: Text.NativeRendering
                    horizontalAlignment: Text.AlignLeft
                    font.family: "fixed"
                    font.pointSize: 10
                    color: control.hovered ? (control.pressed ? "#1b7dba" : "#62b4f7") : "#2786e4"
                    text: control.text
                }
                background: Rectangle{
                    color: "transparent"
                }
            }
            onClicked: {
                dialogRegistModal.show()
            }
        }

        Button{
            id: btnFindPwd
            x: 340
            y: 230
            width: 60
            height: 24
            text: qsTr("找回密码")
            Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
            style: ButtonStyle {
                label: Text {
                    renderType: Text.NativeRendering
                    horizontalAlignment: Text.AlignLeft
                    font.family: "fixed"
                    font.pointSize: 10
                    color: control.hovered ? (control.pressed ? "#1b7dba" : "#62b4f7") : "#2786e4"
                    text: control.text
                }
                background: Rectangle{
                    color: "transparent"
                }
            }
        }
    }

    DialogRegist{
        id: dialogRegistModal
    }

}
