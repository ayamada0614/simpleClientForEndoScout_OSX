#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int
main() {
  /* IP address, port number, socket */
  char servername[20];
  unsigned short port = 20248;
  int conn;

  /* sockaddr_in constructor */
  struct sockaddr_in server;

  /* Parameters */
  int status;
  int numsnt;
  char *toSendText = "This is a test";
  char buff[512];
  char CharPressed;
  int Port1;
  float xyz[3];
  float nvt[3];
  float tvt[3];
  char StatusCode[10];
  float cf=0.0;
  float rr=0.0;
  int wc=0;  
  char greeting[13]="#Server Ready";

  /************************************************************/
  /* Input the partners IP address */
  printf("Connect to ? : (name or IP address) ");
  scanf("%s", servername);

  /* sockaddr_in set the constructor */
  memset(&server, 0, sizeof(server));
  server.sin_addr.s_addr = inet_addr(servername);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  
  /* Create Socket */
  conn = socket(AF_INET, SOCK_STREAM, 0);

  /* Connection */
  printf("Trying to connect to %s: \n", servername);
  if(connect(conn, (struct sockaddr *) &server, sizeof(server)))
  {
    printf("ERROR: Cannot connect to server\n");
    close(conn);
    return -1;    
  }

  printf("Connected to server. ");
  sprintf(buff, "DATA 1");
  send(conn,buff,strlen(buff),0);
  recv(conn,buff,512,0);
  if(strncmp(buff,greeting,13)==0)
  {
    printf("Server greeting good.\n");
  }else
  {
    printf("Unknown server! Exiting program!\n");
    exit(1);
  }

  /* Send Packet */
  while(1)
  {
    CharPressed = toupper(getchar());
    printf("Press D to receive data, Q to quit\n");

    if(CharPressed=='D')
    {
      sprintf(buff, "DATA 1");
      send(conn,buff,strlen(buff),0);
      recv(conn,buff,512,0);
      sscanf(buff, "DATA%d %f %f %f %f %f %f %f %f %f %4s %f %f %d\n",
        &Port1,
        &xyz[0], &xyz[1], &xyz[2],
        &nvt[0], &nvt[1], &nvt[2],
        &tvt[0], &tvt[1], &tvt[2], StatusCode, &cf, &rr, &wc);
      printf("Data received: \nPort=%d\nX=%7.5f\nY=%7.5f\nZ=%7.5f\nNTV1=%7.5f\nNTV2=%7.5f\nNTV3=%7.5f\nTVT1=%7.5f\nTVT2=%7.5f\nTVT3=%7.5f\nSTATUS=%4s\nCF=%7.5f\nRR=%7.5f\nWC=%7.5f\n",
        Port1,xyz[0],xyz[1],xyz[2],nvt[0],nvt[1],nvt[2],tvt[0],tvt[1],tvt[2],StatusCode,cf,rr,wc);
    }

    if(CharPressed=='Q') break;

  }

  /* close socket */
  close(conn);
  return 0;

}
