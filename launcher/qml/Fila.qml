import QtQuick
import QtQuick.Layouts

// Fila de ajuste: título y descripción a la izquierda, control a la derecha.
Item {
    id: raiz
    property string titulo
    property string descripcion
    property bool habilitada: true
    property bool separador: true
    property int anchoControl: 290
    default property alias control: hueco.data

    Layout.fillWidth: true
    implicitHeight: Math.max(textos.implicitHeight, hueco.childrenRect.height) + 26
    opacity: habilitada ? 1.0 : 0.45
    enabled: habilitada

    ColumnLayout {
        id: textos
        anchors.left: parent.left
        anchors.right: hueco.left
        anchors.rightMargin: 24
        anchors.verticalCenter: parent.verticalCenter
        spacing: 3
        Text {
            text: raiz.titulo
            color: Tema.texto
            font.pixelSize: 15
            font.weight: Font.Medium
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
        }
        Text {
            visible: raiz.descripcion.length > 0
            text: raiz.descripcion
            color: Tema.textoTenue
            font.pixelSize: 13
            Layout.fillWidth: true
            wrapMode: Text.WordWrap
            lineHeight: 1.1
        }
    }

    Item {
        id: hueco
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: raiz.anchoControl
        height: childrenRect.height
    }

    Rectangle {
        visible: raiz.separador
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: 1
        color: Tema.borde
        opacity: 0.6
    }
}
