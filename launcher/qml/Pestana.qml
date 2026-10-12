import QtQuick
import QtQuick.Controls

// Pestaña de la barra superior: texto en versalitas y subrayado dorado al estar activa.
TabButton {
    id: raiz
    property string icono: ""
    implicitHeight: 46
    implicitWidth: etiqueta.implicitWidth + 34
    hoverEnabled: true

    contentItem: Text {
        id: etiqueta
        text: raiz.text.toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
        font.family: Tema.fuenteTitulo
        font.pixelSize: 15
        font.weight: Font.DemiBold
        font.letterSpacing: 1.6
        color: raiz.checked ? Tema.oroClaro : (raiz.hovered ? Tema.texto : Tema.textoSuave)
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        Behavior on color { ColorAnimation { duration: 140 } }
    }

    background: Item {
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            height: 2
            width: raiz.checked ? parent.width - 18 : (raiz.hovered ? 18 : 0)
            radius: 1
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.5; color: Tema.oro }
                GradientStop { position: 1.0; color: "transparent" }
            }
            Behavior on width { NumberAnimation { duration: 180; easing.type: Easing.OutCubic } }
        }
    }
}
