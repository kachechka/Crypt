#include "stdafx.h"
#include "File.h"

namespace Crypt
{
	constexpr std::size_t File::Cluster;

	std::deque<char> File::Read(std::ifstream& ifile)
	{

		if (!ifile.is_open())
			throw std::invalid_argument("File is close");

		std::deque<char> buff{};

		std::vector<char> tmpBuff(Cluster);

		while (!ifile.eof())
		{
			if (!ifile.good())
				throw std::runtime_error("File in bad fill");

			ifile.read(tmpBuff.data(), Cluster);

			buff.insert(buff.begin() + buff.size(),
				tmpBuff.cbegin(),
				tmpBuff.cbegin() + static_cast<std::size_t>(ifile.gcount()));
		}

		return std::move(buff);
	}
}