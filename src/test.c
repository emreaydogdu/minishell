#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 // Maximal zulässige Länge des Befehls

void parseInput(char *input, char **args) {
	int i = 0;
	args[i] = strtok(input, " \n");
	while (args[i] != NULL) {
		i++;
		args[i] = strtok(NULL, " \n");
	}
}

int main(void) {
	char *args[MAX_LINE / 2 + 1]; // Argumente-Array
	char input[MAX_LINE];         // Eingabe-String

	while (1) {
		printf("minishell> ");
		fflush(stdout);

		if (!fgets(input, MAX_LINE, stdin)) {
			perror("fgets failed");
			exit(1);
		}

		parseInput(input, args);

		// Wenn kein Befehl eingegeben wurde, überspringen
		if (args[0] == NULL) {
			continue;
		}

		pid_t pid = fork();

		if (pid < 0) {
			perror("Fork failed");
			exit(1);
		} else if (pid == 0) { // Kindprozess
			if (execvp(args[0], args) == -1) {
				perror("execvp failed");
			}
			exit(1);
		} else { // Elternprozess
			int status;
			waitpid(pid, &status, 0);
		}
	}

	return 0;
}
