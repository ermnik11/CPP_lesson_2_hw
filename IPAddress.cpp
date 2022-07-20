#include "IPAddress.h"

IPAddress::IPAddress()
{
	this->ip.resize(SIZE_OF_IP);
}

IPAddress::IPAddress(const std::vector<std::string>& v)
{
	if (v.size() != SIZE_OF_IP)
		throw;

	this->ip.resize(SIZE_OF_IP);

	for (int i = 0; i < SIZE_OF_IP; i++)
	{
		this->ip.at(i) = std::stoi(v.at(i));
	}
}

IPAddress::IPAddress(const IPAddress& other)
{
	this->ip.resize(SIZE_OF_IP);
	*this = other;
}

void IPAddress::swap(IPAddress& other)
{
	for (int i = 0; i < SIZE_OF_IP; i++)
	{
		std::swap(this->ip.at(i), other.ip.at(i));
	}
}

IPAddress::IPAddress(IPAddress&& other)
{
	this->ip.resize(SIZE_OF_IP);
	swap(other);
}

IPAddress& IPAddress::operator=(const IPAddress& other)
{
	for (int i = 0; i < SIZE_OF_IP; i++)
	{
		this->ip.at(i) = other.ip.at(i);
	}

	return *this;
}

IPAddress& IPAddress::operator=(IPAddress&& other)
{
	swap(other);
	return *this;
}

bool IPAddress::operator==(const IPAddress& other)
{
	bool result = true;

	for (int i = 0; i < SIZE_OF_IP; i++)
	{
		if (this->ip.at(i) != other.ip.at(i))
		{
			result = false;
			break;
		}
	}

	return result;
}

bool IPAddress::operator>(const IPAddress& other)
{
	bool result = false;

	for (int i = 0; i < SIZE_OF_IP; i++)
	{
		if (this->ip.at(i) > other.ip.at(i))
		{
			result = true;
			break;
		}
		else if (this->ip.at(i) < other.ip.at(i))
		{
			break;
		}
	}

	return result;
}

bool IPAddress::operator>=(const IPAddress& other)
{
	bool result = false;

	if ((*this > other) || (*this == other))
	{
		result = true;
	}

	return result;
}

bool IPAddress::operator<(const IPAddress& other)
{
	bool result = false;

	if (!(*this >= other))
	{
		result = true;
	}

	return result;
}

bool IPAddress::operator<=(const IPAddress& other)
{
	bool result = false;

	if ((*this < other) || (*this == other))
	{
		result = true;
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const IPAddress& ip)
{
	int i;

	for (i = 0; i < (SIZE_OF_IP - 1); i++)
	{
		os << static_cast<int>(ip.ip.at(i)) << '.';
	}
	os << static_cast<int>(ip.ip.at(i));

	return os;
}