# WSBC-512 - World's Shittiest Block Cipher

- Processes data in 512 bit blocks
- XORs the first block with given PSK
	- If the PSK is over 64 bytes, the remainder will be ignored
- XORs the next block with previous block XOR result
- Decryption is vice versa
