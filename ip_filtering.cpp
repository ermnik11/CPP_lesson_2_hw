#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "IPAddress.h"
#include "algorithms.h"

static int recursionDepth = 0;

std::vector<IPAddress> filter(const std::vector<IPAddress>& src)
{
    return src;
}

template<typename T, typename... Args>
std::vector<IPAddress> filter(const std::vector<IPAddress>& src, T n, Args... args)
{
    static_assert(sizeof...(args) <= SIZE_OF_IP, "::filter Too long byte mask!\n");

    std::vector<IPAddress> result;

    for (auto it = src.begin(); it != src.end(); it++)
    {
        if (it->getPart(recursionDepth) == n)
        {
            result.emplace_back(*it);
        }
    }

    recursionDepth++;

    result = filter(result, args...);

    recursionDepth--;

    return result;
}

std::vector<IPAddress> filter_any(const std::vector<IPAddress>& src, int n)
{
    std::vector<IPAddress> result;

    for (auto it = src.begin(); it != src.end(); it++)
    {
        for (int i = 0; i < SIZE_OF_IP; i++)
        {
            if (it->getPart(i) == n)
            {
                result.emplace_back(*it);
                break;
            }
        }
    }

    return result;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int, char const**)
{
    try
    {
        std::vector<IPAddress> ip_pool;

        std::ifstream inputFile("ip_filter.tsv"); // �������� ���� ��� ������

        for (std::string line; std::getline(inputFile, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.emplace_back(IPAddress(split(v.at(0), '.')));
        }

        // TODO reverse lexicographically sort
        QuickSort(ip_pool.begin(), ip_pool.end());

        for (auto ip = ip_pool.rbegin(); ip != ip_pool.rend(); ++ip)
        {
            std::cout << *ip << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
       auto ip_pool2 = filter(ip_pool, 1);
       for (auto ip = ip_pool2.rbegin(); ip != ip_pool2.rend(); ++ip)
       {
           std::cout << *ip << std::endl;
       }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
       auto ip_pool3 = filter(ip_pool, 46, 70);
       for (auto ip = ip_pool3.rbegin(); ip != ip_pool3.rend(); ++ip)
       {
           std::cout << *ip << std::endl;
       }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
       auto ip_pool4 = filter_any(ip_pool, 46);
       for (auto ip = ip_pool4.rbegin(); ip != ip_pool4.rend(); ++ip)
       {
           std::cout << *ip << std::endl;
       }

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
