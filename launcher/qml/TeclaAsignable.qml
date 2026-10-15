import QtQuick
import QtQuick.Controls
import "Teclas.js" as Teclas

// Hueco de una tecla asignable: clic para cambiarla, clic derecho para borrarla. Ámbar si choca con otra acción.
Rectangle {
    id: raiz
    property int codigo: 0
    property bool conflicto: false
    property bool capturando: false
    property string aviso: ""
    signal elegir()
    signal borrar()

    implicitWidth: 108
    implicitHeight: 32
    radius: 5
    color: capturando ? "#3a2412" : (zona.containsMouse ? "#2e1f17" : "#1b120d")
    border.width: capturando ? 2 : 1
    border.color: capturando ? Tema.oro : (conflicto ? Tema.aviso : (zona.containsMouse ? Tema.bordeClaro : Tema.borde))
    Behavior on color { ColorAnimation { duration: 100 } }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 1
        height: 3
        radius: 3
        color: "#0e0806"
        visible: raiz.codigo !== 0
    }

    Text {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -1
        width: parent.width - 12
        horizontalAlignment: Text.AlignHCenter
        text: raiz.capturando ? "…" : Teclas.nombre(raiz.codigo, (clave) => Tema.t(clave))
        color: raiz.codigo !== 0 ? (raiz.conflicto ? Tema.aviso : Tema.oroClaro) : Tema.textoTenue
        font.pixelSize: 13
        font.weight: Font.DemiBold
        elide: Text.ElideRight
    }

    Rectangle {
        visible: raiz.conflicto
        width: 7
        height: 7
        radius: 4
        color: Tema.aviso
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 4
    }

    MouseArea {
        id: zona
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        cursorShape: Qt.PointingHandCursor
        onClicked: (raton) => raton.button === Qt.RightButton ? raiz.borrar() : raiz.elegir()
    }

    ToolTip.visible: zona.containsMouse && raiz.aviso.length > 0
    ToolTip.delay: 300
    ToolTip.text: raiz.aviso
}
