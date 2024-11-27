// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: parent.width
    height: root.width * 0.25
    anchors.bottom: parent.bottom
    anchors.margins: 10
    color: "black"

    property string buttonText1: "Default Text"
    property string buttonText2: "Default Text"
    property bool button1Available: true
    property bool button2Available: true

    signal button1Clicked()
    signal button2Clicked()
    signal button1PressAndHold()
    signal button1DoubleClick()

    Button {
        id: button1
        property string buttonText: parent.buttonText1
        visible: root.button1Available

        anchors.margins: 10
        anchors.left: parent.left
        // anchors.right: button2.left
        width: parent.width * 0.5 - 20
        height: parent.height

        highlighted: root.button1Available
        onClicked: {
            root.button1Clicked();
        }
        onPressAndHold: {
            root.button1PressAndHold();
        }
        onDoubleClicked: {
            root.button1DoubleClick();
        }

        Text {
            text: parent.buttonText
            anchors.centerIn: parent
        }
    }

    Button {
        id: button2
        property string buttonText: parent.buttonText2
        visible: root.button2Available

        anchors.margins: 10
        anchors.left: button1.right
        anchors.right: parent.right
        width: parent.width * 0.5 - 20
        height: parent.height

        highlighted: root.button2Available
        onClicked: {
            root.button2Clicked();
        }
        Text {
            text: parent.buttonText
            anchors.centerIn: parent
        }
    }
}
