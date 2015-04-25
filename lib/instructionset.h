#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct opcode
{
    char code[10];
    char format[10];
};

typedef struct opcode opcode;

opcode opcodes[NOPCODES];

/* Prototypes */

void intialize_opcodes();
int search(char *code);
int validate_code(char *command);
int is_delimiter(char c);
char **tokenize(char *command);

/* End Prototypes */

void intialize_opcodes()
{
    FILE *fp = fopen("lib/instructions.txt", "r");
    int i = 0;
    while(fscanf(fp, "%s %s", opcodes[i].code, opcodes[i].format) != EOF)
    {
        i++;
    }
}

int search(char *code)
{
    int start = 0, end = NOPCODES, middle, cmp;

    while(start <= end)
    {
        middle = (start + end) / 2;
        cmp = strcmp(opcodes[middle].code, code);

        if(cmp == 0)
        {
            return middle;
        }
        if(cmp < 0)
        {
            start = middle + 1;
        }
        else
        {
            end = middle - 1;
        }
    }
    return -1;
}

int validate_code(char *command)
{
    char **tokens;
    int i=0, opcode_index;
    tokens = tokenize(command);
    opcode_index = search(tokens[0]);
    if(opcode_index == -1)
    {
        return -1;
    }
    opcode opcode_under_obs = opcodes[opcode_index];
    printf("Opcode : %s\nFormat : %s\n", opcode_under_obs.code, opcode_under_obs.format);
    return 0;
}

int is_delimiter(char c)
{
    char delimiters[10] = ", ()";
    int i = 0;
    while(delimiters[i])
    {
        if(c == delimiters[i])
            return 1;
        i++;
    }
    return 0;
}

char **tokenize(char *command)
{
    char **tokens = malloc(5 * sizeof(char *));
    char c = command[0];
    int i = 0, j = 0, k = 1;
    tokens[i] = malloc(10 * sizeof(char));
    while(c != 0)
    {
        if(is_delimiter(c))
        {
            tokens[i][j++] = 0;
            j = 0;
            i++;
            tokens[i] = malloc(10 * sizeof(char));
        }
        else
        {
            tokens[i][j++] = c;
        }
        c = command[k++];
    }
    return tokens;
}
