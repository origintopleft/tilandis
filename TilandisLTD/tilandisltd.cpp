#include <WinSock2.h>
#include <WS2tcpip.h>

int wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int nShow) {
	// initalize sockets
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in sai_server;
	sai_server.sin_family = AF_INET;
	sai_server.sin_port = htons(57175);
	sai_server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (bind(sock, (struct sockaddr *) sai_server, sizeof(sai_server))
		< 0) {
		MessageBox(NULL, L"bind fail", L"bind fail", MB_ICONERROR);
		return 1;
	}

	char buffer[512];

	struct sockaddr_in sai_from;
	int i_fromlen;

	while (true) {
		int recvlen = recvfrom(sock, buffer, 512, 0, (struct sockaddr*) &sai_from, &i_fromlen);
		if (recvlen < 0) {
			MessageBox(NULL, L"recvfrom fail", L"recvfrom fail", MB_ICONERROR);
			return 1;
		}
		else if (recvlen > 0) {
			
		}
	}
}