#pragma once

#include <vector>
#include <string>
#include <iostream>

const int SIZE_OF_IP = 4;

class IPAddress
{
	std::vector<unsigned char> ip;

public:

	IPAddress();
	IPAddress(const std::vector<std::string>& v);
	IPAddress(const IPAddress& other);
	IPAddress(IPAddress&& other);

	IPAddress& operator=(const IPAddress& other);
	IPAddress& operator=(IPAddress&& other);

	bool operator==(const IPAddress& other);
	bool operator>(const IPAddress& other);
	bool operator<(const IPAddress& other);
	bool operator>=(const IPAddress& other);
	bool operator<=(const IPAddress& other);

	friend std::ostream& operator<<(std::ostream& os, const IPAddress& ip);

	void swap(IPAddress& other);

	unsigned char getPart(int n) const { return this->ip.at(n); };
};

std::ostream& operator<<(std::ostream& os, const IPAddress& ip);

