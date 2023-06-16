#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void iter_and_sleep_func(int sleep_duration) {
    printf(".");
    fflush(stdout);
    sleep(sleep_duration);
}

void add_break_line_func(int counter, int limit) {
    if (counter%limit == 0) {
        printf("\n");
    } 
}

void sig_handler_sigint(int signum) {
    //Return type of the handler function should be void
    printf("Inside handler function, got signal: %i\n", signum);
    signal(SIGINT, SIG_DFL);   // Re Register signal handler for default action
}
 


int main()
{
    int SLEEP_DURATION_SECONDS = 1;
    int NUMBER_OF_CHARS_LINE_BREAK = 10;
    int counter = 0;
    // prints hello world with simple signal handling for sigint
    printf("Hello World\n");
    printf("Registering for SIGINT - signum: %i\n", SIGINT);
    signal(SIGINT,sig_handler_sigint); // Register signal handler
    printf("sleep duration: %i\n", SLEEP_DURATION_SECONDS);
    for(;;) {
        counter+=1;
        // printf("c:%i", counter);
        iter_and_sleep_func(SLEEP_DURATION_SECONDS);
        add_break_line_func(counter, NUMBER_OF_CHARS_LINE_BREAK);
    }
    return 0;
}