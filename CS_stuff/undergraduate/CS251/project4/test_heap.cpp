#include <iostream>
#include <ctime>
#include <string>
#include <math.h>

#include "heap.hpp"
#include "stl_heap.hpp"

size_t stl_nb_comp;

std::string me;
void usage() {
	std::cerr << "Usage: " << me << " [<int>]\n"
	<< "  parameter:\n"
	<< "     Maximum heap size\n";
	exit(1);
}

template<typename Container>
void shuffle(Container& out, size_t n) {
	std::vector<int> v(n);
	for (int i=0 ; i<n ; ++i) v[i] = i;
	std::random_shuffle(v.begin(), v.end());
	out.clear();
	for (int i=0 ; i<n ; ++i) out.push_back(v[i]);
}

std::string random_string(size_t maxlength=10) {
	size_t size = 1+rand()%(maxlength-1);
	std::string str(size, 'a');
	for (int i=0 ; i<size ; ++i) {
		str[i] = 'a' +  rand() % ('Z'-'a');
	}
	return str;
}

void fail(const std::string& msg) {
	std::cerr << "FAILED: " << msg << '\n';
	exit(-1);
}

template<typename T>
void random_generator(std::vector<T>& out, size_t n) {}

template<>
void random_generator<int>(std::vector<int>& out, size_t n) {
	shuffle(out, n);
}

template<>
void random_generator<float>(std::vector<float>& out, size_t n) {
	srand48(time(0));
	out.resize(n);
	for (int i=0 ; i<n ; ++i) out[i] = drand48();
}

template<>
void random_generator<std::string>(std::vector<std::string>& out, size_t n) {
	srand48(time(0));
	out.resize(n);
	for (int i=0 ; i<n ; ++i) out[i] = random_string();
}

template<typename T1, typename T2, typename Comp>
struct _pair_comp {
	typedef std::pair<T1, T2>    pair_type;
	
	bool operator()(const pair_type& p1, const pair_type& p2) const {
		Comp c();
		if (c(p1.first, p2.first)) return true;
		else if (c(p2.first, p1.first)) return false;
		return c(p1.second, p2.second);
	}
};

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
	os << "[" << p.first << ", " << p.second << "]";
	return os;
}

size_t nbop;
template<typename Heap1, typename Heap2>
bool same_pop(Heap1& h1, Heap2& h2) {
	typedef typename Heap1::node_type node_type;
	nbop += 2*h1.getHeight();
	node_type check = h1.pop();
	node_type truth = h2.pop();
	return (check.first == truth.first);
}

template<typename Heap1, typename Heap2>
bool same_height(const Heap1& h1, const Heap2& h2) {
	bool asw = (h1.getSize() == h2.getSize() && h1.getHeight() == h2.getHeight());
	if (!asw) {
		std::cerr << "sizes: " << h1.getSize() << " vs. " << h2.getSize() << '\n'
			<< "height: " << h1.getHeight() << " vs. " << h2.getHeight() << '\n';
	}
	return asw;
}

template<typename T, typename Comp>
bool test_correctness(size_t n) {
	std::vector<T> values;
	random_generator<T>(values, n);
	Heap<T, int, Comp>     my_heap;
	STLHeap<T, int, Comp>  stl_heap;
	nbop = 0;
	
	typedef _pair_comp<T, int, Comp>           compare_type;
	typedef typename compare_type::pair_type   pair_type;
	
	// CORRECTNESS CHECK PROCESS
	// 1. push the entire array / pop the entire array
	// 2. push half of the array / pop half of the array x 2
	// 3. push 2 pop 1, repeteadly
	// 4. push n times, pop n+1 times (exception check)
	// 5. push n times, find all inserted keys, including redundant ones
	
	// 1. Complete push followed by complete pop
	for (int i=0 ; i<n ; ++i) {
		my_heap.push(values[i], i);
		nbop += my_heap.getHeight();
		stl_heap.push(values[i], i);
	}
	for (int i=0 ; i<n ; ++i) {
		if (!same_pop(my_heap, stl_heap)) {
			std::cerr << "Test 1 failed after " << i << " iterations (pop)\n";
			return false;
		}
		if (!same_height(my_heap, stl_heap) || my_heap.getNumberOfOperations()>nbop) {
			std::cerr << "Test 1 failed after " << i << " iterations (state)\n";
			return false;
		}
	}
	if (my_heap.getSize()) {
		std::cerr << "Test 1 failed: heap is not empty after " << n << " pops.\n";
		return false;
	}
	std::cout << "Test 1 (push the entire array / pop the entire array) PASSED\n";
	
	// 2. Half push followed by half pop, twice
	for (int i=0 ; i<n/2 ; ++i) {
		my_heap.push(values[i], i);
		nbop += my_heap.getHeight();
		stl_heap.push(values[i], i);
	}
	for (int i=0 ; i<n/2 ; ++i) {
		if (!same_pop(my_heap, stl_heap)) {
			std::cerr << "Test 2a failed after " << i << " iterations (pop)\n";
			return false;
		}
		if (!same_height(my_heap, stl_heap) || my_heap.getNumberOfOperations()>nbop) {
			std::cerr << "Test 2a failed after " << i << " iterations (state)\n";
			return false;
		}
	}
	if (my_heap.getSize()) {
		std::cerr << "Test 2a failed: heap is not empty after " << n/2 << " pops.\n";
		return false;
	}
	for (int i=n/2 ; i<n ; ++i) {
		my_heap.push(values[i], i);
		nbop += my_heap.getHeight();
		stl_heap.push(values[i], i);
	}
	for (int i=n/2 ; i<n ; ++i) {
		if (!same_pop(my_heap, stl_heap)) {
			std::cerr << "Test 2b failed after " << i << " iterations (pop)\n";
			return false;
		}
		if (!same_height(my_heap, stl_heap) || my_heap.getNumberOfOperations()>nbop) {
			std::cerr << "Test 2b failed after " << i << " iterations (state)\n";
			return false;
		}
	}
	if (my_heap.getSize()) {
		std::cerr << "Test 2b failed: heap is not empty after " << n/2 << " pops.\n";
		return false;
	}
	std::cout << "Test 2 (push half of the array / pop half of the array x 2) PASSED\n";
	
	// 3. 2 push followed by 1 pop, repeatedly
	for (int i=0 ; i<n ; ++i) {
		my_heap.push(values[i], i);
		nbop += my_heap.getHeight();
		stl_heap.push(values[i], i);
		my_heap.push(values[++i], i);
		nbop += my_heap.getHeight();
		stl_heap.push(values[i], i);
		if (!same_pop(my_heap, stl_heap)) {
			std::cerr << "Test 3 failed after " << i << " iterations (pop)\n";
			return false;
		}
		if (!same_height(my_heap, stl_heap) || my_heap.getNumberOfOperations()>nbop) {
			std::cerr << "Test 3 failed after " << i << " iterations (state)\n";
			return false;
		}
	}
	if (my_heap.getSize() != stl_heap.getSize()) {
		std::cerr << "Test 3 failed: heap sizes differ: " << my_heap.getSize() << " != " << stl_heap.getSize() << '\n';
		return false;
	}
	std::cout << "Test 3 (2 push followed by 1 pop, repeatedly) PASSED\n";
	
	// 4. One more pop than the size of the heap
	size_t nbleft = my_heap.getSize();
	for (int i=0 ; i<nbleft ; ++i) {
		pair_type tmp = my_heap.pop();
	}
	bool error_caught = false;
	try {
		pair_type tmp = my_heap.pop();
	}
	catch(...) {
		error_caught = true;
	}
	if (error_caught) {
		std::cout << "Test 4 (One more pop than the size of the heap) PASSED\n";
	}
	else {
		std::cerr << "Test 4 failed: no exception caught.\n";
		return false;
	}
	
	// 5. verifying that elements added to the heap are present
	for (int i=0 ; i<n ; ++i) {
		my_heap.push(values[i], i);
	}	
	for (int i=0 ; i<n ; ++i) {
		my_heap.push(values[i], i+n);
	}
	for (int i=0 ; i<n ; ++i) {
		const pair_type* found = my_heap.find(values[i]);
		if (found == NULL) {
			std::cerr << "Test 5 failed: inserted value not found\n";
			return false;
		}
		else if (found->first != values[i]) {
			std::cerr << "Test 5 failed: wrong returned value\n";
			return false;
		}
		const pair_type* found2 = my_heap.find(values[i]);
		if (found == NULL) {
			std::cerr << "Test 5 failed: 2nd inserted value not found\n";
			return false;
		}
		else if (found->first != values[i]) {
			std::cerr << "Test 5 failed: wrong returned value\n";
			return false;
		}
	}
	std::cout << "Test 5 (verifying that elements added to the heap are found) PASSED\n";

	return true;
}

struct Compare_Str {
	bool operator()(const std::string& s1, const std::string& s2) const {
		return s1.compare(s2) < 0;
	}
};
  
int main(int argc, char* argv[]) {
	int N=10000;
	if (argc == 2) N = atoi(argv[1]);
	
	for (int n=2 ; n<=N ; n*=2) {
		std::cerr << "\nTesting heaps of size " << n << "...\n";
		std::cerr << "\tintegers...\n";
		bool ok = test_correctness<int, std::less<int> >(n);
		if (!ok) exit(-1);
		std::cerr << "\tfloats...\n";
		ok = test_correctness<float, std::less<float> >(n);
		if (!ok) exit(-1);
		std::cerr << "\tstrings...\n";
		ok = test_correctness<std::string, Compare_Str>(n);
		if (!ok) exit(-1);
	}
	return 0;
}
	