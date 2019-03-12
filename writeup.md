#Writeup Easy Crypto

Esse chall acabou saindo muito mais facil de oque esperado.

A solução proposta originalmente envolve realizar DoS no serviço, marcar a 
epoch entre o serviço cair e e ele levantar. Desta forma reduzimos muito o
espaço de busca. Mas no final das contas não percebi que epoch já é um
espaço de busca pequeno o suficientemente pequeno. Bom, vamos ao chall.

Essa era a descrição provida:

O challenge mais simples de todas as epochs. Há um serviço TCP servindo uma flag encriptada em 67.205.131.109 9998.
É só se conectar -> pegar a flag -> decryptar a flag -> profit. 
Como ninguém aqui é adivinho, o código fonte está em https://github.com/Supitto/vuln_crypto.

Se analizarmos o codigo em https://github.com/Supitto/vuln_crypto veremos que o serviço em C esta
muuuuito mal escrito, e isso é de proposito. Como a intenção é dar DoS no serviço, também foi
colocado um killswitch que mata serviço após 2000 requisições. 

O chall poderia ser resolvido da seguinte forma:

```python
import socket
import time
from Crypto.Cipher import AES
import base64

inicio = int(time.time())

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
for i in range(2300):
  s.connect(('67.205.131.109', 9998))
  flag = s.recv(1024)
  s.close()
  print i

fim = int(time.time())

decoded = base64.b64decode(flag)

for key in range(inicio, fim):
  try:
    cipher = AES.new(key,AES.MODE_ECB)
    print(cipher.decrypt(decoded))
  except e:
    pass
```


