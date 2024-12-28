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
            timerFromServer2Page.running = false;
            beServer.senddata = false;
        }
    }

    Rectangle {
        id: contentTextRec
        color: "black"

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

    Footer {
        id: footer

        buttonText1: "移动速度: " + beServer.speed;
        buttonText2: timerFromServer2Page.running ? "暂停" : "开始"

        onButton2Clicked: {
            if (timerFromServer2Page.running) timerFromServer2Page.running = false;
            else timerFromServer2Page.running = true;
        }

        onButton1Clicked: {
            beServer.upSpeed();
        }
        onButton1PressAndHold: {
            beServer.downSpeed();
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


        Text {
            color: "white"
            text: "Click Area"
            anchors.centerIn: parent
            font.pixelSize: 25
        }

        MouseArea {
            property int yStart: 0
            property bool tracing: false

            height: parent.height
            width: parent.width - 60
            anchors.centerIn: parent
            onPressed: {
                timerFromServer2Page.running = false;
            }
            onReleased: {
                timerFromServer2Page.running = true;
            }

            onClicked: {
                beServer.motionData(0, 0, 1); // Left Click
            }
            onPressAndHold: {
                beServer.motionData(0, 0, -1); // Right Click
            }
            onDoubleClicked: {
                beServer.motionData(0, 0, 2); // Double Click
            }
        }

        MouseArea {
            height: parent.height
            width: 30
            anchors.right: parent.right
            // anchors.fill: parent
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
                if (mouse.y - yStart >= 30)
                    beServer.motionData(0, 0, 4); // Swipe up
                    // console.log("Swipe down");
                if (yStart - mouse.y >= 30)
                    beServer.motionData(0, 0, 3); //Swipe down
                    // console.log("Swipe up");
                tracing = false
            }
        }

        MouseArea {
            height: parent.height
            width: 30
            anchors.left: parent.left
            // anchors.fill: parent
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
                if (mouse.y - yStart >= 30)
                    beServer.motionData(0, 0, 4); // Swipe up
                    // console.log("Swipe down");
                if (yStart - mouse.y >= 30)
                    beServer.motionData(0, 0, 3); //Swipe down
                    // console.log("Swipe up");
                tracing = false
            }
        }
    }
}
