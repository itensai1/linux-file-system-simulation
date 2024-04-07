#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHILDREN 100
#define CMDs 11
#define nullptr NULL

char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "touch", "rm", "reload", "save", "menu", "quit"};

struct NODE
{
    char name[64];
    char type;
    int childrenNum;
    struct NODE *children[MAX_CHILDREN], *parentPtr;
};

typedef struct NODE Node;

Node *mkNode(char *name, char t, Node *parent)
{
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->type = t;
    newNode->parentPtr = parent;
    newNode->childrenNum = 0;
    return newNode;
}

Node *root, *cwd, *tmp;

void initialize()
{
    root = mkNode("/", 'D', nullptr);
    cwd = root;
}

int findCmd(char *command)
{
    for (int i = 0; i < CMDs; ++i)
    {
        if (!strcmp(command, cmd[i]))
            return i;
    }
    return -1;
}

void mkdir(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *s = strtok(path, "/");
    char *base = s;
    while (s)
    {
        base = s;
        s = strtok(0, "/");
        if (s)
        {
            if (!strcmp("..", base))
            {
                if (tmp != root)
                    tmp = tmp->parentPtr;
            }
            else if (!strcmp(".", base))
            {
                goto nextToken;
            }
            else
            {
                for (int i = 0; i < tmp->childrenNum; ++i)
                {
                    if (!strcmp(tmp->children[i]->name, base))
                    {
                        if (tmp->children[i]->type == 'D')
                        {
                            tmp = tmp->children[i];
                            goto nextToken;
                        }
                        else if (tmp->children[i]->type == 'F')
                        {
                            printf("'%s' is not a directory\n", tmp->children[i]->name);
                            return;
                        }
                    }
                }
                printf("No such file or directory\n");
                return;
            }
        }
    nextToken:
    }
    if (base)
    {
        if (tmp->childrenNum == MAX_CHILDREN)
        {
            printf("Directory is Full!\n");
            return;
        }
        tmp->children[tmp->childrenNum] = mkNode(base, 'D', tmp);
        tmp->childrenNum++;
        printf("directory '%s' created!\n", base);
    }
    else
    {
        printf("'mkdir' needs a path!\n");
    }
}

void rmdir(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *s = strtok(path, "/");
    char *base = s;
    while (s)
    {
        base = s;
        s = strtok(0, "/");
        if (s)
        {
            if (!strcmp("..", base))
            {
                if (tmp != root)
                    tmp = tmp->parentPtr;
            }
            else if (!strcmp(".", base))
            {
                goto nextToken;
            }
            else
            {
                for (int i = 0; i < tmp->childrenNum; ++i)
                {
                    if (!strcmp(tmp->children[i]->name, base))
                    {
                        if (tmp->children[i]->type == 'D')
                        {
                            tmp = tmp->children[i];
                            goto nextToken;
                        }
                        else if (tmp->children[i]->type == 'F')
                        {
                            printf("'%s' is not a directory\n", tmp->children[i]->name);
                            return;
                        }
                    }
                }
                printf("No such file or directory\n");
                return;
            }
        }
    nextToken:
    }
    if (base)
    {
        int index = -1;
        for (int i = 0; i < tmp->childrenNum; ++i)
        {
            if (!strcmp(tmp->children[i]->name, base))
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            if (tmp->children[index]->type == 'F')
            {
                printf("NOT a directory\n");
                return;
            }
            else if (tmp->children[index]->childrenNum)
            {
                printf("Directory NOT empty!\n");
                return;
            }
            if (tmp->children[index] == cwd)
                cwd = tmp;
            tmp->children[index] = nullptr;
            for (int i = index + 1; i < tmp->childrenNum; ++i)
            {
                tmp->children[i - 1] = tmp->children[i];
            }
            tmp->childrenNum--;
            printf("Directory removed!\n");
        }
        else
            printf("No such directory\n");
    }
    else
    {
        printf("'rmdir' needs a path!\n");
    }
}

void touch(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *s = strtok(path, "/");
    char *base = s;
    while (s)
    {
        base = s;
        s = strtok(0, "/");
        if (s)
        {
            if (!strcmp("..", base))
            {
                if (tmp != root)
                    tmp = tmp->parentPtr;
            }
            else if (!strcmp(".", base))
            {
                goto nextToken;
            }
            else
            {
                for (int i = 0; i < tmp->childrenNum; ++i)
                {
                    if (!strcmp(tmp->children[i]->name, base))
                    {
                        if (tmp->children[i]->type == 'D')
                        {
                            tmp = tmp->children[i];
                            goto nextToken;
                        }
                        else if (tmp->children[i]->type == 'F')
                        {
                            printf("'%s' is not a directory\n", tmp->children[i]->name);
                            return;
                        }
                    }
                }
                printf("No such file or directory\n");
                return;
            }
        }
    nextToken:
    }
    if (base)
    {
        if (tmp->childrenNum == MAX_CHILDREN)
        {
            printf("This directory is Full!\n");
            return;
        }
        tmp->children[tmp->childrenNum] = mkNode(base, 'F', tmp);
        tmp->childrenNum++;
        printf("file '%s' created!\n", base);
    }
    else
    {
        printf("'touch' needs a path!");
    }
}

void rm(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *s = strtok(path, "/");
    char *base = s;
    while (s)
    {
        base = s;
        s = strtok(0, "/");
        if (s)
        {
            if (!strcmp("..", base))
            {
                if (tmp != root)
                    tmp = tmp->parentPtr;
            }
            else if (!strcmp(".", base))
            {
                goto nextToken;
            }
            else
            {
                for (int i = 0; i < tmp->childrenNum; ++i)
                {
                    if (!strcmp(tmp->children[i]->name, base))
                    {
                        if (tmp->children[i]->type == 'D')
                        {
                            tmp = tmp->children[i];
                            goto nextToken;
                        }
                        else if (tmp->children[i]->type == 'F')
                        {
                            printf("'%s' is not a directory\n", tmp->children[i]->name);
                            return;
                        }
                    }
                }
                printf("No such file or directory\n");
                return;
            }
        }
    nextToken:
    }
    if (base)
    {
        int index = -1;
        for (int i = 0; i < tmp->childrenNum; ++i)
        {
            if (!strcmp(tmp->children[i]->name, base))
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            if (tmp->children[index]->type == 'D')
            {
                printf("It's not a file\n");
                return;
            }
            tmp->children[index] = nullptr;
            for (int i = index + 1; i < tmp->childrenNum; ++i)
            {
                tmp->children[i - 1] = tmp->children[i];
            }
            tmp->childrenNum--;
            printf("file removed!\n");
        }
        else
            printf("No such file\n");
    }
    else
    {
        printf("'rm' needs a path!\n");
    }
}

void menu()
{
    char option[16];
    for (int i = 0; i < CMDs; ++i)
    {
        printf("- %s", cmd[i]);
        if (!strcmp(cmd[i], "save") || !strcmp(cmd[i], "reload"))
            strcpy(option, "filename");
        else if (!strcmp(cmd[i], "pwd") || !strcmp(cmd[i], "menu") || !strcmp(cmd[i], "quit"))
            strcpy(option, "");
        else
            strcpy(option, "path");
        printf(" %s\n", option);
    }
}

void cd(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *base = strtok(path, "/");
    if (!base)
    {
        cwd = root;
        return;
    }
    while (base)
    {
        if (!strcmp("..", base))
        {
            if (tmp != root)
                tmp = tmp->parentPtr;
        }
        else if (!strcmp(".", base))
        {
            goto nextToken;
        }
        else
        {
            for (int i = 0; i < tmp->childrenNum; ++i)
            {
                if (!strcmp(tmp->children[i]->name, base))
                {
                    if (tmp->children[i]->type == 'D')
                    {
                        tmp = tmp->children[i];
                        goto nextToken;
                    }
                    else if (tmp->children[i]->type == 'F')
                    {
                        printf("'%s' is not a directory\n", tmp->children[i]->name);
                        return;
                    }
                }
            }
            printf("No such directory\n");
            return;
        }
    nextToken:
        base = strtok(0, "/");
    }
    cwd = tmp;
}

void ls(char *path)
{
    tmp = cwd;
    if (path[0] == '/')
        tmp = root;
    char *base = strtok(path, "/");
    while (base)
    {
        if (!strcmp("..", base))
        {
            if (tmp != root)
                tmp = tmp->parentPtr;
        }
        else if (!strcmp(".", base))
        {
            goto nextToken;
        }
        else
        {
            for (int i = 0; i < tmp->childrenNum; ++i)
            {
                if (!strcmp(tmp->children[i]->name, base))
                {
                    if (tmp->children[i]->type == 'D')
                    {
                        tmp = tmp->children[i];
                        goto nextToken;
                    }
                    else if (tmp->children[i]->type == 'F')
                    {
                        printf("'%s' is not a directory\n", tmp->children[i]->name);
                        return;
                    }
                }
            }
            printf("No such directory\n");
            return;
        }
    nextToken:
        base = strtok(0, "/");
    }
    if (!tmp->childrenNum)
        printf("Empty directory..");
    for (int i = 0; i < tmp->childrenNum; ++i)
    {
        printf("[%c %s] ", tmp->children[i]->type, tmp->children[i]->name);
    }
    printf("\n");
}

void rec(Node *node)
{
    if (node == root)
        return;
    rec(node->parentPtr);
    printf("/%s", node->name);
}

void pwd()
{
    printf(">> ");
    if (cwd == root)
    {
        printf("/\n");
        return;
    }
    tmp = cwd;
    rec(tmp);
    printf("\n");
}

void traverseTree(Node *node, char *path, char **currentpath, int pathLength, FILE *file)
{
    if (node == nullptr)
        return;

    currentpath[pathLength] = node->name;
    pathLength++;

    strcpy(path, "");
    for (int i = (pathLength > 1); i < pathLength; i++)
    {
        if (pathLength > 1)
            strcat(path, "/");
        strcat(path, currentpath[i]);
    }
    fprintf(file, "%c \t %s\n", node->type, path);

    for (int i = 0; i < node->childrenNum; i++)
    {
        traverseTree(node->children[i], path, currentpath, pathLength, file);
    }
}

void save(char *fileName)
{

    FILE *myFile = fopen(fileName, "w+");
    if (!myFile)
    {
        printf("ERROR with filename\n");
        return;
    }
    char path[128] = "";
    char *currentpath[100];
    int pathLength = 0;
    fprintf(myFile, "type  path\n");
    fprintf(myFile, "----  ----\n");
    traverseTree(root, path, currentpath, pathLength, myFile);
    fclose(myFile);
    printf("File saved!\n");
}

void reload(char *fileName)
{

    FILE *myFile = fopen(fileName, "r+");
    if (!myFile)
    {
        printf("No such file\n");
        return;
    }

    char type[128], path[128];
    while (fscanf(myFile, "%s  %s\n", type, path) == 2)
    {
        if (strlen(type) == 1 && strlen(path) > 1)
        {
            if (type[0] == 'D')
                mkdir(path);
            else if (type[0] == 'F')
                touch(path);
        }
    }
    fclose(myFile);
    printf("Tree constructed!\n");
}

int main()
{

    initialize();

    char line[128], command[16], operand[64];
    int index;
    bool loop = 1;
    while (loop)
    {
        strcpy(operand, ""), strcpy(command, "");
        printf("input a command line: ");
        fgets(line, 128, stdin);
        line[strlen(line) - 1] = 0;
        sscanf(line, "%s %s", command, operand);
        index = findCmd(command);

        switch (index)
        {
        case 0:
            mkdir(operand);
            break;
        case 1:
            rmdir(operand);
            break;
        case 2:
            ls(operand);
            break;
        case 3:
            cd(operand);
            break;
        case 4:
            pwd();
            break;
        case 5:
            touch(operand);
            break;
        case 6:
            rm(operand);
            break;
        case 7:
            reload(operand);
            break;
        case 8:
            save(operand);
            break;
        case 9:
            menu();
            break;
        case 10:
            loop = 0;
            break;
        default:
            printf("invalid command %s\n", command);
        }
    }

    return 0;
}
