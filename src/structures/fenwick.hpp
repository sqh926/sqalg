#ifndef SQALG_STRUCTURES_FENWICK_HPP
#define SQALG_STRUCTURES_FENWICK_HPP

#include "src/util/common.hpp"
#include <functional>

namespace sqalg {

    template<typename T>
    struct inverse {};

    // basically std::minus
    template<typename T>
    struct inverse<std::plus<T>> {
	static constexpr T operator()(const T& lhs, const T& rhs) {
	    return lhs - rhs;
	}
    };

    template<typename T, typename Op = std::plus<T>>
    struct fenwick {
	Op op;
	i32 n;
	std::vector<T> data;

	fenwick(std::vector<T> init, Op&& op = Op{}) : op(std::move(op)), n(init.size()), data(init) {
	    for (i32 i = 0; i < n; i++) {
		i32 r = i | (i + 1);
		if (r < n) data[r] = op(data[r], data[i]);
	    }	    
	}
	void update(i32 i, const T& val) {
	    for (; i < n; i = i | (i + 1))
		data[i] = op(data[i], val);
	}
	// [0, r)
	T pref(i32 r) const {
	    T res = {};
	    for (; r > 0; r = r & (r - 1))
		res = op(res, data[r - 1]);
	    return res;	    
	}

	// [l, r)
	T range(i32 l, i32 r) {
	    return inverse<Op>::operator()(pref(r), pref(l));
	}
		
    };

    
    
} // namespace sqalg



#endif // SQALG_STRUCTURES_FENWICK_HPP
