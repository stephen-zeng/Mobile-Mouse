// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick

Rectangle {
    id: root
    color: "black"

    signal backToServer1

    Timer {
        id: timerFromServer2Page
        interval: 34
        running: false
        repeat: true
        onTriggered: {
            beServer.motionData(getSensor.x, getSensor.y, 0);
        }
    }

    Timer {
        id: headerTimer
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if (beServer.clientconnect) contentText.text = "已连接";
            else contentText.text = "等待连接";
        }
    }

    Header {
        id: header

        headerText: "陀螺仪"
        onBackButtonClicked: {
            root.backToServer1();
        }
    }

    Rectangle {
        id: contentTextRec
        color: "black"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.top
        anchors.topMargin: 100
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

    Footer {
        id: footer

        buttonText1: "点击"
        buttonText2: timerFromServer2Page.running ? "暂停" : "开始"

        onButton2Clicked: {
            if (timerFromServer2Page.running) timerFromServer2Page.running = false;
            else timerFromServer2Page.running = true;
        }

        onButton1Clicked: {
            // if (timerFromServer2Page.running) beServer.motionData(getSensor.x, getSensor.y, 1);
            // else
                beServer.motionData(0, 0, 1);
        }
        onButton1PressAndHold: {
            // if (timerFromServer2Page.running) beServer.motionData(getSensor.x, getSensor.y, -1);
            // else
                beServer.motionData(0, 0, -1);
        }
        onButton1DoubleClick: {
            beServer.motionData(0, 0, 2);
        }
    }

    Rectangle {
        id: xRec
        color: "black"

        // color: "blue"
        width: parent.width
        height: parent.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: yRec.top
        anchors.bottomMargin: 25

        Text {
            color: "white"
            anchors.centerIn: parent
            text: "X: " + getSensor.x;
            font.pixelSize: 25
        }
    }

    Rectangle {
        id: yRec
        color: "black"

        // color: "blue"
        width: parent.width
        height: parent.height * 0.1
        anchors.centerIn: parent

        Text {
            color: "white"
            anchors.centerIn: parent
            text: "Y: " + getSensor.y;
            font.pixelSize: 25
        }
    }

    Rectangle {
        id: zRec
        color: "black"

        // color: "blue"
        width: parent.width
        height: parent.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: yRec.bottom
        anchors.topMargin: 25

        Text {
            color: "white"
            anchors.centerIn: parent
            text: "Z: " + getSensor.z;
            font.pixelSize: 25
        }
    }
}
