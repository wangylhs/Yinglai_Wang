#ifndef CS251_MERGE_HPP
#define CS251_MERGE_HPP

#include "heap.hpp"
#include <vector>
#include <list>
#include <set>

typedef std::vector<int>                    SparseVector;
typedef std::list<int>                      IList;
typedef std::vector<std::pair<int, IList> > SparseMerge;
typedef std::pair<int, IList>               pair_type;
typedef std::greater<int> 					comp_type;

void merge(const std::vector<SparseVector>& input, SparseMerge& output) {
	size_t m = input.size();
	size_t *index = new size_t[m];
	Heap<int, int, comp_type> heap(m);
	
	for(int i=0; i < m; i++) {
		index[i] = 0;
		heap.push(input[i][0], i);
	}

	do {
		IList l;
		int i;
		do {
			std::pair<int, int> t = heap.pop();
			i = t.first;
			int j = t.second;
			if (index[j] + 1 <input[j].size()) {
				index[j]++;
				heap.push(input[j][index[j]], j);
			}
			l.push_back(j);
		} while(heap.getSize() && heap.getTop().first==i);
		output.push_back(pair<int, IList>(i, l));
	} while(heap.getSize());
	delete [] index;
}

#endif // CS251_MERGE_HPP
