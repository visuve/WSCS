#pragma once

#include <bitset>
#include <cstdint>
#include <istream>

namespace wscs
{
	class wshf2
	{
	public:
		constexpr static size_t bits = 256;

		wshf2();
		wshf2(const wshf2& other);
		wshf2(wshf2&& other) noexcept;
		wshf2& operator = (const wshf2& other);
		wshf2& operator = (wshf2&& other) noexcept;

		void initialize();

		void update(const void* data, size_t length);
		void update(std::istream& stream);

		std::bitset<bits> finalize() const;

	private:
		uint16_t _sum;
	};
}
