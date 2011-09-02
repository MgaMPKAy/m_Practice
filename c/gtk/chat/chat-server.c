#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <glib.h>
#include <string.h>

#define BUFSIZE 2048
#define MAX_CLIENT 2048
int clientfd_set[MAX_CLIENT];
char buffer[BUFSIZE];

pthread_mutex_t mutex_queue = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_queue = PTHREAD_COND_INITIALIZER;
void *service_read(void*);
void *service_deliver(void *data);
GQueue msg_queue = G_QUEUE_INIT;
struct msg {
	//other field
	char *text;
};

int main(int argc, char *argv[])
{
	int sockfd, clientfd, sockfd_len, client_len;
	unsigned short port;
	struct sockaddr_in server_addr, client_addr;
	pthread_t thread_id[MAX_CLIENT];
	pthread_t tid_deliver;
	
	if (argc < 2){
		fprintf(stderr, "usage %s portnumber\n", argv[0]);
		exit(0);
	}
	port = atoi(argv[1]);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("Opening socket");
		exit(0);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	sockfd_len = sizeof(server_addr);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("Binding socket");
		exit(0);
	}
	
	if (listen(sockfd, 5) < 0) {
		perror("Listening");
		exit(0);
	}
	
	pthread_create(&tid_deliver, NULL, service_deliver, NULL);
	
	while (1) {
		client_len = sizeof(client_addr);
		clientfd = accept(sockfd,
				  (struct sockaddr *)&client_addr,
				  (socklen_t *)&client_len);
		if (clientfd < 0) {
			perror("Accpeting");
		}
		//fcntl(clientfd, F_SETFL, O_NONBLOCK | O_FSYNC);
		for (int i = 0; i < 100; i++) {
			if (clientfd_set[i] == 0) {
				clientfd_set[i] = clientfd;
				pthread_create(&thread_id[i], NULL,
					       service_read, (void *)(long)i);
				break;
			}
		}
	}
	return 0;
}

void *service_read(void *data)
{
	int i = (int)(long)data;
	int clientfd = clientfd_set[i];
	int n;
	struct msg *msg = malloc(sizeof(*msg));
	printf("Thread created, fd = %d\n", clientfd);
	while (1) {
		n = recv(clientfd, buffer, BUFSIZE - 2, 0);
		buffer[n] = '\0';
		if (buffer[0] == 'e') {
			close(clientfd);
			clientfd_set[i] = 0;
			pthread_exit(0);
		}
		printf("recv %s\n", buffer);
		fflush(stdout);
		msg->text = malloc(strlen(buffer));
		strcpy(msg->text, buffer);

		pthread_mutex_lock(&mutex_queue);
		g_queue_push_tail(&msg_queue, msg);
		pthread_cond_broadcast(&cond_queue);
		pthread_mutex_unlock(&mutex_queue);
	}
	return NULL;
}

void *service_deliver(void *data)
{
	// *data is of no use
	struct msg *msg;
	int msg_len;
	
	//sched_yield();
	
	while (1) {
		pthread_mutex_lock(&mutex_queue);
		while (g_queue_is_empty(&msg_queue)) {
			printf("deliver stop\n");
			fflush(stdout);
			pthread_cond_wait(&cond_queue, &mutex_queue);
			printf("deliver stop\n");
			fflush(stdout);
		}
		while (!g_queue_is_empty(&msg_queue)) {
			msg = (struct msg *)g_queue_pop_head(&msg_queue);
			msg_len = strlen(msg->text);
			printf("before deliver msg:%s\n", msg->text);
			for (int i = 0, fd = 0; i < 8; i++) {
				//sleep(1);				
				if ((fd = clientfd_set[i]) > 0) {
					printf("send to %d\n", fd);
					send(fd, msg->text, msg_len, 0);
				}
			}
			printf("OK");
			fflush(stdout);
			free(msg->text);
			//free(msg);
		}
		pthread_mutex_unlock(&mutex_queue);
	}
	return NULL;
}
