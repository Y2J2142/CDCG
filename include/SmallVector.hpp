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

	SmallVector(SmallVectorInterface<T>&& o)
		: SmallVectorInterface<T>::SmallVectorInterface(Buffer, N)
	{
		if (!o.empty()) SmallVectorInterface<T>::operator=(::std::move(o));
	}
};

}
