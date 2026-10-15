import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts
import QtQuick.Shapes
import "Teclas.js" as Teclas

// Ventana principal del lanzador: portada con el botón de jugar a la izquierda y ajustes en pestañas a la derecha.
ApplicationWindow {
    id: ventana
    width: 1240
    height: 740
    minimumWidth: 1040
    minimumHeight: 660
    visible: true
    title: "God Of War: Tobiichi Launcher"
    color: Tema.fondo
    flags: Qt.Window | Qt.FramelessWindowHint
    font.family: Tema.fuenteCuerpo

    Settings {
        id: ajustes
        category: "ajustes"
        property string idioma: ""
        property string gpu: "auto"
        property string modoPantalla: "completa"
        property int ancho: 1280
        property int alto: 800
        property string aspecto: ""
        property bool estirar: false
        property string filtro: "bilineal" // GOW-Port (ultimate): imagen suave por defecto
        property real nitidez: 0.8
        property bool fxaa: true
        property string resolucionInterna: "2" // GOW-Port: "auto" (según la pantalla) o "1".."8" (PS2X_GS_ESCALA)
        property bool escalaDinamica: true // GOW-Port: baja la resolución si la GPU no llega a 60 (PS2X_GS_ESCALA_DINAMICA)
        property bool dibujoHardware: true // GOW-Port: triángulos con el pipeline de la GPU (PS2X_GS_HW, experimental)
        property bool imagenNitida: true // GOW-Port: sin doblado de líneas ni antiparpadeo (PS2X_GS_NITIDO)
        property int fpsLimite: 120
        property bool vsync: false
        property bool mostrarFps: false
        property string elf: ""
        property string iso: ""
        property string ejecutable: ""
        property bool saltarVideos: true // GOW-Port: vídeos desactivados por ahora; se retomarán tras optimizar la partida
        property bool arranqueRapido: false // GOW-Port: acortaba la apertura del juego (ver Component.onCompleted)
        property int versionAjustes: 0
        property bool controlesDmc5: true
        property bool cancelarAnimaciones: true // GOW-Port: evasión y búfer de entrada más ágiles (GOW_CANCELAR)
        property bool escSalir: false
        property bool minimizarAlJugar: true
        property int segundosJugados: 0
        property int ultimaSesion: 0
        property string portada: ""
        property string teclas: "" // mapa de teclas en JSON (vacío = esquema por defecto)
        property string trucos: "" // trucos activos al arrancar, separados por comas (gow_trucos.cpp)
        property real portadaFoco: 0.55
        property real portadaBrillo: 0.85
    }

    Binding { target: Tema; property: "idioma"; value: ajustes.idioma || "en" }
    Binding { target: Tema; property: "fuenteTitulo"; value: fuenteTitulo }

    readonly property var pantalla: lanzador.pantalla()
    property var tarjetas: lanzador.tarjetasGraficas()
    readonly property bool gpuPerdida: ajustes.gpu !== "auto" && !tarjetaExiste(ajustes.gpu)
    readonly property var estadoJuego: lanzador.comprobarJuego(ajustes.elf)
    readonly property var estadoDatos: lanzador.comprobarDatos(ajustes.elf, ajustes.iso)
    readonly property var estadoEjecutable: lanzador.comprobarEjecutable(ajustes.ejecutable)
    readonly property bool listo: estadoJuego.valido && estadoDatos.ok && estadoEjecutable.ejecutable
    // Una imagen recortada (fondo transparente) se muestra como figura; una imagen opaca cubre la portada.
    readonly property bool portadaRecorte: ajustes.portada.length > 0 && lanzador.esRecorte(ajustes.portada)

    function tarjetaExiste(id) {
        for (var i = 0; i < tarjetas.length; ++i)
            if (tarjetas[i].id === id) return true
        return false
    }

    function aspectoPorDefecto() {
        var r = pantalla.ancho / pantalla.alto
        if (r >= 2.2) return "21:9"
        if (r >= 1.7) return "16:9"
        if (r >= 1.5) return "16:10"
        return "4:3"
    }

    // GOW-Port: resolución interna. Automático: la altura de la imagen en pantalla entre 448 líneas, de 2× a 8×.
    function escalaAuto() {
        var alto = ajustes.modoPantalla === "completa" ? pantalla.alto : ajustes.alto
        return Math.max(2, Math.min(8, Math.floor(alto / 448)))
    }
    function escalaElegida() {
        var n = parseInt(ajustes.resolucionInterna)
        return ajustes.resolucionInterna === "auto" || isNaN(n) ? escalaAuto() : Math.max(1, Math.min(8, n))
    }
    function textoEscala(n) {
        return n + "× · " + (512 * n) + "×" + (448 * n)
    }

    function detectarRutas(forzar) {
        var r = lanzador.rutasDetectadas()
        if ((forzar || ajustes.elf.length === 0) && r.elf.length > 0) ajustes.elf = r.elf
        if ((forzar || ajustes.ejecutable.length === 0) && r.ejecutable.length > 0) ajustes.ejecutable = r.ejecutable
    }

    function restablecer() {
        ajustes.gpu = "auto"
        ajustes.modoPantalla = "completa"
        ajustes.ancho = 1280
        ajustes.alto = pantalla.ancho / pantalla.alto < 1.7 ? 800 : 720
        ajustes.aspecto = aspectoPorDefecto()
        ajustes.estirar = false
        ajustes.filtro = "bilineal"
        ajustes.nitidez = 0.8
        ajustes.fxaa = true
        ajustes.resolucionInterna = "2"
        ajustes.escalaDinamica = true
        ajustes.dibujoHardware = true
        ajustes.imagenNitida = true
        ajustes.fpsLimite = 120
        ajustes.vsync = false
        ajustes.mostrarFps = false
        ajustes.saltarVideos = true
        ajustes.arranqueRapido = false
        ajustes.controlesDmc5 = true
        ajustes.cancelarAnimaciones = true
        ajustes.escSalir = false
        ajustes.minimizarAlJugar = true
        ajustes.trucos = ""
    }

    function nombreGpu() {
        if (ajustes.gpu === "auto" || gpuPerdida) return Tema.t("gpuAuto")
        for (var i = 0; i < tarjetas.length; ++i)
            if (tarjetas[i].id === ajustes.gpu)
                return lanzador.sistema === "windows" ? Tema.t(tarjetas[i].id === "ahorro" ? "gpuAhorro" : "gpuRendimiento")
                                                      : tarjetas[i].fabricante + " " + tarjetas[i].nombre
        return Tema.t("gpuAuto")
    }

    function jugar() {
        var a = {
            gpu: gpuPerdida ? "auto" : ajustes.gpu,
            modoPantalla: ajustes.modoPantalla,
            ancho: ajustes.ancho, alto: ajustes.alto,
            aspecto: ajustes.aspecto, estirar: ajustes.estirar,
            filtro: ajustes.filtro, nitidez: ajustes.nitidez, fxaa: ajustes.fxaa,
            escala: escalaElegida(), escalaDinamica: ajustes.escalaDinamica, imagenNitida: ajustes.imagenNitida,
            dibujoHardware: ajustes.dibujoHardware,
            fpsLimite: ajustes.fpsLimite, vsync: ajustes.vsync, mostrarFps: ajustes.mostrarFps,
            elf: ajustes.elf, iso: ajustes.iso, ejecutable: ajustes.ejecutable,
            saltarVideos: ajustes.saltarVideos, arranqueRapido: ajustes.arranqueRapido,
            controlesDmc5: ajustes.controlesDmc5, escSalir: ajustes.escSalir,
            cancelarAnimaciones: ajustes.cancelarAnimaciones,
            teclas: Teclas.cadena(Teclas.leer(ajustes.teclas)),
            trucos: ajustes.trucos, idioma: Tema.idioma
        }
        if (lanzador.iniciar(a) && ajustes.minimizarAlJugar)
            minimizarTrasArrancar.start()
    }

    function ponerPortada(ruta) {
        var copia = lanzador.guardarPortada(ruta)
        if (copia.length > 0) {
            ajustes.portada = copia
            aviso(Tema.t("portadaHecha"))
        } else {
            aviso(Tema.t("portadaNoValida"))
        }
    }

    function quitarPortada() {
        lanzador.borrarPortada()
        ajustes.portada = ""
    }

    function aviso(texto) {
        tostada.texto = texto
        tostada.mostrar()
    }

    Timer {
        id: minimizarTrasArrancar
        interval: 600
        onTriggered: if (lanzador.jugando) ventana.showMinimized()
    }

    Connections {
        target: lanzador
        function onJuegoTerminado(codigo, fallo, segundos, resumen) {
            ajustes.segundosJugados += segundos
            ajustes.ultimaSesion = segundos
            if (ventana.visibility === Window.Minimized) ventana.showNormal()
            ventana.raise()
            ventana.requestActivate()
            if (fallo) {
                dialogoError.texto = Tema.tf("terminadoFallo", codigo)
                dialogoError.detalle = resumen
                dialogoError.open()
            } else {
                ventana.aviso(Tema.tf("terminadoOk", Tema.duracion(segundos)))
            }
        }
        function onError(clave, detalle) {
            dialogoError.texto = Tema.tf(clave, detalle)
            dialogoError.detalle = clave === "errorArranque" ? "" : detalle
            dialogoError.open()
        }
    }

    Component.onCompleted: {
        // GOW-Port: versión 2 de los ajustes. El arranque rápido venía activado por defecto y da por terminada la
        // animación de entrada al cargar el nivel, así que la apertura se acortaba; se desactiva una vez.
        if (ajustes.versionAjustes < 2) {
            ajustes.arranqueRapido = false
            ajustes.versionAjustes = 2
        }
        // GOW-Port: versión 3: resolución de dibujo 2× por defecto, con la dinámica que protege los 60 FPS.
        if (ajustes.versionAjustes < 3) {
            ajustes.resolucionInterna = "2"
            ajustes.escalaDinamica = true
            ajustes.versionAjustes = 3
        }
        // GOW-Port: versión 4: el renderizador por hardware de triángulos, activado una vez.
        if (ajustes.versionAjustes < 4) {
            ajustes.dibujoHardware = true
            ajustes.versionAjustes = 4
        }
        // GOW-Port: versión 5: los vídeos se saltan por defecto mientras se optimiza la partida.
        if (ajustes.versionAjustes < 5) {
            ajustes.saltarVideos = true
            ajustes.versionAjustes = 5
        }
        // GOW-Port: versión 6 (rama ultimate): el runtime de Waffle reproduce los vídeos de forma nativa, con sonido.
        if (ajustes.versionAjustes < 6) {
            ajustes.saltarVideos = false
            ajustes.versionAjustes = 6
        }
        if (ajustes.idioma.length === 0) {
            var loc = Qt.locale().name
            ajustes.idioma = loc.indexOf("tr") === 0 ? "tr" : (loc.indexOf("es") === 0 ? "es" : "en")
        }
        if (ajustes.aspecto.length === 0) ajustes.aspecto = aspectoPorDefecto()
        detectarRutas(false)
        // "--jugar": arranca el juego directamente con los ajustes guardados (acción "Jugar ya" del acceso directo).
        if (Qt.application.arguments.indexOf("--jugar") >= 0 && listo)
            jugar()
    }

    // ---------------------------------------------------------------- Fondo
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#160907" }
            GradientStop { position: 0.6; color: "#0b0605" }
            GradientStop { position: 1.0; color: "#050302" }
        }
    }
    Shape {
        anchors.fill: parent
        preferredRendererType: Shape.CurveRenderer
        ShapePath {
            strokeWidth: 0
            strokeColor: "transparent"
            fillGradient: RadialGradient {
                centerX: ventana.width * 0.2; centerY: ventana.height * 1.05
                centerRadius: ventana.height * 0.95
                focalX: centerX; focalY: centerY
                GradientStop { position: 0.0; color: "#7a1d0c" }
                GradientStop { position: 0.35; color: "#3a0d07" }
                GradientStop { position: 1.0; color: "transparent" }
            }
            startX: 0; startY: 0
            PathLine { x: ventana.width; y: 0 }
            PathLine { x: ventana.width; y: ventana.height }
            PathLine { x: 0; y: ventana.height }
            PathLine { x: 0; y: 0 }
        }
    }
    Ascuas {
        anchors.fill: parent
        intensidad: lanzador.jugando ? 0.35 : 1.0
    }
    Rectangle {
        // Marco de la ventana.
        anchors.fill: parent
        color: "transparent"
        border.width: 1
        border.color: "#4a2e1c"
        z: 10
    }

    // ---------------------------------------------------------------- Barra de título
    Item {
        id: barra
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: 42
        z: 5

        DragHandler {
            target: null
            grabPermissions: PointerHandler.CanTakeOverFromAnything
            onActiveChanged: if (active) ventana.startSystemMove()
        }

        Row {
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            Image {
                source: lanzador.urlDesdeRuta(lanzador.rutaIcono)
                width: 20
                height: 20
                anchors.verticalCenter: parent.verticalCenter
                smooth: true
                mipmap: true
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "God Of War: Tobiichi Launcher"
                color: Tema.textoTenue
                font.pixelSize: 13
                font.letterSpacing: 0.5
            }
        }

        Row {
            anchors.right: parent.right
            anchors.top: parent.top
            height: parent.height
            Repeater {
                model: [{ simbolo: "minimizar", accion: 0 }, { simbolo: "cerrar", accion: 1 }]
                delegate: Rectangle {
                    id: botonVentana
                    required property var modelData
                    width: 50
                    height: barra.height
                    color: zona.containsMouse ? (modelData.accion === 1 ? "#b3241a" : "#2a1a12") : "transparent"
                    Canvas {
                        anchors.centerIn: parent
                        width: 12
                        height: 12
                        property bool cerrar: botonVentana.modelData.accion === 1
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.reset()
                            ctx.strokeStyle = "#d9c9b8"
                            ctx.lineWidth = 1.3
                            ctx.beginPath()
                            if (cerrar) {
                                ctx.moveTo(1, 1); ctx.lineTo(11, 11)
                                ctx.moveTo(11, 1); ctx.lineTo(1, 11)
                            } else {
                                ctx.moveTo(1, 6.5); ctx.lineTo(11, 6.5)
                            }
                            ctx.stroke()
                        }
                    }
                    MouseArea {
                        id: zona
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: botonVentana.modelData.accion === 1 ? ventana.close() : ventana.showMinimized()
                    }
                    ToolTip.visible: zona.containsMouse
                    ToolTip.delay: 600
                    ToolTip.text: Tema.t(modelData.simbolo)
                }
            }
        }
    }

    // ---------------------------------------------------------------- Contenido
    RowLayout {
        anchors.fill: parent
        anchors.topMargin: barra.height
        spacing: 0

        // Portada.
        Item {
            id: portada
            Layout.preferredWidth: 476
            Layout.fillHeight: true

            // Imagen de portada del usuario. Opaca: cubre la zona sin deformarse y se funde con el fondo por los
            // bordes. Recortada (fondo transparente): figura en el centro, con aura roja, la omega detrás y los pies
            // perdiéndose en la oscuridad bajo el botón.
            Item {
                id: marcoImagen
                readonly property bool figura: ventana.portadaRecorte
                anchors.fill: parent
                clip: true
                visible: imagenPortada.status === Image.Ready
                Image {
                    id: imagenPortada
                    readonly property real escala: !(implicitWidth > 0 && implicitHeight > 0) ? 1
                        : marcoImagen.figura ? marcoImagen.height * 0.95 / implicitHeight
                        : Math.max(marcoImagen.width / implicitWidth, marcoImagen.height / implicitHeight)
                    readonly property real sobrante: Math.max(0, height - marcoImagen.height)
                    source: ajustes.portada.length > 0 ? lanzador.urlDesdeRuta(ajustes.portada) : ""
                    asynchronous: true
                    cache: false
                    smooth: true
                    mipmap: true
                    visible: false
                    width: implicitWidth * escala
                    height: implicitHeight * escala
                    x: marcoImagen.figura ? marcoImagen.width * 0.6 - width / 2 : (marcoImagen.width - width) / 2
                    // Opaca: 0 = la parte de abajo de la imagen arriba del todo; 1 = bajada un 40 % de la zona.
                    // Figura: la parte de arriba entre el borde superior (0) y el 62 % de la zona (1).
                    y: marcoImagen.figura ? marcoImagen.height * 0.62 * ajustes.portadaFoco
                                          : -sobrante + ajustes.portadaFoco * (sobrante + marcoImagen.height * 0.4)
                }
                Gradient {
                    id: mascaraArriba
                    GradientStop { position: 0.0; color: "transparent" }
                    GradientStop { position: 0.2; color: "white" }
                    GradientStop { position: 1.0; color: "white" }
                }
                Gradient {
                    id: mascaraFigura
                    // Opaca hasta el pecho y transparente a la altura de los datos de configuración.
                    GradientStop { position: 0.0; color: "white" }
                    GradientStop {
                        position: Math.max(0.01, Math.min(0.98, (marcoImagen.height * 0.55 - imagenPortada.y) / Math.max(1, imagenPortada.height)))
                        color: "white"
                    }
                    GradientStop {
                        position: Math.max(0.02, Math.min(0.99, (marcoImagen.height * 0.77 - imagenPortada.y) / Math.max(1, imagenPortada.height)))
                        color: "transparent"
                    }
                    GradientStop { position: 1.0; color: "transparent" }
                }
                Rectangle {
                    // Máscara: el borde superior de la imagen se desvanece hacia el fondo.
                    id: mascaraPortada
                    x: imagenPortada.x
                    y: imagenPortada.y
                    width: imagenPortada.width
                    height: imagenPortada.height
                    visible: false
                    layer.enabled: true
                    gradient: marcoImagen.figura ? mascaraFigura : mascaraArriba
                }
                MultiEffect {
                    x: imagenPortada.x
                    y: imagenPortada.y
                    width: imagenPortada.width
                    height: imagenPortada.height
                    source: imagenPortada
                    maskEnabled: true
                    maskSource: mascaraPortada
                    // Sin dispersión la máscara es un umbral duro; así sigue el degradado.
                    maskThresholdMin: 0.5
                    maskSpreadAtMin: 1.0
                    // Figura: aura de fuego como la del título y brillo ajustable.
                    brightness: marcoImagen.figura ? (ajustes.portadaBrillo - 1.0) * 0.6 : 0
                    shadowEnabled: marcoImagen.figura
                    shadowColor: "#e4502a"
                    shadowBlur: 1.0
                    shadowOpacity: 0.9
                    shadowHorizontalOffset: 0
                    shadowVerticalOffset: 0
                    blurMax: 56
                    opacity: imagenPortada.status === Image.Ready ? 1 : 0
                    Behavior on opacity { NumberAnimation { duration: 600; easing.type: Easing.OutCubic } }
                }
                Rectangle {
                    visible: !marcoImagen.figura
                    anchors.fill: parent
                    color: Tema.fondo
                    opacity: 1 - ajustes.portadaBrillo
                }
                Rectangle {
                    // Oscuro arriba (título) y abajo (estado y botón); la imagen se ve en el centro.
                    visible: !marcoImagen.figura
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#c00a0605" }
                        GradientStop { position: 0.2; color: "#600a0605" }
                        GradientStop { position: 0.38; color: "#000a0605" }
                        GradientStop { position: 0.58; color: "#100a0605" }
                        GradientStop { position: 0.76; color: "#c80a0605" }
                        GradientStop { position: 1.0; color: "#f40a0605" }
                    }
                }
                Rectangle {
                    // Bordes laterales: a la izquierda suave, a la derecha hasta el color del fondo.
                    visible: !marcoImagen.figura
                    anchors.fill: parent
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#990a0605" }
                        GradientStop { position: 0.16; color: "#000a0605" }
                        GradientStop { position: 0.72; color: "#000a0605" }
                        GradientStop { position: 1.0; color: "#ff0a0605" }
                    }
                }
            }

            Text {
                // Omega de fondo, detrás del hueco central de la portada (y de la figura, como un halo).
                visible: !marcoImagen.visible || marcoImagen.figura
                z: -1
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -10
                text: "Ω"
                font.family: Tema.fuenteTitulo
                font.pixelSize: 400
                font.weight: Font.Black
                color: Tema.oro
                opacity: marcoImagen.figura ? 0.09 : 0.06
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.leftMargin: 52
                anchors.rightMargin: 40
                anchors.topMargin: 34
                anchors.bottomMargin: 34
                spacing: 0

                Item {
                    id: titulo
                    Layout.preferredWidth: textoTitulo.implicitWidth
                    Layout.preferredHeight: textoTitulo.implicitHeight
                    layer.enabled: true
                    layer.effect: MultiEffect {
                        shadowEnabled: true
                        shadowColor: "#c2341a"
                        shadowBlur: 0.9
                        shadowOpacity: 0.55
                        shadowHorizontalOffset: 0
                        shadowVerticalOffset: 0
                    }
                    Text {
                        id: textoTitulo
                        text: "GOD OF WAR"
                        font.family: Tema.fuenteTitulo
                        font.pixelSize: 54
                        font.weight: Font.Black
                        font.letterSpacing: 3
                        color: "white"
                        visible: false
                        layer.enabled: true
                    }
                    Rectangle {
                        id: degradadoOro
                        anchors.fill: parent
                        visible: false
                        layer.enabled: true
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#fff1c4" }
                            GradientStop { position: 0.45; color: "#e2b866" }
                            GradientStop { position: 0.55; color: "#c08a3a" }
                            GradientStop { position: 1.0; color: "#7a5220" }
                        }
                    }
                    MultiEffect {
                        anchors.fill: parent
                        source: degradadoOro
                        maskEnabled: true
                        maskSource: textoTitulo
                    }
                }

                Meandro {
                    Layout.fillWidth: true
                    Layout.topMargin: 12
                }

                Text {
                    Layout.topMargin: 12
                    text: Tema.t("subtitulo")
                    font.family: Tema.fuenteTitulo
                    font.pixelSize: 17
                    font.weight: Font.Bold
                    font.letterSpacing: 7
                    color: Tema.textoSuave
                }
                Text {
                    Layout.topMargin: 10
                    Layout.fillWidth: true
                    text: Tema.t("lema")
                    color: Tema.textoTenue
                    font.pixelSize: 14
                    wrapMode: Text.WordWrap
                }

                Item { Layout.fillHeight: true }

                // Estado.
                RowLayout {
                    spacing: 9
                    Rectangle {
                        width: 10
                        height: 10
                        radius: 5
                        color: ventana.listo ? Tema.bien : Tema.mal
                        SequentialAnimation on opacity {
                            running: lanzador.jugando
                            loops: Animation.Infinite
                            NumberAnimation { to: 0.3; duration: 700 }
                            NumberAnimation { to: 1.0; duration: 700 }
                        }
                    }
                    Text {
                        text: ventana.listo ? (ventana.estadoJuego.valido ? Tema.t("verificado") : Tema.t("listo")) : Tema.t("faltan")
                        color: ventana.listo ? Tema.texto : Tema.mal
                        font.pixelSize: 14
                        font.weight: Font.Medium
                    }
                }

                // Resumen de la configuración.
                Flow {
                    Layout.fillWidth: true
                    Layout.topMargin: 14
                    spacing: 6
                    Repeater {
                        model: [
                            ventana.nombreGpu(),
                            ajustes.modoPantalla === "completa" ? Tema.t("completa") + " · " + ventana.pantalla.ancho + "×" + ventana.pantalla.alto
                                                                : Tema.t("ventana") + " · " + ajustes.ancho + "×" + ajustes.alto,
                            ajustes.aspecto,
                            ventana.textoEscala(ventana.escalaElegida()) + (ajustes.escalaDinamica ? " · " + Tema.t("dinamicaCorta") : ""),
                            (ajustes.filtro === "fsr" ? "Bicubic" : "Bilinear") + (ajustes.fxaa ? " + FXAA" : ""),
                            (ajustes.fpsLimite > 0 ? ajustes.fpsLimite + " FPS" : Tema.t("sinLimite")) + (ajustes.vsync ? " · VSync" : "")
                        ]
                        delegate: Rectangle {
                            required property string modelData
                            height: 26
                            width: chip.implicitWidth + 18
                            radius: 13
                            color: "#2a1a12"
                            border.width: 1
                            border.color: Tema.borde
                            Text {
                                id: chip
                                anchors.centerIn: parent
                                text: parent.modelData
                                color: Tema.textoSuave
                                font.pixelSize: 12
                            }
                        }
                    }
                }

                BotonJugar {
                    Layout.topMargin: 22
                    Layout.fillWidth: true
                    listo: ventana.listo
                    jugando: lanzador.jugando
                    text: lanzador.jugando ? Tema.t("jugando") : Tema.t("jugar")
                    onClicked: if (!lanzador.jugando) ventana.jugar()
                }

                RowLayout {
                    Layout.topMargin: 12
                    Layout.fillWidth: true
                    Text {
                        Layout.fillWidth: true
                        text: ajustes.segundosJugados > 0 ? Tema.tf("tiempoTotal", Tema.duracion(ajustes.segundosJugados)) : ""
                        color: Tema.textoTenue
                        font.pixelSize: 13
                    }
                    Text {
                        visible: lanzador.jugando
                        text: Tema.t("cerrarJuego")
                        color: zonaCerrar.containsMouse ? Tema.rojoClaro : Tema.textoSuave
                        font.pixelSize: 13
                        font.underline: zonaCerrar.containsMouse
                        MouseArea {
                            id: zonaCerrar
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: lanzador.detener()
                        }
                    }
                }
            }
        }

        // Separador vertical.
        Rectangle {
            Layout.fillHeight: true
            Layout.topMargin: 30
            Layout.bottomMargin: 30
            width: 1
            gradient: Gradient {
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.5; color: Tema.bordeClaro }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }

        // Ajustes.
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 34
            Layout.rightMargin: 34
            Layout.topMargin: 14
            Layout.bottomMargin: 26
            spacing: 14

            TabBar {
                id: pestanas
                Layout.fillWidth: true
                currentIndex: pestanaInicial
                background: Item {
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 1
                        color: Tema.borde
                    }
                }
                Pestana { text: Tema.t("pestGrafico") }
                Pestana { text: Tema.t("pestRendimiento") }
                Pestana { text: Tema.t("pestArchivos") }
                Pestana { text: Tema.t("pestControles") }
                Pestana { text: Tema.t("pestTrucos") }
                Pestana { text: Tema.t("pestOtros") }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 6
                color: "#b3120a07"
                border.width: 1
                border.color: Tema.borde

                StackLayout {
                    anchors.fill: parent
                    anchors.margins: 22
                    anchors.rightMargin: 14
                    currentIndex: pestanas.currentIndex

                    PaginaGrafico {
                        ajustes: ajustes
                        tarjetas: ventana.tarjetas
                        pantalla: ventana.pantalla
                        gpuPerdida: ventana.gpuPerdida
                        escalaAuto: ventana.escalaAuto()
                    }
                    PaginaRendimiento {
                        ajustes: ajustes
                        pantalla: ventana.pantalla
                    }
                    PaginaArchivos {
                        ajustes: ajustes
                        estadoJuego: ventana.estadoJuego
                        estadoDatos: ventana.estadoDatos
                        estadoEjecutable: ventana.estadoEjecutable
                        onDetectar: ventana.detectarRutas(true)
                    }
                    PaginaControles {
                        ajustes: ajustes
                    }
                    PaginaTrucos {
                        ajustes: ajustes
                    }
                    PaginaOtros {
                        ajustes: ajustes
                        onRestablecer: ventana.restablecer()
                        onAviso: (t) => ventana.aviso(t)
                        onPonerPortada: (r) => ventana.ponerPortada(r)
                        onQuitarPortada: ventana.quitarPortada()
                    }
                }
            }
        }
    }

    // Arrastrar una imagen a la ventana la pone como portada.
    DropArea {
        id: zonaSoltar
        anchors.fill: parent
        z: 30
        onEntered: (drag) => drag.accepted = drag.hasUrls
        onDropped: (drop) => {
            if (drop.hasUrls && drop.urls.length > 0)
                ventana.ponerPortada(lanzador.rutaDesdeUrl(drop.urls[0]))
        }
        Rectangle {
            anchors.fill: parent
            anchors.margins: 14
            visible: zonaSoltar.containsDrag
            radius: 10
            color: "#b30a0605"
            border.width: 2
            border.color: Tema.oro
            Text {
                anchors.centerIn: parent
                text: Tema.t("portadaSoltar")
                color: Tema.oroClaro
                font.family: Tema.fuenteTitulo
                font.pixelSize: 26
                font.weight: Font.Bold
                font.letterSpacing: 2
            }
        }
    }

    // Asa para redimensionar.
    MouseArea {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 18
        height: 18
        z: 11
        cursorShape: Qt.SizeFDiagCursor
        onPressed: ventana.startSystemResize(Qt.RightEdge | Qt.BottomEdge)
    }

    // ---------------------------------------------------------------- Avisos
    Rectangle {
        id: tostada
        property string texto
        function mostrar() {
            animacionTostada.restart()
        }
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height - 70
        z: 20
        width: textoTostada.implicitWidth + 36
        height: 40
        radius: 20
        color: "#ee1d120c"
        border.width: 1
        border.color: Tema.oro
        opacity: 0
        visible: opacity > 0
        Text {
            id: textoTostada
            anchors.centerIn: parent
            text: tostada.texto
            color: Tema.oroClaro
            font.pixelSize: 14
        }
        SequentialAnimation {
            id: animacionTostada
            NumberAnimation { target: tostada; property: "opacity"; to: 1; duration: 180 }
            PauseAnimation { duration: 4200 }
            NumberAnimation { target: tostada; property: "opacity"; to: 0; duration: 400 }
        }
    }

    Popup {
        id: dialogoError
        property string texto
        property string detalle
        anchors.centerIn: Overlay.overlay
        width: 560
        modal: true
        padding: 24
        Overlay.modal: Rectangle { color: "#a0000000" }
        background: Rectangle {
            radius: 6
            color: "#1c110c"
            border.width: 1
            border.color: Tema.mal
        }
        contentItem: ColumnLayout {
            spacing: 14
            Text {
                Layout.fillWidth: true
                text: dialogoError.texto
                color: Tema.texto
                font.pixelSize: 15
                font.weight: Font.Medium
                wrapMode: Text.WordWrap
            }
            Rectangle {
                visible: dialogoError.detalle.length > 0
                Layout.fillWidth: true
                implicitHeight: textoDetalle.implicitHeight + 20
                radius: 4
                color: "#120b08"
                border.width: 1
                border.color: Tema.borde
                Text {
                    id: textoDetalle
                    anchors.fill: parent
                    anchors.margins: 10
                    text: dialogoError.detalle
                    color: Tema.textoSuave
                    font.family: "monospace"
                    font.pixelSize: 12
                    wrapMode: Text.WrapAnywhere
                }
            }
            RowLayout {
                Layout.alignment: Qt.AlignRight
                spacing: 8
                BotonSecundario {
                    text: Tema.t("verRegistro")
                    onClicked: lanzador.abrirRegistro()
                }
                BotonSecundario {
                    text: Tema.t("entendido")
                    onClicked: dialogoError.close()
                }
            }
        }
    }
}
