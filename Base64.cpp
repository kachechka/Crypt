#include "stdafx.h"
#include "Base64.h"

namespace Crypt
{
	constexpr char* Base64::Codes;

	void Base64::Encrypt(container& data)
	{
		container result{};

		std::size_t i{};

		vec from(3), to(4);

		auto encrypt = [&](auto size)
		{
			ToEncrypt(to, from);

			if (to.size() != size)
				to.resize(size);

			for (auto item : to)
				result.emplace_back(Codes[item]);
		};

		for (auto it : data)
		{
			from[i] = it;

			if (++i < from.size())
				continue;

			encrypt(to.size());

			i = {};
		}

		if (i)
		{
			encrypt(i + 1);

			for (; i < from.size(); result.emplace_back('='), ++i);
		}

		data = std::move(result);
	}

	void Base64::Decrypt(container& result, vec& from, vec& to, std::size_t size)
	{
		std::for_each(from.begin(), from.end(),
			[=](auto& c)
		{
			if (c >= 'A' && c <= 'Z')
				c -= 'A';
			else if (c >= 'a' && c <= 'z')
				c -= static_cast<char>(71);
			else if (c >= '0' && c <= '9')
				c += static_cast<char>(4);
			else if (c == '+')
				c = static_cast<char>(62);
			else if (c == '/')
				c = static_cast<char>(63);
			else
				c = static_cast<char>(-1);
		});

		ToDecrypt(to, from);

		if (to.size() != size)
			to.resize(size);
		
		for (auto item : to)
			result.emplace_back(item);
	}

	void Base64::Decrypt(container& data)
	{
		container result{};

		std::size_t i{};

		vec to(3), from(4);

		for (auto it : data)
		{
			if (it == '=')
				break;

			from[i] = it;

			if (++i < from.size())
				continue;

			Decrypt(result, from, to, to.size());

			i = {};
		}
	
		if (i)
			Decrypt(result, from, to, i - 1);

		data = std::move(result);
	}
}