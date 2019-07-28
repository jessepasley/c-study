#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#ifdef _WIN32
#include <editline/history.h>
#endif

/* Declare a buffer for suer inputer of size 2048 */

int main(int argc, char** argv) {

	/* Print Version and Exit Information */
	puts("JLisp Version 0.0.0.0.1");
	puts("Press Ctrl-c to Exit\n");

	/* In a never ending loop */
	while (1) {
		
		/* Output our prompt and get input */
		char* input = readline("jlisp> ");

		/* Add input to history */
		add_history(input);

		/* Echo input back to user */
		printf("No, you're a %s\n", input);
	
		/* Free retrieved input */
		free(input);

	}
	
	return 0;
}
