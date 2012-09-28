tag:
	mpicc -Wall any-tag-test.c -o any-tag-test
	mpiexec -n 2 ./any-tag-test
