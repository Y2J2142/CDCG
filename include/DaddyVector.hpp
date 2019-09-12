#pragma once
#include <cstdint>
#include <type_traits>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <memory>

template<typename T>
class DaddyVector {

    

    T *Begin;
    size_t Size, Capacity;
    
    
    protected:
        DaddyVector(T* begin, size_t size, size_t capacity) : Begin{begin}, Size{size}, Capacity{capacity} {}
        void grow(size_t);
        void grow() {grow(Capacity * 2); }

    public:

        using size_t = std::uint64_t;
        using value_type = T;
        using iterator = T*;




        iterator begin() noexcept { return Begin; }
        const iterator begin() const noexcept { return Begin; }
        
        iterator end() noexcept { return Begin + Size; }
        const iterator end() const noexcept { return Begin + Size; }

        iterator data() { return Begin; }
        const iterator data() const noexcept { return Begin; }
        bool empty() const noexcept { return !Size; }
        size_t capacity() const noexcept { return Capacity; }
        bool isSmall() const noexcept;
        void push_back(const T& Element);
        void pop_back();
        T& operator[](size_t);
        const T& operator[](size_t) const;
        



};


template <typename T>
bool DaddyVector<T>::isSmall() const noexcept {
    //Hacky as fuck so probably should be rewritten in the future
    
    
    //obtaining pointer to the endof the first adress after the end of the class
    //and casting it to void as required for std::align
    auto endOfClass = (void*)( (char*) this + sizeof(*this));
    //not needed here
    std::size_t discard;
    //obtaining a pointer to the first valid address for T object 
    auto ptr = std::align(alignof(T), sizeof(T), endOfClass, discard);
    //checking if Begin points to the Buffer in BabyVector
    return ptr  == (char*)Begin;
    
}



template<typename T>
void DaddyVector<T>::pop_back() {
    end()->~T();
    --Size;
}


template<typename T>
void DaddyVector<T>::grow(DaddyVector::size_t newSize) {
    if(newSize <= Capacity) return;
    
    T* newElements = static_cast<T*>(newSize * sizeof(T));
    std::uninitialized_move(Begin, Begin + Size, newElements);

    if(!isSmall())
        delete[] Begin;
    Begin = newElements;

}