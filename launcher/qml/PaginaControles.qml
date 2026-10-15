import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Teclas.js" as Teclas

// Pestaña "Controles": esquema del mando, Escape y teclado/ratón totalmente configurables (TOBIICHI_TECLAS).
ScrollView {
    id: raiz
    required property var ajustes
    readonly property var mapa: Teclas.leer(ajustes.teclas)
    property string capturaAccion: ""
    property int capturaIndice: 0
    contentWidth: availableWidth
    clip: true

    function guardar(nuevo) {
        ajustes.teclas = JSON.stringify(nuevo)
    }

    function textoAviso(accion, codigo) {
        if (!codigo)
            return ""
        if (Teclas.reservada(codigo))
            return Tema.t("reservadaAviso")
        const otras = Teclas.conflictos(mapa, accion, codigo)
        if (otras.length === 0)
            return ""
        return Tema.tf("conflicto", otras.map((id) => Tema.t("acc_" + id)).join(", "))
    }

    function abrirCaptura(accion, indice) {
        capturaAccion = accion
        capturaIndice = indice
        captura.open()
    }

    function asignar(codigo) {
        if (codigo > 0)
            guardar(Teclas.asignar(mapa, capturaAccion, capturaIndice, codigo))
        captura.close()
    }

    component Grupo: Text {
        Layout.topMargin: 18
        Layout.bottomMargin: 6
        color: Tema.oro
        font.family: Tema.fuenteTitulo
        font.pixelSize: 14
        font.weight: Font.Bold
        font.letterSpacing: 2
    }

    component FilaAccion: Rectangle {
        id: fila
        required property var modelData
        readonly property var codigos: raiz.mapa[modelData.id] || []
        Layout.fillWidth: true
        implicitHeight: 42
        radius: 5
        color: zonaFila.containsMouse ? "#1a110c" : "transparent"
        MouseArea {
            id: zonaFila
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.NoButton
        }
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 8
            anchors.rightMargin: 4
            spacing: 12
            Rectangle {
                // Botón del mando de PS2 al que va la acción.
                Layout.preferredWidth: 58
                Layout.preferredHeight: 24
                radius: 12
                color: "#24160f"
                border.width: 1
                border.color: Tema.borde
                Text {
                    anchors.centerIn: parent
                    text: fila.modelData.boton
                    color: Tema.textoSuave
                    font.pixelSize: fila.modelData.boton.length > 4 ? 10 : 12
                    font.weight: Font.DemiBold
                }
            }
            Text {
                Layout.fillWidth: true
                text: Tema.t("acc_" + fila.modelData.id)
                color: Tema.texto
                font.pixelSize: 14
                elide: Text.ElideRight
            }
            Repeater {
                model: 2
                delegate: TeclaAsignable {
                    required property int index
                    readonly property int miCodigo: index < fila.codigos.length ? fila.codigos[index] : 0
                    codigo: miCodigo
                    capturando: captura.opened && raiz.capturaAccion === fila.modelData.id && raiz.capturaIndice === index
                    aviso: raiz.textoAviso(fila.modelData.id, miCodigo)
                    conflicto: aviso.length > 0
                    onElegir: raiz.abrirCaptura(fila.modelData.id, Math.min(index, fila.codigos.length))
                    onBorrar: if (miCodigo !== 0) raiz.guardar(Teclas.asignar(raiz.mapa, fila.modelData.id, index, 0))
                }
            }
        }
    }

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 0

        Fila {
            titulo: Tema.t("mandoEsquema")
            descripcion: Tema.t("mandoEsquemaDesc")
            Selector {
                opciones: [{ texto: Tema.t("mandoModerno"), valor: true }, { texto: Tema.t("mandoClasico"), valor: false }]
                valor: raiz.ajustes.controlesDmc5
                onElegido: (v) => raiz.ajustes.controlesDmc5 = v
            }
        }
        Fila {
            titulo: Tema.t("cancelarAnimaciones")
            descripcion: Tema.t("cancelarAnimacionesDesc")
            Interruptor {
                checked: raiz.ajustes.cancelarAnimaciones
                onToggled: raiz.ajustes.cancelarAnimaciones = checked
            }
        }
        Fila {
            titulo: Tema.t("escSalir")
            descripcion: Tema.t("escSalirDesc")
            separador: false
            Interruptor {
                checked: raiz.ajustes.escSalir
                onToggled: raiz.ajustes.escSalir = checked
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 22
            spacing: 12
            Text {
                Layout.fillWidth: true
                text: Tema.t("tecladoTitulo").toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
                color: Tema.oroClaro
                font.family: Tema.fuenteTitulo
                font.pixelSize: 17
                font.weight: Font.Bold
                font.letterSpacing: 2
            }
            BotonSecundario {
                text: Tema.t("tecladoRestablecer")
                onClicked: raiz.ajustes.teclas = ""
            }
        }
        Text {
            Layout.fillWidth: true
            Layout.topMargin: 4
            text: Tema.t("tecladoDesc")
            color: Tema.textoTenue
            font.pixelSize: 13
            wrapMode: Text.WordWrap
        }

        Repeater {
            model: Teclas.grupos
            delegate: ColumnLayout {
                id: grupo
                required property string modelData
                Layout.fillWidth: true
                spacing: 2
                Grupo {
                    text: Tema.t(grupo.modelData).toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
                }
                Repeater {
                    model: Teclas.acciones.filter((a) => a.grupo === grupo.modelData)
                    delegate: FilaAccion {}
                }
            }
        }

        Grupo {
            text: Tema.t("teclasSistema").toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
        }
        GridLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 8
            Layout.bottomMargin: 12
            columns: 4
            columnSpacing: 12
            rowSpacing: 8
            Tecla { texto: "F11" }
            Text { text: Tema.t("tPantalla"); color: Tema.textoSuave; font.pixelSize: 14; Layout.fillWidth: true }
            Tecla { texto: "F1" }
            Text { text: Tema.t("tPanel"); color: Tema.textoSuave; font.pixelSize: 14; Layout.fillWidth: true }
            Tecla { texto: "F2" }
            Text { text: Tema.t("tTrucos"); color: Tema.textoSuave; font.pixelSize: 14; Layout.fillWidth: true }
        }
    }

    // Captura de la tecla: ocupa toda la ventana para recoger también clics del ratón.
    Popup {
        id: captura
        parent: Overlay.overlay
        x: 0
        y: 0
        width: parent ? parent.width : 800
        height: parent ? parent.height : 600
        modal: true
        closePolicy: Popup.NoAutoClose
        padding: 0
        background: Rectangle { color: "#c8080403" }
        onOpened: contenido.forceActiveFocus()
        contentItem: Item {
            id: contenido
            focus: true
            Keys.onPressed: (evento) => {
                evento.accepted = true
                if (evento.isAutoRepeat)
                    return
                if (evento.key === Qt.Key_Escape) {
                    captura.close()
                    return
                }
                raiz.asignar(Teclas.desdeEvento(evento, typeof lanzador !== "undefined" && lanzador.sistema === "linux"))
            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.AllButtons
                onPressed: (raton) => raiz.asignar(Teclas.desdeRaton(raton.button))
            }
            Rectangle {
                anchors.centerIn: parent
                width: 470
                height: 190
                radius: 8
                color: "#1c110c"
                border.width: 1
                border.color: Tema.oro
                ColumnLayout {
                    anchors.centerIn: parent
                    width: parent.width - 48
                    spacing: 12
                    Text {
                        Layout.alignment: Qt.AlignHCenter
                        text: Tema.t("capturaTitulo").toLocaleUpperCase(Tema.idioma === "tr" ? "tr-TR" : "en-US")
                        color: Tema.oroClaro
                        font.family: Tema.fuenteTitulo
                        font.pixelSize: 22
                        font.weight: Font.Bold
                        font.letterSpacing: 2
                    }
                    Text {
                        Layout.fillWidth: true
                        horizontalAlignment: Text.AlignHCenter
                        text: Tema.tf("capturaDesc", raiz.capturaAccion.length > 0 ? "«" + Tema.t("acc_" + raiz.capturaAccion) + "»" : "")
                        color: Tema.textoSuave
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                    }
                    Rectangle {
                        Layout.alignment: Qt.AlignHCenter
                        width: 64
                        height: 4
                        radius: 2
                        color: Tema.oro
                        SequentialAnimation on opacity {
                            running: captura.opened
                            loops: Animation.Infinite
                            NumberAnimation { to: 0.25; duration: 600 }
                            NumberAnimation { to: 1.0; duration: 600 }
                        }
                    }
                }
            }
        }
    }
}
