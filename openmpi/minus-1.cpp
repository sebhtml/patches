#include <iostream>
#include <stdint.h>
using namespace std;

union joe{
	int value_int;
	uint32_t u32;
};

void dump(int value){
	union joe val;
	val.value_int=value;
	cout<<"int: "<<value<<" uint32_t: "<<val.u32<<endl;


}

int main(){

	dump(0);
	dump(2147483647);
	dump(-1);
	dump(-2147483648);

	return 0;
}
