
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
// TODO inttypes.h

// returtned streucture
// struct addrinfo {
//     int       ai_flags;
//     int       ai_family;
//     int       ai_socktype;
//     int       ai_protocol;
//     socklen_t ai_addrlen;
//     struct    sockaddr* ai_addr;
//     char*     ai_canonname;      /* canonical name */
//     struct    addrinfo* ai_next; /* this struct can form a linked list */
// };

// int getaddrinfo(const char *restrict node,
//             const char *restrict service,
//             const struct addrinfo *restrict hints,
//             struct addrinfo **restrict res);

// int getnameinfo(const struct sockaddr *restrict addr, socklen_t addrlen,
//                 char host[],
//                 socklen_t hostlen,
//                 char serv[],
//                 socklen_t servlen,
//                 int flags);


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

void print_address_string(struct addrinfo *lst) {
    int return_code;
    #define NI_MAXHOST 1025
    #define NI_MAXSERV 32
    printf("got addrinfo at: %p\n", (void *)&lst);
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
    return_code = getnameinfo(lst->ai_addr, lst->ai_addrlen, hbuf, sizeof(hbuf), sbuf,
                sizeof(sbuf), NI_NUMERICHOST);
    if (return_code == 0)
        printf("host=%s, serv=%s\n", hbuf, sbuf);
    else
        printf("could not resolve hostname");
}

void print_address_string_via_socket(struct sockaddr *lst) {
    struct sockaddr_in *addr_in = (struct sockaddr_in *)lst;
    char *s = inet_ntoa(addr_in->sin_addr);
    printf("IP address: %s\n", s);
}

int main() {
    int SLEEP_DURATION_SECONDS = 1;
    int NUMBER_OF_CHARS_LINE_BREAK = 10;
    int counter = 0;

    int return_code = 0;

    char hostname[100] = "localhost";
    if (gethostname(hostname, sizeof(hostname)) == 0)
        printf("using local hostname of: %s\n", hostname);
    else
        printf("was not able to gethostname - using locahost as hostname\n");
    struct addrinfo hints_1, *res_1;
    memset(&hints_1, '\0', sizeof(hints_1));
    hints_1.ai_family = AF_INET;


    return_code = getaddrinfo(hostname, NULL, &hints_1, &res_1);
    
    printf("rc: %i\n", return_code);

    print_address_string(res_1);
    print_address_string_via_socket(res_1->ai_addr);

    printf("releasing addinfo at: %p\n", (void *)&res_1);
    void freeaddrinfo(struct addrinfo *res_1);
    for(;;) {
        counter+=1;
        iter_and_sleep_func(SLEEP_DURATION_SECONDS);
        add_break_line_func(counter, NUMBER_OF_CHARS_LINE_BREAK);
    }
    printf("c: %i\n", counter);
    return 0;
}