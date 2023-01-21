import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import qt.restaurant 1.0

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Restaurant time")

    Rectangle{
        id: ret1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        Text {
            id: label
            font.pointSize: 12
            text: "Avaliable Hours: "
        }
        TextInput {
            anchors.horizontalCenter: parent.horizontalCenter
            id: input
            font.pointSize: 12
            text: "00:00"
            validator: RegExpValidator { 
                regExp: /^(?:(?:([01]?\d|2[0-3]):)?([0-5]?\d))$/
            }
        }
    }
   Rectangle {
        anchors.centerIn: parent
        Restaurant {
            id: cpp
            availableHours: input.text
        }
        Text {
            text: cpp.availableHours
            font.pointSize: 12
            anchors.centerIn: parent
            Component.onCompleted: {
                Qt.inputMethod.reset()
            }
        }
   }
}
