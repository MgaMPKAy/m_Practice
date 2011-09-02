#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFSIZE 4096
extern int errno;
void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[])
{
	int sock, clientfd, len, clientlen, n;
	unsigned short port;
	struct sockaddr_in server, client;
	char buffer[BUFSIZE];
	pid_t cpid;

	if (argc < 2) {
		fprintf(stderr,"usage %s portnumber\n",argv[0]);
		exit(0);
	}
	port = (unsigned short) atoi(argv[1]);
	
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		error("Opening socket");
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(port);
	
	len=sizeof(server);
	if (bind(sock, (struct sockaddr *)&server, len) < 0) 
		error("binding socket");

	clientlen=sizeof(clientlen);
	if (listen(sock,5) < 0) 
		error("listening");
	while (1) {
		clientfd = accept(sock, (struct sockaddr *)&client,
				  (socklen_t *)&clientlen);
		if (clientfd < 0)
			error("Accepting");
		printf("A connection has been accepted from %s\n",
		       inet_ntoa((struct in_addr)client.sin_addr));
		cpid = fork();
		if (cpid == -1) {
			perror("call to fork");
			exit(1);
		} else if (cpid == 0) {
			/* child process*/
			close(sock);
			while (1) {
				n = recv(clientfd, buffer, BUFSIZE-1,0);
				printf("Read %d bytes from client\n",n);
				if (n < 1) {
					error("Reading");
				} else {
					buffer[n]='\0';
					printf("Message from client is: %s\n",buffer);
					len = strlen(buffer);
					for (int i = 0; i < n; i++) {
						buffer[i] = toupper(buffer[i]);
					}
					n = send(clientfd, buffer, n, 0);
					if (n < len)
						error("Error writing");
				}
			}
			if (close(clientfd) < 0)
				error("closing");
			exit(0);
		} else {
			/* parent process */
			close(clientfd);
		}
	} 
	return 0;
}
