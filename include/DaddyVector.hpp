#pragma once
#include <cstdint>
#include <type_traits>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <memory>
#include <optional>
#include <limits>

namespace CDCG {


template<typename T>
class DaddyVector {

public:

    using SizeType = std::uint64_t;
    using ValueType = T;
    using Iterator = T*;
    using ConstIterator = const T*;
    typedef typename std::aligned_storage_t<sizeof(T), alignof(T)> Storage;
private:

    Storage *Begin;
    SizeType Size, Capacity;
    
    
protected:
    DaddyVector(Storage *begin, SizeType capacity) 
        :   Begin{begin}, 
            Size{0},
            Capacity{capacity} {}
    DaddyVector(const DaddyVector& other) = delete;
    DaddyVector& operator=(const DaddyVector&) = delete;
    DaddyVector& operator=(DaddyVector&&);
    
    DaddyVector(DaddyVector&& o) {
        operator=(std::move(o));
    }

    void grow(uint64_t);
    void grow() {grow(Capacity * 2); }
    void* getBuffer() const noexcept;
    void setSize(SizeType n) {Size = n;}
    void clear() { std::destroy(begin(), end()); Size = 0;}
public:


    bool operator==(const DaddyVector& other);

    


    SizeType size() const noexcept { return Size;}
    Iterator begin() noexcept {
        return std::launder( reinterpret_cast<T*>( Begin ) );
    }

    ConstIterator begin() const noexcept {
        return std::launder( reinterpret_cast<T*>( Begin ) );
    }

    Iterator end() noexcept {
        return std::launder( reinterpret_cast<T*>( &Begin[Size] ) );
    }
    ConstIterator end() const noexcept {
        return std::launder( reinterpret_cast<T*>( &Begin[Size] ) );
    }

    Iterator data() { return std::launder( reinterpret_cast<T*>( Begin ) ); }
    ConstIterator data() const noexcept { return std::launder( reinterpret_cast<T*>( Begin ) ); }
    bool empty() const noexcept { return !Size; }
    SizeType capacity() const noexcept { return Capacity; }
    bool isSmall() const noexcept;
    void push_back(const T& Element);
    void pop_back();
    T& operator[](SizeType) noexcept;
    const T& operator[](SizeType) const noexcept;
    void reserve(SizeType);
    void reset();
    std::optional<T> at(SizeType) const noexcept;



    template<typename ...Args>
    T& emplace_back(Args&& ... args) {
        if(Size == Capacity)
            grow();
        auto ptr = std::launder( reinterpret_cast<T*>( &Begin[Size] ) );
        new(ptr) T{std::forward<Args>(args)...};
        return this->operator[](Size++);
    }

    ~DaddyVector() {
        auto valuePtr = std::launder( reinterpret_cast<T*>( Begin ) );
        std::destroy(valuePtr, valuePtr + Size);
        if(!isSmall())
            delete[] Begin;

    }



};


template <typename T>
bool DaddyVector<T>::isSmall() const noexcept {
   return getBuffer() == Begin;
}


template<typename T>
void* DaddyVector<T>::getBuffer() const noexcept {
    //Hacky as fuck so probably should be rewritten in the future
    
    
    //obtaining pointer to the endof the first adress after the end of the class
    //and casting it to void as required for std::align
    auto endOfClass = (void*)( (char*) this + sizeof(*this));
    //not needed here
    std::size_t discard = std::numeric_limits<std::size_t>::max();
    //obtaining a pointer to the first valid address for T object 
    auto ptr = std::align(alignof(T), sizeof(T), endOfClass, discard);
    //checking if Begin points to the Buffer in BabyVector
    return ptr;

}

template<typename T>
void DaddyVector<T>::reset() {
    Begin = std::launder( reinterpret_cast<Storage*>( getBuffer() ) );
    Size = Capacity = 0;        
}


template<typename T>
void DaddyVector<T>::pop_back() {
    end()->~T();
    --Size;
}


template<typename T>
void DaddyVector<T>::grow(uint64_t newSize) {
    if(newSize <= Capacity) return;
    
    Storage *newElements = new Storage[newSize];
    auto newStorage = std::launder( reinterpret_cast<T*>( newElements ) );
    auto oldStorage = std::launder( reinterpret_cast<T*>( Begin ) );
    std::uninitialized_move(oldStorage, oldStorage + Size, newStorage);
    std::destroy(oldStorage, oldStorage+Size);

    if(!isSmall()) delete[] Begin;

    Begin = newElements;
    Capacity = newSize;
}


template<typename T>
void DaddyVector<T>::push_back(const T& elem) {
    if(Size == Capacity)
        grow();
    new(Begin + Size) T{elem};
    ++Size;
}

template<typename T>
T& DaddyVector<T>::operator[](DaddyVector<T>::SizeType idx) noexcept {
     return *std::launder( reinterpret_cast<T*>( &Begin[idx] ) );
}

template<typename T>
const T& DaddyVector<T>::operator[](DaddyVector<T>::SizeType idx) const noexcept {
     return *std::launder( reinterpret_cast<T*>( &Begin[idx] ) );
}


template<typename T>
void DaddyVector<T>::reserve(DaddyVector<T>::SizeType newSize) {
    grow(newSize);
}

template<typename T>
std::optional<T> DaddyVector<T>::at(DaddyVector<T>::SizeType idx) const noexcept {
    std::optional<T> retval{};
    if(idx < Size)
        retval = Begin[idx];
    return retval;
}


template<typename T>
DaddyVector<T>& DaddyVector<T>::operator=(DaddyVector&& o) {
    if(this == &o) return *this;

    if(!o.isSmall()) {
        std::destroy(begin(),end());
        if(!isSmall()) delete[] Begin;
        Begin = o.Begin;
        Size = o.Size;
        Capacity = o.Capacity;
        o.reset();
        return *this; 
    }


    auto oSize = o.size();
    auto curSize = size();
    if(curSize >= oSize) {
        auto newEnd = begin();
        if(oSize)
            newEnd = std::move(o.begin(), o.end(), newEnd);
        
        std::destroy(newEnd, end());
        o.clear();
        return *this;
    }

    if(capacity() < oSize) {
        std::destroy(begin(), end());
        setSize(0);
        curSize = 0;
        grow(oSize);
    } else if(curSize) {
        std::move(o.begin(), o.end() + curSize, begin());
    }
    std::uninitialized_move(o.begin()+curSize, o.end(), begin()+curSize);

    setSize(oSize);
    o.clear();
    return *this;

}

}