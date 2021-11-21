#pragma once
#include "SmallVectorInterface.hpp"

namespace CDCG {

template<typename T, std::uint64_t N>
class SmallVector : public SmallVectorInterface<T>
{
	typename SmallVectorInterface<T>::Storage Buffer[N];

  public:
	SmallVector()
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{}
	SmallVector(std::initializer_list<T> init)
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{
		SmallVectorInterface<T>::append(init.begin(), init.end());
	}
	SmallVector(const SmallVector& other)
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{
		if (!other.empty()) SmallVectorInterface<T>::operator=(other);
	}
	SmallVector(const SmallVectorInterface<T>& other)
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{
		if (!other.empty()) SmallVectorInterface<T>::operator=(other);
	}
	SmallVector(SmallVectorInterface<T>&& o)
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{
		if (!o.empty()) SmallVectorInterface<T>::operator=(::std::move(o));
	}
};

}
