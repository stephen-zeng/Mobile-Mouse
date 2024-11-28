// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls

Rectangle {
    id: root
    color: "black"

    signal backToMode;
    signal goToServer2;

    Timer {
        id: timerFromServer1Page
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if (beServer.clientconnect) contentText.text = "已连接";
            else contentText.text = "等待连接";
            if (beServer.senddata) footer.buttonText2 = "暂停";
            else footer.buttonText2 = "开始";
        }
    }

    Header {
        id: header

        rightIsShown: true
        headerText: "按钮控制"
        rightButtonText: "陀螺仪"
        onBackButtonClicked: {
            root.backToMode();
        }
        onRightButtonClicked: {
            root.goToServer2();
            getSensor.startUpdates();
        }
    }

    Rectangle {
        id: contentTextRec

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        anchors.topMargin: 50
        width: parent.width
        Text {
            id: contentText
            color: "white"
            text:""
            visible: true
            font.pixelSize: 25
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: touchArea
        color: "black"
        border.color: "lightblue"
        border.width: 5
        width: parent.width

        anchors.top: contentTextRec.bottom
        anchors.bottom: footer.top
        anchors.topMargin: 50
        anchors.bottomMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter

        MouseArea {
            anchors.fill: parent
            property int yStart: 0
            property bool tracing: false

            onPressed: {
                yStart = mouse.y
                tracing = true
            }
            onPositionChanged: {
                if (!tracing) return;
            }
            onReleased: {
                if (!tracing) return;
                if (mouse.y - yStart >= root.height * 0.2)
                    beServer.motionData(0, 0, 3); // Swipe down
                    // console.log("Swipe down");
                if (yStart - mouse.y >= root.height * 0.2)
                    beServer.motionData(0, 0, 4); //Swipe up
                    // console.log("Swipe up");
                tracing = false
            }
        }
    }

    Footer {
        id: footer

        buttonText1: "移动速度: " + beServer.speed
        buttonText2: "暂停"

        onButton2Clicked: {
            if (beServer.senddata) beServer.senddata = false;
            else beServer.senddata = true;
        }

        onButton1Clicked: {
            beServer.upSpeed();
        }
        onButton1PressAndHold: {
            beServer.downSpeed();
        }
    }

    Button {
        id: clickBtn
        highlighted: true
        anchors.horizontalCenter: parent.horizontalCenter;
        y: root.height * 0.4
        width: 80
        height: 80

        onClicked: {
            beServer.sig = 5;
            beServer.generateData();
        }

        onPressAndHold: {
            beServer.sig = 6;
            beServer.generateData();
        }

        onDoubleClicked: {
            console.log("Double Clicked");
            beServer.sig = 7;
            beServer.generateData();
        }

        Text {
            text: "CLICK"
            anchors.centerIn: parent
        }
    }

    Button {
        id: upBtn
        highlighted: true
        width: clickBtn.width
        height: clickBtn.height
        autoRepeat: true
        anchors.bottom: clickBtn.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        onPressed: {
            beServer.sig = 1;
            beServer.generateData();
        }

        Text {
            text: "UP"
            anchors.centerIn: parent
        }
    }

    Button {
        id: downBtn
        highlighted: true
        width: clickBtn.width
        height: clickBtn.height
        autoRepeat: true
        anchors.top: clickBtn.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        onPressed: {
            beServer.sig = 2;
            beServer.generateData();
        }

        Text {
            text: "DOWN"
            anchors.centerIn: parent
        }
    }

    Button {
        id: leftBtn
        highlighted: true
        width: clickBtn.width
        height: clickBtn.height
        y: root.height * 0.4
        autoRepeat: true
        anchors.right: clickBtn.left
        anchors.rightMargin: 10

        onPressed: {
            beServer.sig = 3;
            beServer.generateData();
        }

        Text {
            text: "LEFT"
            anchors.centerIn: parent
        }
    }

    Button {
        id: rightBtn
        highlighted: true
        width: clickBtn.width
        height: clickBtn.height
        y: root.height * 0.4
        autoRepeat: true
        anchors.left: clickBtn.right
        anchors.leftMargin: 10

        onPressed: {
            beServer.sig = 4;
            beServer.generateData();
        }

        Text {
            text: "RIGHT"
            anchors.centerIn: parent
        }
    }

    Rectangle {
        color: "black"
        id: deviceName
        anchors.topMargin: 30
        anchors.top: downBtn.bottom
        width: parent.width

        Text {
            id: text1
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            text: "如果你的设备是iOS设备，则名称为"
            font.pixelSize: 15
        }

        Text {
            id: text2
            color: "white"
            anchors.top: text1.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: "SZ Remote Device"
            font.pixelSize: 15
        }

        Text {
            id: text3
            color: "white"
            anchors.top: text2.bottom
            anchors.topMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            text: "如果你的设备是安卓设备，则名称为设备名称"
            font.pixelSize: 15
        }
    }

    MessageDialog {
        id: beServerError
        title: "通知"
        text: beServer.msg
        visible: beServer.msgbox
        onAccepted: {
            beServerError.visible = false;
            beServer.msgbox = false;
        }
    }

}
