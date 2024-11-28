import QtQuick
import QtQuick.Dialogs
import QtQuick.Controls

Rectangle {
    id: root

    signal backToMode;

    Timer {
        id: timerFromServerPage
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            if (beServer.clientconnect) header.headerText = "已连接";
            else header.headerText = "等待连接";
            if (beServer.senddata) footer.buttonText2 = "Stop";
            else footer.buttonText2 = "Start";
        }
    }

    Header {
        id: header
        headerText: "等待连接"
        onBackButtonClicked: {
            root.backToMode();
        }
    }

    Footer {
        id: footer

        buttonText1: "Disconnect"
        buttonText2: "Stop"

        onButton1Clicked: {
            beServer.disconnectClient();
        }
        onButton2Clicked: {
            if (beServer.senddata) beServer.senddata = false;
            else beServer.senddata = true;
        }
    }

    Button {
        id: button2
        highlighted: true
        anchors.centerIn: parent;
        width: 120
        height: 80

        onClicked: {
            beServer.provideData();
        }

        Text {
            text: "Send Data"
            anchors.centerIn: parent
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
