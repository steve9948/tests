#include <stdio.h>
#include <unistd.h>

/**
 * main - Parent PID
 *
 * Return: Always 0
 */

int main(void)
{
	pid_t parent_pid = getppid();
	printf("PArent process PID: %d/n", parent_pid);

	return(0);
}
