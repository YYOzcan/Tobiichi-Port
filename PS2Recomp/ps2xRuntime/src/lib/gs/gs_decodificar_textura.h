// GOW-Port: decodificación de una textura del GS a RGBA8 en la CPU (diagnóstico y sustitución de iconos).
// Misma lógica que el sombreador de decodificación de gs_hw_render.cpp: CLUT (CSM1/CSM2, CSA) y TEXA.
#pragma once

#include "runtime/gs/gs_backend.h"
#include "runtime/gs/gs_backend_state.h"
#include "runtime/gs/gs_types.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <vector>

namespace GSDecodificar
{
    inline bool cuatroBits(uint32_t psm) { return psm == 0x14u || psm == 0x24u || psm == 0x2Cu; }
    inline bool ochoBits(uint32_t psm) { return psm == 0x13u || psm == 0x1Bu; }
    inline bool indexado(uint32_t psm) { return cuatroBits(psm) || ochoBits(psm); }

    inline uint32_t rgba5551(uint32_t v)
    {
        const uint32_t r = (v & 0x1Fu) << 3, g = ((v >> 5) & 0x1Fu) << 3, b = ((v >> 10) & 0x1Fu) << 3;
        return r | (g << 8) | (b << 16) | ((v & 0x8000u) ? 0x80000000u : 0u);
    }

    inline uint32_t texa(uint32_t psm, uint32_t texel, const GSTexaReg &t)
    {
        if (psm == 0u)
            return texel;
        const bool rgbCero = (texel & 0x00FFFFFFu) == 0u;
        uint32_t a = texel >> 24;
        if (psm == 1u)
            a = (t.aem && rgbCero) ? 0u : t.ta0;
        else if (psm == 2u || psm == 10u)
            a = (a & 0x80u) ? t.ta1 : ((t.aem && rgbCero) ? 0u : t.ta0);
        return (texel & 0x00FFFFFFu) | (a << 24);
    }

    // Posición en el búfer de CLUT (512 medias palabras) de un índice de textura.
    inline uint32_t posicionClut(uint32_t indice, const GSTex0Reg &t)
    {
        const bool dieciseis = t.cpsm == 2u || t.cpsm == 10u;
        const uint32_t base = (t.csa & (dieciseis ? 0x1Fu : 0x0Fu)) << 4;
        const uint32_t fuente = cuatroBits(t.psm) ? (indice & 0x0Fu) : indice;
        uint32_t i = (base + fuente) & (dieciseis ? 0x1FFu : 0x0FFu);
        if (!dieciseis && t.csm == 0u && ochoBits(t.psm))
            i = std::min((fuente & 0xF0u) + base, 240u) + (fuente & 0x0Fu);
        return i;
    }

    inline uint32_t deClut(uint32_t indice, const GSTex0Reg &t, const std::array<uint16_t, 512> &clut, const GSTexaReg &tx)
    {
        const uint32_t i = posicionClut(indice, t);
        if (t.cpsm == 0u || t.cpsm == 1u)
        {
            const uint32_t v = clut[i] | (uint32_t(clut[(i + 256u) & 511u]) << 16);
            return texa(t.cpsm, t.cpsm == 1u ? (v & 0x00FFFFFFu) : v, tx);
        }
        if (t.cpsm == 2u || t.cpsm == 10u)
            return texa(t.cpsm, rgba5551(clut[i]), tx);
        return 0xFFFF00FFu;
    }

    // Texel (x, y) de la textura en RGBA8 del GS (alfa 0x80 = opaco). vram: un backend que lea la memoria del GS.
    inline uint32_t texel(const GSRasterBackend &vram, const GSTex0Reg &t, const std::array<uint16_t, 512> &clut,
                          const GSTexaReg &tx, uint32_t x, uint32_t y)
    {
        const uint32_t crudo = vram.ReadVram(t.psm, t.tbp0, t.tbw, x, y);
        if (indexado(t.psm))
            return deClut(crudo, t, clut, tx);
        if (t.psm == 2u || t.psm == 10u)
            return texa(t.psm, rgba5551(crudo), tx);
        if (t.psm == 0u || t.psm == 1u)
            return texa(t.psm, crudo, tx);
        return 0xFFFF00FFu;
    }

    // Textura completa (hasta 1024 x 1024) en RGBA8 para PNG: alfa del GS duplicado; sin TCC, opaca.
    inline std::vector<uint32_t> imagen(const GSRasterBackend &vram, const GSTex0Reg &t, const std::array<uint16_t, 512> &clut,
                                        const GSTexaReg &tx, uint32_t &ancho, uint32_t &alto)
    {
        ancho = std::min(1u << t.tw, 1024u);
        alto = std::min(1u << t.th, 1024u);
        std::vector<uint32_t> px(size_t(ancho) * alto);
        for (uint32_t y = 0; y < alto; ++y)
            for (uint32_t x = 0; x < ancho; ++x)
            {
                const uint32_t c = texel(vram, t, clut, tx, x, y);
                const uint32_t a = t.tcc ? std::min<uint32_t>((c >> 24) * 2u, 255u) : 255u;
                px[size_t(y) * ancho + x] = (c & 0x00FFFFFFu) | (a << 24);
            }
        return px;
    }
}
