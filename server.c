#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#define PORT 8888

int main(int argc, char *argv[]) {
	char msg [30];
	WSADATA wsa;
	SOCKET listen_socket, client_socket;
	struct sockaddr_in server, client;
	int c, recv_size;
	char client_message[2000];
	printf("Initialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup failed. Error code: %d\n", WSAGetLastError());
		return 1;
		}
	printf("Winsock initialised.\n");
	if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket. Error code: %d\n", WSAGetLastError());
		return 1;
		}
	printf("Socket created.\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	if (bind(listen_socket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed. Error code: %d\n", WSAGetLastError());
		return 1;
		}
	printf("Bind done.\n");
	listen(listen_socket, 3);
	printf("Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);
	if ((client_socket = accept(listen_socket, (struct sockaddr *)&client, &c)) ==INVALID_SOCKET) {
		printf("COnnection failed. Error code: %d\n", WSAGetLastError());
		return 1;
		}
	printf("Connection accepted.\n");
	system("pause");
	system("Cls");
	printf("Selamat datang di server pusat\nServer pusat berperan sebagai database dan hanya bersifat satu arah\nMenunggu respon........");
	if ((recv_size = recv(client_socket, client_message, 2000, 0)) > 0) {
		client_message[recv_size] = '\0';
		printf("Laporan diterima");
		printf("\npesan dari client : %s", client_message);
		}
	closesocket(client_socket);
	closesocket(listen_socket);
	WSACleanup();
	return 0;
}
