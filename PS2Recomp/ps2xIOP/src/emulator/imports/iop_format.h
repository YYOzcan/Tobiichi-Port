#pragma once

// GOW-Port: formateo estilo printf para sysclib sprintf/vsprintf y stdio printf del IOP.
// Antes, sprintf copiaba el formato literal: SMPD_IOP.IRX de God of War hace sprintf(buf, "%s.wad", nombre)
// para buscar sus recursos y acababa buscando "%S.WAD".

#include "../core/iop_memory.h"

#include <cstdint>
#include <cstdio>
#include <functional>
#include <string>

namespace ps2x::iop::detail
{
    // nextArg devuelve la siguiente palabra de 32 bits de la lista de argumentos variables
    // (o32: a1..a3 o a2..a3 y despues la pila desde sp+16; en vsprintf, la memoria apuntada por va_list).
    inline std::string formatGuestString(const IopMemory &memory, uint32_t formatAddress,
                                         const std::function<uint32_t()> &nextArg, size_t limit = 4096u)
    {
        const std::string format = memory.readString(formatAddress, limit);
        std::string out;
        out.reserve(format.size() + 32u);
        for (size_t i = 0; i < format.size(); ++i)
        {
            const char c = format[i];
            if (c != '%')
            {
                out += c;
                continue;
            }
            const size_t start = i++;
            if (i >= format.size())
            {
                out += '%';
                break;
            }
            if (format[i] == '%')
            {
                out += '%';
                continue;
            }

            std::string spec = "%";
            while (i < format.size() && (format[i] == '-' || format[i] == '+' || format[i] == ' ' ||
                                         format[i] == '#' || format[i] == '0'))
                spec += format[i++];
            if (i < format.size() && format[i] == '*')
            {
                spec += std::to_string(static_cast<int32_t>(nextArg()));
                ++i;
            }
            while (i < format.size() && format[i] >= '0' && format[i] <= '9')
                spec += format[i++];
            if (i < format.size() && format[i] == '.')
            {
                spec += format[i++];
                if (i < format.size() && format[i] == '*')
                {
                    spec += std::to_string(static_cast<int32_t>(nextArg()));
                    ++i;
                }
                while (i < format.size() && format[i] >= '0' && format[i] <= '9')
                    spec += format[i++];
            }
            int longCount = 0;
            while (i < format.size() && (format[i] == 'l' || format[i] == 'h' || format[i] == 'q' || format[i] == 'L'))
            {
                if (format[i] == 'l' || format[i] == 'q' || format[i] == 'L')
                    ++longCount;
                ++i;
            }
            if (i >= format.size())
            {
                out += format.substr(start);
                break;
            }

            const char conversion = format[i];
            char buffer[512];
            buffer[0] = '\0';
            switch (conversion)
            {
            case 'd':
            case 'i':
            {
                long long value = static_cast<int32_t>(nextArg());
                if (longCount >= 2)
                    value = static_cast<long long>((static_cast<uint64_t>(nextArg()) << 32) | static_cast<uint32_t>(value));
                std::snprintf(buffer, sizeof(buffer), (spec + "lld").c_str(), value);
                break;
            }
            case 'u':
            case 'x':
            case 'X':
            case 'o':
            {
                unsigned long long value = nextArg();
                if (longCount >= 2)
                    value |= static_cast<unsigned long long>(nextArg()) << 32;
                std::snprintf(buffer, sizeof(buffer), (spec + "ll" + conversion).c_str(), value);
                break;
            }
            case 'p':
                std::snprintf(buffer, sizeof(buffer), "0x%08x", nextArg());
                break;
            case 'c':
                std::snprintf(buffer, sizeof(buffer), (spec + "c").c_str(), static_cast<int>(nextArg() & 0xFFu));
                break;
            case 's':
            {
                const uint32_t address = nextArg();
                const std::string text = address ? memory.readString(address, limit) : std::string("(null)");
                std::snprintf(buffer, sizeof(buffer), (spec + "s").c_str(), text.c_str());
                break;
            }
            default:
                // Conversion desconocida: se deja tal cual.
                out += format.substr(start, i - start + 1u);
                continue;
            }
            out += buffer;
        }
        return out;
    }
}
