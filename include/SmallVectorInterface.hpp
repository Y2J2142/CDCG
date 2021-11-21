#pragma once
#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

namespace CDCG {

template<typename T>
class SmallVectorInterface
{

  public:
	using SizeType = std::size_t;
	using ValueType = T;
	using Iterator = T*;
	using ConstIterator = const T*;
	typedef typename std::aligned_storage_t<sizeof(T), alignof(T)> Storage;

  private:
	Storage* Begin;
	SizeType Size, Capacity;

  protected:
	SmallVectorInterface(Storage* begin, SizeType capacity)
		: Begin{ begin }
		, Size{ 0 }
		, Capacity{ capacity }
	{}

	SmallVectorInterface(const SmallVectorInterface& other) = delete;

	void grow(SizeType);
	void grow() { grow(Capacity * 2); }
	void* getBuffer() const noexcept;
	void setSize(SizeType n) { Size = n; }
	void clear() { reset(); }

  public:
	template<std::input_iterator Iter,
			 typename IterValueType = std::iterator_traits<Iter>::value_type>
		requires std::is_convertible_v<IterValueType, ValueType>
	void append(Iter first, Iter last)
	{
		auto count = std::distance(first, last);
		this->reserve(this->Size + count);
		std::uninitialized_copy(first, last, this->begin());
		this->Size += count;
	}
	SmallVectorInterface& operator=(const SmallVectorInterface& other)
	{
		if (this->Size > other.Size) {
			std::copy(other.begin(), other.end(), this->begin());
			auto dist = std::distance(other.begin(), other.end());
			std::destroy(this->begin() + dist, this->end());
		}
		if (this->Size == other.Size) {
			std::copy(other.begin(), other.end(), this->begin());
		} else {
			this->reserve(other.Size);
			auto dist = std::distance(this->begin(), this->end());
			std::copy(other.begin(), other.begin() + dist, this->begin());
			auto last_copy = std::copy_n(other.begin(), dist, this->begin());
			std::uninitialized_copy(
				other.begin() + dist, other.end(), last_copy);
		}
		this->Size = other.Size;
		return *this;
	}
	SmallVectorInterface(SmallVectorInterface&& o) { operator=(std::move(o)); }
	SmallVectorInterface& operator=(SmallVectorInterface&&);
	bool operator==(const SmallVectorInterface& other);

	SizeType size() const noexcept { return Size; }
	Iterator begin() noexcept
	{
		return std::launder(reinterpret_cast<T*>(Begin));
	}

	ConstIterator begin() const noexcept
	{
		return std::launder(reinterpret_cast<T*>(Begin));
	}

	Iterator end() noexcept
	{
		return std::launder(reinterpret_cast<T*>(&Begin[Size]));
	}
	ConstIterator end() const noexcept
	{
		return std::launder(reinterpret_cast<T*>(&Begin[Size]));
	}

	Iterator data() { return std::launder(reinterpret_cast<T*>(Begin)); }
	ConstIterator data() const noexcept
	{
		return std::launder(reinterpret_cast<T*>(Begin));
	}
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

	template<typename... Args>
	T& emplace_back(Args&&... args)
	{
		if (Size == Capacity) grow();
		auto ptr = std::launder(reinterpret_cast<T*>(&Begin[Size]));
		new (ptr) T{ std::forward<Args>(args)... };
		return this->operator[](Size++);
	}

	~SmallVectorInterface()
	{
		auto valuePtr = std::launder(reinterpret_cast<T*>(Begin));
		std::destroy(valuePtr, valuePtr + Size);
		if (!isSmall()) delete[] Begin;
	}
};

template<typename T>
bool
SmallVectorInterface<T>::operator==(const SmallVectorInterface& other)
{
	if (this->Size != other.Size) return false;
	return std::equal(this->begin(), this->end(), other->begin());
}

template<typename T>
bool
SmallVectorInterface<T>::isSmall() const noexcept
{
	return getBuffer() == Begin;
}

template<typename T>
void*
SmallVectorInterface<T>::getBuffer() const noexcept
{
	// obtaining pointer to the end of the first adress after the end of the
	// class and casting it to void as required for std::align
	auto endOfClass = reinterpret_cast<void*>(
		reinterpret_cast<char*>(const_cast<SmallVectorInterface*>(this)) +
		sizeof(*this));
	// not needed here
	std::size_t discard = std::numeric_limits<std::size_t>::max();
	// obtaining a pointer to the first valid address for T object
	auto ptr = std::align(alignof(T), sizeof(T), endOfClass, discard);
	// checking if Begin points to the Buffer in SmallVector
	return ptr;
}

template<typename T>
void
SmallVectorInterface<T>::reset()
{
	std::destroy(this->begin(), this->end());
	Begin = std::launder(reinterpret_cast<Storage*>(getBuffer()));
	Size = Capacity = 0;
}

template<typename T>
void
SmallVectorInterface<T>::pop_back()
{
	end()->~T();
	--Size;
}

template<typename T>
void
SmallVectorInterface<T>::grow(SmallVectorInterface<T>::SizeType newSize)
{
	if (newSize <= Capacity) return;

	Storage* newElements = new Storage[newSize];
	auto newStorage = std::launder(reinterpret_cast<T*>(newElements));
	auto oldStorage = std::launder(reinterpret_cast<T*>(Begin));
	std::uninitialized_move(oldStorage, oldStorage + Size, newStorage);
	std::destroy(oldStorage, oldStorage + Size);

	if (!isSmall()) delete[] Begin;

	Begin = newElements;
	Capacity = newSize;
}

template<typename T>
void
SmallVectorInterface<T>::push_back(const T& elem)
{
	if (Size == Capacity) grow();
	new (Begin + Size) T{ elem };
	++Size;
}

template<typename T>
T&
SmallVectorInterface<T>::operator[](
	SmallVectorInterface<T>::SizeType idx) noexcept
{
	return *std::launder(reinterpret_cast<T*>(&Begin[idx]));
}

template<typename T>
const T&
SmallVectorInterface<T>::operator[](
	SmallVectorInterface<T>::SizeType idx) const noexcept
{
	return *std::launder(reinterpret_cast<T*>(&Begin[idx]));
}

template<typename T>
void
SmallVectorInterface<T>::reserve(SmallVectorInterface<T>::SizeType newSize)
{
	grow(newSize);
}

template<typename T>
std::optional<T>
SmallVectorInterface<T>::at(
	SmallVectorInterface<T>::SizeType idx) const noexcept
{
	std::optional<T> retval{};
	if (idx < Size) retval = Begin[idx];
	return retval;
}

template<typename T>
SmallVectorInterface<T>&
SmallVectorInterface<T>::operator=(SmallVectorInterface&& o)
{
	if (this == &o) return *this;

	if (!o.isSmall()) {
		std::destroy(begin(), end());
		if (!isSmall()) delete[] Begin;
		Begin = o.Begin;
		Size = o.Size;
		Capacity = o.Capacity;
		o.reset();
		return *this;
	}

	auto oSize = o.size();
	auto curSize = size();
	if (curSize >= oSize) {
		auto newEnd = begin();
		if (oSize) newEnd = std::move(o.begin(), o.end(), newEnd);

		std::destroy(newEnd, end());
		o.reset();
		return *this;
	}

	if (capacity() < oSize) {
		std::destroy(begin(), end());
		setSize(0);
		curSize = 0;
		grow(oSize);
	} else if (curSize) {
		std::move(o.begin(), o.end() + curSize, begin());
	}
	std::uninitialized_move(o.begin() + curSize, o.end(), begin() + curSize);

	setSize(oSize);
	o.reset();
	return *this;
}

}
