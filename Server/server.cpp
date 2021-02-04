#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#include <string>
#include <thread>
#include <ctime>

#define PORT 2000
#define MAX_SIZE 58110
#define USERS 10
#define END_POINTS 100

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
    int playersCount = 0;
} game;

struct Player
{
    char login[20];
    char opponentWords[MAX_SIZE][100];
    int fd = 0;
    int points = 0;
    int oppCount = 0;
} players[USERS];

void getDictionary()
{
    int count = 0;
    FILE *fp = fopen("dictionary.txt", "r");

    char line[100];
    if(fp == NULL)
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
    for (int i = 2; i < j; i++)
        if(x == game.letters[i])
            count++;
    if(count >= 2)
        return false;
    return true;
}

void generateLetters()
{
    srand(time(NULL));
    int vowels = 0, i, ascii;
    game.letters[0] = '1';
    game.letters[1] = '-';
    while (vowels < 5)
    {
        do
        {
            ascii = 97 + rand() % 26;
        } while ((ascii != 97 and ascii != 101 and ascii != 105 and ascii != 111 and ascii != 117 and ascii != 121) or !canAdd((char)ascii, vowels));
        game.letters[vowels + 2] = (char)ascii;
        vowels++;
    }
    i = vowels + 2;
    while (i < 17)
    {
        ascii = 97 + rand() % 26;
        if(canAdd((char)ascii, i))
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
    for (i = message + 2; *i; i++)
    {
        check = 0;
        for (j = list + 2; *j; j++)
            if(*i != '*' && *i == *j)
            {
                check = 1;
                *j = '*';
                break;
            }
        if(check == 0)
            return false;
    }
    return true;
}

bool checkDictionary(char *message)
{
    char *ptr = &message[2];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if(!strcmp(ptr, game.dictionary[i]))
            return true;
    }
    return false;
}

bool checkBase(char *message)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if(!strcmp(message, game.base[i]))
            return true;
    }
    return false;
}

void sendAnswer(char *answer, int fd)
{
    int messageSize, tempSize;
    clock_t begin;
    if ((unsigned)(messageSize = send(fd, answer, strlen(answer), MSG_DONTWAIT)) != strlen(answer))
    {
        begin = clock();
        while((unsigned)messageSize != strlen(answer))
        {
            char *temp = &answer[messageSize];
            if((unsigned)(tempSize = send(fd, temp, strlen(temp), MSG_DONTWAIT)) != (strlen(answer)-messageSize))
            {
                messageSize += tempSize;
                begin = clock();
            }
            if((clock()-begin)/CLOCKS_PER_SEC > 5)
            {
                perror("send failed");
                break;
            }
        }
    }
}

void sendBroadcast(char *answer)
{
    for (int i = 0; i < USERS; i++)
        if(players[i].fd != 0)
            sendAnswer(answer,players[i].fd);
}

void sendResult(char *answer, char *message, int who)
{
    char temp[5];
    char *ptr = &message[2];
    printf("Player %s %d suggested word %s\n", players[who].login, players[who].fd, ptr);
    int len = static_cast<int>(strlen(message)) - 2;
    if(len < 3)
        strcpy(answer, "2-This word is too short.");
    else if(!checkWord(message))
        strcpy(answer, "2-This word cannot be made from the given letters.");
    else if(!checkDictionary(message))
        strcpy(answer, "2-Such a word does not exist.");
    else if(checkBase(message))
        strcpy(answer, "2-This word has already been given.");
    else
    {
        players[who].points += strlen(message) - 2;
        strcpy(answer, "2-You entered the correct word, congratulations!.");
        strcpy(game.base[game.baseSize], message);
        game.baseSize++;
        for (int i = 0; i < USERS; i++)
            if(i != who && players[i].fd != 0)
            {
                strcpy(players[i].opponentWords[players[i].oppCount], ptr);
                strcpy(game.words[game.wordCount], ptr);
                game.wordCount++;
                players[i].oppCount++;
            }
    }
    sprintf(temp, "%d", players[who].points);
    strcat(answer, temp);
}

void getLogin(char *message, int number)
{
    char *ptr = &message[2];
    strcpy(players[number].login, ptr);
}

void deleteData()
{
    for (int i = 0; i < USERS; i++)
    {
        if(game.started == 0)
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
    players[who].fd = 0;
    players[who].points = 0;
    players[who].oppCount = 0;
    memset(players[who].login, 0, 20);
    memset(players[who].opponentWords, 0, sizeof(players[who].opponentWords[0][0]) * MAX_SIZE * 100);
}

void gameEnd(char *answer, int who)
{
    strcpy(answer, "4-Game won by ");
    strcat(answer, players[who].login);
    sendBroadcast(answer);
}

void sendData(int who)
{
    char temp[5], answer[50];
    sprintf(temp, "%d", game.roundNumber);
    strcpy(answer, game.letters);
    strcat(answer, temp);
    strcpy(temp, "!");
    strcat(answer, temp);
    sprintf(temp, "%d", players[who].points);
    strcat(answer, temp);
    sendAnswer(answer,players[who].fd);
}

void startRound()
{
    char temp[5], answer[50], message[50];
    game.started = 1;
    printf("Round %d started\n", game.roundNumber);
    sprintf(temp, "%d", game.roundNumber);
    strcpy(message, game.letters);
    strcat(message, temp);
    strcpy(temp, "!");
    strcat(message, temp);
    for (int i = 0; i < USERS; i++)
        if(players[i].fd != 0)
        {
            strcpy(answer, message);
            sprintf(temp, "%d", players[i].points);
            strcat(answer, temp);
            sendAnswer(answer, players[i].fd);
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
    char sign[3] = ", ", answer[50];
    printf("Round %d ended\n", game.roundNumber);
    for (int i = 0; i < USERS; i++)
    {
        strcpy(answer, "4-Opponents\' words: ");
        if(players[i].fd != 0)
        {
            for (int j = 0; j < players[i].oppCount; j++)
            {
                strcat(answer, players[i].opponentWords[j]);
                strcat(answer, sign);
            }
            answer[strlen(answer) - 2] = '\0';
            if(players[i].oppCount == 0)
                strcpy(answer, "4-None of the players have found different words");
            sendAnswer(answer, players[i].fd);
        }
    }
    deleteData();
}

int waitTime()
{
    int max = players[0].oppCount;
    for (int i = 1; i < USERS; i++)
        if(max < players[i].oppCount)
            max = players[i].oppCount;
    return max + 5;
}

void countTime()
{
    int warning = 0, timer = 60;
    char answer[50];
    while (true)
        if(game.started == 1)
        {
            timer--;
            if(timer < 0)
            {
                endRound();
                sleep(waitTime());
                nextRound();
                timer = 60;
                warning = 0;
            }
            if(timer < 10 && warning == 0)
            {
                strcpy(answer, "2-10 seconds remaining.");
                sendBroadcast(answer);
                warning = 1;
            }
            sleep(1);
        }
}

int main(int argc, char *argv[])
{
    constexpr const int one = 1;
    int fd, fail, clientFd, messageSize, tempSize, max, newPlayer, correct;
    char message[1025], tempMessage[1025], answer[50];
    clock_t begin;
    std::thread t(countTime);
    fd_set fds;
    sockaddr_in myAddr {};

    getDictionary();

    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = INADDR_ANY;
    myAddr.sin_port = htons(PORT);

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket failed");
        return 1;
    }

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    fail = bind(fd, (sockaddr*) &myAddr, sizeof(myAddr));
    if(fail)
    {
        perror("bind failed");
        return 1;
    }

    fail = listen(fd, 3);
    if(fail)
    {
        perror("listen failed");
        return 1;
    }

    printf("Waiting for players\n");
    while (true)
    {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        max = fd;

        for (int i = 0; i < USERS; i++)
        {
            if(players[i].fd > 0)
                FD_SET(players[i].fd, &fds);

            if(players[i].fd > max)
                max = players[i].fd;
        }

        if((select(max + 1, &fds, NULL, NULL, NULL) < 0) && (errno != EINTR))
            printf("select");

        if(FD_ISSET(fd, &fds))
        {
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            clientFd = accept(fd, (sockaddr*) &clientAddr, &clientAddrLen);
            if(clientFd == -1)
            {
                perror("accept failed");
                return 1;
            }
            if((messageSize = recv(clientFd, message, 1024, 0)) > 0)
            {
                begin = clock();
                correct = 1;
                while (messageSize < 1024)
                {
                    if((tempSize = recv(clientFd, tempMessage, 1024-messageSize, MSG_DONTWAIT)) < 1024-messageSize)
                    {
                        messageSize += tempSize;
                        strcat(message,tempMessage);
                        begin = clock();
                    }
                    if((clock()-begin)/CLOCKS_PER_SEC > 5)
                    {
                        correct = 0;
                        break;
                    }
                }
                if (correct == 1)
                {
                    if(game.playersCount < USERS)
                    {
                        game.playersCount++;
                        for (int i = 0; i < USERS; i++)
                        {
                            if(players[i].fd == 0)
                            {
                                newPlayer = i;
                                players[i].fd = clientFd;
                                getLogin(message, i);
                                printf("New player named %s %d joined the game\n", players[i].login, players[i].fd);
                                for (int j = 0; j < game.wordCount; j++)
                                {
                                    strcpy(players[i].opponentWords[players[i].oppCount], game.words[j]);
                                    players[i].oppCount++;
                                }
                                break;
                            }
                        }
                        if(game.playersCount >= 2 && game.started == 0)
                        {
                            strcpy(answer, "3-enough players");
                            sendBroadcast(answer);
                        }
                        if(game.started == 1)
                            sendData(newPlayer);
                    }
                    else
                    {
                        strcpy(answer, "5-");
                        sendAnswer(answer,clientFd);
                    }
                }
            }
        }

        for (int i = 0; i < USERS; i++)
            if(FD_ISSET(players[i].fd, &fds))
            {
                if((messageSize =recv(players[i].fd, message, 1024, MSG_DONTWAIT)) <= 0)
                {
                    printf("Player named %s %d left the game\n", players[i].login, players[i].fd);
                    close(players[i].fd);
                    deletePlayer(i);
                    game.playersCount--;
                    if(game.playersCount == 0)
                    {
                        game.started = 0;
                        deleteData();
                    }
                }
                else
                {
                    begin = clock();
                    correct = 1;
                    while (messageSize < 1024)
                    {
                        if((tempSize = recv(clientFd, tempMessage, 1, MSG_DONTWAIT)) < 1)
                        {
                            messageSize += tempSize;
                            strcat(message,tempMessage);
                            begin = clock();
                        }
                        if((clock()-begin)/CLOCKS_PER_SEC > 5)
                        {
                            correct = 0;
                            break;
                        }
                    }
                    if (correct == 1)
                    {
                        switch (message[0])
                        {
                            case '1':
                                game.roundNumber = 1;
                                generateLetters();
                                startRound();
                                break;
                            case '2':
                                sendResult(answer, message, i);
                                if(players[i].points >= END_POINTS)
                                {
                                    gameEnd(answer, i);
                                    game.started = 0;
                                    deleteData();
                                }
                                else
                                    sendAnswer(answer,players[i].fd);
                                break;
                        }
                    }
                    else
                    {
                        printf("Player named %s %d left the game\n", players[i].login,players[i].fd);
                        close(players[i].fd);
                        deletePlayer(i);
                        game.playersCount--;
                        if(game.playersCount == 0)
                        {
                            game.started = 0;
                            deleteData();
                        }
                    }
                }
            }
    }
    close(fd);
    return 0;
}
