#pragma once
#include "DaddyVector.hpp"




template <typename T, std::uint64_t N>
class BabyVector : public  DaddyVector<T> {
    alignas(T) char Buffer[sizeof(T) * N];

    public:

    BabyVector() 
        : DaddyVector<T>::DaddyVector((T*)Buffer, 0, N) {}

};


