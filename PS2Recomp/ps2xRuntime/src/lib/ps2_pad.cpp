#include "runtime/ps2_pad.h"
#include "ps2_host_backend.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#ifdef _WIN32
bool ps2PadWindowsRumble(uint8_t large, bool small); // ps2_pad_rumble_win.cpp
#endif

namespace
{
    constexpr uint8_t kPadAnalogMarker = 0x73;
    constexpr uint8_t kPadStickCenter = 0x80;

    constexpr uint16_t PAD_LEFT = 0x0080u;
    constexpr uint16_t PAD_DOWN = 0x0040u;
    constexpr uint16_t PAD_RIGHT = 0x0020u;
    constexpr uint16_t PAD_UP = 0x0010u;
    constexpr uint16_t PAD_START = 0x0008u;
    constexpr uint16_t PAD_R3 = 0x0004u;
    constexpr uint16_t PAD_L3 = 0x0002u;
    constexpr uint16_t PAD_SELECT = 0x0001u;
    constexpr uint16_t PAD_SQUARE = 0x8000u;
    constexpr uint16_t PAD_CROSS = 0x4000u;
    constexpr uint16_t PAD_CIRCLE = 0x2000u;
    constexpr uint16_t PAD_TRIANGLE = 0x1000u;
    constexpr uint16_t PAD_R1 = 0x0800u;
    constexpr uint16_t PAD_L1 = 0x0400u;
    constexpr uint16_t PAD_R2 = 0x0200u;
    constexpr uint16_t PAD_L2 = 0x0100u;

    // GOW-Port: teclado y ratón configurables desde el lanzador. TOBIICHI_TECLAS="accion=codigo,codigo;..." con códigos
    // de tecla de raylib (los de GLFW, por posición física) y 1000 + botón para el ratón (1000 izquierdo, 1001
    // derecho, 1002 central, 1003/1004 laterales). Mayúsculas, Ctrl y Alt izquierdos valen también por los derechos.
    // Sin la variable, el teclado sigue como antes (esquema fijo). El mando no cambia.
    //
    // Acciones propias de God of War: cada magia pulsa su dirección de la cruceta, según la tabla de controles del
    // juego (0x29D058: derecha, izquierda, arriba y abajo dan los bits 26-29, que 0x1D7250 convierte en SelectMagic
    // 3-6): derecha = Furia de Zeus, izquierda = Mirada de Medusa, arriba = Ejército de Hades, abajo = Ira de
    // Poseidón. "artemisa" pulsa L1 + R1 a la vez (sacar y guardar la Espada de Artemisa); "furia", L3 + R3.
    enum Accion : size_t
    {
        AccArriba, AccAbajo, AccIzquierda, AccDerecha, AccCruz, AccCirculo, AccCuadrado, AccTriangulo,
        AccL1, AccR1, AccL2, AccR2, AccL3, AccR3, AccStart, AccSelect,
        AccPoseidon, AccMedusa, AccZeus, AccHades, AccArtemisa, AccFuria,
        AccLiArriba, AccLiAbajo, AccLiIzq, AccLiDer, AccLdArriba, AccLdAbajo, AccLdIzq, AccLdDer, AccLdMod,
        NumAcciones
    };
    constexpr const char *kNombresAccion[NumAcciones] = {
        "up", "down", "left", "right", "cross", "circle", "square", "triangle",
        "l1", "r1", "l2", "r2", "l3", "r3", "start", "select",
        "poseidon", "medusa", "zeus", "hades", "artemisa", "furia",
        "li_arriba", "li_abajo", "li_izq", "li_der", "ld_arriba", "ld_abajo", "ld_izq", "ld_der", "ld_mod"};
    // Botones que pulsa cada acción (hasta AccFuria; las demás mueven los sticks).
    constexpr uint16_t kBitAccion[AccFuria + 1] = {
        PAD_UP, PAD_DOWN, PAD_LEFT, PAD_RIGHT, PAD_CROSS, PAD_CIRCLE, PAD_SQUARE, PAD_TRIANGLE,
        PAD_L1, PAD_R1, PAD_L2, PAD_R2, PAD_L3, PAD_R3, PAD_START, PAD_SELECT,
        PAD_DOWN, PAD_LEFT, PAD_RIGHT, PAD_UP, PAD_L1 | PAD_R1, PAD_L3 | PAD_R3};

    struct MapaTeclas
    {
        bool activo = false;
        std::array<std::vector<int>, NumAcciones> codigos;
    };

    const MapaTeclas &mapaTeclas()
    {
        static const MapaTeclas mapa = []
        {
            MapaTeclas m;
            const char *valor = std::getenv("TOBIICHI_TECLAS");
            if (!valor || !*valor)
                return m;
            m.activo = true;
            const std::string texto(valor);
            size_t pos = 0;
            while (pos < texto.size())
            {
                size_t fin = texto.find(';', pos);
                if (fin == std::string::npos)
                    fin = texto.size();
                const std::string par = texto.substr(pos, fin - pos);
                const size_t igual = par.find('=');
                if (igual != std::string::npos)
                {
                    const std::string nombre = par.substr(0, igual);
                    for (size_t a = 0; a < NumAcciones; ++a)
                    {
                        if (nombre != kNombresAccion[a])
                            continue;
                        size_t p = igual + 1;
                        while (p < par.size())
                        {
                            size_t coma = par.find(',', p);
                            if (coma == std::string::npos)
                                coma = par.size();
                            const int codigo = std::atoi(par.substr(p, coma - p).c_str());
                            if (codigo > 0)
                                m.codigos[a].push_back(codigo);
                            p = coma + 1;
                        }
                    }
                }
                pos = fin + 1;
            }
            return m;
        }();
        return mapa;
    }

    bool codigoPulsado(int codigo)
    {
        if (codigo >= 1000)
            return IsMouseButtonDown(codigo - 1000);
        switch (codigo)
        {
        case KEY_LEFT_SHIFT:
        case KEY_RIGHT_SHIFT:
            return IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        case KEY_LEFT_CONTROL:
        case KEY_RIGHT_CONTROL:
            return IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
        case KEY_LEFT_ALT:
        case KEY_RIGHT_ALT:
            return IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
        default:
            return IsKeyDown(codigo);
        }
    }

    bool accionPulsada(const MapaTeclas &m, size_t accion)
    {
        for (const int codigo : m.codigos[accion])
            if (codigoPulsado(codigo))
                return true;
        return false;
    }

    bool esModificador(const MapaTeclas &m, int codigo)
    {
        for (const int mod : m.codigos[AccLdMod])
            if (mod == codigo)
                return true;
        return false;
    }

    // Botón: una tecla que también es el modificador del stick derecho (Ctrl = R2 y Ctrl + WASD = esquiva) solo cuenta
    // si no se está moviendo con el stick izquierdo; así esquivar no lanza también el botón.
    bool botonPulsado(const MapaTeclas &m, size_t accion, bool moviendo)
    {
        for (const int codigo : m.codigos[accion])
            if (codigoPulsado(codigo) && !(moviendo && esModificador(m, codigo)))
                return true;
        return false;
    }

    bool moviendoStickIzquierdo(const MapaTeclas &m)
    {
        return accionPulsada(m, AccLiArriba) || accionPulsada(m, AccLiAbajo) || accionPulsada(m, AccLiIzq) ||
               accionPulsada(m, AccLiDer);
    }

    uint8_t eje(bool negativo, bool positivo)
    {
        return negativo == positivo ? kPadStickCenter : (negativo ? 0u : 255u);
    }
}

// GOW-Port: sticks desde el teclado configurable, en el orden del paquete de libpad2 (RX, RY, LX, LY). Lo usa el
// envoltorio de la lectura del mando de God of War (ps2_runtime.cpp), porque gowPad2Read pone sus propios sticks fijos.
bool tobiichiSticksTeclado(uint8_t (&sticks)[4])
{
    const MapaTeclas &m = mapaTeclas();
    if (!m.activo || IsGamepadAvailable(0))
        return false;
    const uint8_t x = eje(accionPulsada(m, AccLiIzq), accionPulsada(m, AccLiDer));
    const uint8_t y = eje(accionPulsada(m, AccLiArriba), accionPulsada(m, AccLiAbajo));
    if (accionPulsada(m, AccLdMod))
    {
        sticks[0] = x;
        sticks[1] = y;
        sticks[2] = sticks[3] = kPadStickCenter;
        return true;
    }
    sticks[0] = eje(accionPulsada(m, AccLdIzq), accionPulsada(m, AccLdDer));
    sticks[1] = eje(accionPulsada(m, AccLdArriba), accionPulsada(m, AccLdAbajo));
    sticks[2] = x;
    sticks[3] = y;
    return true;
}

bool PSPadBackend::readState(int /*port*/, int /*slot*/, uint8_t *data, size_t size)
{
    if (!data || size < 32)
        return false;

    std::memset(data, 0, 32);
    data[0] = 0x01;
    data[1] = kPadAnalogMarker;
    data[2] = 0xFF;
    data[3] = 0xFF;
    data[4] = data[5] = data[6] = data[7] = kPadStickCenter;

    uint16_t btns = 0xFFFFu;
    // GOW-Port: GLFW can list racing gear (handbrake, pedals) as gamepads before the real pad. The pad whose
    // button was pressed last becomes the active one (press edges, so idle devices never take over);
    // until then, the first available slot.
    static int s_activeGamepad = -1;
    for (int i = 0; i < 4; ++i)
    {
        if (i == s_activeGamepad || !IsGamepadAvailable(i))
            continue;
        for (int button = GAMEPAD_BUTTON_LEFT_FACE_UP; button <= GAMEPAD_BUTTON_RIGHT_THUMB; ++button)
            if (IsGamepadButtonPressed(i, button))
            {
                s_activeGamepad = i;
                break;
            }
    }
    if (s_activeGamepad >= 0 && !IsGamepadAvailable(s_activeGamepad))
        s_activeGamepad = -1;
    int kGamepad = s_activeGamepad;
    for (int i = 0; i < 4 && kGamepad < 0; ++i)
        if (IsGamepadAvailable(i))
            kGamepad = i;
    const bool useGamepad = kGamepad >= 0;
    static int s_loggedGamepad = -2;
    if (kGamepad != s_loggedGamepad)
    {
        s_loggedGamepad = kGamepad;
        std::fprintf(stderr, "[pad] gamepad slot %d: %s\n", kGamepad, useGamepad ? GetGamepadName(kGamepad) : "none (keyboard)");
    }
    auto clearBit = [&btns](uint16_t mask)
    { btns &= ~mask; };

    // Tobiichi DMC5 Control Layout:
    // When enabled (via TOBIICHI_DMC5_CONTROLS=1, default 1):
    // Gamepad:
    //   Y (Triangle) -> Light/Normal Melee Attack (Square in GoW)
    //   B (Circle)   -> Heavy Melee Attack (Triangle in GoW)
    //   X (Square)   -> Grab / Special Interact (Circle in GoW)
    //   A (Cross)    -> Jump (Cross in GoW)
    //   LB (L1)      -> Parry / Block (L1 in GoW)
    //   RB (R1)      -> Lock-on / Combat Stance (R1 in GoW)
    //   LT (L2)      -> Magic / Devil Trigger (R2 in GoW)
    //   RT (R2)      -> Sub-weapon switch / Magic toggle (L2 in GoW)
    static const bool dmc5Controls = [] {
        const char *val = std::getenv("TOBIICHI_DMC5_CONTROLS");
        return val == nullptr || std::strcmp(val, "0") != 0;
    }();

    if (useGamepad)
    {
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_UP))
            clearBit(PAD_UP);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
            clearBit(PAD_DOWN);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
            clearBit(PAD_LEFT);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
            clearBit(PAD_RIGHT);

        if (dmc5Controls)
        {
            // DMC5 mapping
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) // A -> Jump
                clearBit(PAD_CROSS);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) // B -> Heavy Attack
                clearBit(PAD_TRIANGLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) // X -> Grab / Interact
                clearBit(PAD_CIRCLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) // Y -> Light Attack
                clearBit(PAD_SQUARE);

            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) // LB -> Block / Parry
                clearBit(PAD_L1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) // RB -> Stance / Charge
                clearBit(PAD_R1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) // LT -> Magic
                clearBit(PAD_R2);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) // RT -> Magic Toggle / Secondary
                clearBit(PAD_L2);
        }
        else
        {
            // Classic PS2 GoW layout
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
                clearBit(PAD_CROSS);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
                clearBit(PAD_CIRCLE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
                clearBit(PAD_SQUARE);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP))
                clearBit(PAD_TRIANGLE);

            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
                clearBit(PAD_L1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
                clearBit(PAD_R1);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
                clearBit(PAD_L2);
            if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
                clearBit(PAD_R2);
        }

        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT))
            clearBit(PAD_START);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_MIDDLE_LEFT))
            clearBit(PAD_SELECT);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_LEFT_THUMB))
            clearBit(PAD_L3);
        if (IsGamepadButtonDown(kGamepad, GAMEPAD_BUTTON_RIGHT_THUMB))
            clearBit(PAD_R3);

        float lx = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_LEFT_X);
        float ly = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_LEFT_Y);
        float rx = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_RIGHT_X);
        float ry = GetGamepadAxisMovement(kGamepad, GAMEPAD_AXIS_RIGHT_Y);
        data[6] = static_cast<uint8_t>(128 + lx * 127);
        data[7] = static_cast<uint8_t>(128 + ly * 127);
        data[4] = static_cast<uint8_t>(128 + rx * 127);
        data[5] = static_cast<uint8_t>(128 + ry * 127);
    }
    else if (mapaTeclas().activo)
    {
        // GOW-Port: teclado configurable (lanzador).
        const MapaTeclas &m = mapaTeclas();
        const bool moviendo = moviendoStickIzquierdo(m);
        for (size_t accion = 0; accion <= AccFuria; ++accion)
            if (botonPulsado(m, accion, moviendo))
                clearBit(kBitAccion[accion]);
        uint8_t sticks[4];
        if (tobiichiSticksTeclado(sticks))
        {
            data[4] = sticks[0];
            data[5] = sticks[1];
            data[6] = sticks[2];
            data[7] = sticks[3];
        }
    }
    else
    {
        if (dmc5Controls)
        {
            // GOW-Port: teclado y ratón (Tobiichi). Los sticks los pone gowPad2Read (gow_overrides.cpp):
            // WASD = stick izquierdo, Ctrl + WASD = stick derecho (esquiva).
            //   Flechas -> cruceta (selección)     Espacio -> X (salto)
            //   Clic izquierdo -> Cuadrado (ligero) Clic derecho -> Triángulo (fuerte)
            //   F -> Círculo (agarre)              Shift -> L1 (bloqueo / parada)
            //   Q -> R2 (magia)                    E -> R1 (habilidad / acción)
            //   V -> L3 + R3 (Furia de los dioses)
            if (IsKeyDown(KEY_UP))
                clearBit(PAD_UP);
            if (IsKeyDown(KEY_DOWN))
                clearBit(PAD_DOWN);
            if (IsKeyDown(KEY_LEFT))
                clearBit(PAD_LEFT);
            if (IsKeyDown(KEY_RIGHT))
                clearBit(PAD_RIGHT);

            if (IsKeyDown(KEY_SPACE))
                clearBit(PAD_CROSS);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                clearBit(PAD_SQUARE);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                clearBit(PAD_TRIANGLE);
            if (IsKeyDown(KEY_F))
                clearBit(PAD_CIRCLE);

            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                clearBit(PAD_L1);
            if (IsKeyDown(KEY_Q))
                clearBit(PAD_R2);
            if (IsKeyDown(KEY_E))
                clearBit(PAD_R1);
            if (IsKeyDown(KEY_V))
            {
                clearBit(PAD_L3);
                clearBit(PAD_R3);
            }
        }
        else
        {
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
                clearBit(PAD_UP);
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
                clearBit(PAD_DOWN);
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
                clearBit(PAD_LEFT);
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
                clearBit(PAD_RIGHT);
            if (IsKeyDown(KEY_X) || IsKeyDown(KEY_SPACE))
                clearBit(PAD_CROSS);
            if (IsKeyDown(KEY_C) || IsKeyDown(KEY_ESCAPE))
                clearBit(PAD_CIRCLE);
            if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_KP_0))
                clearBit(PAD_SQUARE);
            if (IsKeyDown(KEY_V) || IsKeyDown(KEY_KP_1))
                clearBit(PAD_TRIANGLE);
            if (IsKeyDown(KEY_Q))
                clearBit(PAD_L1);
            if (IsKeyDown(KEY_E))
                clearBit(PAD_R1);
            if (IsKeyDown(KEY_LEFT_SHIFT))
                clearBit(PAD_L2);
            if (IsKeyDown(KEY_RIGHT_SHIFT))
                clearBit(PAD_R2);
        }

        if (IsKeyDown(KEY_ENTER))
            clearBit(PAD_START);
        if (IsKeyDown(KEY_TAB))
            clearBit(PAD_SELECT);
    }

    data[2] = static_cast<uint8_t>(btns & 0xFF);
    data[3] = static_cast<uint8_t>(btns >> 8);

    if (kGamepad != m_activeGamepad)
    {
        m_activeGamepad = kGamepad;
        applyRumble(false); // the new gamepad takes over the current actuator state
    }
    else
        applyRumble(true);
    return true;
}

void PSPadBackend::setActuators(int port, bool small, uint8_t large)
{
    if (port != 0 || (small == m_small && large == m_large))
        return;
    m_small = small;
    m_large = large;
    applyRumble(false);
}

// refresh = periodic call from readState: only backends whose rumble times out need it resent.
void PSPadBackend::applyRumble(bool refresh)
{
#ifdef _WIN32
    // raylib's GLFW backend has no vibration: XInput and Sony HID pads directly. Both keep the motors running until changed.
    if (refresh)
        return;
    ps2PadWindowsRumble(m_large, m_small);
#else
    // Other platforms (SDL, Switch): raylib's rumble, which stops after at most 2 s, so it is resent every second.
    if (m_activeGamepad < 0 || !IsWindowReady())
        return;
    const bool on = m_small || m_large;
    const double now = GetTime();
    if (refresh && (!on || now - m_rumbleSentAt < 1.0))
        return;
    m_rumbleSentAt = now;
    SetGamepadVibration(m_activeGamepad, m_large / 255.0f, m_small ? 1.0f : 0.0f, on ? 2.0f : 0.1f); // zero motors with any duration stop it
#endif
}

// GOW-Port: rótulos de los iconos de botones (gow_iconos.cpp). Para una acción ("cross", "l1", "up", "li_arriba"...)
// devuelve hasta max códigos asignados en el teclado: los de TOBIICHI_TECLAS o, sin la variable, los del esquema fijo
// (códigos de raylib/GLFW y 1000 + botón para el ratón). Devuelve cuántos ha escrito.
int tobiichiCodigosAccion(const char *accion, int *codigos, int max)
{
    size_t a = NumAcciones;
    for (size_t i = 0; i < NumAcciones; ++i)
        if (std::strcmp(kNombresAccion[i], accion) == 0)
            a = i;
    if (a == NumAcciones || max <= 0)
        return 0;
    const MapaTeclas &m = mapaTeclas();
    int n = 0;
    if (m.activo)
    {
        for (const int c : m.codigos[a])
            if (n < max)
                codigos[n++] = c;
        return n;
    }
    static const bool dmc5 = [] {
        const char *val = std::getenv("TOBIICHI_DMC5_CONTROLS");
        return val == nullptr || std::strcmp(val, "0") != 0;
    }();
    // Igual que la rama de teclado de PSPadBackend::readState y gowPad2Read (WASD, Ctrl + WASD).
    int c = -1;
    switch (a)
    {
    case AccArriba: c = KEY_UP; break;
    case AccAbajo: c = KEY_DOWN; break;
    case AccIzquierda: c = KEY_LEFT; break;
    case AccDerecha: c = KEY_RIGHT; break;
    case AccCruz: c = dmc5 ? KEY_SPACE : KEY_X; break;
    case AccCirculo: c = dmc5 ? KEY_F : KEY_C; break;
    case AccCuadrado: c = dmc5 ? 1000 + MOUSE_BUTTON_LEFT : KEY_Z; break;
    case AccTriangulo: c = dmc5 ? 1000 + MOUSE_BUTTON_RIGHT : KEY_V; break;
    case AccL1: c = dmc5 ? KEY_LEFT_SHIFT : KEY_Q; break;
    case AccR1: c = KEY_E; break;
    case AccL2: c = dmc5 ? -1 : KEY_LEFT_SHIFT; break;
    case AccR2: c = dmc5 ? KEY_Q : KEY_RIGHT_SHIFT; break;
    case AccL3:
    case AccR3:
    case AccFuria: c = dmc5 ? KEY_V : -1; break;
    case AccStart: c = KEY_ENTER; break;
    case AccSelect: c = KEY_TAB; break;
    case AccLiArriba: c = KEY_W; break;
    case AccLiAbajo: c = KEY_S; break;
    case AccLiIzq: c = KEY_A; break;
    case AccLiDer: c = KEY_D; break;
    case AccLdMod: c = KEY_LEFT_CONTROL; break;
    default: break;
    }
    if (c >= 0)
        codigos[n++] = c;
    return n;
}

// GOW-Port: botón del mando (GAMEPAD_BUTTON_* de raylib) que da cada botón del PS2 con el esquema activo (DMC5 por
// defecto, TOBIICHI_DMC5_CONTROLS=0 el clásico). -1 si ninguno.
int tobiichiBotonMandoAccion(const char *accion)
{
    static const bool dmc5 = [] {
        const char *val = std::getenv("TOBIICHI_DMC5_CONTROLS");
        return val == nullptr || std::strcmp(val, "0") != 0;
    }();
    struct Par
    {
        const char *accion;
        int dmc5, clasico;
    };
    static const Par kPares[] = {
        {"cross", GAMEPAD_BUTTON_RIGHT_FACE_DOWN, GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
        {"circle", GAMEPAD_BUTTON_RIGHT_FACE_LEFT, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
        {"square", GAMEPAD_BUTTON_RIGHT_FACE_UP, GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
        {"triangle", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, GAMEPAD_BUTTON_RIGHT_FACE_UP},
        {"l1", GAMEPAD_BUTTON_LEFT_TRIGGER_1, GAMEPAD_BUTTON_LEFT_TRIGGER_1},
        {"r1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
        {"l2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2, GAMEPAD_BUTTON_LEFT_TRIGGER_2},
        {"r2", GAMEPAD_BUTTON_LEFT_TRIGGER_2, GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
        {"l3", GAMEPAD_BUTTON_LEFT_THUMB, GAMEPAD_BUTTON_LEFT_THUMB},
        {"r3", GAMEPAD_BUTTON_RIGHT_THUMB, GAMEPAD_BUTTON_RIGHT_THUMB},
        {"start", GAMEPAD_BUTTON_MIDDLE_RIGHT, GAMEPAD_BUTTON_MIDDLE_RIGHT},
        {"select", GAMEPAD_BUTTON_MIDDLE_LEFT, GAMEPAD_BUTTON_MIDDLE_LEFT},
        {"up", GAMEPAD_BUTTON_LEFT_FACE_UP, GAMEPAD_BUTTON_LEFT_FACE_UP},
        {"down", GAMEPAD_BUTTON_LEFT_FACE_DOWN, GAMEPAD_BUTTON_LEFT_FACE_DOWN},
        {"left", GAMEPAD_BUTTON_LEFT_FACE_LEFT, GAMEPAD_BUTTON_LEFT_FACE_LEFT},
        {"right", GAMEPAD_BUTTON_LEFT_FACE_RIGHT, GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
    };
    for (const Par &p : kPares)
        if (std::strcmp(p.accion, accion) == 0)
            return dmc5 ? p.dmc5 : p.clasico;
    return -1;
}
