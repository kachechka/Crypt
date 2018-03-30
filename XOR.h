#pragma once

#include <string>
#include <algorithm>

namespace Crypt
{
	class XOR
	{
		XOR() = delete;
		XOR(const XOR&) = delete;
		XOR(XOR&&) = delete;
		XOR& operator = (const XOR&) = delete;
		XOR& operator = (XOR&&) = delete;
		~XOR() = delete;

	public:

		template <typename It>
		static void Crypt(It, It, const std::string&) noexcept;
	};

	template <typename It>
	void XOR::Crypt(It begin, It end, const std::string& key) noexcept
	{
		if (key.empty())
			return;

		std::size_t i{};

		std::for_each(begin, end,
			[&](auto& item) noexcept 
		{
			item ^= key[i++ % key.size() + 1];
		});
	}
}