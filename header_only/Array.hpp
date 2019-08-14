#include<cstddef>
#include<type_traits>
#include<cstring>
#include<algorithm>

namespace CDCG::Containers {

    template<typename T, std::size_t N>
    struct Array {


        T data[N];
        
        constexpr Array() noexcept = default;
        constexpr Array(const Array& other) noexcept(noexcept(std::is_nothrow_copy_constructible_v<T>)) {
            std::copy(other.begin(), other.end(), this->begin());

        }
        constexpr Array& operator=(const Array& other) noexcept(noexcept(std::is_nothrow_copy_assignable_v<T>)) {
            std::copy(other.begin(), other.end(), this->begin());
            return this;
        } 

        constexpr Array(Array&&) noexcept = default;
        constexpr Array& operator=(Array&&) noexcept = default;
        ~Array() = default;
    

        const T* begin() const noexcept{
            return data;
        } 
        
        const T* end() const noexcept {
            return data + N;
        }
        
        T* begin() noexcept {
            return data;
        }

        T* end() noexcept {
            return data + N;
        }

        std::size_t size() const noexcept {
            return N;
        }

        T& operator[](std::size_t index) noexcept{
            return data[index];
        }

        const T& operator[](std::size_t index) const noexcept {
            return data[index];
        }

        void fill(const T& t) noexcept(noexcept(std::is_trivially_copyable_v<T>)){
            if constexpr(std::is_trivially_copyable_v<T>)
                std::memset(data, t, N);
            else
                for(auto && d : data)
                    d = t;
        }

        template<typename ...Args>
        Array(Args&& ... args) : data{std::forward<Args>(args)...} {}

    };

    template<typename First, typename ...Args>
    Array(First&& f, Args&& ... args) -> Array<First, sizeof...(args) + 1>;


}

