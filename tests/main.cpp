#include "../wshf2/wshf2.hpp"
#include "../wsbc512/wsbc512.hpp"

#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>

namespace wscs
{
	void wshf2_test()
	{
		{
			wshf2 hash;
			hash.update("lol", 3);

			std::bitset<wshf2::bits> result = hash.finalize();
			assert(result.all());
		}
		{
			std::stringstream stream;
			stream << "lol";

			wshf2 hash;
			hash.update(stream);

			std::bitset<wshf2::bits> result = hash.finalize();
			assert(result.all());
		}
	}

	void wsbc512_test()
	{
		// Underflow
		{
			wsbc512 crypt;
			crypt.initialize("password", 8);

			std::string secret = "Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida";
			crypt.encrypt(secret.data(), secret.length());

			assert(secret.compare("Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida") != 0);
		}
		// Exact
		{
			wsbc512 crypt;
			crypt.initialize("password", 8);

			std::string secret = "Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.";
			crypt.encrypt(secret.data(), secret.length());

			assert(secret.compare("Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.") != 0);
		}
		// Overflow
		{
			wsbc512 crypt;
			crypt.initialize("password", 8);

			std::string secret = "Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida...";
			crypt.encrypt(secret.data(), secret.length());

			assert(secret.compare("Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida...") != 0);
		}

		// String encrypt to decrypt equals
		{
			wsbc512 encryption;
			encryption.initialize("password", 8);

			std::string secret = "Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.";
			encryption.encrypt(secret.data(), secret.length());
			assert(secret.compare("Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.") != 0);

			wsbc512 decryption;
			decryption.initialize("password", 8);
			decryption.decrypt(secret.data(), secret.length());
			assert(secret.compare("Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.") == 0);
		}

		// Stream encrypt to decrypt equals
		{
			wsbc512 encryption;
			encryption.initialize("password", 8);

			std::stringstream plain, secret;
			plain << "Lorem ipsum dolor sit amet, consectetur adipiscing elit gravida.";
			plain << " Mauris feugiat aliquam tempor. Integer laoreet vulputate donec.";

			std::string copy(plain.str());

			encryption.encrypt(plain, secret);

			wsbc512 decryption;
			decryption.initialize("password", 8);
			decryption.decrypt(secret, plain);

			assert(copy == plain.str());
		}
	}

	int run_tests()
	{
		try
		{
			auto before = std::chrono::high_resolution_clock::now();

			wshf2_test();
			wsbc512_test();

			auto after = std::chrono::high_resolution_clock::now();
			auto diff = std::chrono::duration_cast<std::chrono::microseconds>(after - before);

			std::cout << "Tests completed in: " << diff.count() << "us" << std::endl;
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