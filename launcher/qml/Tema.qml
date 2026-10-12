pragma Singleton
import QtQuick
import "Textos.js" as Textos

// Colores, fuentes e idioma de la interfaz. t(clave) se reevalúa al cambiar "idioma".
QtObject {
    property string idioma: "tr"
    property string fuenteTitulo: "serif"
    readonly property string fuenteCuerpo: Qt.application.font.family

    readonly property color fondo: "#0a0605"
    readonly property color fondoAlto: "#1c0d0a"
    readonly property color panel: "#cc140c0a"
    readonly property color panelClaro: "#24160f"
    readonly property color campo: "#1d120d"
    readonly property color borde: "#3d2619"
    readonly property color bordeClaro: "#5e3d26"
    readonly property color oro: "#d4a857"
    readonly property color oroClaro: "#f3d896"
    readonly property color oroOscuro: "#8c6222"
    readonly property color rojo: "#b0221a"
    readonly property color rojoClaro: "#de3b26"
    readonly property color rojoOscuro: "#5a0d09"
    readonly property color texto: "#f0e6da"
    readonly property color textoSuave: "#bca999"
    readonly property color textoTenue: "#7f6d60"
    readonly property color bien: "#86c97c"
    readonly property color aviso: "#e8b04a"
    readonly property color mal: "#e2604e"

    function t(clave) {
        return Textos.texto(clave, idioma)
    }
    // t con %1, %2... sustituidos.
    function tf(clave, a, b) {
        var s = t(clave)
        if (a !== undefined) s = s.replace("%1", a)
        if (b !== undefined) s = s.replace("%2", b)
        return s
    }
    function duracion(segundos) {
        var h = Math.floor(segundos / 3600)
        var m = Math.floor((segundos % 3600) / 60)
        if (h > 0) return tf("horasMinutos", h, m)
        if (m > 0) return tf("minutos", m)
        return tf("segundos", segundos)
    }
}
