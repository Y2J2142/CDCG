#include "LazyArrayBase.hpp"

template<typename T, std::uint64_t N>
struct LazyArray : public LazyArrayBase<T> {

    typename LazyArrayBase<T>::Storage buffer[N];


    LazyArray() 
        : LazyArrayBase<T>(
            std::launder( reinterpret_cast<T*>( buffer ) ),
            std::launder( reinterpret_cast<T*>( buffer ) ),
            N
        ) {}
    LazyArray(const std::initializer_list<T>& lst)
        : LazyArrayBase<T>(
            std::launder( reinterpret_cast<T*>( buffer ) ),
            N,
            lst
        ) {}
    
    
};