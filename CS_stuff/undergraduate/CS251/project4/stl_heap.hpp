#ifndef CS251_STL_HEAP_HPP
#define CS251_STL_HEAP_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <bits/stl_pair.h>

namespace {
template<typename T1, typename T2, typename Compare>
struct pair_comp {
	typedef std::pair<T1, T2>    pair_type;
	
	bool operator()(const pair_type& p1, const pair_type& p2) const {
		return (_comp(p1.first, p2.first));
	}
	
	Compare  _comp;
};
}

template<typename Key, typename Value, typename Compare=std::less<Key> >
class STLHeap {
public:
	typedef Key                                         key_type;
	typedef Value                                       value_type;
	typedef std::pair<key_type, value_type>             node_type;
	typedef pair_comp<key_type, value_type, Compare>    comp_type;  

	STLHeap() : _array(), _less() {}

	void push(const key_type& k, const value_type& v) {
		_array.push_back(node_type(k, v));
		std::push_heap(_array.begin(), _array.end(), _less);
	}

	node_type pop() {
		if (_array.empty()) throw std::runtime_error("heap underflow");
		node_type max = _array.front();
		std::pop_heap(_array.begin(), _array.end(), _less);
		_array.pop_back();
		return max;
	}

    size_t getHeight() const {
		if (_array.empty()) return 0;
		else return log2(_array.size());
	}

    size_t getSize() const {
		return _array.size();
	}

private:
	comp_type              _less;
	std::vector<node_type> _array;
	
	bool equal(const key_type& k, const node_type& x) const {
		node_type y(k, value_type());
		return !(_less(x, y) || _less(y, x));
	}
};

#endif // CS251_STL_HEAP_HPP