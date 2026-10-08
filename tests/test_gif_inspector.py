"""Regresiones del inspector con paquetes sintéticos, sin archivos del juego."""
import struct
import unittest

from tools.gs.inspeccionar_paquetes import inspeccionar


def tag(registros, nloop, formato=0):
    nr = len(registros) & 15
    return struct.pack('<QQ', nloop | (1 << 15) | (formato << 58) | (nr << 60),
                       sum(r << (4 * i) for i, r in enumerate(registros)))


class GifInspectorTests(unittest.TestCase):
    def test_packed_adc_y_xyz3(self):
        datos = tag([5, 13], 2)
        for adc in [0, 0, 1, 1]:
            datos += struct.pack('<QQ', 160 | (320 << 32), 12345 | (adc << 47))
        r = inspeccionar(datos)
        self.assertEqual((r['vertices'], r['vertices_con_kick'], r['vertices_sin_kick']), (4, 1, 3))
        self.assertEqual(r['limites_xyz'], [[160, 160], [320, 320], [12345, 12345]])

    def test_xyzf_fog_no_es_adc(self):
        datos = tag([4], 1) + struct.pack('<QQ', 16 | (32 << 32), (0xabcdef << 4) | (255 << 36))
        r = inspeccionar(datos)
        self.assertEqual(r['vertices_con_kick'], 1)
        self.assertEqual(r['limites_xyz'][2], [0xabcdef, 0xabcdef])

    def test_reglist_padding_y_siguiente_tag(self):
        valor = 16 | (32 << 16) | (123 << 32)
        datos = tag([5], 1, 1) + struct.pack('<QQ', valor, 0xffffffffffffffff)
        datos += tag([13], 1, 1) + struct.pack('<QQ', valor, 0)
        r = inspeccionar(datos)
        self.assertEqual((r['vertices'], r['vertices_con_kick']), (2, 1))
        self.assertEqual(r['limites_xyz'], [[16, 16], [32, 32], [123, 123]])

    def test_ad_usa_coordenadas_de_registro(self):
        datos = tag([14], 1) + struct.pack('<QQ', 16 | (32 << 16) | (456 << 32), 5)
        self.assertEqual(inspeccionar(datos)['limites_xyz'], [[16, 16], [32, 32], [456, 456]])

    def test_nreg_cero_significa_dieciséis(self):
        datos = tag([15] * 16, 1) + bytes(16 * 16)
        r = inspeccionar(datos)
        self.assertEqual(r['etiquetas'][0]['nreg'], 16)
        self.assertEqual(r['vertices'], 0)

    def test_image_y_tag_vacio(self):
        r = inspeccionar(tag([15], 2, 2) + bytes(32) + tag([5], 0))
        self.assertEqual(len(r['etiquetas']), 2)
        self.assertEqual(r['vertices'], 0)

    def test_pre_solo_se_aplica_en_packed(self):
        for formato in [0, 1, 2]:
            datos = bytearray(tag([15], 0, formato))
            bajo, = struct.unpack_from('<Q', datos)
            struct.pack_into('<Q', datos, 0, bajo | (1 << 46) | (4 << 47))
            self.assertEqual(inspeccionar(datos)['tipos_prim_con_pre'], {4: 1} if formato == 0 else {})

    def test_payloads_incompletos_y_formato_no_soportado(self):
        for datos in [bytes(15), tag([5], 1), tag([5], 1, 1) + bytes(8),
                      tag([15], 1, 2), tag([15], 0, 3)]:
            with self.subTest(datos=datos), self.assertRaises(ValueError):
                inspeccionar(datos)


if __name__ == '__main__':
    unittest.main()
