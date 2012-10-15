#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc,char**argv){

	MPI_Init(&argc,&argv);

	void*tag_ub;
	int flag;

	MPI_Comm_get_attr(MPI_COMM_WORLD, MPI_TAG_UB, &tag_ub, &flag);

	int value=*(int*)tag_ub;
	MPI_Finalize();

	cout<<"MPI_TAG_UB= "<<value<<endl;

	return 0;
}

