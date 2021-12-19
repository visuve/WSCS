#include "wshf2.hpp"

namespace wscs
{
	wshf2::wshf2(const wshf2& other) :
		_sum(other._sum)
	{
	}

	wshf2::wshf2(wshf2&& other) noexcept:
		_sum(other._sum)
	{
	}

	wshf2& wshf2::operator = (const wshf2& other)
	{
		if (this != &other)
		{
			_sum = other._sum;
		}

		return *this;
	}

	wshf2& wshf2::operator = (wshf2&& other) noexcept
	{
		if (this != &other)
		{
			_sum = other._sum;
		}

		return *this;
	}

	void wshf2::initialize()
	{
		_sum = 0;
	}

	void wshf2::update(void* data, size_t length)
	{
		if (!data)
		{
			throw std::invalid_argument("Data is null!");
		}

		uint8_t* iter = reinterpret_cast<uint8_t*>(data);

		for (size_t i = 0; i < length; ++i)
		{
			_sum += iter[i];
		}
	}

	void wshf2::update(std::istream& stream)
	{
		uint8_t buffer = '\0';

		while (stream.get(reinterpret_cast<char*>(&buffer), 1))
		{
			_sum += buffer;
		}
	}

	std::bitset<wshf2::bits> wshf2::finalize() const
	{
		std::bitset<bits> result;

		if (_sum % 2)
		{
			result.flip();
		}

		return result;
	}
}