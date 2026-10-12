import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Pestaña "Controles": esquema de teclado y tabla de teclas (la de ps2_pad.cpp).
ScrollView {
    id: raiz
    required property var ajustes
    contentWidth: availableWidth
    clip: true

    readonly property var teclasModerno: [
        { teclas: ["W", "A", "S", "D"], accion: "tMover" },
        { teclas: ["Ctrl", "+", "WASD"], accion: "tEsquivar" },
        { teclas: [Tema.t("oklar")], accion: "tCruceta" },
        { teclas: [Tema.t("espacio")], accion: "tSaltar" },
        { teclas: [Tema.t("clicIzq")], accion: "tLigero" },
        { teclas: [Tema.t("clicDer")], accion: "tFuerte" },
        { teclas: ["F"], accion: "tAgarre" },
        { teclas: ["Shift"], accion: "tBloqueo" },
        { teclas: ["Q"], accion: "tMagia" },
        { teclas: ["E"], accion: "tAccion" },
        { teclas: ["V"], accion: "tFuria" },
        { teclas: ["Enter"], accion: "tStart" },
        { teclas: ["Tab"], accion: "tSelect" }
    ]
    readonly property var teclasClasico: [
        { teclas: ["WASD", "/", Tema.t("oklar")], accion: "tCruceta" },
        { teclas: ["X", "/", Tema.t("espacio")], accion: "tSaltar" },
        { teclas: ["C", "/", "Esc"], accion: "tCirculo" },
        { teclas: ["Z"], accion: "tCuadrado" },
        { teclas: ["V"], accion: "tTriangulo" },
        { teclas: ["Q"], accion: "tL1" },
        { teclas: ["E"], accion: "tR1" },
        { teclas: ["L-Shift"], accion: "tL2" },
        { teclas: ["R-Shift"], accion: "tR2" },
        { teclas: ["Enter"], accion: "tStart" },
        { teclas: ["Tab"], accion: "tSelect" }
    ]
    readonly property var teclasGenerales: [
        { teclas: ["F11"], accion: "tPantalla" },
        { teclas: ["F1"], accion: "tPanel" }
    ]

    component FilaTecla: RowLayout {
        id: fila
        required property var modelData
        spacing: 12
        Row {
            Layout.preferredWidth: 138
            Layout.alignment: Qt.AlignTop
            spacing: 4
            Repeater {
                model: fila.modelData.teclas
                delegate: Item {
                    id: celda
                    required property string modelData
                    readonly property bool separa: modelData === "+" || modelData === "/"
                    width: separa ? signo.implicitWidth + 2 : tapa.implicitWidth
                    height: 28
                    Tecla {
                        id: tapa
                        visible: !celda.separa
                        texto: celda.modelData
                    }
                    Text {
                        id: signo
                        visible: celda.separa
                        anchors.centerIn: parent
                        text: celda.modelData
                        color: Tema.textoTenue
                        font.pixelSize: 13
                    }
                }
            }
        }
        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            text: Tema.t(fila.modelData.accion)
            color: Tema.textoSuave
            font.pixelSize: 14
            wrapMode: Text.WordWrap
        }
    }

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 0

        Fila {
            titulo: Tema.t("esquema")
            descripcion: Tema.t("esquemaDesc")
            Selector {
                opciones: [{ texto: Tema.t("esquemaModerno"), valor: true }, { texto: Tema.t("esquemaClasico"), valor: false }]
                valor: raiz.ajustes.controlesDmc5
                onElegido: (v) => raiz.ajustes.controlesDmc5 = v
            }
        }
        Fila {
            titulo: Tema.t("escSalir")
            descripcion: Tema.t("escSalirDesc")
            Interruptor {
                checked: raiz.ajustes.escSalir
                onToggled: raiz.ajustes.escSalir = checked
            }
        }

        Text {
            Layout.topMargin: 18
            Layout.bottomMargin: 10
            text: Tema.t("teclasTitulo").toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
            color: Tema.oro
            font.family: Tema.fuenteTitulo
            font.pixelSize: 14
            font.weight: Font.Bold
            font.letterSpacing: 2
        }
        GridLayout {
            Layout.fillWidth: true
            columns: raiz.availableWidth > 620 ? 2 : 1
            columnSpacing: 26
            rowSpacing: 8
            Repeater {
                model: raiz.ajustes.controlesDmc5 ? raiz.teclasModerno : raiz.teclasClasico
                delegate: FilaTecla {
                    Layout.fillWidth: true
                }
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.topMargin: 16
            Layout.bottomMargin: 12
            height: 1
            color: Tema.borde
        }
        GridLayout {
            Layout.fillWidth: true
            columns: raiz.availableWidth > 620 ? 2 : 1
            columnSpacing: 26
            rowSpacing: 8
            Repeater {
                model: raiz.teclasGenerales
                delegate: FilaTecla {
                    Layout.fillWidth: true
                }
            }
        }
    }
}
