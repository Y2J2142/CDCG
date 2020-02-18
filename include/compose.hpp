#include <utility>

namespace CDCG {

template<typename F, typename G>
auto
compose(F&& f, G&& g)
{

	return [f = std::forward<F>(f), g = std::forward<G>(g)](auto&&... args) {
		return f(g(std::forward<decltype(args)>(args)...));
	};
}

template<typename F, typename... Funcs>
auto
compose(F&& f, Funcs&&... funcs)
{
	return compose(std::forward<F>(f), compose(std::forward<Funcs>(funcs)...));
}

template<typename F, typename G>
auto
composeRight(F&& f, G&& g)
{
	return [f = std::forward<F>(f), g = std::forward<G>(g)](auto&&... args) {
		return g(f(std::forward<decltype(args)>(args)...));
	};
}

template<typename F, typename... Funcs>
auto
composeRight(F&& f, Funcs&&... funcs)
{
	return composeRight(std::forward<F>(f),
						composeRight(std::forward<Funcs>(funcs)...));
}

}