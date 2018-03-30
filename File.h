#pragma once

#include <fstream>
#include <iterator>
#include <string>
#include <queue>

namespace Crypt
{
	class File
	{
		File() = delete;
		File(const File&) = delete;
		File(File&&) = delete;
		File& operator = (const File&) = delete;
		File& operator = (File&&) = delete;
		~File() = delete;
		
	public:

		static constexpr std::size_t Cluster = 4096;

		static std::deque<char> Read(std::ifstream&);

		template <typename OutIt>
		static void Write(std::ofstream&, OutIt, OutIt);
	};
	
	template <typename OutIt>
	inline void File::Write(std::ofstream& ofile, OutIt cbegin, OutIt cend)
	{
		if (!ofile.is_open())
			throw std::invalid_argument("File is close");

		if (!ofile.good())
			throw std::runtime_error("File in bad fill");

		std::copy(cbegin, cend, 
			std::ostream_iterator<char>(ofile));
	}
}