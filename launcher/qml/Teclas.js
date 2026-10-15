.pragma library

// Teclas configurables: códigos de raylib/GLFW (posición física, como en el juego) y 1000 + botón para el ratón.
// El mapa va al juego en TOBIICHI_TECLAS (ps2_pad.cpp lo lee).

var RATON = 1000

// Acciones en el orden de la pestaña; "grupo" agrupa las filas, "boton" es el botón del mando de PS2.
var acciones = [
    { id: "li_arriba", grupo: "grupoMovimiento", boton: "L↑" },
    { id: "li_abajo", grupo: "grupoMovimiento", boton: "L↓" },
    { id: "li_izq", grupo: "grupoMovimiento", boton: "L←" },
    { id: "li_der", grupo: "grupoMovimiento", boton: "L→" },
    { id: "ld_mod", grupo: "grupoMovimiento", boton: "R" },
    { id: "square", grupo: "grupoCombate", boton: "□" },
    { id: "triangle", grupo: "grupoCombate", boton: "△" },
    { id: "circle", grupo: "grupoCombate", boton: "○" },
    { id: "cross", grupo: "grupoCombate", boton: "✕" },
    { id: "l1", grupo: "grupoCombate", boton: "L1" },
    { id: "r1", grupo: "grupoCombate", boton: "R1" },
    { id: "artemisa", grupo: "grupoCombate", boton: "L1+R1" },
    { id: "r2", grupo: "grupoPoderes", boton: "R2" },
    { id: "l2", grupo: "grupoPoderes", boton: "L2" },
    { id: "furia", grupo: "grupoPoderes", boton: "L3+R3" },
    // Cada magia pulsa su dirección de la cruceta (tabla de controles del juego, ver ps2_pad.cpp).
    { id: "poseidon", grupo: "grupoPoderes", boton: "↓" },
    { id: "medusa", grupo: "grupoPoderes", boton: "←" },
    { id: "zeus", grupo: "grupoPoderes", boton: "→" },
    { id: "hades", grupo: "grupoPoderes", boton: "↑" },
    { id: "up", grupo: "grupoMenus", boton: "↑" },
    { id: "right", grupo: "grupoMenus", boton: "→" },
    { id: "down", grupo: "grupoMenus", boton: "↓" },
    { id: "left", grupo: "grupoMenus", boton: "←" },
    { id: "start", grupo: "grupoMenus", boton: "START" },
    { id: "select", grupo: "grupoMenus", boton: "SELECT" },
    { id: "ld_arriba", grupo: "grupoAvanzado", boton: "R↑" },
    { id: "ld_abajo", grupo: "grupoAvanzado", boton: "R↓" },
    { id: "ld_izq", grupo: "grupoAvanzado", boton: "R←" },
    { id: "ld_der", grupo: "grupoAvanzado", boton: "R→" },
    { id: "l3", grupo: "grupoAvanzado", boton: "L3" },
    { id: "r3", grupo: "grupoAvanzado", boton: "R3" }
]

var grupos = ["grupoMovimiento", "grupoCombate", "grupoPoderes", "grupoMenus", "grupoAvanzado"]

// Esquema por defecto: WASD mueve, Ctrl + WASD esquiva, 1 Ira de Poseidón, 2 Mirada de Medusa, 3 Furia de Zeus,
// 4 Ejército de Hades, clic izquierdo/derecho atacan, clic central saca/guarda la Espada de Artemisa (L1 + R1),
// F agarra, Q bloquea/para, Shift L2, Ctrl R2, E R1, V Furia de los dioses, flechas cruceta, Enter Start, Tab Select.
function predeterminado() {
    return {
        li_arriba: [87], li_abajo: [83], li_izq: [65], li_der: [68],
        ld_mod: [341],
        square: [RATON + 0], triangle: [RATON + 1], circle: [70], cross: [32],
        l1: [81], r1: [69], artemisa: [RATON + 2], r2: [341], l2: [340], furia: [86],
        poseidon: [49], medusa: [50], zeus: [51], hades: [52],
        up: [265], right: [262], down: [264], left: [263],
        start: [257], select: [258],
        ld_arriba: [73], ld_abajo: [75], ld_izq: [74], ld_der: [76],
        l3: [], r3: []
    }
}

// Mapa guardado (JSON) con las acciones que falten tomadas del esquema por defecto.
function leer(texto) {
    var base = predeterminado()
    if (!texto)
        return base
    try {
        var guardado = JSON.parse(texto)
        // Mapas de antes de las acciones de cada magia: 1-4 estaban en la cruceta (1 arriba, 2 derecha, 3 abajo,
        // 4 izquierda). Ahora van a las magias por defecto; se quitan de la cruceta para que no pulsen dos
        // direcciones a la vez.
        if (!Array.isArray(guardado.poseidon)) {
            var cruceta = ["up", "right", "down", "left"]
            for (var k = 0; k < cruceta.length; ++k)
                if (Array.isArray(guardado[cruceta[k]]))
                    guardado[cruceta[k]] = guardado[cruceta[k]].filter(function (c) { return c < 49 || c > 52 })
        }
        for (var i = 0; i < acciones.length; ++i) {
            var id = acciones[i].id
            if (Array.isArray(guardado[id]))
                base[id] = guardado[id].slice(0, 2).filter(function (c) { return typeof c === "number" && c > 0 })
        }
    } catch (e) {
    }
    return base
}

function cadena(mapa) {
    var partes = []
    for (var i = 0; i < acciones.length; ++i) {
        var id = acciones[i].id
        var codigos = mapa[id] || []
        if (codigos.length > 0)
            partes.push(id + "=" + codigos.join(","))
    }
    return partes.join(";")
}

function asignar(mapa, accion, indice, codigo) {
    var nuevo = JSON.parse(JSON.stringify(mapa))
    var lista = (nuevo[accion] || []).slice()
    if (codigo <= 0) {
        lista.splice(indice, 1)
    } else {
        var existente = lista.indexOf(codigo)
        if (existente >= 0 && existente !== indice)
            lista.splice(existente, 1)
        if (indice < lista.length)
            lista[indice] = codigo
        else
            lista.push(codigo)
    }
    nuevo[accion] = lista.slice(0, 2)
    return nuevo
}

// Mayúsculas, Ctrl y Alt izquierdos y derechos son la misma tecla en el juego.
function normal(codigo) {
    if (codigo === 344) return 340
    if (codigo === 345) return 341
    if (codigo === 346) return 342
    return codigo
}

// Otras acciones que usan el mismo código. Ctrl como esquiva y R2 a la vez es intencionado (el juego separa los
// dos usos), así que esa pareja no cuenta como conflicto.
function conflictos(mapa, accion, codigo) {
    var resultado = []
    var c = normal(codigo)
    for (var i = 0; i < acciones.length; ++i) {
        var otra = acciones[i].id
        if (otra === accion)
            continue
        var lista = mapa[otra] || []
        for (var j = 0; j < lista.length; ++j) {
            if (normal(lista[j]) !== c)
                continue
            var pareja = (accion === "ld_mod" && otra !== "ld_mod") || (otra === "ld_mod" && accion !== "ld_mod")
            if (!pareja)
                resultado.push(otra)
        }
    }
    return resultado
}

// Teclas que usa el propio juego/ventana.
function reservada(codigo) {
    return codigo === 290 || codigo === 291 || codigo === 300 // F1 (panel de desarrollo), F2 (trucos), F11 (pantalla completa)
}

// Código X/Wayland (evdev + 8) -> tecla GLFW. Posición física, igual que GLFW en el juego.
var porEscaneo = {
    9: 256, 10: 49, 11: 50, 12: 51, 13: 52, 14: 53, 15: 54, 16: 55, 17: 56, 18: 57, 19: 48, 20: 45, 21: 61, 22: 259,
    23: 258, 24: 81, 25: 87, 26: 69, 27: 82, 28: 84, 29: 89, 30: 85, 31: 73, 32: 79, 33: 80, 34: 91, 35: 93, 36: 257,
    37: 341, 38: 65, 39: 83, 40: 68, 41: 70, 42: 71, 43: 72, 44: 74, 45: 75, 46: 76, 47: 59, 48: 39, 49: 96, 50: 340,
    51: 92, 52: 90, 53: 88, 54: 67, 55: 86, 56: 66, 57: 78, 58: 77, 59: 44, 60: 46, 61: 47, 62: 344, 63: 332, 64: 342,
    65: 32, 66: 280, 67: 290, 68: 291, 69: 292, 70: 293, 71: 294, 72: 295, 73: 296, 74: 297, 75: 298, 76: 299, 77: 282,
    78: 281, 79: 327, 80: 328, 81: 329, 82: 333, 83: 324, 84: 325, 85: 326, 86: 334, 87: 321, 88: 322, 89: 323, 90: 320,
    91: 330, 94: 162, 95: 300, 96: 301, 104: 335, 105: 345, 106: 331, 107: 283, 108: 346, 110: 268, 111: 265, 112: 266,
    113: 263, 114: 262, 115: 269, 116: 264, 117: 267, 118: 260, 119: 261, 127: 284, 133: 343, 134: 347, 135: 348
}

// Respaldo por tecla de Qt (Windows, o si no hay código de escaneo).
function desdeTeclaQt(tecla, modificadores) {
    var teclado = (modificadores & 0x20000000) !== 0 // Qt.KeypadModifier
    if (teclado && tecla >= 0x30 && tecla <= 0x39) return 320 + (tecla - 0x30)
    if (tecla >= 0x41 && tecla <= 0x5A) return tecla
    if (tecla >= 0x30 && tecla <= 0x39) return tecla
    var tabla = {
        0x20: 32, 0x27: 39, 0x2C: 44, 0x2D: 45, 0x2E: 46, 0x2F: 47, 0x3B: 59, 0x3D: 61, 0x5B: 91, 0x5C: 92, 0x5D: 93,
        0x60: 96, 0x01000000: 256, 0x01000001: 258, 0x01000002: 258, 0x01000003: 259, 0x01000004: 257, 0x01000005: 257,
        0x01000006: 260, 0x01000007: 261, 0x01000008: 284, 0x01000009: 283, 0x01000010: 268, 0x01000011: 269,
        0x01000012: 263, 0x01000013: 265, 0x01000014: 262, 0x01000015: 264, 0x01000016: 266, 0x01000017: 267,
        0x01000020: 340, 0x01000021: 341, 0x01000022: 343, 0x01000023: 342, 0x01001103: 346, 0x01000024: 280,
        0x01000025: 282, 0x01000026: 281
    }
    if (tecla >= 0x01000030 && tecla <= 0x0100003B) return 290 + (tecla - 0x01000030)
    return tabla[tecla] || 0
}

function desdeEvento(evento, linux) {
    if (linux && evento.nativeScanCode > 8 && porEscaneo[evento.nativeScanCode] !== undefined)
        return porEscaneo[evento.nativeScanCode]
    return desdeTeclaQt(evento.key, evento.modifiers)
}

// Botón de Qt -> código del ratón (1000 izquierdo, 1001 derecho, 1002 central, 1003/1004 laterales).
function desdeRaton(boton) {
    if (boton === 1) return RATON + 0
    if (boton === 2) return RATON + 1
    if (boton === 4) return RATON + 2
    if (boton === 8) return RATON + 3
    if (boton === 16) return RATON + 4
    return 0
}

// Nombre corto para mostrar en la tecla. "t" es la función de traducción de la interfaz.
function nombre(codigo, t) {
    if (!codigo) return "—"
    if (codigo >= RATON) {
        var r = ["ratonIzq", "ratonDer", "ratonMedio", "raton4", "raton5"][codigo - RATON]
        return r ? t(r) : "?"
    }
    if ((codigo >= 65 && codigo <= 90) || (codigo >= 48 && codigo <= 57)) return String.fromCharCode(codigo)
    if (codigo >= 290 && codigo <= 301) return "F" + (codigo - 289)
    if (codigo >= 320 && codigo <= 329) return "Num " + (codigo - 320)
    var nombres = {
        32: t("espacio"), 39: "'", 44: ",", 45: "-", 46: ".", 47: "/", 59: ";", 61: "=", 91: "[", 92: "\\", 93: "]",
        96: "`", 162: "<>", 256: "Esc", 257: "Enter", 258: "Tab", 259: "⌫", 260: "Ins", 261: "Del", 262: "→", 263: "←",
        264: "↓", 265: "↑", 266: "PgUp", 267: "PgDn", 268: "Home", 269: "End", 280: "Caps", 281: "Scroll", 282: "NumLk",
        283: "PrtSc", 284: "Pause", 330: "Num .", 331: "Num /", 332: "Num *", 333: "Num -", 334: "Num +",
        335: "Num Enter", 340: "Shift", 341: "Ctrl", 342: "Alt", 343: "Super", 344: "Shift", 345: "Ctrl", 346: "AltGr",
        347: "Super", 348: "Menu"
    }
    return nombres[codigo] || ("#" + codigo)
}
