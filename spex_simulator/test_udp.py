import socket

IP = "127.0.0.1"
PORT = 8000

messages = [
    b"\x01\x00\x00\x00\x08\x11\x22\x33\x44\x55\x66\x77\x88",
    b"\x01\x00\x00\x00\x07\x11\x22\x33\x44\x55\x66\x77\x88",
    b"\x01\x00\x00\x00\x08\x11\x22\x33\x44\x55\x66\x77\x88\x99",
]

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# sock.bind((IP, PORT))
#
# while True:
#     data, addr = sock.recvfrom(1024)  # Buffer size is 1024 bytes
#
#     id = int.from_bytes(data[:4])
#
#     len = (data[4])
#
#     msg_data = data[5:]
#
#     print(f"Received message: ID {id} LEN {len} DATA {msg_data}")

for m in messages:
    sock.sendto(m, (IP, PORT))



