# WSHF-2 - World's Shittiest Hash Function

- Sums all bytes together in a uint16_t
	- The uint16_t will flip over with large data, but we do not care
- Takes modulus 2 of the sum, hence the "2" name
	- The return value is effectively 0 or 1...
