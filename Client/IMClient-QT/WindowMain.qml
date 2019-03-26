import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 760
    height: 660
    title: qsTr("IM")
    color: "#ffffff"
    flags: Qt.FramelessWindowHint | Qt.WindowSystemMenuHint| Qt.WindowMinimizeButtonHint| Qt.Window

    Rectangle{
        anchors.fill: parent

        MouseArea{
            id: mouseMoveWindowArea
            anchors.fill: parent
            property int dx
            property int dy
            onPressed: {
                dx = mouseX
                dy = mouseY
            }
            onPositionChanged: {
              mainWindow.x += mouseX - dx
              mainWindow.y += mouseY - dy
            }
        }

        // title bar
        Rectangle{
            x: 0
            y: 0
            width: parent.width
            height: 55
            Image{
                id: backgroundImg
                anchors.fill: parent
                smooth: true
                source: "/image/MainBG.png"
            }
            Button{
                id: headIconBtn
                x: 10
                y: 8
                width: 40
                height: 40
                Component.onCompleted: __behavior.cursorShape = Qt.PointingHandCursor
                style: ButtonStyle{
                    label: Image {
                        source: control.hovered ? "/image/HeadMaleHot.png" : "/image/HeadMale.png"
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
                    dialogUserInfo.show()
                }
            }
            // sub page buttons
            Button{
                id: pageMessageBtn
                x: parent.width / 2 - 60
                y: 7
                width: 40
                height: 50
                style: ButtonStyle{
                    label: Image {
                        source: messageSubPage.visible ? "/image/message_down.png" :
                            control.hovered ? "/image/message_hover.png" : "/image/message_normal.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{
                        color: "transparent"
                    }
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
                onClicked: {
                    messageSubPage.visible = true
                    contactorSubPage.visible = false
                }
            }
            Button{
                id: pageContactorBtn
                x: parent.width / 2 + 10
                y: 7
                width: 40
                height: 50
                style: ButtonStyle{
                    label: Image {
                        source: contactorSubPage.visible ? "/image/contactor_down.png" :
                            control.hovered ? "/image/contactor_hover.png" : "/image/contactor_normal.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{
                        color: "transparent"
                    }
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
                onClicked: {
                    messageSubPage.visible = false
                    contactorSubPage.visible = true
                }
            }

            // window buttons
            Button{
                id: configBtn
                x: parent.width - 115
                y: 17
                width: 25
                height: 25
                style: ButtonStyle{
                    label: Image {
                        source: control.hovered ? (control.pressed ? "/image/config_down.png" : "/image/config_hover.png") : "/image/config_normal.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{
                        color: "transparent"
                    }
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
            }
            Button{
                id: minBtn
                x: parent.width - 90
                y: 17
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
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
                onClicked: {
                    mainWindow.showMinimized()
                }
            }
            Button{
                id: maxBtn
                x: parent.width - 65
                y: 17
                width: 25
                height: 25
                style: ButtonStyle{
                    label: Image {
                        id: maxBtnImg
                        source: mainWindow.visibility == Window.Windowed ?
                                    (control.hovered ? (control.pressed ? "/image/max_down.png" : "/image/max_hover.png") : "/image/max_normal.png") :
                                    (control.hovered ? (control.pressed ? "/image/restore_down.png" : "/image/restore_hover.png") : "/image/restore_normal.png")
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{
                        color: "transparent"
                    }
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
                onClicked: {
                    if(mainWindow.visibility == Window.Maximized){
                        mainWindow.visibility = Window.Windowed
                    }
                    else{
                        mainWindow.visibility = Window.Maximized
                    }
                }
            }
            Button{
                id: minClose
                x: parent.width - 40
                y: 17
                width: 25
                height: 25
                style: ButtonStyle{
                    label: Image {
                        source: control.hovered ? (control.pressed ? "/image/close_down.png" : "/image/close_hover.png") : "/image/close_normal.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{
                        color: "transparent"
                    }
                    padding { left: 0; right: 0; top: 0; bottom: 0; }
                }
                onClicked: {
                    mainWindow.close()
                }
            }
        }

        Item {
            id: subPageLoader
            x: 0
            y: 55
            width: parent.width
            height: parent.height - 55

            MessageSubPage {
                id: messageSubPage
                visible: true
            }
            ContactorSubPage{
                id: contactorSubPage
                visible: false
            }
        }

        DialogUserInfo{
            id: dialogUserInfo
        }
    }

}
