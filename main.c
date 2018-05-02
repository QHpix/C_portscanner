#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int sockfd, port;
    int end_port;
    struct sockaddr_in target_addr;
    struct hostent *target;

    if(argc < 3)
    {
        printf("Usage: %s <target> <last port>\n", argv[0]);
        return -1;
    }

    if((target = gethostbyname(argv[1])) == NULL)
    {
        printf("Host not found!\n");
        return -1;
    }
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Error on socket creation!\n");
        return -1;
    }
    bzero((char *) &target_addr, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    bcopy((char *)target->h_addr, (char *)&target_addr.sin_addr.s_addr, target->h_length);
    end_port = atoi(argv[2]);
    for(port = 1;port <= end_port;port++)
    {
        target_addr.sin_port = htons(port);
        if(connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
            continue;
        else
            printf("Open port: %d\n", port);
    }
    printf("Scan complete.\n");
}
