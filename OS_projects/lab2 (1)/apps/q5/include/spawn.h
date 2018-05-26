#ifndef __USERPROG__
#define __USERPROG__

typedef struct data{
	int temp;
	int curr_n;
	int curr_o;
	int curr_n2;
	int curr_o2;
	lock_t lock;
	cond_t c_n2;
	cond_t c_o2;
	cond_t c_no2;
	cond_t c_o3;
}data;

#define INJECT_N "inject_n.dlx.obj"
#define INJECT_O "inject_o.dlx.obj"

#endif
