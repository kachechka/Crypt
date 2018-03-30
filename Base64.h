#pragma once

#include <string>
#include <queue>
#include <vector>
#include <algorithm>

namespace Crypt
{
	class Base64
	{
		Base64() = delete;
		Base64(const Base64&) = delete;
		Base64(Base64&&) = delete;
		Base64& operator = (const Base64&) = delete;
		Base64& operator = (Base64&&) = delete;
		~Base64() = delete;

		static constexpr char* Codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";

		using container = std::deque<char>;
		using vec = std::vector<char>;

		static void ToEncrypt(vec&,	// to crypt data
						const vec&)	// from data
			noexcept;

		static void ToDecrypt(vec&,	// to decrypt data
						const vec&)	// from crypt data
			noexcept;

		static void Decrypt(container&, vec&, vec&, std::size_t);

	public:
		
		static void Encrypt(container&);

		static void Decrypt(container&);
	};

	inline void Base64::ToEncrypt(vec& lhs, const vec& rhs) noexcept
	{
		lhs[0] = (rhs[0] & 0xfc) >> 2;
		lhs[1] = ((rhs[0] & 0x03) << 4) + ((rhs[1] & 0xf0) >> 4);
		lhs[2] = ((rhs[1] & 0x0f) << 2) + ((rhs[2] & 0xc0) >> 6);
		lhs[3] = (rhs[2] & 0x3f);
	}

	inline void Base64::ToDecrypt(vec& lhs, const vec& rhs) noexcept
	{
		lhs[0] = (rhs[0] << 2) + ((rhs[1] & 0x30) >> 4);
		lhs[1] = ((rhs[1] & 0xf) << 4) + ((rhs[2] & 0x3c) >> 2);
		lhs[2] = ((rhs[2] & 0x3) << 6) + rhs[3];
	}
}