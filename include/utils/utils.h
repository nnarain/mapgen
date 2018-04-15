#ifndef UTILS_H
#define UTILS_H

namespace utils
{
	/**
		Remap a range
	*/
	template<typename T>
	T range(T value, T from1, T to1, T from2, T to2)
	{
		return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
	}
}

#endif // UTILS_H