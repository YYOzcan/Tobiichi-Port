import QtQuick
import QtTest
import Tobiichi
import "../qml/Teclas.js" as Teclas

// Pruebas de la pestaña de controles: captura de teclas y botones del ratón, cancelar con Escape y conflictos.
// qmltestrunner -import <dir con Tobiichi/qmldir> -input launcher/pruebas/tst_teclas.qml
Item {
    id: raizPrueba
    width: 900
    height: 1600

    QtObject {
        id: ajustesFalsos
        property string teclas: ""
        property bool controlesDmc5: true
        property bool escSalir: false
    }

    PaginaControles {
        id: pagina
        anchors.fill: parent
        ajustes: ajustesFalsos
    }

    TestCase {
        name: "Teclas"
        when: windowShown

        function init() {
            ajustesFalsos.teclas = ""
        }

        function test_esquemaPorDefecto() {
            const mapa = Teclas.leer("")
            compare(mapa.l2, [340], "L2 = Shift")
            compare(mapa.r2, [341], "R2 = Ctrl")
            compare(mapa.l1, [81], "L1 = Q")
            compare(mapa.up, [265], "cruceta arriba = flecha")
            compare(mapa.poseidon, [49], "Ira de Poseidón = 1")
            compare(mapa.medusa, [50], "Mirada de Medusa = 2")
            compare(mapa.zeus, [51], "Furia de Zeus = 3")
            compare(mapa.hades, [52], "Ejército de Hades = 4")
            compare(mapa.artemisa, [1002], "Espada de Artemisa = clic central")
            verify(Teclas.cadena(mapa).indexOf("artemisa=1002") >= 0, "Artemisa va al juego")
            compare(mapa.square, [1000], "cuadrado = clic izquierdo")
            verify(Teclas.cadena(mapa).indexOf("l2=340") >= 0, "L2 va al juego")
            compare(Teclas.conflictos(mapa, "r2", 341).length, 0, "Ctrl como esquiva y R2 no es conflicto")
        }

        function test_mapaAntiguo() {
            // Mapa guardado antes de las acciones de las magias: 1-4 en la cruceta, R2 en un botón lateral.
            const antiguo = JSON.stringify({ up: [265, 49], right: [262, 50], down: [264, 51], left: [263, 52], r2: [1004] })
            const mapa = Teclas.leer(antiguo)
            compare(mapa.up, [265], "1 sale de la cruceta")
            compare(mapa.left, [263], "4 sale de la cruceta")
            compare(mapa.poseidon, [49], "1 pasa a Poseidón")
            compare(mapa.hades, [52], "4 pasa a Hades")
            compare(mapa.r2, [1004], "lo demás se conserva")
            compare(Teclas.conflictos(mapa, "poseidon", 49).length, 0, "sin conflicto con la cruceta")
        }

        function test_capturaTecla() {
            pagina.abrirCaptura("l2", 1)
            wait(50)
            keyPress(Qt.Key_X)
            keyRelease(Qt.Key_X)
            compare(Teclas.leer(ajustesFalsos.teclas).l2, [340, 88], "segunda tecla de L2 = X")
        }

        function test_capturaRaton() {
            pagina.abrirCaptura("cross", 0)
            wait(50)
            mouseClick(raizPrueba, 450, 800, Qt.MiddleButton)
            compare(Teclas.leer(ajustesFalsos.teclas).cross, [1002], "salto = clic central")
        }

        function test_escapeCancela() {
            pagina.abrirCaptura("r1", 0)
            wait(50)
            keyPress(Qt.Key_Escape)
            compare(ajustesFalsos.teclas, "", "Escape no cambia nada")
            pagina.abrirCaptura("r1", 0)
            wait(50)
            keyPress(Qt.Key_G)
            compare(Teclas.leer(ajustesFalsos.teclas).r1, [71], "tras cancelar, la captura sigue funcionando")
        }

        function test_conflictoYBorrado() {
            let mapa = Teclas.asignar(Teclas.leer(""), "l1", 0, 87) // Q -> W, que ya es "adelante"
            compare(Teclas.conflictos(mapa, "l1", 87), ["li_arriba"], "W en dos acciones")
            mapa = Teclas.asignar(mapa, "l1", 0, 0)
            compare(mapa.l1, [], "clic derecho borra")
        }
    }
}
