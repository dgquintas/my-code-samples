from Crypto.PublicKey import RSA
from Crypto.Cipher import AES
from Crypto.Hash import SHA
from Crypto.Util.randpool import RandomPool

AES_KEY_LENGTH = 32
RSA_KEY_LENGTH = 512

randomPool = RandomPool()
rsaKeyPair = RSA.generate(RSA_KEY_LENGTH, randomPool.get_bytes)

#def SimCrypt(simCipher, plaintext):
#    paddingBytes = simCipher.block_size - (len(plaintext) % simCipher.block_size)
#    padding = ('\x00' * (paddingBytes-1)) + chr(paddingBytes)
#    plaintext += padding
#    return simCipher.encrypt(plaintext)
#
#def SimDecrypt(simCipher, crypttext):
#    paddedClearText = simCipher.decrypt(crypttext)
#    paddingBytes = paddedClearText[-1]
#    clearText = paddedClearText[:-ord(paddingBytes)]
#    return clearText




def PubCrypt(pubKey, plaintext):
  aesKey = randomPool.get_bytes(AES_KEY_LENGTH)
  aesIV =  randomPool.get_bytes(AES.block_size)
  aes = AES.new(key=aesKey, mode=AES.MODE_CFB, IV=aesIV)

  #plaintext can be an iterator/generator (e_1..e_n)
  #if so, we'll have (ct_1..ct_n) pieces of ciphertext 
  #that can be written to disk as soon as they become
  #available.
  #What's then returned by the public encryption 
  #is the (publickey'd) encrypted symetric key/IV pair
  #and some kind of *pointer* to its (symetric) cyphertext.
  #Such pointer can very well be the filename itself

  #Each user has it's own "FAT":
  # user visible filename -> (sym-encrypt'd ct file, key/IV)
  # persistence with "shelve" module?
  ct = aes.encrypt(plaintext)
  return (ct, pubKey.encrypt(aesIV + aesKey, None))

def PubSign(privKey, plaintext):
  hash = SHA.new(plaintext).digest()
  signature = privKey.sign(hash, None)
  return signature

def PubDecrypt(privKey, cyphertext):
  aesIVPlusKey = privKey.decrypt(cyphertext[1])
  aesIV = aesIVPlusKey[:AES.block_size]
  aesKey = aesIVPlusKey[AES.block_size:]
  aes = AES.new(key=aesKey, mode=AES.MODE_CFB, IV=aesIV)

  decryptedtext = aes.decrypt(cyphertext[0])
  return decryptedtext

def PubVerify(pubKey, message, signature):
  hash = SHA.new(message).digest()
  return rsaKeyPair.verify(hash, signature)



########################################


import timeit

ITERS = 100

if __name__ == "__main__":
  plaintext = "A"*1024
  print timeit.Timer('PubCrypt(rsaKeyPair.publickey(), plaintext)', 'from __main__ import PubCrypt, rsaKeyPair, plaintext').timeit(ITERS) / ITERS
  ct = PubCrypt(rsaKeyPair.publickey(), plaintext)
  sign = PubSign(rsaKeyPair, plaintext)
  print timeit.Timer('PubSign(rsaKeyPair, plaintext)', 'from __main__ import PubSign, rsaKeyPair, plaintext').timeit(ITERS) / ITERS

  decryptedtext = PubDecrypt(rsaKeyPair, ct)
  print "Decryption successful?", plaintext == decryptedtext and "Yes!" or "No!"
  print "Correct signature?", PubVerify(rsaKeyPair.publickey(), decryptedtext, sign) == True and "Yes!" or "No!"


  print rsaKeyPair.publickey().__getstate__()
