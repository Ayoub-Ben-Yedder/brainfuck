#include <stdio.h>

#define MAX_CELLS 30000
#define MAX_FILE_LENGTH 300000

FILE *fptr;
char content[MAX_FILE_LENGTH];
int len;

int cells[MAX_CELLS] = {0};
int data_pointer = 0;

int loop_stack[MAX_CELLS] = {0};
int stack_pointer = -1;


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: Invalid argument.\n");
        fprintf(stderr, "USAGE: brainfk <input-file-path>\n");
        return 1;
    }

    if (!(fptr = fopen(argv[1], "r")))
    {
        fprintf(stderr, "ERROR: Cannot open file %s.\n", argv[1]);
        return 1;
    }
    len = fread(content, 1, MAX_FILE_LENGTH, fptr);
    fclose(fptr);

    for (int i = 0; i < len; i++){
        switch (content[i]){
        case '>':
            data_pointer++;
            break;
        case '<':
            data_pointer--;
            break;
        case '+':
            cells[data_pointer]++;
            break;
        case '-':
            cells[data_pointer]--;
            break;
        case '.':
            printf("%c", (char)cells[data_pointer]);
            break;
        case ',':
            scanf("%c", (char *)&cells[data_pointer]);
            break;
        case '[':
            if (cells[data_pointer])
                loop_stack[++stack_pointer] = i;
            else
            {
                int brackets = 1;
                while (brackets > 0)
                {
                    i++;
                    if (content[i] == '[')
                        brackets++;
                    else if (content[i] == ']')
                        brackets--;
                }
            }
            break;
        case ']':
            if (cells[data_pointer])
                i = loop_stack[stack_pointer];
            else
                stack_pointer--;
            break;
        default:
            break;
        }
    }
    return 0;
}
