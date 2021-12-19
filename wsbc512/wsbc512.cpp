#include "wsbc512.hpp"
#include <cstring>

namespace wscs
{
	void update(const void* data, size_t length, std::array<uint8_t, wsbc512::bytes>& key)
	{
		std::memset(key.data(), 0, key.size());
		std::memcpy(key.data(), data, std::min(length, key.size()));
	}

	void xorshift(void* data, size_t length, std::array<uint8_t, wsbc512::bytes> key)
	{
		if (!data)
		{
			throw std::invalid_argument("data is null!");
		}

		uint8_t* iter = reinterpret_cast<uint8_t*>(data);

		for (size_t i = 0; i < std::min(length, key.size()); ++i)
		{
			iter[i] ^= key[i];
		}
	}

	wsbc512::wsbc512() :
		_key({})
	{
	}

	void wsbc512::initialize(const void* key, size_t length)
	{
		if (!key)
		{
			throw std::invalid_argument("data is null!");
		}

		update(key, length, _key);
	}

	void wsbc512::encrypt(void* data, size_t length) 
	{
		xorshift(data, length, _key);
		update(data, length, _key);

		if (length > bytes)
		{
			size_t remainder = length - bytes;
			encrypt(static_cast<uint8_t*>(data) + remainder, remainder);
		}
	}

	void wsbc512::encrypt(std::istream& input, std::ostream& output)
	{
		char buffer[bytes] = {};

		while (input.read(buffer, bytes))
		{
			std::streamsize bytes_read = input.gcount();

			if (bytes_read <= 0)
			{
				break;
			}

			encrypt(buffer, bytes_read);
			output.write(buffer, bytes_read);
		}
	}

	void wsbc512::decrypt(void* data, size_t length)
	{
		std::array<uint8_t, bytes> key = _key;

		update(data, length, _key);
		xorshift(data, length, key);

		if (length > bytes)
		{
			size_t remainder = length - bytes;
			decrypt(static_cast<uint8_t*>(data) + remainder, remainder);
		}
	}

	void wsbc512::decrypt(std::istream& input, std::ostream& output)
	{
		char buffer[bytes] = {};

		while (input.read(buffer, bytes))
		{
			std::streamsize bytes_read = input.gcount();

			if (bytes_read <= 0)
			{
				break;
			}

			decrypt(buffer, static_cast<size_t>(bytes_read));
			output.write(buffer, bytes_read);
		}
	}
}
