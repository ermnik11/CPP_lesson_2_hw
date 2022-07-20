#pragma once

#include <utility>
#include <iterator>

//binary search
template<typename It, typename El, typename Func>
It get_pos(It start, It end, El element, Func pred)
{
	It lower = start;
	It upper = end;
	It m = lower + (upper - lower) / 2;

	while (lower != upper)
	{
		if (pred(*m, element))
		{
			lower = m + 1;

		}
		else
		{
			upper = m;
		}
		m = lower + (upper - lower) / 2;
	}

	return m;
}

template<typename T>
std::pair<T, T> Partition(T start, T end)
{
	auto x = *(start + rand() % std::distance(start, end));    //*(start + (end - start) / 2);
	T l = start;
	T r = end;
	size_t m = 0;
	while (std::distance((l + m), r) > 0)
	{
		if (*(l + m) < x)
		{
			std::swap(*l, *(l + m));
			l++;
		}
		else if (*(l + m) > x)
		{
			r--;
			std::swap(*(l + m), *r);
		}
		else
		{
			m++;
		}
	}

	return std::pair<T, T>(l, r);
}

template<typename T>
void QuickSort(T start, T end)
{
	int dist = std::distance(start, end);

	if (dist > 1)
	{
		auto m = Partition(start, end);
		QuickSort(start, m.first);
		if (m.second != end)
		{
			QuickSort(m.second, end);
		}
	}
}