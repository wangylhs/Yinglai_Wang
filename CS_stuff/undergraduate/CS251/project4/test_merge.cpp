#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include "merge.hpp"

std::string me;
void usage() {
	std::cerr << "Usage: " << me << " [parameters]\n"
	<< "  parameters:\n"
	<< "     -n      Size of individual vectors\n"
	<< "     -m      Number of input vectors\n"
	<< "     -s      Sparsity coefficient (0<s<1)\n";
	exit(1);
}

template<typename Container>
void random_pick(Container& out, size_t n, size_t N) {
	std::vector<int> v(N);
	for (int i=0 ; i<N ; ++i) v[i] = i;
	std::random_shuffle(v.begin(), v.end());
	out.clear();
	for (int i=0 ; i<n ; ++i) out.push_back(v[i]);
}

void fail(const std::string& msg) {
	std::cerr << "FAILED: " << msg << '\n';
	exit(-1);
}

double timeeval_diff(const timeval& t1, const timeval& t2 )
{
	timeval r;
	r.tv_sec  = t2.tv_sec  - t1.tv_sec;
	r.tv_usec = t2.tv_usec - t1.tv_usec;
	
	if( r.tv_usec < 0 )
	{
	    --r.tv_sec;
	    r.tv_usec += 1000000;
	}

	return (double)r.tv_sec + (double)r.tv_usec / 1000000.0;
}

bool correctness(int& N, int M, float s, double& duration, bool verbose=false) {
	// start with solution vector
	size_t nelem = s*N;
	std::vector<int> sv;
	random_pick(sv, nelem, N);
	std::sort(sv.begin(), sv.end());
	
	// create matching input sparse vectors
	std::vector<SparseVector> input(M);
	std::vector< std::list<int> > solution(nelem);
	for (int i=0 ; i<nelem ; ++i) {
		// distribute non-zero entry over a random number of input vectors
		int k = 1 + rand() % std::max(M/5, 1); // a random number between 1 and M/5
		random_pick(solution[i], k, M);
		const std::list<int>& l = solution[i];
		for (std::list<int>::const_iterator it=l.begin() ; it!=l.end() ; ++it) {
			input[*it].push_back(sv[i]);
		}
	}
	// identify the vectors that we left empty
	std::vector<int> empty;
	for (int i=0 ; i<M ; ++i) {
		if (input[i].empty()) {
			empty.push_back(i);
		}
	}
	// fill those vectors
	for (int i=0 ; i<empty.size() ; ++i) {
		int queue = empty[i];
		// select a random subset of non-zero rows in the solution vector
		int k = 1 + rand() % (nelem - 1);
		std::vector<int> ids;
		random_pick(ids, k, nelem);
		for (int i=0 ; i<k ; ++i) {
			int idx = sv[ids[i]];
			// add those coefficients to the sparsity description of the input vector
			input[queue].push_back(idx);
			// update solution vector accordingly
			solution[ids[i]].push_back(queue);
		}
	}
	// ensure that the coefficients in each vector are in increasing order
	size_t total_N=0;
	for (int i=0 ; i<M ; ++i) {
		std::sort(input[i].begin(), input[i].end());
		total_N += input[i].size();
	}
	
	SparseMerge output;
	
	timeval begin, end;
	gettimeofday(&begin, 0);
	merge(input, output);
	gettimeofday(&end, 0);
	duration = timeeval_diff(begin, end);

	if (verbose) {	
		std::cerr << "produced result:\n";
		for (int i=0 ; i<output.size() ; ++i) {
			std::cerr << output[i].first << ": ";
			for (std::list<int>::const_iterator it=output[i].second.begin() ; it!=output[i].second.end() ; ++it) {
				std::cerr << *it << ", ";
			}
			std::cerr << '\n';
		}
	}
	
	// check results
	if (output.size() != nelem) {
		std::cerr << "output size = " << output.size() << ", nelem=" << nelem << '\n';
		fail("wrong size");
	}
	for (int i=0 ; i<nelem ; ++i) {
		int idx = output[i].first;
		if (idx != sv[i]) {
			std:cerr<<sv[i]<<" "<<idx<<endl;
			fail("wrong index");
		}
		std::set<int> answer(output[i].second.begin(), output[i].second.end());
		std::set<int> truth(solution[i].begin(), solution[i].end());
		std::set<int>::const_iterator it1, it2;
		for (it1=answer.begin(), it2=truth.begin() ; it1!=answer.end() && it2!=truth.end() ; ++it1, ++it2) {
			if (*it1 != *it2) fail("wrong vectors");
		}
		if (it1 != answer.end() && it2 != truth.end()) fail("wrong vectors");
	}
	N = total_N;
	
	return true;
}
  
int main(int argc, char* argv[]) {
	int N=100, M=100;
	float s=0.05;
	
	for (int i=1 ; i<argc ; ++i) {
		std::string arg(argv[i]);
		if (arg == "-n") {
			if (i == argc-1) usage();
			N = atoi(argv[++i]);
		}
		else if (arg == "-m") {
			if (i == argc-1) usage();
			M = atoi(argv[++i]);
		}
		else if (arg == "-s") {
			if (i == argc-1) usage();
			s = atof(argv[++i]);
		} 
		else {
			std::cerr << "unrecognized input flag\n";
			usage();
		}
	}
	
	double duration;
	std::cerr << "Testing correctness\n";
	int total_N = N;
	correctness(total_N, M, s, duration, total_N <= 1000);
	std::cout << "CORRECTNESS TEST PASSED\n";
	std::cout << "solution took " << duration << " seconds\n";
	double K = duration/(double)total_N/log2((double)M);
	std::cerr << "total number of non-zero coefficients was " << total_N << '\n';
	std::cerr << "estimated constant = " << K << '\n';
	
	std::cerr << "Testing performance\n";
	N*=10;
	total_N = N;
	correctness(total_N, M, s, duration, false);
	std::cout << "solution for Nx10 took " << duration << " seconds\n";
	std::cerr << "total number of non-zero coefficients was " << total_N << '\n';
	double prediction = K * total_N * log2(M);
	std::cout << "predicted time for this computation was " << prediction << '\n';
	double error = fabs(duration-prediction)/prediction;
	std::cout << "error = " << error*100 << "%\n";
	if (error < 0.5) std::cout << "PERFORMANCE TEST PASSED\n";
	else std::cout << "PERFORMANCE TEST FAILED\n";
	
	return 0;
}
