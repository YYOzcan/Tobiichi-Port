"""Controles CLI con la captura sintética del test C++; no usar datos del juego."""
import pathlib
import struct
import subprocess
import sys
import tempfile


def main():
    if len(sys.argv) != 3:
        raise SystemExit("Uso: gs_replay_cli_test.py ejecutable captura_sintetica.bin")
    executable = pathlib.Path(sys.argv[1]).resolve()
    sample = pathlib.Path(sys.argv[2]).resolve()
    with tempfile.TemporaryDirectory(prefix="gow_gs_cli_") as temporary:
        output = pathlib.Path(temporary)

        def run(arguments, expected, capture=sample):
            result = subprocess.run(
                [str(executable), str(capture), "cpu", *arguments, str(output)],
                capture_output=True, text=True, encoding="utf-8", errors="replace", timeout=60,
            )
            if result.returncode != expected:
                raise AssertionError((arguments, result.returncode, result.stdout, result.stderr))
            return result.stdout + result.stderr

        invalid = [
            ["--checkpoints-sync"],
            ["--checkpoints-sync", "--repeticiones", "1"],
            ["--checkpoints-sync", "--checkpoints-sync", "--repeticiones", "2"],
            ["--checkpoints-sync", "--repeticiones", "0"],
            ["--checkpoints-sync", "--repeticiones", "-2"],
            ["--hasta-registro"],
            ["--hasta-registro", "0"],
            ["--hasta-registro", "-1"],
            ["--hasta-registro", "abc"],
            ["--hasta-registro", "4294967296"],
            ["--hasta-registro", "1", "--hasta-registro", "2"],
        ]
        for arguments in invalid:
            assert "Uso:" in run(arguments, 2)
        for arguments in [
            ["--checkpoints-sync", "--repeticiones", "3"],
            ["--repeticiones", "2", "--checkpoints-sync", "--lockstep"],
        ]:
            text = run(arguments, 0)
            assert "Controles sincronizados: previos=1 actuales=1 distintos=0" in text
            assert "Primer control variable:" not in text
            assert "CPU vs captura final: bytes=0" in text

        # Añadir Flush no modifica el End CPU. El exceso debe rechazarse ANTES de
        # hacer miles de readbacks: probar también el límite en una entrada válida.
        data = sample.read_bytes()
        assert data[:8] == b"GOWGSR1\0"
        position = 24
        end_offset = None
        operations = []
        while position < len(data):
            start = position
            operation, size = struct.unpack_from("<BI", data, position)
            position += 5 + size
            assert position <= len(data)
            operations.append(operation)
            if operation == 16:
                end_offset = start
        assert position == len(data) and end_offset is not None
        synchronized = output / "controles_intermedios.bin"
        # GSSyncReason tiene ABI uint8_t; DebugReadback=3. Ambos comandos son
        # inocuos para la VRAM CPU, pero deben registrarse además del End.
        synchronized.write_bytes(data[:end_offset] + struct.pack("<BI", 13, 0) +
                                 struct.pack("<BIB", 14, 1, 3) + data[end_offset:])
        text = run(["--checkpoints-sync", "--repeticiones", "2"], 0, synchronized)
        assert "Controles sincronizados: previos=3 actuales=3 distintos=0" in text
        assert "CPU vs captura final: bytes=0" in text
        # Initial=0; los dos comandos añadidos delimitan un prefijo que se
        # compara con CPU, sin presentarlo como validación del End original.
        before_end = len(operations) - 2
        for stop in [before_end + 1, before_end + 2]:
            text = run(["--hasta-registro", str(stop), "--checkpoints-sync", "--repeticiones", "2"],
                       0, synchronized)
            assert f"Prefijo hasta registro={stop}" in text
            assert "CPU vs cpu prefijo: bytes=0" in text
            assert "CPU vs captura final:" not in text
            assert "Controles sincronizados: previos=" in text and "distintos=0" in text
        text = run(["--hasta-registro", str(before_end + 3)], 0, synchronized)
        assert "CPU vs captura final: bytes=0" in text
        text = run(["--hasta-registro", str(before_end + 4)], 2, synchronized)
        assert "excede la captura" in text
        for operation in [2, 6]:  # Submit y TEXFLUSH no son fronteras admitidas.
            assert operation in operations
            stop = operations.index(operation)
            text = run(["--hasta-registro", str(stop)], 2)
            assert "requiere Flush, Sync, Present o End" in text

        bad_end = output / "end_distinto.bin"
        cut_data = synchronized.read_bytes()
        bad_end.write_bytes(cut_data[:-1] + bytes([cut_data[-1] ^ 1]))
        assert "CPU vs captura final: bytes=1" in run([], 3, bad_end)
        text = run(["--hasta-registro", str(before_end + 1)], 0, bad_end)
        assert "CPU vs captura final:" not in text
        oversized = output / "demasiados_controles.bin"
        oversized.write_bytes(data[:end_offset] + struct.pack("<BI", 13, 0) * 4096 + data[end_offset:])
        text = run(["--checkpoints-sync", "--repeticiones", "2"], 2, oversized)
        assert "4096" in text
        assert "CPU vs captura final:" not in text
        text = run(["--hasta-registro", str(before_end + 1), "--checkpoints-sync", "--repeticiones", "2"],
                   0, oversized)
        assert "CPU vs cpu prefijo: bytes=0" in text and "distintos=0" in text
    print("CLI GS: 11 argumentos inválidos, controles CPU completos/prefijos y límites previos al replay: OK")


if __name__ == "__main__":
    main()
