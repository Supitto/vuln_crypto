/* tcp-server-fork.c */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 10240000

int main()
{
  int *blockchain = malloc(sizeof(int));
  /* Create the listener socket as TCP socket */
  int sd = socket(PF_INET, SOCK_STREAM, 0);
  /* here, the sd is a socket descriptor (part of the fd table) */

  if (sd == -1)
  {
    perror("socket() failed");
    return EXIT_FAILURE;
  }

  /* socket structures */
  struct sockaddr_in server;
  server.sin_family = PF_INET;
  server.sin_addr.s_addr = INADDR_ANY; /* allow any IP address to connect */

  unsigned short port = 9998;

  /* htons() is host-to-network short for data marshalling */
  /* Internet is big endian; Intel is little endian */
  server.sin_port = htons(port);
  int len = sizeof(server);

  if (bind(sd, (struct sockaddr *)&server, len) == -1)
  {
    perror("bind() failed");
    return EXIT_FAILURE;
  }

  /* identify this port as a listener port */
  if (listen(sd, 5) == -1)
  {
    perror("listen() failed");
    return EXIT_FAILURE;
  }

  struct sockaddr_in client;
  int fromlen = sizeof(client);

  int n;
  pid_t pid;
  char *buffer;
  while (1)
  {

    int newsd = accept(sd, (struct sockaddr *)&client, (socklen_t *)&fromlen);

    pid = fork();
    if (*blockchain == 2000)
      return 0;
    else
    {
      *blockchain = *blockchain + 1;
    }

    if (pid == -1)
    {
      perror("fork() failed");
      return EXIT_FAILURE;
    }

    if (pid > 0)
    {
      /* parent simply closes the new client socket
          because the child process will handle that connection */
      close(newsd);
    }
    else /* pid == 0 */
    {

      buffer = malloc(BUFFER_SIZE);
      // Open file
      FILE *fptr = fopen("flag.enc", "r");
      if (fptr == NULL)
      {
        printf("Cannot open file \n");
        exit(EXIT_FAILURE);
      } /* send ACK message back to the client */

      fread(buffer, BUFFER_SIZE, 1, fptr);

      send(newsd, buffer, BUFFER_SIZE, 0);
      free(buffer);
      close(newsd);
      exit(EXIT_SUCCESS);
    }
  }

  return EXIT_SUCCESS;
}
