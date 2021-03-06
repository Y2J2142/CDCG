#include <cstddef>
#include <type_traits>
namespace CDCG {

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
class Range
{

	struct FakeIterator
	{
		T val;
		T step;
		constexpr FakeIterator& operator++()
		{
			val += step;
			return *this;
		}
		constexpr FakeIterator operator++(int)
		{
			T t{ val + _step };
			val += step;
			return t;
		}

		constexpr T& operator*() { return val; }

		constexpr bool operator!=(const FakeIterator& other) const
		{
			if constexpr(std::is_floating_point_v<T>)
				return this->val < other.val;
			else
				return this->val != other.val && this->val < other.val;
		}
	};

  public:
	const T _begin = 0;
	const T _end;
	const T _step = 1;

	constexpr Range(T begin, T end, T step = 1)
		: _begin{ begin }
		, _end{ end }
		, _step{ step }
	{}
	constexpr Range(T end)
		: _end{ end }
	{}

	constexpr FakeIterator begin() const
	{
		return FakeIterator{ _begin, _step };
	}

	constexpr FakeIterator end() const { return FakeIterator{ _end, _step }; }

	constexpr std::size_t size() const { return static_cast<std::size_t>((_end - _begin) / _step); }
};
}
