#include <algorithm>
#include <cstddef>
#include <cstring>
#include <type_traits>
namespace CDCG {

template<typename T, std::size_t N>
struct Array
{

	T data[N];

	constexpr Array() noexcept = default;

	constexpr Array(Array&&) noexcept = default;
	constexpr Array& operator=(Array&&) noexcept = default;
	~Array() = default;

	constexpr const T* begin() const noexcept { return data; }

	constexpr const T* end() const noexcept { return data + N; }

	T* begin() noexcept { return data; }

	T* end() noexcept { return data + N; }

	constexpr std::size_t size() const noexcept { return N; }

	T& operator[](std::size_t index) noexcept { return data[index]; }

	constexpr const T& operator[](std::size_t index) const noexcept
	{
		return data[index];
	}

	T& at(std::size_t index) noexcept
	{
		assert((index < size()) && "index out of bounds");
		return data[index];
	}

	constexpr const T& at(std::size_t index) const noexcept
	{
		assert((index < size()) && "index out of bounds");
		return data[index];
	}
	void fill(const T& t) noexcept(noexcept(std::is_trivially_copyable_v<T>))
	{
		if constexpr (std::is_trivially_copyable_v<T>)
			std::memset(data, t, N);
		else
			for (auto&& d : data)
				d = t;
	}

	template<typename... Args>
	constexpr Array(Args&&... args)
		: data{ std::forward<Args>(args)... }
	{}
};

template<typename First, typename... Args>
Array(First&& f, Args&&... args)->Array<First, sizeof...(args) + 1>;

}
