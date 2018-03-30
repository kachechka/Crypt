#pragma once

#include <iterator>
#include <algorithm>

namespace Crypt
{
	class Ceasar
	{

		Ceasar() = delete;
		Ceasar(const Ceasar&) = delete;
		Ceasar(Ceasar&&) = delete;
		Ceasar& operator = (const Ceasar&) = delete;
		Ceasar& operator = (Ceasar&&) = delete;
		~Ceasar() = delete;

		template <typename It>
		static void Crypt(It, It, int) noexcept;

	public:
		
		template <typename It>
		static void Encrypt(It, It, int) noexcept;

		template <typename It>
		static void Decrypt(It, It, int) noexcept;
	};

	template <typename It>
	inline void Ceasar::Encrypt(It begin, It end, int key) noexcept
	{
		Ceasar::Crypt(begin, end, key);
	}

	template <typename It>
	inline void Ceasar::Decrypt(It begin, It end, int key) noexcept
	{
		Ceasar::Crypt(begin, end, -key);
	}

	template <typename It>
	inline void Ceasar::Crypt(It begin, It end, int key) noexcept
	{
		std::for_each(begin, end, [=](auto& item) noexcept
		{
			item += key;
		});
	}
}