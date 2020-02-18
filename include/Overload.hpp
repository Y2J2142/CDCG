
namespace CDCG {

template<typename... Base>
struct Overload : Base...
{
	using Base::operator()...;
};

template<typename... Args>
Overload(Args&&... args)->Overload<Args...>;

}
