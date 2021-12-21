#include "wssc8.hpp"
#include <bitset>
#include <cstring>

namespace wscs
{
	void flip_bits(void* data, size_t length, const std::array<uint8_t, wssc8::bytes>& key)
	{
		uint8_t* iter = reinterpret_cast<uint8_t*>(data);

		for (size_t i = 0; i < length; ++i)
		{
			uint8_t index_to_flip = key[i % key.size()];
			iter[i] ^= 1u << index_to_flip;
		}
	}

	void flip_bits(std::istream& input, std::ostream& output, const std::array<uint8_t, wssc8::bytes>& key)
	{
		char buffer = '\0';

		for (uint64_t bytes_read = 0; input.get(buffer); ++bytes_read)
		{
			uint8_t index_to_flip = key[bytes_read % key.size()];
			buffer ^= 1u << index_to_flip;
			output << buffer;
		}
	}

	wssc8::wssc8() :
		_key({})
	{
	}

	void wssc8::initialize(const void* key, size_t length)
	{
		if (!key)
		{
			throw std::invalid_argument("data is null!");
		}

		std::memcpy(_key.data(), key, std::min(length, _key.size()));
	}

	void wssc8::encrypt(void* data, size_t length)
	{
		return flip_bits(data, length, _key);
	}

	void wssc8::encrypt(std::istream& input, std::ostream& output)
	{
		return flip_bits(input, output, _key);
	}

	void wssc8::decrypt(void* data, size_t length)
	{
		return flip_bits(data, length, _key);
	}

	void wssc8::decrypt(std::istream& input, std::ostream& output)
	{
		return flip_bits(input, output, _key);
	}
}
