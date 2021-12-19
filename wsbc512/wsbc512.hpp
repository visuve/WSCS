#pragma once

#include <array>
#include <bitset>
#include <filesystem>
#include <string_view>

namespace wscs
{
	class wsbc512
	{
	public:
		constexpr static size_t bits = 512;
		constexpr static size_t bytes = bits / 8;

		wsbc512();
		wsbc512(const wsbc512& other) = delete;
		wsbc512(wsbc512&& other) = delete;
		wsbc512& operator = (const wsbc512& other) = delete;
		wsbc512& operator = (wsbc512&& other) = delete;

		void initialize(const void* key, size_t length);

		void encrypt(void* data, size_t length);
		void encrypt(std::istream& input, std::ostream& output);

		void decrypt(void* data, size_t length);
		void decrypt(std::istream& input, std::ostream& output);

	private:
		std::array<uint8_t, bytes> _key;
	};
}