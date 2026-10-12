import QtQuick
import QtQuick.Controls

// Interruptor de encendido/apagado: píldora dorada al estar activo.
Switch {
    id: raiz
    hoverEnabled: true
    padding: 0
    implicitWidth: 48
    implicitHeight: 26
    anchors.right: parent ? parent.right : undefined

    indicator: Rectangle {
        implicitWidth: 48
        implicitHeight: 26
        radius: 13
        border.width: 1
        border.color: raiz.checked ? Tema.oro : (raiz.hovered ? Tema.bordeClaro : Tema.borde)
        gradient: Gradient {
            GradientStop { position: 0.0; color: raiz.checked ? Tema.oroClaro : Tema.campo }
            GradientStop { position: 1.0; color: raiz.checked ? Tema.oroOscuro : Tema.campo }
        }
        Rectangle {
            width: 20
            height: 20
            radius: 10
            y: 3
            x: raiz.checked ? parent.width - width - 3 : 3
            color: raiz.checked ? "#2a1608" : Tema.textoSuave
            Behavior on x { NumberAnimation { duration: 160; easing.type: Easing.OutCubic } }
        }
    }
    contentItem: Item {}
}
