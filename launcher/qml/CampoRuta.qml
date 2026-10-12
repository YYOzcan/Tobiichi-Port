import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

// Ruta de archivo editable con "Examinar" y una línea de estado (bien / aviso / mal).
ColumnLayout {
    id: raiz
    property string ruta
    property string estado
    property string nivel: "bien" // "bien", "aviso" o "mal"
    property string tituloDialogo
    property var filtros: []
    property bool vaciable: false
    property bool soloCarpeta: false
    signal cambiada(string ruta)

    Layout.fillWidth: true
    spacing: 6

    RowLayout {
        Layout.fillWidth: true
        spacing: 8
        TextField {
            id: campo
            Layout.fillWidth: true
            implicitHeight: 36
            text: raiz.ruta
            color: Tema.texto
            font.pixelSize: 13
            selectByMouse: true
            readOnly: raiz.soloCarpeta
            placeholderText: "—"
            placeholderTextColor: Tema.textoTenue
            leftPadding: 10
            onEditingFinished: if (text !== raiz.ruta) raiz.cambiada(text.trim())
            onTextChanged: if (!activeFocus) cursorPosition = 0
            background: Rectangle {
                radius: 4
                color: Tema.campo
                border.width: 1
                border.color: campo.activeFocus ? Tema.oro : Tema.borde
            }
        }
        BotonSecundario {
            visible: !raiz.soloCarpeta
            text: Tema.t("examinar")
            onClicked: dialogo.open()
        }
        BotonSecundario {
            visible: raiz.vaciable && raiz.ruta.length > 0
            text: Tema.t("vaciar")
            onClicked: raiz.cambiada("")
        }
        BotonSecundario {
            visible: raiz.soloCarpeta
            text: Tema.t("abrir")
            onClicked: lanzador.abrirCarpeta(raiz.ruta)
        }
    }

    RowLayout {
        visible: raiz.estado.length > 0
        spacing: 7
        Rectangle {
            width: 8
            height: 8
            radius: 4
            color: raiz.nivel === "bien" ? Tema.bien : (raiz.nivel === "aviso" ? Tema.aviso : Tema.mal)
        }
        Text {
            Layout.fillWidth: true
            text: raiz.estado
            color: raiz.nivel === "bien" ? Tema.textoSuave : (raiz.nivel === "aviso" ? Tema.aviso : Tema.mal)
            font.pixelSize: 13
            elide: Text.ElideMiddle
        }
    }

    FileDialog {
        id: dialogo
        title: raiz.tituloDialogo
        nameFilters: raiz.filtros
        currentFolder: raiz.ruta.length > 0 ? lanzador.urlDesdeRuta(raiz.ruta.substring(0, raiz.ruta.lastIndexOf("/"))) : ""
        onAccepted: raiz.cambiada(lanzador.rutaDesdeUrl(selectedFile))
    }
}
