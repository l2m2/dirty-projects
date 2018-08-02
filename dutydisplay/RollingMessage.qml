import QtQuick 2.0

Rectangle {
    id: root_rolling_message
    property string message
    property var anim_obj: undefined
    color: "transparent"

    Text {
        id: text_msg
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.95
        font.pixelSize: parent.height * 0.5
        color: "white"
        text: message

        onImplicitWidthChanged: {
            if (implicitWidth <= 0) {
                return
            }
            anim_obj = Qt.createQmlObject('import QtQuick 2.0; NumberAnimation {}', text_msg)
            anim_obj.target = text_msg
            anim_obj.property = "x"
            anim_obj.from = root_rolling_message.width
            anim_obj.to = -text_msg.implicitWidth
            anim_obj.duration = (text_msg.implicitWidth < root_rolling_message.width
                    ? 1 : text_msg.implicitWidth / root_rolling_message.width) * 16000
            anim_obj.loops = Animation.Infinite
            anim_obj.restart()
        }
    }
}
