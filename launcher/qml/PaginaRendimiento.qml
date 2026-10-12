import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Pestaña "Rendimiento": límite de la ventana, VSync y contador de FPS.
ScrollView {
    id: raiz
    required property var ajustes
    required property var pantalla
    contentWidth: availableWidth
    clip: true

    readonly property var opcionesFps: {
        var valores = [30, 60, 120, 144, 165, 240]
        if (pantalla.hz > 0 && valores.indexOf(pantalla.hz) < 0) {
            valores.push(pantalla.hz)
            valores.sort(function (a, b) { return a - b })
        }
        var lista = []
        for (var i = 0; i < valores.length; ++i)
            lista.push({ texto: valores[i] + " FPS" + (valores[i] === pantalla.hz ? "  ·  " + Tema.t("aspectoPantalla") : ""), valor: valores[i] })
        lista.push({ texto: Tema.t("sinLimite"), valor: 0 })
        return lista
    }

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 0

        Fila {
            titulo: Tema.t("fpsLimite")
            descripcion: Tema.tf("fpsLimiteDesc", raiz.pantalla.hz)
            Selector {
                opciones: raiz.opcionesFps
                valor: raiz.ajustes.fpsLimite
                onElegido: (v) => raiz.ajustes.fpsLimite = v
            }
        }
        Fila {
            titulo: Tema.t("vsync")
            descripcion: Tema.t("vsyncDesc")
            Interruptor {
                checked: raiz.ajustes.vsync
                onToggled: raiz.ajustes.vsync = checked
            }
        }
        Fila {
            titulo: Tema.t("mostrarFps")
            descripcion: Tema.t("mostrarFpsDesc")
            separador: false
            Interruptor {
                checked: raiz.ajustes.mostrarFps
                onToggled: raiz.ajustes.mostrarFps = checked
            }
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.topMargin: 18
            implicitHeight: nota.implicitHeight + 28
            radius: 5
            color: "#1f1510"
            border.width: 1
            border.color: Tema.borde
            Rectangle {
                width: 3
                height: parent.height - 16
                anchors.left: parent.left
                anchors.leftMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                radius: 1
                color: Tema.oro
            }
            ColumnLayout {
                id: nota
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 24
                anchors.rightMargin: 16
                spacing: 4
                Text {
                    text: Tema.t("notaFpsTitulo")
                    color: Tema.oroClaro
                    font.family: Tema.fuenteTitulo
                    font.pixelSize: 14
                    font.weight: Font.Bold
                }
                Text {
                    Layout.fillWidth: true
                    text: Tema.t("notaFps")
                    color: Tema.textoSuave
                    font.pixelSize: 13
                    wrapMode: Text.WordWrap
                    lineHeight: 1.15
                }
            }
        }
    }
}
