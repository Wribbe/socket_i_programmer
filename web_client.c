#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int
main(void)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = 0x22d8b85d; // Byte-reversed.

    int res = connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));
    if (res) {
        fprintf(stderr, "Could not connect, aborting.\n");
        return EXIT_FAILURE;
    }

    char header[] = "GET /index.html HTTP/1.1\r\nHOST:example.org\r\n\r\n";
    int n = write(socketfd, header, strlen(header));
    size_t size_buffer = 2048;
    char buffer[size_buffer];
    n = read(socketfd, buffer, size_buffer);
    printf("%s", buffer);
}
