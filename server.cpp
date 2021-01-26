#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>    //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <string>

#define TRUE 1
#define FALSE 0
#define PORT 2000
#define MAX_SIZE 58110
#define USERS 10
char dictionary[MAX_SIZE][100], base[MAX_SIZE][100];
int size = 0;

struct Player
{
    int port;
    int points = 0;
} players[USERS];

void generateLetters(char *letters)
{
    srand(time(NULL));
    int ascii;
    letters[0] = '1';
    letters[1] = '-';
    for (int i = 2; i < 17; i++)
    {
        ascii = 97 + rand() % 26;
        letters[i] = (char)ascii;
    }
    letters[17] = '\0';
}

bool checkWord(char *buffer, char *letters)
{
    int check = 0;
    char list[20];
    strcpy(list, letters);
    char *i, *j;
    for(i=buffer+2;*i;i++)
    {
        check = 0;
        for(j=list+2;*j;j++)
            if(*i!= '*' && *i == *j)
            {
                check = 1;
                *j = '*';
                break;
            }
        if (check == 0)
            return false;
    }
    return true;
}

bool checkDictionary(char *buffer)
{
    char *ptr = &buffer[2];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (!strcmp(ptr, dictionary[i]))
            return true;
    }
    return false;
}

bool checkBase(char *buffer)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (!strcmp(buffer, base[i]))
            return true;
    }
    return false;
}

void sendResult(char *result, char *buffer, char *letters, int who)
{
    char temp[5];
    int len = static_cast<int>(strlen(buffer)) - 2;
    if (len < 3)
        strcpy(result, "2-This word is too short.");
    else if (!checkWord(buffer, letters))
        strcpy(result, "2-This word cannot be made from the given letters.");
    else if (!checkDictionary(buffer))
        strcpy(result, "2-Such a word does not exist.");
    else if (checkBase(buffer))
        strcpy(result, "2-This word has already been given.");
    else
    {
        players[who].points += strlen(buffer) - 2;
        strcpy(result, "2-You entered the correct word, congratulations!.");
        strcpy(base[size], buffer);
        size++;
    }
    sprintf(temp, "%d", players[who].points);
    strcat(result, temp);
}

int main(int argc, char *argv[])
{
    int opt = TRUE;
    int master_socket, addrlen, new_socket, client_socket[30], activity, i, valread, sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025]; //data buffer of 1K
    char answer[50], letters[20], result[50];

    //set of socket descriptors
    fd_set readfds;

    int count = 0;
    FILE *fp = fopen("dictionary.txt", "r");
    ;
    char line[100];
    if (fp == NULL)
    {
        perror("Error opening file");
    }
    while (fgets(line, 100, fp) != NULL)
    {
        strcpy(dictionary[count], line);
        dictionary[count][strlen(dictionary[count]) - 2] = '\0';
        count++;
    }
    fclose(fp);

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < USERS; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for (i = 0; i < USERS; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            //highest file descriptor number, need it for the select function
            if (sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            valread = read(new_socket, buffer, 1024);
            printf("%s\n", buffer);
            if (valread > 0)
            {
                strcpy(answer, "0-LoggedIn");
                if (send(new_socket, answer, strlen(answer), 0) != strlen(answer))
                {
                    perror("send");
                }
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < USERS; i++)
            {
                //if position is empty
                if (client_socket[i] == 0)
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < USERS; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET(sd, &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valread = read(sd, buffer, 1024)) <= 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    client_socket[i] = 0;
                }

                //Echo back the message that came in
                else
                {
                    buffer[valread] = '\0';
                    printf("%s\n", buffer);
                    switch (buffer[0])
                    {
                    case '1':
                        generateLetters(letters);
                        strcpy(answer, letters);
                        break;
                    case '2':
                        sendResult(result, buffer, letters, i);
                        strcpy(answer, result);
                        break;
                    }
                    if (send(new_socket, answer, strlen(answer), 0) != strlen(answer))
                    {
                        perror("send");
                    }
                }
            }
        }
    }

    return 0;
}
