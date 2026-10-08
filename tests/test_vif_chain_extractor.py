"""Pruebas sintéticas de selección DMA; no usan archivos ni paquetes del juego."""
import importlib.util
from pathlib import Path
import struct
import unittest
from unittest.mock import patch


RUTA = Path(__file__).resolve().parents[1] / 'tools' / 'render' / 'extraer_cadena_vif.py'
SPEC = importlib.util.spec_from_file_location('extraer_cadena_vif', RUTA)
extractor = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(extractor)


class SeleccionCadenaTests(unittest.TestCase):
    def setUp(self):
        self.ee = bytearray(0x400)
        self.cabeceras = patch.object(extractor, 'INICIOS_CUADRO', (0x100, 0x200))
        self.cabeceras.start()
        self.addCleanup(self.cabeceras.stop)

    def etiqueta(self, direccion, tipo=7, destino=0, qwc=0, tte=0):
        struct.pack_into('<QQ', self.ee, direccion,
                         qwc | (tipo << 28) | (destino << 32), tte)

    def test_unica_cabecera_valida_aunque_no_sea_la_primera(self):
        self.etiqueta(0x200)
        self.assertEqual(extractor.seleccionar_cadena(self.ee), (0x200, 0x200, 1))

    def test_ambiguedad_indica_ambos_candidatos_y_opcion_explicita(self):
        self.etiqueta(0x100)
        self.etiqueta(0x200)
        with self.assertRaises(ValueError) as error:
            extractor.seleccionar_cadena(self.ee)
        texto = str(error.exception)
        self.assertIn('0x100 -> END 0x100', texto)
        self.assertIn('0x200 -> END 0x200', texto)
        self.assertIn('--inicio', texto)
        self.assertIn('no demuestra', texto)

    def test_eleccion_explicita_resuelve_ambiguedad(self):
        self.etiqueta(0x100)
        self.etiqueta(0x200)
        self.assertEqual(extractor.seleccionar_cadena(self.ee, inicio=0x200), (0x200, 0x200, 1))

    def test_eleccion_explicita_fuera_de_cabeceras_conocidas(self):
        self.etiqueta(0x300)
        self.assertEqual(extractor.seleccionar_cadena(self.ee, inicio=0x300), (0x300, 0x300, 1))

    def test_ninguna_cabecera_valida(self):
        with self.assertRaisesRegex(ValueError, 'Ninguna cabecera'):
            extractor.seleccionar_cadena(self.ee)

    def test_cabecera_explicita_invalida_no_recurre_a_otra(self):
        self.etiqueta(0x100)
        with self.assertRaisesRegex(ValueError, '--inicio 0x200'):
            extractor.seleccionar_cadena(self.ee, inicio=0x200)

    def test_end_del_savestate_selecciona_unica_cadena(self):
        self.etiqueta(0x100)
        self.etiqueta(0x200)
        self.assertEqual(extractor.seleccionar_cadena(self.ee, fin=0x200), (0x200, 0x200, 1))
        with self.assertRaisesRegex(ValueError, 'END 0x300'):
            extractor.seleccionar_cadena(self.ee, fin=0x300)

    def test_end_del_savestate_tambien_puede_ser_ambiguo(self):
        self.etiqueta(0x100, tipo=2, destino=0x300)
        self.etiqueta(0x200, tipo=2, destino=0x300)
        self.etiqueta(0x300)
        with self.assertRaisesRegex(ValueError, 'Selección ambigua'):
            extractor.seleccionar_cadena(self.ee, fin=0x300)
        self.assertEqual(extractor.seleccionar_cadena(self.ee, inicio=0x200, fin=0x300),
                         (0x200, 0x300, 2))

    def test_inicio_explicito_respeta_end_del_savestate(self):
        self.etiqueta(0x100)
        self.etiqueta(0x200)
        with self.assertRaisesRegex(ValueError, 'END 0x200'):
            extractor.seleccionar_cadena(self.ee, inicio=0x100, fin=0x200)

    def test_etiquetas_cargas_y_ciclos_invalidos_se_rechazan(self):
        self.etiqueta(0x3F0, qwc=1)
        self.etiqueta(0x100, tipo=2, destino=0x100)
        for inicio in (-16, 0x401, 0x3F8, 0x3F0):
            with self.subTest(inicio=inicio):
                self.assertIsNone(extractor.recorrer(self.ee, inicio)[0])
                with self.assertRaises(ValueError):
                    extractor.aplanar(self.ee, inicio)
        self.assertEqual(extractor.recorrer(self.ee, 0x100, limite=3), (None, 3))

    def test_aplanar_conserva_tte_ref_call_y_ret(self):
        # CALL -> REF -> RET -> END, con las cargas y TTE distintos en cada etiqueta.
        self.etiqueta(0x100, tipo=5, destino=0x200, qwc=1, tte=0x1111)
        self.ee[0x110:0x120] = b'A' * 16
        self.etiqueta(0x120, tte=0x4444)
        self.etiqueta(0x200, tipo=3, destino=0x300, qwc=1, tte=0x2222)
        self.ee[0x300:0x310] = b'B' * 16
        self.etiqueta(0x210, tipo=6, qwc=1, tte=0x3333)
        self.ee[0x220:0x230] = b'C' * 16
        self.assertEqual(extractor.seleccionar_cadena(self.ee, inicio=0x100), (0x100, 0x120, 4))
        esperado = (struct.pack('<Q', 0x1111) + b'A' * 16 +
                    struct.pack('<Q', 0x2222) + b'B' * 16 +
                    struct.pack('<Q', 0x3333) + b'C' * 16 + struct.pack('<Q', 0x4444))
        self.assertEqual(extractor.aplanar(self.ee, 0x100), esperado)


if __name__ == '__main__':
    unittest.main()
