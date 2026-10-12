import QtQuick

// Tecla dibujada como una tapa de teclado.
Rectangle {
    id: raiz
    property string texto
    implicitWidth: Math.max(30, etiqueta.implicitWidth + 16)
    implicitHeight: 28
    radius: 4
    border.width: 1
    border.color: Tema.bordeClaro
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#2e1f17" }
        GradientStop { position: 1.0; color: "#1a110c" }
    }
    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 1
        height: 3
        radius: 3
        color: "#0e0806"
    }
    Text {
        id: etiqueta
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -1
        text: raiz.texto
        color: Tema.oroClaro
        font.pixelSize: 12
        font.weight: Font.DemiBold
    }
}
