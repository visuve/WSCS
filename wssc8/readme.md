# WSSC-8 - World's Shittiest Stream Cipher

- Processes eight bit character by character, hence the name
- The key is indexed based on bytes read modulus to the key size
- With the single character from the key, a bit is flipped within the byte being processed
