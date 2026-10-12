import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Pestaña "Archivos": ejecutable del juego, imagen de disco, ejecutor del port y tarjeta de memoria.
ScrollView {
    id: raiz
    required property var ajustes
    required property var estadoJuego
    required property var estadoDatos
    required property var estadoEjecutable
    signal detectar()
    contentWidth: availableWidth
    clip: true

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 16

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4
            Text { text: Tema.t("elf"); color: Tema.texto; font.pixelSize: 15; font.weight: Font.Medium }
            Text { text: Tema.t("elfDesc"); color: Tema.textoTenue; font.pixelSize: 13; Layout.fillWidth: true; wrapMode: Text.WordWrap }
            CampoRuta {
                Layout.topMargin: 4
                ruta: raiz.ajustes.elf
                tituloDialogo: Tema.t("elegirElf")
                filtros: ["SCUS_973.99 (SCUS_973.99)", "* (*)"]
                estado: !raiz.estadoJuego.existe ? Tema.t("noEncontrado")
                        : raiz.estadoJuego.valido ? Tema.t("elfOk") : Tema.tf("elfMal", raiz.estadoJuego.crc)
                nivel: raiz.estadoJuego.valido ? "bien" : (raiz.estadoJuego.existe ? "aviso" : "mal")
                onCambiada: (r) => raiz.ajustes.elf = r
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4
            Text { text: Tema.t("iso"); color: Tema.texto; font.pixelSize: 15; font.weight: Font.Medium }
            Text { text: Tema.t("isoDesc"); color: Tema.textoTenue; font.pixelSize: 13; Layout.fillWidth: true; wrapMode: Text.WordWrap }
            CampoRuta {
                Layout.topMargin: 4
                ruta: raiz.ajustes.iso
                vaciable: true
                tituloDialogo: Tema.t("elegirIso")
                filtros: ["ISO (*.iso *.ISO)", "* (*)"]
                estado: raiz.estadoDatos.isoElegidaFalta ? Tema.t("isoElegidaFalta")
                        : raiz.estadoDatos.iso.length > 0 ? Tema.tf("isoUsada", raiz.estadoDatos.iso)
                        : raiz.estadoDatos.extraidos ? Tema.t("isoExtraidos") : Tema.t("isoFalta")
                nivel: raiz.estadoDatos.isoElegidaFalta ? "mal" : (raiz.estadoDatos.ok ? "bien" : "mal")
                onCambiada: (r) => raiz.ajustes.iso = r
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4
            Text { text: Tema.t("ejecutable"); color: Tema.texto; font.pixelSize: 15; font.weight: Font.Medium }
            Text { text: Tema.t("ejecutableDesc"); color: Tema.textoTenue; font.pixelSize: 13; Layout.fillWidth: true; wrapMode: Text.WordWrap }
            CampoRuta {
                Layout.topMargin: 4
                ruta: raiz.ajustes.ejecutable
                tituloDialogo: Tema.t("elegirEjecutable")
                estado: !raiz.estadoEjecutable.existe ? Tema.t("noEncontrado")
                        : raiz.estadoEjecutable.ejecutable ? Tema.t("ejecutableOk") : Tema.t("ejecutableNoExe")
                nivel: raiz.estadoEjecutable.ejecutable ? "bien" : "mal"
                onCambiada: (r) => raiz.ajustes.ejecutable = r
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4
            visible: raiz.ajustes.elf.length > 0
            Text { text: Tema.t("memoria"); color: Tema.texto; font.pixelSize: 15; font.weight: Font.Medium }
            Text { text: Tema.t("memoriaDesc"); color: Tema.textoTenue; font.pixelSize: 13 }
            CampoRuta {
                Layout.topMargin: 4
                ruta: lanzador.carpetaMemoria(raiz.ajustes.elf)
                soloCarpeta: true
            }
        }

        BotonSecundario {
            Layout.topMargin: 4
            text: Tema.t("detectar")
            onClicked: raiz.detectar()
        }
    }
}
