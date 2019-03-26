import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

SplitView {
    x: 0
    y: 0
    width: parent.width
    height: parent.height
    orientation: Qt.Horizontal

    // Friends list
    Rectangle {
        width: 58
        color: "#ebebeb"
        Layout.minimumWidth: 58
        Layout.maximumWidth: 160

        ListModel {
            id: model
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
            ListElement { imagePath: "/image/HeadMale.png"; imageName: "Male" }
            ListElement { imagePath: "/image/HeadFemale.png"; imageName: "Female" }
            ListElement { imagePath: "/image/Anonymous.png"; imageName: "Anonymous" }
        }

        ListView {
            id: listView
            anchors.fill: parent
            model: model
            delegate: Rectangle {
                id: delegateItem
                height: 50
                width: parent.width
                color: "transparent"
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: {
                        listView.currentIndex = index
                        if(mouse.button & Qt.RightButton) {
                            menu.popup()
                        }
                    }
                }
                Image {
                    id: listViewImg
                    x: 10
                    y: 5
                    width: 40
                    height: 40
                    source: imagePath
                }
                Text {
                    x: 58
                    width: parent.width
                    height: parent.height
                    font.pointSize: 10
                    verticalAlignment: Text.AlignVCenter
                    text: imageName
                }
            }
            highlight: Component {
                Rectangle {
                    width: parent.width
                    height: 50
                    color: "#dbdbdb"
                    y: listView.currentItem.y
                    Behavior on y {
                        SpringAnimation {
                            spring: 3
                            damping: 0.2
                        }
                    }
                }
            }
            highlightFollowsCurrentItem: false
            focus: true
            Menu {
                id: menu
                MenuItem { text: qsTr("查看信息") }
                MenuItem { text: qsTr("删除好友") }
            }
        }
    }

    // Friend communication
    Rectangle {
        id: centerItem
        color: "gray"
        Layout.fillWidth: true
        Rectangle{
            id: friendTitleRect
            x: 0
            y: 0
            height: 30
            width: parent.width
            color: "white"
            Button{
                id: configBtn
                x: parent.width - 32
                y: 5
                width: 20
                height: 20
                style: ButtonStyle {
                    label: Image {
                        source: control.hovered ? (control.pressed ? "/image/BtnConfig_hover.png" : "/image/BtnConfig_hover.png") : "/image/BtnConfig_normal.png"
                        fillMode: Image.PreserveAspectFit
                    }
                    background: Rectangle{ color: "transparent" }
                    padding { left: 0; right: 0;  top: 0; bottom: 0 }
                }
            }
        }

        SplitView{
            x: 0
            y: 30
            width: parent.width
            height: parent.height - 60
            orientation: Qt.Vertical

            Rectangle{
                id: friendCommRect
                Layout.fillHeight: true
                Text {
                    text: "communications"
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                id: friendDraftRect
                height: 100
                Layout.minimumHeight: 100
                Layout.maximumHeight: 270
                Button{
                    id: fontBtn
                    x: 6
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnFont_hover.png" : "/image/BtnFont_hover.png") : "/image/BtnFont_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }

                Button{
                    id: faceBtn
                    x: fontBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnFace_hover.png" : "/image/BtnFace_hover.png") : "/image/BtnFace_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }
                Button{
                    id: scissorBtn
                    x: faceBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnScissors_hover.png" : "/image/BtnScissors_hover.png") : "/image/BtnScissors_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }
                Button{
                    id: shakeBtn
                    x: scissorBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnShake_hover.png" : "/image/BtnShake_hover.png") : "/image/BtnShake_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }
                Button{
                    id: microphoneBtn
                    x: shakeBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnMicrophone_hover.png" : "/image/BtnMicrophone_hover.png") : "/image/BtnMicrophone_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }
                Button{
                    id: photoBtn
                    x: microphoneBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnPhoto_hover.png" : "/image/BtnPhoto_hover.png") : "/image/BtnPhoto_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }
                Button{
                    id: fileBtn
                    x: photoBtn.x + 30
                    y: 6
                    width: 20
                    height: 20
                    style: ButtonStyle {
                        label: Image {
                            source: control.hovered ? (control.pressed ? "/image/BtnFile_hover.png" : "/image/BtnFile_hover.png") : "/image/BtnFile_normal.png"
                            fillMode: Image.PreserveAspectFit
                        }
                        background: Rectangle{ color: "transparent" }
                        padding { left: 0; right: 0;  top: 0; bottom: 0 }
                    }
                }

                Button{
                    id: historyBtn
                    x: parent.width - 70
                    y: 6
                    width: 60
                    height: 20
                    text: qsTr("消息记录")
                    style: ButtonStyle {
                        label: Text {
                            renderType: Text.NativeRendering
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            font.family: "fixed"
                            font.pointSize: 10
                            color: "#888888"
                            text: control.text
                        }
                        background: Rectangle{
                            color: control.hovered ? "#f2f2f2" : "#ffffff"
                        }
                    }
                }

                Text{
                    text: "Draft"
                    anchors.centerIn: parent
                }
            }
        }

        Rectangle{
            x: 0
            y: parent.height - 30
            width: parent.width
            height: 30

            Button{
                id: sendMsgBtn
                x: parent.width - 70
                y: 0
                width: 60
                height: 20
                text: qsTr("发送(&s)")
                style: ButtonStyle {
                    label: Text {
                        renderType: Text.NativeRendering
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "fixed"
                        font.pointSize: 10
                        color: "white"
                        text: control.text
                    }
                    background: Rectangle{
                        color: control.hovered ? "#0188fb" : "#289cfe"
                    }
                }
            }
        }



    }
 }
