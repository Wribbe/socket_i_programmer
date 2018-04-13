#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#include <netdb.h>

int
main(void)
{
    struct addrinfo hints = {0};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo * servinfo = NULL;
    int status = getaddrinfo("www.example.com", "80", &hints, &servinfo);
    int socketfd = socket(servinfo->ai_family,
            servinfo->ai_socktype,
            servinfo->ai_protocol);

    int res = connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if (res) {
        fprintf(stderr, "Could not connect, aborting.\n");
        return EXIT_FAILURE;
    }

    char header[] = "GET /index.html HTTP/1.1\r\nHOST:example.org\r\n\r\n";
    int n = write(socketfd, header, strlen(header));
    size_t size_buffer = 2048;
    char buffer[size_buffer];
    n = read(socketfd, buffer, size_buffer);
    printf("%s\n", buffer);

    /* Free the address information. */
    freeaddrinfo(servinfo);
}
