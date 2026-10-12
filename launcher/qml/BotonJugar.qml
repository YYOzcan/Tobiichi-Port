import QtQuick
import QtQuick.Controls
import QtQuick.Effects

// Botón principal. Rojo con brillo pulsante cuando el juego está listo; sobrio mientras se juega.
Button {
    id: raiz
    property bool jugando: false
    property bool listo: true
    implicitWidth: 340
    implicitHeight: 66
    hoverEnabled: true
    enabled: listo || jugando

    contentItem: Item {
        Text {
            anchors.centerIn: parent
            text: raiz.text
            font.family: Tema.fuenteTitulo
            font.pixelSize: raiz.jugando ? 20 : 27
            font.weight: Font.Black
            font.letterSpacing: raiz.jugando ? 4 : 8
            color: raiz.jugando ? Tema.oroClaro : (raiz.enabled ? "#fff3df" : "#a08f84")
            style: Text.Raised
            styleColor: "#40000000"
        }
    }

    background: Item {
        // Resplandor detrás del botón.
        Rectangle {
            id: brillo
            anchors.fill: parent
            anchors.margins: 4
            radius: 6
            visible: !raiz.jugando && raiz.enabled
            color: Tema.rojoClaro
            layer.enabled: true
            layer.effect: MultiEffect {
                blurEnabled: true
                blurMax: 48
                blur: 1.0
                brightness: 0.1
            }
            SequentialAnimation on opacity {
                running: brillo.visible
                loops: Animation.Infinite
                NumberAnimation { from: 0.35; to: 0.85; duration: 1600; easing.type: Easing.InOutSine }
                NumberAnimation { from: 0.85; to: 0.35; duration: 1600; easing.type: Easing.InOutSine }
            }
        }
        Rectangle {
            anchors.fill: parent
            radius: 5
            border.width: 1
            border.color: raiz.jugando ? Tema.oro : (raiz.hovered ? "#ffcf8a" : "#c9805a")
            gradient: Gradient {
                GradientStop { position: 0.0; color: raiz.jugando ? "#2a1a12" : (!raiz.enabled ? "#3a2420" : raiz.pressed ? "#8e1a12" : raiz.hovered ? "#e8452c" : "#cf2f1f") }
                GradientStop { position: 0.55; color: raiz.jugando ? "#1d120d" : (!raiz.enabled ? "#2a1a17" : raiz.pressed ? "#6a120c" : raiz.hovered ? "#b3241a" : "#9a1c14") }
                GradientStop { position: 1.0; color: raiz.jugando ? "#140c09" : (!raiz.enabled ? "#201412" : "#5a0d09") }
            }
            // Filo de luz superior.
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 1
                height: 1
                color: "#55ffffff"
                visible: !raiz.jugando
            }
        }
    }

    scale: pressed ? 0.985 : (hovered && !jugando ? 1.015 : 1.0)
    Behavior on scale { NumberAnimation { duration: 110 } }
}
