import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Pestaña "Trucos": estado inicial del menú de trucos del juego (TOBIICHI_TRUCOS). En la partida, F2 abre el menú
// y los cambia sin reiniciar.
ScrollView {
    id: raiz
    required property var ajustes
    // Mismo orden e identificadores que kIds en gow_trucos.cpp.
    readonly property var lista: ["inmortal", "un_golpe", "magia", "furia", "orbes", "mejoras", "poderes", "medidores", "extras"]
    readonly property var activos: ajustes.trucos.length > 0 ? ajustes.trucos.split(",") : []
    contentWidth: availableWidth
    clip: true

    function poner(id, encendido) {
        const nuevos = lista.filter((t) => t === id ? encendido : activos.indexOf(t) >= 0)
        ajustes.trucos = nuevos.join(",")
    }

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.bottomMargin: 6
            implicitHeight: aviso.implicitHeight + 24
            radius: 5
            color: "#1f140d"
            border.width: 1
            border.color: Tema.borde
            RowLayout {
                id: aviso
                anchors.fill: parent
                anchors.margins: 12
                spacing: 12
                Tecla { texto: "F2" }
                Text {
                    Layout.fillWidth: true
                    text: Tema.t("trucosAviso")
                    color: Tema.textoSuave
                    font.pixelSize: 13
                    wrapMode: Text.WordWrap
                }
                BotonSecundario {
                    visible: raiz.activos.length > 0
                    text: Tema.t("trucosApagar")
                    onClicked: raiz.ajustes.trucos = ""
                }
            }
        }

        Repeater {
            model: raiz.lista
            delegate: Fila {
                id: fila
                required property string modelData
                required property int index
                titulo: Tema.t("truco_" + modelData)
                descripcion: Tema.t("truco_" + modelData + "Desc")
                separador: index < raiz.lista.length - 1
                Interruptor {
                    checked: raiz.activos.indexOf(fila.modelData) >= 0
                    onToggled: raiz.poner(fila.modelData, checked)
                }
            }
        }
    }
}
