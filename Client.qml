// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls

Rectangle {
    id: root
    color: "black"

    signal backToMode();
    signal button1Clicked();
    signal goToConnect();

    Header {
        id: header
        headerText: "查找移动设备"
        onBackButtonClicked: {
            root.backToMode();
        }
    }


    Timer {
        id: timerFromClientPage
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if (getServer.agentstart) {
                // console.log("hi");
                footer.buttonText1 = "停止查找";
                serverModel.clear();
                for (var i=0;i<getServer.serverlist.length;i++)
                    serverModel.append({name: getServer.serverlist[i].name,
                                        addr: getServer.serverlist[i].addr});
            }
            else footer.buttonText1 = "开始查找";
        }
    }

    Footer {
        id: footer

        buttonText1: ""
        buttonText2: "刷新"

        onButton1Clicked: {
            if (getServer.agentstart) {
                getServer.stopGetServer();
                console.log("stop scan");
            } else {
                getServer.startGetServer();
                console.log("start scan");
            }
        }

        onButton2Clicked: {
            getServer.refresh();
        }
    }

    // Button {
    //     id: startScanBtn
    //     width: parent.width * 0.3
    //     height: parent.height * 0.1
    //     anchors.centerIn: parent

    //     highlighted: true
    //     Text {
    //         text: "扫描设备"
    //         anchors.centerIn: parent
    //         font.bold: true
    //     }
    //     onClicked: {
    //         startScanBtn.visible = false;
    //         serverList.visible = true;
    //         getServer.startGetServer();
    //     }
    // }

    Rectangle {
        id: lastConnect
        anchors.top: header.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.9
        height: 50
        radius: 5
        color: "lightblue"
        border.width: 2
        border.color: "blue"
        Text {
            text: "上一次连接的设备: " + getServer.last
            anchors.centerIn: parent
        }
        MouseArea {
            anchors.fill: parent
            visible: getServer.haveLast
            onClicked: {
                getServer.stopGetServer();
                getServer.connectLast();
                root.goToConnect();
            }
        }
    }

    ListModel {
        id: serverModel
    }

    Component {
        id: serverComponent
        Rectangle {
            id: serverItem
            // required property var modelData
            width: parent.width * 0.9
            height: 50
            radius: 5
            color: "lightgreen"
            border.width: 2
            border.color: "green"
            anchors.horizontalCenter: parent.horizontalCenter
            Text {
                text: name
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    getServer.stopGetServer();
                    getServer.startGetService(addr, name);
                    root.goToConnect();
                }
            }
        }
    }

    ListView {
        id: serverList
        width: parent.width
        clip: true
        anchors.top: lastConnect.bottom
        anchors.bottom: footer.top
        anchors.topMargin: 5
        model: serverModel
        delegate: serverComponent
        spacing: 5
    }

    // Button {
    //     anchors.centerIn: parent
    //     Text {
    //         anchors.centerIn: parent
    //         text: "Error"
    //     }
    //     onClicked: {
    //         getServerError.visible = true
    //     }
    // }

    MessageDialog {
        id: getServerError
        title: "通知"
        text: getServer.msg
        visible: getServer.msgbox
        onAccepted: {
            getServerError.visible = false;
            getServer.msgbox = false;
        }
    }

}
