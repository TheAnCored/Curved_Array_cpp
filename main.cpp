#include "header.hpp"


int main(void){

	int render=0;

	const char *filename_input = "data.dat";
	const char *filename_output = "data.res";

	render = dance_with_array(filename_input, filename_output);

	if(render != 0){
		return -1;
	}

	return 0;
}