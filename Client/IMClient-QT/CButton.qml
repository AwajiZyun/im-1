import QtQuick 2.9

Item {
    id: button

    property string buttonNormalImage: ""
    property string buttonPressedImage: ""
    property string buttonHoverImage: ""
    property string buttonDisableImage: ""
    property bool buttonDisable: false

    signal clicked();
    signal exited();
    signal entered();

    Image {
        id: buttonImage
        anchors.fill: parent
        source: buttonNormalImage
        MouseArea {
            id: buttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                cursorShape = Qt.PointingHandCursor;
                if(false == buttonDisable){
                    button.entered();
                    buttonImage.source = buttonHoverImage;
                }
            }
            onPressed:{
                if(false == buttonDisable){
                    buttonImage.source = buttonPressedImage;
                }
            }
            onClicked: {
                if(false == buttonDisable){
                    button.clicked();
                    buttonImage.source = buttonPressedImage;
                }
            }
            onExited: {
                if(false == buttonDisable){
                    button.exited();
                    buttonImage.source = buttonNormalImage;
                }
            }
        }
    }

    onButtonDisableChanged : {
        buttonDisable === false ? (buttonImage.source = buttonNormalImage)
                                : (buttonImage.source = buttonDisableImage);
    }
}
