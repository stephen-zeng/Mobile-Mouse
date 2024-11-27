// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick

Rectangle {
    id: root
    color: "black"

    signal backToClient
    Header {
        id: header
        headerText: "连接到移动设备"
        onBackButtonClicked: {
            root.backToClient();
        }
    }

    Timer {
        id: timeFromConnectPage
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if (getServer.serverconnect == 0) {
                emojiText.text = "🔄";
                statusText.text = "连接中";
            } else if (getServer.serverconnect == 1) {
                emojiText.text = "🔄";
                statusText.text = "搜索服务";
            } else if (getServer.serverconnect == 2) {
                emojiText.text = "✅";
                statusText.text = "连接成功";
            } else if (getServer.serverconnect == 3) {
                emojiText.text = "❌";
                statusText.text = "无法连接";
            } else if (getServer.serverconnect == 4) {
                emojiText.text = "❌";
                statusText.text = "连接断开";
            } else if (getServer.serverconnect == 5) {
                emojiText.text = "✅";
                statusText.text = "可以使用";
            }

            getServer.checkController();
        }
    }

    Rectangle {
        id: connectStatus
        color: "black"
        width: parent.width
        height: parent.height - header.height
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        // color: "lightgreen"

        Text {
            id: emojiText
            text: ""
            font.pointSize: 50
            anchors.horizontalCenter: parent.horizontalCenter
            y: root.height * 0.5 - 100
        }
        Text {
            id: statusText
            color: "white"
            text: ""
            font.pointSize: 25
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            anchors.top: emojiText.bottom
        }
        // Text {
        //     id: dataText
        //     text: getServer.data;
        //     font.pointSize: 100
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     anchors.topMargin: 20
        //     anchors.top: statusText.bottom
        // }
    }

    Footer {
        id: footer

        buttonText1: "重试"
        buttonText2: "断开连接"

        onButton1Clicked: {
            getServer.retry();
        }

        onButton2Clicked: {
            getServer.disconnectServer();
        }
    }
}
