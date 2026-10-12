import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Pestaña "Gráficos": tarjeta, modo de pantalla, resolución, aspecto y escalado.
ScrollView {
    id: raiz
    required property var ajustes
    required property var tarjetas
    required property var pantalla
    required property bool gpuPerdida
    contentWidth: availableWidth
    clip: true

    readonly property bool completa: ajustes.modoPantalla === "completa"
    readonly property real aspectoPantalla: pantalla.ancho / pantalla.alto

    function nombreTarjeta(t) {
        if (lanzador.sistema === "windows")
            return t.id === "ahorro" ? Tema.t("gpuAhorro") : Tema.t("gpuRendimiento")
        return t.fabricante + " " + t.nombre
    }

    readonly property var opcionesGpu: {
        var lista = [{ texto: Tema.t("gpuAuto"), valor: "auto" }]
        for (var i = 0; i < tarjetas.length; ++i) {
            var t = tarjetas[i]
            var tipo = t.tipo ? Tema.t(t.tipo) : ""
            lista.push({ texto: nombreTarjeta(t), valor: t.id, detalle: tipo + (lanzador.sistema === "linux" ? "  ·  " + t.id : "") })
        }
        return lista
    }

    readonly property var opcionesResolucion: {
        var comunes = [[1024, 768], [1280, 720], [1280, 800], [1280, 960], [1366, 768], [1440, 900], [1600, 900], [1600, 1200],
                       [1680, 1050], [1920, 1080], [1920, 1200], [2560, 1080], [2560, 1440], [2560, 1600], [3440, 1440], [3840, 2160]]
        var lista = []
        for (var i = 0; i < comunes.length; ++i) {
            var w = comunes[i][0], h = comunes[i][1]
            if (w > pantalla.ancho || h > pantalla.alto) continue
            var nativa = w === pantalla.ancho && h === pantalla.alto
            lista.push({ texto: w + " × " + h + (nativa ? "  (" + Tema.t("nativa") + ")" : ""), valor: w + "x" + h })
        }
        var clave = pantalla.ancho + "x" + pantalla.alto
        var esta = false
        for (var j = 0; j < lista.length; ++j) if (lista[j].valor === clave) esta = true
        if (!esta) lista.push({ texto: pantalla.ancho + " × " + pantalla.alto + "  (" + Tema.t("nativa") + ")", valor: clave })
        return lista
    }

    function marcaPantalla(a) {
        return Math.abs(a - aspectoPantalla) < 0.04 ? "  ·  " + Tema.t("aspectoPantalla") : ""
    }

    ColumnLayout {
        width: raiz.availableWidth
        spacing: 0

        Fila {
            titulo: Tema.t("gpu")
            descripcion: raiz.gpuPerdida ? Tema.t("gpuFalta") : Tema.t("gpuDesc")
            Selector {
                opciones: raiz.opcionesGpu
                valor: raiz.ajustes.gpu
                onElegido: (v) => raiz.ajustes.gpu = v
            }
        }
        Fila {
            titulo: Tema.t("modo")
            descripcion: Tema.t("modoDesc")
            Selector {
                opciones: [{ texto: Tema.t("completa"), valor: "completa" }, { texto: Tema.t("ventana"), valor: "ventana" }]
                valor: raiz.ajustes.modoPantalla
                onElegido: (v) => raiz.ajustes.modoPantalla = v
            }
        }
        Fila {
            titulo: Tema.t("resolucion")
            descripcion: raiz.completa ? Tema.t("resolucionCompleta") : Tema.t("resolucionVentana")
            Selector {
                enabled: !raiz.completa
                opacity: enabled ? 1 : 0.5
                opciones: raiz.completa ? [{ texto: raiz.pantalla.ancho + " × " + raiz.pantalla.alto + "  (" + Tema.t("nativa") + ")", valor: "nativa" }]
                                        : raiz.opcionesResolucion
                valor: raiz.completa ? "nativa" : raiz.ajustes.ancho + "x" + raiz.ajustes.alto
                onElegido: (v) => {
                    var partes = String(v).split("x")
                    raiz.ajustes.ancho = parseInt(partes[0])
                    raiz.ajustes.alto = parseInt(partes[1])
                }
            }
        }
        Fila {
            titulo: Tema.t("aspecto")
            descripcion: Tema.t("aspectoDesc")
            Selector {
                opciones: [
                    { texto: Tema.t("aspecto43") + raiz.marcaPantalla(4 / 3), valor: "4:3" },
                    { texto: Tema.t("aspecto169") + raiz.marcaPantalla(16 / 9), valor: "16:9" },
                    { texto: Tema.t("aspecto1610") + raiz.marcaPantalla(16 / 10), valor: "16:10" },
                    { texto: Tema.t("aspecto219") + raiz.marcaPantalla(21 / 9), valor: "21:9" }
                ]
                valor: raiz.ajustes.aspecto
                onElegido: (v) => raiz.ajustes.aspecto = v
            }
        }
        Fila {
            titulo: Tema.t("estirar")
            descripcion: Tema.t("estirarDesc")
            Interruptor {
                checked: raiz.ajustes.estirar
                onToggled: raiz.ajustes.estirar = checked
            }
        }
        Fila {
            titulo: Tema.t("escalado")
            descripcion: Tema.t("escaladoDesc")
            Selector {
                opciones: [
                    { texto: Tema.t("filtroFsr"), valor: "fsr" },
                    { texto: Tema.t("filtroBilineal"), valor: "bilineal" },
                    { texto: Tema.t("filtroPixel"), valor: "pixel" }
                ]
                valor: raiz.ajustes.filtro
                onElegido: (v) => raiz.ajustes.filtro = v
            }
        }
        Fila {
            titulo: Tema.t("nitidez")
            descripcion: Tema.t("nitidezDesc")
            habilitada: raiz.ajustes.filtro === "fsr"
            Deslizador {
                from: 0
                to: 1
                stepSize: 0.05
                value: raiz.ajustes.nitidez
                onMovido: (v) => raiz.ajustes.nitidez = v
            }
        }
        Fila {
            titulo: Tema.t("fxaa")
            descripcion: Tema.t("fxaaDesc")
            Interruptor {
                checked: raiz.ajustes.fxaa
                onToggled: raiz.ajustes.fxaa = checked
            }
        }
        Fila {
            titulo: Tema.t("interna")
            descripcion: Tema.t("internaDesc")
            separador: false
            Text {
                anchors.right: parent.right
                text: Tema.t("internaValor")
                color: Tema.textoSuave
                font.pixelSize: 14
            }
        }
    }
}
