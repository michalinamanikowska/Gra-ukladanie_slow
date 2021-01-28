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
#define USERS 2
char dictionary[MAX_SIZE][100], base[MAX_SIZE][100];
int size = 0, timer, roundNumber = 1;

struct Player
{
    char login[20];
    int port = 0;
    int points = 0;
    char opponentWords[MAX_SIZE][100];
    int oppCount = 0;
}players[USERS];

bool canAdd(char x, char *letters, int j)
{
    int count = 0;
    for (int i=2;i<j;i++)
        if (x == letters[i])
            count++;
    if (count>=2)
        return false;
    return true;
}

void generateLetters(char *letters)
{
    srand(time(NULL));
    int ascii, vowels = 0, repeat = 0, i;
    char temp[5];
    letters[0] = '1';
    letters[1] = '-';
    while(vowels<5)
    {
        do{
        ascii = 97 + rand() % 26;
        }
        while((ascii!=97 and ascii!=101 and ascii!=105 and ascii!=111 and ascii!=117 and ascii!=121) or !canAdd((char)ascii,letters,vowels));
        letters[vowels+2] = (char)ascii;
        vowels++;
    }
    i = vowels;
    while (i<17)
    {
        ascii = 97 + rand() % 26;
        if (canAdd((char)ascii,letters,i))
            letters[i] = (char)ascii;
        i++;
    }
    strcpy(letters,"1-qwertyuiopasdfg");
    letters[17] = '!';
    letters[18] = '\0';
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

void sendBroadcast(char *answer)
{
    for (int i=0;i<USERS;i++)
        if (players[i].port!=0)
            if (send(players[i].port, answer, strlen(answer), 0) != strlen(answer))
                perror("send");
}

void sendResult(char *result, char *buffer, char *letters, int who)
{
    char temp[5];
    char *ptr = &buffer[2];
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
        sprintf(temp, "%d", players[who].points);
        strcat(result, temp);
        size++;
        for (int i=0;i<USERS;i++)
            if(i!=who && players[i].port != 0)
                {
                    strcpy(players[i].opponentWords[players[i].oppCount],ptr);
                    players[i].oppCount++;
                }
        for (int i=0;i<USERS;i++)
            printf("%s",players[who].opponentWords[i]);
    }
}

void getLogin(char *buffer, int number)
{
    char *ptr = &buffer[2];
    strcpy(players[number].login,ptr);
}

void deleteData(int started)
{
    for (int i=0;i<USERS;i++)
        {
            if (started == 0)
                players[i].points = 0;
            memset(players[i].opponentWords, 0, sizeof(players[i].opponentWords[0][0]) * MAX_SIZE * 100);
        }
    memset(base, 0, sizeof(base[0][0]) * MAX_SIZE * 100);
}

void* countTime(void *vargp) {
    int warning = 0, timer = 60;
    char round[10], letters[25], answer[50];
    while (1) {
        timer--;
        if (timer < 0)
        {
            roundNumber++;
            generateLetters(letters);
            sprintf(round, "%d", roundNumber);
            strcpy(answer, "1-asdfghjklzxcvbn!");
            strcat(answer, round);
            sendBroadcast(answer);
            break;
        }
        if (timer < 10 && warning == 0)
        {
            strcpy(answer, "4-10 seconds remaining");
            sendBroadcast(answer);
            warning = 1;
        }
        sleep(1);
    };
}

int main(int argc, char *argv[])
{
    int opt = TRUE;
    int master_socket, addrlen, new_socket, activity, i, valread, sd;
    int max_sd;
    int started = 0, playersCount = 0;
    struct sockaddr_in address;
    pthread_t tid;

    char buffer[1025]; //data buffer of 1K
    char answer[50], letters[25], result[50], round[10], player[5], logged[50], temp[5];
    char *ptr;

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
        players[i].port = 0;
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
            sd = players[i].port;

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
                if (playersCount<USERS)
                {
                
                    playersCount++;
                    //add new socket to array of sockets
                    for (i = 0; i < USERS; i++)
                    {
                        //if position is empty
                        if (players[i].port == 0)
                        {
                            players[i].port = new_socket;
                            getLogin(buffer,i);
                            printf("Adding to list of sockets as %d\n", i); 
                            break;
                        }
                    }
                    if (playersCount>=2 && started == 0)
                    {
                        strcpy(answer,"3-enough players");
                        sendBroadcast(answer);
                    }
                    if (started == 1)
                        {
                            sprintf(round, "%d", roundNumber);
                            strcpy(answer, letters);
                            strcat(answer, round);
                            if (send(new_socket, answer, strlen(answer), 0) != strlen(answer))
                                perror("send");
                        }
                }
                else
                {
                    strcpy(answer,"5-Sorry, this game is full");
                    if (send(new_socket, answer, strlen(answer), 0) != strlen(answer))
                                perror("send");
                }
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            puts("Welcome message sent successfully");

           
        }

        //else its some IO operation on some other socket
        for (i = 0; i < USERS; i++)
        {
            sd = players[i].port;

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
                    players[i].port = 0;
                    players[i].points = 0;
                    memset(players[i].login, 0, 20);
                    playersCount--;
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
                        started = 1;
                        sprintf(round, "%d", roundNumber);
                        strcpy(answer, letters);
                        strcat(answer, round);
                        sendBroadcast(answer);
                        pthread_create(&tid, NULL, countTime, (void *)&tid);
                        break;
                    case '2':
                        sendResult(result, buffer, letters, i);
                        if (players[i].points>=5)
                        {
                            strcpy(answer,"4-Game won by ");
                            strcat(answer,players[i].login);
                            sendBroadcast(answer);
                            started = 0;
                            deleteData(started);
                        }
                        else 
                        {
                            strcpy(answer, result);
                            if (send(players[i].port, answer, strlen(answer), 0) != strlen(answer))
                                perror("send");
                        }
                        break;
                    }
                    
                }
            }
        }
    }

    return 0;
}
