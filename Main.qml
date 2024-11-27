// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: basement
    width: 400
    height: 700
    visible: true
    // anchors.topMargin: Qt.platform.os === "ios" ? topMargin : 20

    StackLayout {
        id: mainLayout
        anchors.fill: parent
        currentIndex: 0

        Mode { // 0
            onGoToServer1: mainLayout.currentIndex = 1
            onGoToClient: mainLayout.currentIndex = 2
        }
        Server1 {// 1
            onBackToMode: mainLayout.currentIndex = 0
            onGoToServer2: mainLayout.currentIndex = 4
        }
        Client{ // 2
            onBackToMode: mainLayout.currentIndex = 0
            onGoToConnect: mainLayout.currentIndex = 3
        }
        Connect { // 3
            onBackToClient: mainLayout.currentIndex = 2
        }
        Server2 {
            onBackToServer1: mainLayout.currentIndex = 1
        }
    }
}
