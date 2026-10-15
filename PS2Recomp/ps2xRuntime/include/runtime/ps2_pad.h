#ifndef PS2_PAD_H
#define PS2_PAD_H

#include <cstddef>
#include <cstdint>

class PSPadBackend
{
public:
    PSPadBackend() = default;
    ~PSPadBackend() = default;

    bool readState(int port, int slot, uint8_t *data, size_t size);

    // GOW-Port: DualShock 2 actuators (libvib profile 0x03): small motor on/off, large motor 0-255. Held until the
    // next call, as on the real pad; drives the active host gamepad's rumble.
    void setActuators(int port, bool small, uint8_t large);

private:
    void applyRumble(bool refresh);

    int m_activeGamepad = -1; // host gamepad the input comes from (-1 = keyboard)
    bool m_small = false;
    uint8_t m_large = 0;
    double m_rumbleSentAt = 0.0;
};

#endif
