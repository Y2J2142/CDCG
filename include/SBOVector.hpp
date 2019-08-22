#include<cstddef>
#include<memory>
#include <cstring>
#include<type_traits>


namespace CDCG::Containers {

template <typename Type, std::size_t BufferSize = 5, typename Allocator = std::allocator<Type>>
class SBOVector {

	Type _buffer[BufferSize];
	Type* _data;
	std::size_t _size;
	std::size_t _capacity;

    void grow(std::size_t newSize);

public:
	using valueType = Type;

	bool operator==(const SBOVector& other) const noexcept;

	SBOVector() : _buffer{}, _data{_buffer}, _size{0}, _capacity{BufferSize} {}

	SBOVector(SBOVector&& other) noexcept;

	SBOVector& operator=(SBOVector&& other) noexcept;
	

    template <typename ...Args>
    Type& emplace_back(Args&& ... args) {
        if(_size == _capacity)
            grow(_capacity * 2);
        new(_data + _size) Type{std::forward<Args>(args)...};
        return _data[_size++];
    }

	
	void push_back(Type t) {
		if (_size == _capacity) {
			grow(_capacity * 2);
	    }
		new(_data + _size++) Type(std::move(t));
	}

    void reserve(std::size_t newSize) {
        if(newSize <= _capacity)
            return;

        grow(newSize); 
       
    }

	const Type& at(std::size_t i) const noexcept {
		assert(i < size() && "Index out of bounds");
		return _data[i];
	}
	Type& at(std::size_t index) noexcept {
		assert(index < size() && "Index out of bounds");
		return _data[index];
	}
	Type& operator[](std::size_t index) noexcept {
		return _data[index];
	}
	const Type& operator[](std::size_t index) const noexcept {
		return _data[index];
	}

	std::size_t size() const noexcept {
		return _size;
	}
	std::size_t capacity() const noexcept {
		return _capacity;
	}

	Type* data() noexcept {
		return _data;
	}

	Type* begin() noexcept {
		return _data;
	}

	Type* end() noexcept {
		return _data + _size;
	}

	const Type* data() const noexcept {
		return _data;
	}

	const Type* begin() const noexcept {
		return _data;
	}

	const Type* end() const noexcept {
		return _data + _size;
	}

	~SBOVector() {
		if (_data != _buffer)
			delete[] _data;
	}


};


template <typename Type, std::size_t BufferSize, typename Allocator>
bool SBOVector<Type, BufferSize, Allocator>::operator==(const SBOVector& other) const noexcept {
	if(_size != other._size)
		return false;
	for(std::size_t i{0}; i < _size; ++i) {
		if(_data[i] != other._data[i])
			return false;
	}

	return true;
}

template <typename Type, std::size_t BufferSize, typename Allocator>
SBOVector<Type, BufferSize, Allocator>::SBOVector(SBOVector&& other) noexcept : _data{ _buffer },_size { other._size }, _capacity{ other._capacity }  {

		if (other._data != other._buffer) {
			_data = other._data;
			other._data = other._buffer;
		}
		else {
			if constexpr (std::is_trivially_copyable_v<Type>) 
				std::memcpy(_data, other._data, sizeof(Type) * other._size);
			else
				for (std::size_t i{ 0 }; i < other._size; ++i) 
					new(_data + i) Type(std::move(other._data[i]));
		}

		other._size = 0;
		other._capacity = BufferSize;

	}

template <typename Type, std::size_t BufferSize, typename Allocator>
void
SBOVector<Type, BufferSize, Allocator>::grow(std::size_t newSize)
{
    _capacity = newSize;
    Type* newVector = new Type[_capacity];

    if constexpr (std::is_trivially_copyable_v<Type>) {
        std::memcpy(newVector, _data, sizeof(Type) * _size + 1);
    }
    else {
        std::size_t i{ 0 };
        while (i < _size) {
            new(newVector + i) Type(std::move(_data[i]));
            ++i;
        }

    }
    if(_data != _buffer)
        delete[] _data;
    _data = newVector;
}
	
}

