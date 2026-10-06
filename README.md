# Tobiichi Port — God of War PS2 PC Port Projesi

Bu repo, **God of War (SCUS-97399)** oyununun PS2'den PC'ye statik yeniden derleme (static recompilation) yöntemiyle taşınması sürecini içermektedir.

## Proje Yapısı

```
Origami Tobiichi/
├── PS2Recomp/              # PS2Recomp framework (ran-j/PS2Recomp fork)
│   └── ps2xRuntime/
│       └── src/lib/
│           └── game_overrides.cpp  ← GoW'a özgü tüm hook'lar buradadır
├── god_of_war.toml         # Recompiler konfigürasyonu
├── GODOFWAR.TOC            # Oyun içerik tablosu
├── *.IRX                   # IOP modül dosyaları (PlayStation 2 I/O işlemcisi)
└── SYSTEM.CNF              # PlayStation 2 sistem yapılandırması
```

## Nasıl Çalışır?

1. God of War ELF dosyası (`SCUS_973.99`) statik olarak MIPS → C++ olarak derlenir
2. `ps2xRuntime`, PS2 kernel/IOP/GS donanımını HLE (High-Level Emulation) ile taklit eder
3. `game_overrides.cpp` içindeki hook'lar oyuna özgü donanım senkronizasyonlarını bypass eder

## Kurulum

### Gereksinimler
- CMake 3.20+
- GCC/Clang (C++20)
- Raylib

### Derleme
```bash
cd PS2Recomp
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### Çalıştırma
```bash
./build/ps2xRuntime/ps2EntryRunner <SCUS_973.99 yolu> --window
```

> **Not:** `SCUS_973.99` ve `PART1.PAK` telif hakkına tabi oyun dosyaları olup bu repoya dahil edilmemiştir.

## Durum

- [x] ELF analizi ve recompile
- [x] Temel kernel (thread, semaphore)
- [x] GS (Graphics Synthesizer) frame output
- [x] IOP senkronizasyon stub'ları
- [x] SCEA logo ekranı görüntüleniyor
- [ ] Ana oyun thread'i aktif hale getirilmesi
- [ ] Main menu (Title Screen)
- [ ] Oynanabilir seviye

## Katkıda Bulunma

Bu proje aktif geliştirme aşamasındadır. Katkıda bulunmak için fork'layıp PR açabilirsiniz.
