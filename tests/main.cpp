#include "../wshf2/wshf2.hpp"

#include <cassert>
#include <iostream>

namespace wscs
{
	void wshf2_test()
	{
		wshf2 hash;
		hash.update(reinterpret_cast<const void*>("lol"), 3);
		std::bitset<wshf2::bits> result = hash.finalize();
		assert(result.all());
	}

	int run_tests()
	{
		try
		{
			wshf2_test();
		}
		catch (const std::exception& e)
		{
			std::cerr << "An exception occurred: " << e.what() << std::endl;
			return -1;
		}

		return 0;
	}
}

int main()
{
	return wscs::run_tests();
}