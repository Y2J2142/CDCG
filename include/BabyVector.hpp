#pragma once
#include "DaddyVector.hpp"




template <typename T, std::uint64_t N>
class BabyVector : public  DaddyVector<T> {
    typename DaddyVector<T>::Storage Buffer[N];

    public:

    BabyVector() 
        : DaddyVector<T>::DaddyVector(Buffer, N) {}

    BabyVector(DaddyVector<T>&& o) 
        : DaddyVector<T>::DaddyVector(Buffer, N) {
            if(!o.empty())
                DaddyVector<T>::operator=(::std::move(o));
        }
};


