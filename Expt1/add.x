/*
This is the IDL file. Combine the argument to be passed to the server side in a structure
*/

struct numbers {
	int a;
	int b;
}

program ADD_PROG {
	version ADD_VERS {
		int add(numbers) = 1;
	} = 1;
} = 0x4562877;

/*
numbers 	-> name of the structure which sends the parameters to the server.
ADD_PROG 	-> name of the program
ADD_VERS	-> name of the program version
add(numbers)	-> method that we are going to call remotely. We pass the structure as the parameter to this method.
*/
