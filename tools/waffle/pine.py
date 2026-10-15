"""Read EE memory from a running PCSX2 through PINE (enable EmuCore/EnablePINE, slot 28011).

usage: python -I tools/pine.py ADDR LEN [ADDR LEN ...]      hex dump (EE virtual addresses, hex)
       python -I tools/pine.py --status
IOP RAM is visible from the EE side at 0xBC000000 + iop_address.
"""
import socket
import struct
import sys

PORT = 28011
MSG_READ8, MSG_READ32, MSG_VERSION, MSG_STATUS = 0, 2, 8, 15


class Pine:
    def __init__(self, port=PORT):
        self.sock = socket.create_connection(('127.0.0.1', port), timeout=5)

    def _call(self, opcode, payload=b''):
        self.sock.sendall(struct.pack('<IB', 5 + len(payload), opcode) + payload)
        head = self._recv(5)
        size, result = struct.unpack('<IB', head)
        body = self._recv(size - 5)
        if result != 0:
            raise RuntimeError(f'PINE opcode {opcode} failed')
        return body

    def _recv(self, n):
        data = b''
        while len(data) < n:
            chunk = self.sock.recv(n - len(data))
            if not chunk:
                raise ConnectionError('PINE closed')
            data += chunk
        return data

    def read32(self, address):
        return struct.unpack('<I', self._call(MSG_READ32, struct.pack('<I', address)))[0]

    def read(self, address, length):
        words = [self.read32(address + i) for i in range(0, (length + 3) & ~3, 4)]
        return struct.pack(f'<{len(words)}I', *words)[:length]

    def status(self):
        return ['running', 'paused', 'shutdown'][struct.unpack('<I', self._call(MSG_STATUS))[0]]


def main():
    pine = Pine()
    if sys.argv[1:] == ['--status']:
        print(pine.status())
        return
    args = sys.argv[1:]
    for address, length in zip(args[0::2], args[1::2]):
        address, length = int(address, 16), int(length, 16)
        data = pine.read(address, length)
        for off in range(0, len(data), 16):
            row = data[off:off + 16]
            words = ' '.join(f'{w:08X}' for w in struct.unpack(f'<{len(row) // 4}I', row))
            text = ''.join(chr(b) if 32 <= b < 127 else '.' for b in row)
            print(f'{address + off:08X}: {words}  {text}')


if __name__ == '__main__':
    main()
