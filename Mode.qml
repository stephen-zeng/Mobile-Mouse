// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Controls

Rectangle {
    id: modeWindow
    color: "black"
    visible: true
    signal goToServer1()
    signal goToClient()

    Header {
        id: header
        visible: true
        backIsShown: false
        headerText: "选择模式"
    }

    Rectangle {
        color: "black"
        id: infoContent
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: parent.width
        height: parent.height - footer.height - header.height

        Rectangle {
            width: parent.width
            y: (Qt.platform.os == "ios") ? parent.height * 0.2 : parent.height * 0.3

            Text {
                id: infoTitle
                color: "white"
                text: "使用说明"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 25
                y: parent.height * 0.2
                font.pixelSize: 25
            }

            Text {
                id: infoTextDesktop
                color: "white"
                anchors.top: infoTitle.bottom
                anchors.topMargin: 25
                anchors.horizontalCenter: parent.horizontalCenter
                text: "这个程序运行在电脑上，请选择“被控端”。"
                font.pixelSize: 15
            }

            Text {
                id: infoTextMobile
                color: "white"
                anchors.top: infoTextDesktop.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "这个程序运行在移动设备上，请选择“主控端”。"
                font.pixelSize: 15
            }

            Text {
                id: text3
                color: "white"
                anchors.top: infoTextMobile.bottom
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: "macOS请用brew安装cliclick，"
                font.pixelSize: 15
            }

            Text {
                id: text3_2
                color: "white"
                anchors.top: text3.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "并在设置--隐私与安全--辅助功能中打开权限"
                font.pixelSize: 15
            }

            Text {
                id: text3_5
                color: "white"
                anchors.top: text3_2.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "移动设备请暂时关闭自动旋转"
                font.pixelSize: 15
            }

            Text {
                id: text4
                color: "white"
                anchors.top: text3_5.bottom
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: "短按点击为左键，长按为右键"
                font.pixelSize: 15
            }

            Text {
                id: text5
                color: "white"
                anchors.top: text4.bottom
                anchors.topMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: "左右边缘滑动以滚动页面"
                font.pixelSize: 15
            }

            Rectangle {
                id: deviceName
                anchors.top: text5.bottom
                anchors.topMargin: 15
                visible: (Qt.platform.os == "ios") ? true: false
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    id: nameText
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "white"
                    font.pixelSize: 15
                    text: "iOS设备可以在下面自定义设备名"
                }

                TextField {
                    id: nameField
                    width: 200
                    anchors.top: nameText.bottom
                    anchors.topMargin: 5
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pixelSize: 15
                    text: beServer.name
                    onTextChanged: beServer.name = nameField.text
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    Footer {
        id: footer
        visible: true
        buttonText1: "主控端"
        buttonText2: "被控端"

        onButton1Clicked: {
            if (Qt.platform.os == "android" || Qt.platform.os == "ios") {
                modeWindow.goToServer1();
                beServer.startAdvertising();
            }
        }
        onButton2Clicked: {
            if (Qt.platform.os == "windows" || Qt.platform.os == "osx") {
                modeWindow.goToClient();
                if (getServer.agentstart) {
                    getServer.stopGetServer();
                    console.log("stop scan");
                } else {
                    getServer.startGetServer();
                    console.log("start scan");
                }
            }
        }
    }
}
