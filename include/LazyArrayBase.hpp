#pragma once
#include <algorithm>
#include <assert.h>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <type_traits>
namespace CDCG {

template<typename T>
struct LazyArrayBase
{

	using SizeType = std::uint64_t;
	using ConstSizeType = const std::uint64_t;
	using Iterator = T*;
	using ConstIterator = const T*;
	using Ref = T&;
	using ConstRef = const T&;
	typedef typename std::aligned_storage_t<sizeof(T), alignof(T)> Storage;

  private:
	Iterator Begin;
	Iterator End;
	ConstSizeType Capacity;

  protected:
	LazyArrayBase(Iterator begin, Iterator end, SizeType capacity)
		: Begin{ begin }
		, End{ end }
		, Capacity{ capacity }
	{}

	LazyArrayBase(
		Iterator begin,
		SizeType capacity,
		const std::initializer_list<T>&
			list) noexcept(noexcept(std::is_nothrow_copy_constructible_v<T>))
		: Begin{ begin }
		, End{ Begin + list.size() }
		, Capacity{ capacity }
	{
		std::uninitialized_copy(list.begin(), list.end(), Begin);
	}
	LazyArrayBase(const LazyArrayBase&) = delete;
	LazyArrayBase& operator=(const LazyArrayBase&) = delete;

	~LazyArrayBase() { std::destroy(Begin, End); }

	void* getBuffer() const noexcept;

  public:
	void push_back(const T&) noexcept(
		noexcept(std::is_nothrow_copy_constructible_v<T>));
	void push_back(T&&) noexcept(
		noexcept(std::is_nothrow_move_constructible_v<T>));
	SizeType size() const noexcept { return std::distance(Begin, End); }
	Iterator begin() noexcept { return Begin; }
	ConstIterator begin() const noexcept { return Begin; }
	Iterator end() noexcept { return End; }
	ConstIterator end() const noexcept { return End; }
	Iterator data() noexcept { return Begin; }
	ConstIterator data() const noexcept { return Begin; }
	bool empty() const noexcept { return Begin == End; }
	SizeType capacity() const noexcept { return Capacity; }
	Ref operator[](SizeType idx) noexcept { return Begin[idx]; }
	ConstRef operator[](SizeType idx) const noexcept { return Begin[idx]; }
	Ref at(SizeType) noexcept;
	ConstRef at(SizeType) const noexcept;
	void clear() noexcept(noexcept(std::is_nothrow_destructible_v<T>));
	bool operator==(const LazyArrayBase&) const noexcept;
	bool operator!=(const LazyArrayBase&) const noexcept;
	template<typename... Args>
	Ref emplace_back(Args&&... args)
	{
		assert(size() < Capacity && "No more space in LazyArray");
		new (End) T{ std::forward<Args>(args)... };
		return *(End++);
	}
};

template<typename T>
void*
LazyArrayBase<T>::getBuffer() const noexcept
{
	auto endOfClass =
		static_cast<void*>(static_cast<char*>(this) + sizeof(*this));

	auto discard = std::numeric_limits<std::size_t>::max();
	auto ptr = std::align(alignof(T), sizeof(T), endOfClass, discard);

	return ptr;
}

template<typename T>
void
LazyArrayBase<T>::push_back(const T& t) noexcept(
	noexcept(std::is_nothrow_copy_constructible_v<T>))
{
	assert(size() < Capacity && "No more space in LazyArray");
	new (End++) T{ t };
}

template<typename T>
void
LazyArrayBase<T>::push_back(T&& t) noexcept(
	noexcept(std::is_nothrow_move_constructible_v<T>))
{
	assert(size() < Capacity && "No more space in LazyArray");
	new (End++) T{ std::move(t) };
}

template<typename T>
void
LazyArrayBase<T>::clear() noexcept(noexcept(std::is_nothrow_destructible_v<T>))
{
	std::destroy(Begin, End);
	End = Begin;
}

template<typename T>
T&
LazyArrayBase<T>::at(LazyArrayBase<T>::SizeType idx) noexcept
{
	assert(idx < size() && "Index out of bounds!");
	return Begin[idx];
}

template<typename T>
const T&
LazyArrayBase<T>::at(LazyArrayBase<T>::SizeType idx) const noexcept
{
	assert(idx < size() && "Index out of bounds!");
	return Begin[idx];
}

template<typename T>
bool
LazyArrayBase<T>::operator==(const LazyArrayBase<T>& other) const noexcept
{
	if (this->size() != other.size()) return false;
	return std::equal(this->begin(), this->end(), other.begin(), other.end());
}

template<typename T>
bool
LazyArrayBase<T>::operator!=(const LazyArrayBase<T>& other) const noexcept
{
	return !this->operator==(other);
}

}
