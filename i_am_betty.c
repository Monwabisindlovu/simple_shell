#include <stdio.h>

int pass_betty_checks(void);
/**
 * main - Entry point
 *
 * Description: A collaborative simple shell project
 * Task 1: Writing code that meets all the Betty checks
 * We will run the code and check if it passes the checks
 * If it fails, we will start over until we get it right
 * Once it passes, we can proceed to the next task
 *
 * Return: Always 0
 */
int main(void)
{
int pass_checks = 0;

printf("Welcome to our collaborative simple shell project!\n");
printf("Task 1: Writing code that meets all the Betty checks.\n");
printf("We will write code together and check if it passes the checks.\n");

while (!pass_checks)
{

printf("Writing code...\n");

printf("This is my code that meets the Betty checks.\n");
printf("I have followed the coding style guidelines.\n");
printf("My code is well-documented and organized.\n");

printf("Code has been written.\n");
printf("Running the Betty style checks...\n");

if (pass_betty_checks())
{
printf("Code passed the Betty checks! Proceeding to the next task.\n");
pass_checks = 1;
}
else
{
printf("Code did not pass the Betty checks. Starting over.\n");
}
}

printf("Task 1 is complete. Moving on to the next task.\n");

return (0);
}

/**
 * pass_betty_checks - Simulates running the Betty style checks
 *
 * Return: 1 if code passes the checks, 0 otherwise
 */
int pass_betty_checks(void)
{

int passed = 0;

printf("betty i_am_betty.c\n");

return (passed);
}

