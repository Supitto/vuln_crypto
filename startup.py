import requests
import json
from Crypto.Cipher import AES
import base64
import random
import time

random.seed(int(time.time()))

with open('flag.txt', 'r') as f:
	msg_text = f.read()

msg_text = msg_text.zfill(64)
secret_key = str(random.getrandbits(256))[:32]

cipher = AES.new(secret_key,AES.MODE_ECB) # never use ECB in strong systems obviously
encoded = base64.b64encode(cipher.encrypt(msg_text))

with open('flag.enc','w') as f:
	f.write(encoded)
