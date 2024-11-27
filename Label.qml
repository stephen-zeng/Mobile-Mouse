// Author: Stephen Zeng 曾浩正
// Mail: stephenzeng@goforit.top

import QtQuick

Text {
    property string textContent: ""
    font.pointSize: 20
    anchors.horizontalCenter: parent.horizontalCenter
    color: "#363636"
    horizontalAlignment: Text.AlignHCenter
    elide: Text.ElideMiddle
    width: parent.width
    wrapMode: Text.Wrap
    text: textContent
}
