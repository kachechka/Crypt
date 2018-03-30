#include "stdafx.h"

#include <iostream>
#include <conio.h>
#include "File.h"

#include "Ceasar.h"
#include "Base64.h"
#include "XOR.h"

namespace Crypt
{
	enum class TypeCrypt : unsigned char {
		Ceas = '1',	// Ceasar
		Base = '2',	// Base64
		Xor = '3'		// XOR
	};
}

int main()
{
	try
	{
		_wsetlocale(LC_ALL, L".866");

		std::wcout << L"Enter path to the file: ";
		std::wstring wPath{};
		std::getline(std::wcin, wPath);

		auto data = std::move(Crypt::File::Read(std::ifstream(wPath, std::ios::in
			| std::ios::binary)));

		std::wcout << L"File is crypted?(y/n): " << std::endl;

		bool is_crypted{};

		for (char select{}; (select = _getch()) != 'n' && select != 'N';)
		{
			if (select == 'y' || select == 'Y')
			{
				is_crypted = true;
				break;
			}
		}

		std::wcout << L"1 - Ceasar" << std::endl;
		std::wcout << L"2 - Base64" << std::endl;
		std::wcout << L"3 - XOR" << std::endl;

		for (;;)
		{
			switch (static_cast<Crypt::TypeCrypt>(_getch()))
			{

			default:
				continue;

			case Crypt::TypeCrypt::Base:

				if (is_crypted)
					Crypt::Base64::Decrypt(data);
				else
					Crypt::Base64::Encrypt(data);
				break;

			case Crypt::TypeCrypt::Ceas:
			{
				int key{};

				std::wcout << L"Enter key(int): ";
				std::cin >> key;
				if (!std::cin)
					throw std::runtime_error("Input is not correct");

				if (is_crypted)
					Crypt::Ceasar::Decrypt(data.begin(), data.end(), key);
				else
					Crypt::Ceasar::Encrypt(data.begin(), data.end(), key);
				break;
			}
			case Crypt::TypeCrypt::Xor:
			{
				std::string key{};

				std::wcout << L"Enter key(string): ";
				std::getline(std::cin, key);
				if (!std::cin)
					throw std::runtime_error("Input is not correct");

				Crypt::XOR::Crypt(data.begin(), data.end(), key);
				
				break;
			}
			}

			break;
		}

		Crypt::File::Write(std::ofstream(wPath, std::ios::out
												| std::ios::binary),
							data.cbegin(), data.cend());
	}
	catch (const std::exception& ex)
	{
		if (system("cls"))
			return {};

		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		if (system("cls"))
			return {};

		std::wcout << L"Unhandled exception" << std::endl;
	}

	_getch();

	return {};
}