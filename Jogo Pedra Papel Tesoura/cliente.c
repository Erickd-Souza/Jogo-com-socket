#include <winsock2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

typedef struct {
	int pontuacao_servidor;
	int pontuacao_cliente;
	char jogada_servidor[512];
} Pontuacao;

Pontuacao pontuacao;

void set_color(int text_color, int bg_color) { // Esta funcao permite mudar as cores da interface

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)(bg_color << 4) | text_color);
}

void validar_entrada(char* jogada_cliente) {
	while(1) {
        printf("\n\n Escolha pedra, papel ou tesoura (ou 'exit' para sair): ");
        fgets(jogada_cliente, sizeof(jogada_cliente), stdin);
        jogada_cliente[strcspn(jogada_cliente, "\n")] = 0;
        
        int i;
        char temp;
        char string[512];
        
        strcpy(string, "");
        
        for (i = 0; i <= strlen(jogada_cliente); i += 1) {
        	temp = tolower(jogada_cliente[i]);
        	string[i] = temp;
		}
		
		strcpy(jogada_cliente, string);

        if (strcmp(jogada_cliente, "exit") == 0) {
            printf("Encerrando o servidor\n");
            break;
        }
        if (strcmp(jogada_cliente, "pedra") == 0 || strcmp(jogada_cliente, "papel") == 0 ||
            strcmp(jogada_cliente, "tesoura") == 0 || strcmp(jogada_cliente, "exit") == 0) {
            break;  // Sai do loop se a entrada for válida
        } else {
            printf("\n Entrada invalida! Tente novamente.\n");
        }
        }
}

void imprimir_resultado_final() {
	system("cls");
	set_color(6, 0);
	
	if (pontuacao.pontuacao_cliente > pontuacao.pontuacao_servidor) {
        printf("\n");
        printf("         ##########################          \n");
        printf("         ##########################          \n");
        printf("    #####################################    \n");
        printf("  #########################################  \n");
        printf(" ####      ######################       #### \n");
        printf(" ###       ######################        ### \n");
        printf(" ##        ######################        ### \n");
        printf(" ###     ##########################      ### \n");
        printf(" ###    ############################    #### \n");
        printf("  ###   ### #################### ###    ###  \n");
        printf("  ####   ### ################## ####  ####   \n");
        printf("    ####  ######################### #####    \n");
        printf("     ######## ################ #########     \n");
        printf("       ######  ##############   ######       \n");
        printf("                ############                  \n");
        printf("                  ########                    \n");
        printf("                    ####                      \n");
        printf("                    ####                      \n");
        printf("                    ####                      \n");
        printf("                    ####                      \n");
        printf("                ############                  \n");
        printf("             ##################               \n");
        printf("             ##################               \n");
        printf("             ###            ###               \n");
        printf("             ###  PLAYER 2  ###               \n");
        printf("             ###            ###               \n");
        printf("             ##################               \n");
        printf("             ##################               \n");
        printf("           ######################              \n");
        printf("          ########################              \n");
    } else if (pontuacao.pontuacao_servidor > pontuacao.pontuacao_cliente) {
        	set_color(4, 0);
            printf("\n          _.-\"\"\"-._\n");
    		printf("         /  _   _  \\\n");
    		printf("        /  (9) (9)  \\\n");
    		printf("       /_,         ,_\\\n");
    		printf("       | \\         / |\n");
    		printf(" _     \\  \\._____./  /  __\n");
			printf(" \\`\\    \\   \\___/   / _|  \\\n");
    		printf("  \\ `\\  /\\         /\\ \\   /\n");
    		printf("   |  `\\/ /`'-----'\\ \\/  / \n");
    		printf("   |_|\\/ /           \\   /  \n");
    		printf("   /    /|           |\\_/   \n");
    		printf("   \\___/ |           | \\    \n");
    		printf("    \\ .  |           |  \\   \n");
    		printf("     \\|  |           |  |   \n");
    		printf("      |  `.         .'  |   \n");
    		printf("      \\    `-.___.-'    /   \n");
    		printf("       `\\       |       /'   \n");
    		printf("         `\\     |     /'     \n");
    		printf("      .-.-.`\\   |   /'.-.-.  \n");
    		printf("     (,(,(,`^   |   ^`,),),)  \n");
    		printf("      '-'-'-----`-----'-'-'   \n");
    		printf("\n");
    		printf("     VV     VV  OO OO OO  CC CC CC   EE EE EE          PP PP    EE EE EE   RR RR     DD DD     EE EE EE  UU    UU \n");
    		printf("     vv     vv  OO    OO  CC         EE                PP   PP  EE         RR   RR   DD    DD  EE        UU    UU \n");
    		printf("      vv   vv   OO    OO  CC         EE EE EE          PP PP    EE EE EE   RR RR     DD    DD  EE EE EE  UU    UU \n");
    		printf("       vv vv    OO    OO  CC         EE                PP       EE         RR   RR   DD    DD  EE        UU    UU \n");
    		printf("        vv      OO OO OO  CC CC CC   EE EE EE          PP       EE EE EE   RR    RR  DD  DD    EE EE EE  UU UU UU \n  ");
            
        }
        
    set_color(7, 0);
}

void teste_mostrar_score(void) {
	int x;
	for(x=0;x<120;x++){
		Sleep(1);
		printf(">");
	}
	printf("\n");
	printf("\n                  |++++++++++++++++++++++++++++++++|               |++++++++++++++++++++++++++++++++|");
    printf("\n                  |     PONTUACAO SERVIDOR : 0%d    |               |      PONTUACAO CLIENTE : 0%d    |", pontuacao.pontuacao_servidor, pontuacao.pontuacao_cliente);
    printf("\n                  |++++++++++++++++++++++++++++++++|               |++++++++++++++++++++++++++++++++|\n\n");
    for(x=0;x<120;x++){
		Sleep(1);
		printf(">");
	}
}

int main() {
    WSADATA winsocketsDados;
    if (WSAStartup(MAKEWORD(2, 2), &winsocketsDados) != 0) {
        printf("Falha ao inicializar o Winsock\n");
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("Erro ao criar o socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(51171);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Erro ao conectar ao servidor: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    Pontuacao dados_recebidos;
    char jogada_cliente[512], jogada_servidor[512];
    int bytesReceived;
    int sair = 0;
    
    recv(clientSocket, (char*)&dados_recebidos, sizeof(Pontuacao), 0);
    pontuacao = dados_recebidos;

    printf("\n                                 ||-----------------BEM VINDO JOGADOR 2-------------------||\n"); 

    while (1) {
    	system("cls");
    	teste_mostrar_score();
    	fflush(stdin);
		validar_entrada(jogada_cliente);
		
		if (strcmp("exit", jogada_cliente) == 0) {
			closesocket(clientSocket);
    		WSACleanup();
			return 0;
		}
     
        int bytesSent = send(clientSocket, jogada_cliente, strlen(jogada_cliente), 0);
        if (bytesSent == SOCKET_ERROR) {
            printf("Erro ao enviar dados: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }
        printf("\n\n < Aguardando a jogada do jogador 1.. >\n");
        // Recebe a jogada do jogador 1
            bytesReceived = recv(clientSocket, (char*)&dados_recebidos, sizeof(Pontuacao), 0);
            if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
                printf("Erro ao receber jogada do jogador 1 ou conexao encerrada\n");
                break;
            } else {
            	pontuacao = dados_recebidos;
			}
			
			strcpy(jogada_servidor, dados_recebidos.jogada_servidor);
            jogada_servidor[strlen(dados_recebidos.jogada_servidor)] = '\0';
            
            printf("\n     < Jogada do servidor: %s >\n", jogada_servidor);
            
            // Verifica se algum jogador atingiu 3 pontos
    		if (pontuacao.pontuacao_servidor >= 3 || pontuacao.pontuacao_cliente >= 3) {
    			imprimir_resultado_final();
    			system("pause");
        		return 0;  // Encerra o jogo se alguém venceu
    		}
	}
	

	
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
