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

#define PORT 2000
#define MAX_SIZE 58110
#define USERS 1

struct Game
{
    char dictionary[MAX_SIZE][100];
    char base[MAX_SIZE][100];
    char words[MAX_SIZE][100];
    char letters[25];
    int baseSize = 0;
    int started = 0;
    int roundNumber = 1;
    int wordCount = 0;
}game;

struct Player
{
    char login[20];
    int port = 0;
    int points = 0;
    char opponentWords[MAX_SIZE][100];
    int oppCount = 0;
}players[USERS];

void getDictionary()
{
    int count = 0;
    FILE *fp = fopen("dictionary.txt", "r");

    char line[100];
    if (fp == NULL)
    {
        perror("Error opening file");
    }
    while (fgets(line, 100, fp) != NULL)
    {
        strcpy(game.dictionary[count], line);
        game.dictionary[count][strlen(game.dictionary[count]) - 2] = '\0';
        count++;
    }
    fclose(fp);
}

bool canAdd(char x, int j)
{
    int count = 0;
    for (int i=2;i<j;i++)
        if (x == game.letters[i])
            count++;
    if (count>=2)
        return false;
    return true;
}

void generateLetters()
{
    srand(time(NULL));
    int vowels = 0, i, ascii;
    game.letters[0] = '1';
    game.letters[1] = '-';
    while(vowels<5)
    {
        do{
        ascii = 97 + rand() % 26;
        }
        while((ascii!=97 and ascii!=101 and ascii!=105 and ascii!=111 and ascii!=117 and ascii!=121) or !canAdd((char)ascii,vowels));
        game.letters[vowels+2] = (char)ascii;
        vowels++;
    }
    i = vowels+2;
    while (i<17)
    {
        ascii = 97 + rand() % 26;
        if (canAdd((char)ascii,i))
            {
                game.letters[i] = (char)ascii;
                i++;
            }
    }
    game.letters[17] = '!';
    game.letters[18] = '\0';
}

bool checkWord(char *message)
{
    int check = 0;
    char list[20];
    strcpy(list, game.letters);
    char *i, *j;
    for(i=message+2;*i;i++)
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

bool checkDictionary(char *message)
{
    char *ptr = &message[2];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (!strcmp(ptr, game.dictionary[i]))
            return true;
    }
    return false;
}

bool checkBase(char *message)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (!strcmp(message, game.base[i]))
            return true;
    }
    return false;
}

void sendBroadcast(char *answer)
{
    for (int i=0;i<USERS;i++)
        if (players[i].port!=0)
            if ((unsigned)send(players[i].port, answer, strlen(answer), 0) != strlen(answer))
                perror("send");         
}

void sendResult(char *result, char *message, int who)
{
    char temp[5];
    char *ptr = &message[2];
    int len = static_cast<int>(strlen(message)) - 2;
    if (len < 3)
        strcpy(result, "2-This word is too short.");
    else if (!checkWord(message))
        strcpy(result, "2-This word cannot be made from the given letters.");
    else if (!checkDictionary(message))
        strcpy(result, "2-Such a word does not exist.");
    else if (checkBase(message))
        strcpy(result, "2-This word has already been given.");
    else
    {
        players[who].points += strlen(message) - 2;
        strcpy(result, "2-You entered the correct word, congratulations!.");
        strcpy(game.base[game.baseSize], message);
        game.baseSize++;
        for (int i=0;i<USERS;i++)
            if(i!=who && players[i].port != 0)
            {
                strcpy(players[i].opponentWords[players[i].oppCount],ptr);
                strcpy(game.words[game.wordCount],ptr);
                game.wordCount++;
                players[i].oppCount++;
            }
    }
    sprintf(temp, "%d", players[who].points);
    strcat(result, temp);
}

void getLogin(char *message, int number)
{
    char *ptr = &message[2];
    strcpy(players[number].login,ptr);
}

void deleteData()
{
    for (int i=0;i<USERS;i++)
        {
            if (game.started == 0)
                players[i].points = 0;
            memset(players[i].opponentWords, 0, sizeof(players[i].opponentWords[0][0]) * MAX_SIZE * 100);
            players[i].oppCount = 0;
        }
    memset(game.base, 0, sizeof(game.base[0][0]) * MAX_SIZE * 100);
    memset(game.words, 0, sizeof(game.words[0][0]) * MAX_SIZE * 100);
    game.wordCount = 0;
}

void deletePlayer(int who)
{
    players[who].port = 0;
    players[who].points = 0;
    players[who].oppCount = 0;
    memset(players[who].login, 0, 20);
    memset(players[who].opponentWords, 0, sizeof(players[who].opponentWords[0][0]) * MAX_SIZE * 100);
}

void gameEnd(char *answer, int who)
{
    strcpy(answer,"4-Game won by ");
    strcat(answer,players[who].login);
    sendBroadcast(answer);
}

void sendData(int who)
{
    char temp[5], answer[50];
    game.started = 1;
    sprintf(temp, "%d", game.roundNumber);
    strcpy(answer, game.letters);
    strcat(answer, temp);
    strcpy(temp,"!");
    strcat(answer,temp);
    sprintf(temp, "%d", players[who].points);
    strcat(answer,temp);
    if ((unsigned)send(players[who].port, answer, strlen(answer), 0) != strlen(answer))
        perror("send");
}

void startRound()
{
    char temp[5], answer[50], message[50];
    game.started = 1;
    sprintf(temp, "%d", game.roundNumber);
    strcpy(message, game.letters);
    strcat(message, temp);
    strcpy(temp,"!");
    strcat(message,temp);
    for (int i=0;i<USERS;i++)
        if (players[i].port!=0)
        {
            strcpy(answer,message);
            sprintf(temp, "%d", players[i].points);
            strcat(answer,temp);
            if ((unsigned)send(players[i].port, answer, strlen(answer), 0) != strlen(answer))
                perror("send");
        }
}

void nextRound()
{
    char round[10];
    game.roundNumber++;
    sprintf(round, "%d", game.roundNumber);
    generateLetters();
    startRound();
}

void endRound()
{
    char sign[3] = ", ", answer[100];
    for (int i=0;i<USERS;i++)
    {
        strcpy(answer,"4-Opponents\' words: ");
        if (players[i].port!=0)
        {
            for (int j=0;j<players[i].oppCount;j++)
                {
                    strcat(answer,players[i].opponentWords[j]);
                    strcat(answer,sign);
                }
            answer[strlen(answer)-2]='\0';
            if (players[i].oppCount == 0)
                strcpy(answer,"4-None of your opponents have found different words");
            if ((unsigned)send(players[i].port, answer, strlen(answer), 0) != strlen(answer))
                perror("send");
        }
    }
    deleteData();
}

int waitTime()
{
    int max = players[0].oppCount;
    for (int i=1;i<USERS;i++)   
        if (max<players[i].oppCount)
            max = players[i].oppCount;
    return max+5;
}


void* countTime(void *vargp) {
    int warning = 0, timer = 60;
    char answer[50];
    while (1) {
        printf("%d\n",timer);
        timer--;
        if (timer < 0 && game.started == 1)
        {
            endRound();
            sleep(waitTime());
            nextRound();
            timer = 60;
            warning = 0;
        }
        if (timer < 10 && warning == 0 && game.started == 1)
        {
            strcpy(answer, "2-10 seconds remaining.");
            sendBroadcast(answer);
            warning = 1;
        }
        if (game.started == 0)
            return NULL;
        sleep(1);
    };
}

int main(int argc, char *argv[])
{
    int opt = 1;
    int mainSocket, addrlen, new_socket, activity, i, valread, sd, newPlayer;
    int max_sd;
    int playersCount = 0;
    struct sockaddr_in address;
    pthread_t tid;

    char message[1025];
    char answer[50], result[50];

    getDictionary();
    //set of socket descriptors
    fd_set readfds;



    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < USERS; i++)
    {
        players[i].port = 0;
    }

    //create a master socket
    if ((mainSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if (setsockopt(mainSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
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
    if (bind(mainSocket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(mainSocket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while (true)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(mainSocket, &readfds);
        max_sd = mainSocket;

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
        if (FD_ISSET(mainSocket, &readfds))
        {
            if ((new_socket = accept(mainSocket, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            valread = read(new_socket, message, 1024);
            printf("%s\n", message);
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
                            newPlayer = i;
                            players[i].port = new_socket;
                            getLogin(message,i);
                            printf("Adding to list of sockets as %d\n", i); 
                            for (int j=0;j<game.wordCount;j++)
                                {
                                    strcpy(players[i].opponentWords[players[i].oppCount],game.words[j]);
                                    players[i].oppCount++;
                                }
                            break;
                        }
                    }
                    if (playersCount>=2 && game.started == 0)
                    {
                        strcpy(answer,"3-enough players");
                        sendBroadcast(answer);
                    }
                    if (game.started == 1)
                        sendData(newPlayer);

                }
                else
                {
                    strcpy(answer,"5-Sorry, this game is full");
                    if ((unsigned)send(new_socket, answer, strlen(answer), 0) != strlen(answer))
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
                if ((valread = read(sd, message, 1024)) <= 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close(sd);
                    deletePlayer(i);
                    playersCount--;
                    if (playersCount == 0)
                        {
                            game.started = 0;
                            deleteData();
                        }
                }

                //Echo back the message that came in
                else
                {
                    message[valread] = '\0';
                    printf("%s\n", message);
                    switch (message[0])
                    {
                    case '1':
                        game.roundNumber = 1;
                        generateLetters();
                        startRound();
                        pthread_create(&tid, NULL, countTime, (void *)&tid);
                        break;
                    case '2':
                        sendResult(result, message, i);
                        if (players[i].points>=20)
                        {
                            gameEnd(answer,i);
                            game.started = 0;
                            deleteData();
                        }
                        else 
                            if ((unsigned)send(players[i].port, result, strlen(result), 0) != strlen(result))
                                perror("send");
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
