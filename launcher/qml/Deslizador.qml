import QtQuick
import QtQuick.Controls

// Deslizador con relleno dorado y el valor en porcentaje a la derecha.
Item {
    id: raiz
    property alias value: control.value
    property alias from: control.from
    property alias to: control.to
    property alias stepSize: control.stepSize
    signal movido(real valor)
    width: parent ? parent.width : 290
    implicitHeight: 30

    Slider {
        id: control
        anchors.left: parent.left
        anchors.right: etiqueta.left
        anchors.rightMargin: 12
        anchors.verticalCenter: parent.verticalCenter
        hoverEnabled: true
        onMoved: raiz.movido(value)

        background: Rectangle {
            x: control.leftPadding
            y: control.topPadding + control.availableHeight / 2 - height / 2
            width: control.availableWidth
            height: 4
            radius: 2
            color: Tema.campo
            border.width: 1
            border.color: Tema.borde
            Rectangle {
                width: control.visualPosition * parent.width
                height: parent.height
                radius: 2
                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: Tema.oroOscuro }
                    GradientStop { position: 1.0; color: Tema.oroClaro }
                }
            }
        }
        handle: Rectangle {
            x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
            y: control.topPadding + control.availableHeight / 2 - height / 2
            width: 18
            height: 18
            radius: 9
            color: control.pressed ? Tema.oro : Tema.oroClaro
            border.width: 3
            border.color: "#2a1608"
            scale: control.hovered || control.pressed ? 1.12 : 1.0
            Behavior on scale { NumberAnimation { duration: 100 } }
        }
    }

    Text {
        id: etiqueta
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: 44
        horizontalAlignment: Text.AlignRight
        text: Math.round((control.value - control.from) / (control.to - control.from) * 100) + "%"
        color: Tema.oroClaro
        font.pixelSize: 13
        font.weight: Font.Medium
    }
}
