int temp[20];
int array[20];

void mergesort(int *begin, int num) {
	if (num<=1) return ;
	
	int num1 = num >> 1;
	int num2 = num - num1;
	mergesort(begin, num1);
	mergesort(begin+num1, num2);
	
	int i = 0, j = 0, c = 0;
	enterwhile:
		if (begin[i]>begin[num1+j]) goto elsebranch;
			temp[c++] = begin[i++];
			if (i<num1) goto enterwhile;
				append2:
					temp[c++] = begin[num+j++];
				if (j<num2) goto append2;
				goto exitwhile;

		elsebranch:
			temp[c++] = begin[num1+j++];
			if (j<num2) goto enterwhile;
				append1:
					temp[c++] = being[i++];
				if (i<num1) goto append1;

	exitwhile:
	
	while(c--){
		begin[c] = temp[c];
	}
}