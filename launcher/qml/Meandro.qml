import QtQuick

// Franja de greca (meandro griego) que se desvanece hacia los extremos.
Canvas {
    id: raiz
    property color color: Tema.oro
    property real grosor: 1.4
    property int celda: 3
    implicitHeight: celda * 6 + grosor * 2
    antialiasing: true

    onColorChanged: requestPaint()
    onWidthChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.reset()
        ctx.lineWidth = grosor
        ctx.strokeStyle = color
        ctx.lineCap = "square"
        var c = celda
        var periodo = 6 * c
        var y0 = grosor
        var n = Math.floor(width / periodo)
        var inicio = (width - n * periodo) / 2
        for (var i = 0; i < n; ++i) {
            var x = inicio + i * periodo
            var centro = Math.abs((x + periodo / 2) - width / 2) / (width / 2)
            ctx.globalAlpha = Math.max(0, 1 - centro * centro) * 0.95
            ctx.beginPath()
            ctx.moveTo(x, y0 + 6 * c)
            ctx.lineTo(x, y0)
            ctx.lineTo(x + 5 * c, y0)
            ctx.lineTo(x + 5 * c, y0 + 4 * c)
            ctx.lineTo(x + 2 * c, y0 + 4 * c)
            ctx.lineTo(x + 2 * c, y0 + 2 * c)
            ctx.lineTo(x + 3 * c, y0 + 2 * c)
            ctx.moveTo(x, y0 + 6 * c)
            ctx.lineTo(x + periodo, y0 + 6 * c)
            ctx.stroke()
        }
    }
}
