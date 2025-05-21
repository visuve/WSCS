#pragma once

#include <array>
#include <cstdint>
#include <istream>

namespace wscs
{
	class wssc8
	{
	public:
		constexpr static size_t bits = 256;
		constexpr static size_t bytes = bits / 8;

		wssc8();
		wssc8(const wssc8&) = delete;
		wssc8(wssc8&& other) = delete;
		wssc8& operator = (const wssc8&) = delete;
		wssc8& operator = (wssc8&&) = delete;

		void initialize(const void* key, size_t length);

		void encrypt(void* data, size_t length);
		void encrypt(std::istream& input, std::ostream& output);

		void decrypt(void* data, size_t length);
		void decrypt(std::istream& input, std::ostream& output);

	private:
		std::array<uint8_t, bytes> _key;
	};
}
