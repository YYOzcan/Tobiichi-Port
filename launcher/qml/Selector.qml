import QtQuick
import QtQuick.Controls

// Lista desplegable con el estilo del lanzador. opciones: [{texto, valor, detalle}].
ComboBox {
    id: raiz
    property var opciones: []
    property var valor
    signal elegido(var valor)

    function indice(v) {
        for (var i = 0; i < opciones.length; ++i)
            if (opciones[i].valor == v)
                return i
        return -1
    }

    width: parent ? parent.width : 290
    implicitHeight: 38
    model: opciones
    textRole: "texto"
    currentIndex: indice(valor)
    hoverEnabled: true
    onActivated: (i) => elegido(opciones[i].valor)

    background: Rectangle {
        radius: 4
        color: raiz.pressed ? Tema.panelClaro : Tema.campo
        border.width: 1
        border.color: raiz.activeFocus || raiz.popup.visible ? Tema.oro : (raiz.hovered ? Tema.bordeClaro : Tema.borde)
        Behavior on border.color { ColorAnimation { duration: 120 } }
    }

    contentItem: Text {
        leftPadding: 12
        rightPadding: 32
        text: raiz.currentIndex >= 0 ? raiz.opciones[raiz.currentIndex].texto : ""
        color: Tema.texto
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    indicator: Canvas {
        x: raiz.width - width - 12
        y: (raiz.height - height) / 2
        width: 10
        height: 6
        contextType: "2d"
        rotation: raiz.popup.visible ? 180 : 0
        Behavior on rotation { NumberAnimation { duration: 150 } }
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.strokeStyle = Tema.oro
            ctx.lineWidth = 1.6
            ctx.beginPath()
            ctx.moveTo(1, 1)
            ctx.lineTo(width / 2, height - 1)
            ctx.lineTo(width - 1, 1)
            ctx.stroke()
        }
    }

    delegate: ItemDelegate {
        id: opcion
        required property int index
        required property var modelData
        width: raiz.width - 8
        height: Math.max(34, columna.implicitHeight + 12)
        hoverEnabled: true
        highlighted: raiz.highlightedIndex === index
        contentItem: Column {
            id: columna
            spacing: 1
            Text {
                text: opcion.modelData.texto
                color: opcion.index === raiz.currentIndex ? Tema.oroClaro : Tema.texto
                font.pixelSize: 14
                width: parent.width
                elide: Text.ElideRight
            }
            Text {
                visible: (opcion.modelData.detalle || "").length > 0
                text: opcion.modelData.detalle || ""
                color: Tema.textoTenue
                font.pixelSize: 12
                width: parent.width
                elide: Text.ElideRight
            }
        }
        background: Rectangle {
            radius: 3
            color: opcion.highlighted || opcion.hovered ? Tema.panelClaro : "transparent"
            Rectangle {
                visible: opcion.index === raiz.currentIndex
                width: 2
                height: parent.height - 12
                anchors.verticalCenter: parent.verticalCenter
                color: Tema.oro
            }
        }
    }

    popup: Popup {
        y: raiz.height + 4
        width: raiz.width
        implicitHeight: Math.min(contentItem.implicitHeight + 8, 340)
        padding: 4
        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: raiz.popup.visible ? raiz.delegateModel : null
            currentIndex: raiz.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator {}
        }
        background: Rectangle {
            radius: 4
            color: "#f2170e0b"
            border.width: 1
            border.color: Tema.bordeClaro
        }
        enter: Transition { NumberAnimation { property: "opacity"; from: 0; to: 1; duration: 110 } }
        exit: Transition { NumberAnimation { property: "opacity"; from: 1; to: 0; duration: 90 } }
    }
}
