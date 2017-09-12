#ifndef CS251_HEAP_HPP
#define CS251_HEAP_HPP

#include <bits/stl_pair.h>
#include <stdexcept>
#include <functional>
using namespace std;

template<typename Key, typename Value, typename Comp=std::less<Key> >
class Heap {
public:
	typedef Key                               key_type;
	typedef Value                             value_type;
	typedef std::pair<key_type, value_type>   node_type;
	typedef Comp                              comp_type;
		
	Heap(int alloc = 32) {
		size = 0;
		allocatedSize = alloc;
		pq = new node_type[allocatedSize];
		opNum = 0;
	}
	
    ~Heap() {
		delete [] pq;
	}
	
	void push(const key_type& k, const value_type& v) {
		//printf("push %s\n", k);
		//cout<<"Push "<<k<<endl;
		if (size==allocatedSize) {
			resize(size<<1);
		}

		pq[size] = node_type(k, v);
		
		int i = size++; 
		while(i) {
			int p = (i - 1) >> 1;
			if (cmp(pq[p].first, k)) {
				swap(pq[p], pq[i]);
				i = p;
			} else {
				break;
			}
		}
	}
	
	node_type pop() {
		//cout<<pq[0].first<<endl;
		if (size==0) throw "The heap is empty.";
		/*if (size<allocatedSize/4) {
			resize(size);
		}*/
		swap(pq[0], pq[--size]);
		int i = 0, l, r, m;
		while(1) {
			l = (i << 1) + 1;
			r = l + 1;
			m = i;
			if (l<size){
				if (cmp(pq[i].first, pq[l].first)) m = l;
				if (r<size){
					if (cmp(pq[m].first, pq[r].first)) m = r;
				}
			}
			if (m==i) break;
			swap(pq[m], pq[i]);
			i = m;
		}
		//printf("pop %s\n", pq[size].first);
		//cout<<"pop "<<pq[size].first<<endl;
		return pq[size];
	}
	node_type getTop() {
		return pq[0];
	}
	bool cmp(const key_type &a, const key_type &b) {
		comp_type c;
		opNum++;
		return c(a,b);
	}
	const node_type* find(const key_type& k) {//const {
		for(int i=0; i<size; i++) {
			if (!cmp(k, pq[i].first) && !cmp(pq[i].first, k)) {
				return pq + i;
			}
		}
		return NULL;
	}
	
	void resize(int newSize) {
		node_type *p = new node_type[newSize];
		for(int i=0; i<size; i++) {
			p[i] = pq[i];
		}
		delete [] pq;
		allocatedSize = newSize;
		pq = p;
	}
	
   size_t getNumberOfOperations() const {
		return opNum;
	}
	
	size_t getHeight() const {
		if (size==0) return 0;
		return static_cast<size_t>(log2(size));
	}
	
	size_t getSize() const {
		return size;
	}

private:
	node_type* pq;
	int size, allocatedSize;
	int opNum;
};

#endif // CS251_HEAP_HPP
