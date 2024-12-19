// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    color: "black"
    width: parent.width
    height: 50
    anchors.top: parent.top

    property bool backIsShown: true
    property bool rightIsShown: false
    property string headerText: "Default Title"
    property string rightButtonText: ""
    signal backButtonClicked()
    signal rightButtonClicked();

    Button {
        id: backButton
        anchors.margins: 1
        anchors.top: parent.top
        anchors.left: parent.left
        visible: parent.backIsShown
        width: parent.width * 0.1
        height: parent.height - 2
        highlighted: true
        onClicked: {
            root.backButtonClicked();
        }
        Text {
            text: "←"
            anchors.centerIn: parent
        }
    }

    Rectangle {
        property string headerText: parent.headerText
        height: backButton.height
        anchors.centerIn: parent
        anchors.margins: 10

        Text {
            text: parent.headerText
            color: "white"
            font.bold: true
            anchors.centerIn: parent
        }
    }

    Button {
        id: backButtonRight
        property string rightButtonText: parent.rightButtonText
        anchors.margins: 1
        anchors.top: parent.top
        anchors.right: parent.right
        visible: parent.rightIsShown
        width: parent.width * 0.2
        height: parent.height - 2
        highlighted: true
        onClicked: {
            root.rightButtonClicked();
        }
        Text {
            text: parent.rightButtonText
            anchors.centerIn: parent
        }
    }
}
