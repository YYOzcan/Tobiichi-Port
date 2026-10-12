import QtQuick
import QtQuick.Controls

// Botón secundario: contorno dorado, se rellena al pasar el ratón.
Button {
    id: raiz
    property bool peligro: false
    implicitHeight: 36
    implicitWidth: Math.max(88, etiqueta.implicitWidth + 28)
    hoverEnabled: true

    contentItem: Text {
        id: etiqueta
        text: raiz.text
        color: raiz.peligro ? (raiz.hovered ? "#ffd0c4" : Tema.mal) : (raiz.hovered ? "#1d0f07" : Tema.oroClaro)
        font.pixelSize: 14
        font.weight: Font.Medium
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        Behavior on color { ColorAnimation { duration: 120 } }
    }

    background: Rectangle {
        radius: 4
        border.width: 1
        border.color: raiz.peligro ? Tema.mal : Tema.oro
        color: raiz.hovered ? (raiz.peligro ? "#7a1e14" : Tema.oro) : "transparent"
        opacity: raiz.enabled ? 1.0 : 0.4
        Behavior on color { ColorAnimation { duration: 120 } }
    }
}
