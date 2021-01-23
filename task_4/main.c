#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_LENGTH 40
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define HOME 71
#define END 79
#define ENTER 13

typedef enum {True, False} boolean_t;


/* check if char. is alphabetical character */
boolean_t isalphab(char c);
/*
 * shift text starting from current pointer address
 * to the right and return the new end pointer address
 */
void shiftText(char * currPtr, char * endPtr);
/* Display current text to the console */
void displayLineEditor(char * startPtr, char * currPtr, char * endPtr);

int main()
{
    /* variable for holding input key stroke char */
    char ch = 0;
    char text[MAX_LENGTH] = {0};
    /* start_ptr is a pointer to the first char in the text */
    char * start_ptr = &text[0];
    /* start_ptr is a pointer to the last char in the text */
    char * end_ptr = &text[0];
    /* current_ptr is a pointer to curser('_') in the text */
    char * current_ptr = &text[0];
    /* accept key strokes until text length reach 40 characters ,ESC key is pressed or ENTER key is pressed */
    while (((end_ptr - start_ptr) < MAX_LENGTH) && (ch != ESC) && (ch != ENTER))
    {
        ch = getch();
        /* check if key stroke is an extended key */
        if (ch == 0 || ch == -32)
        {
            ch = getch();
            /* chick if current pointer is not at the end of the text when right key is pressed */
            if ((ch == RIGHT) && (current_ptr != end_ptr))
            {
                /* move the current pointer to the right */
                current_ptr++;
            }
            /* chick if current pointer is not at the start of the text when left key is pressed */
            else if ((ch == LEFT) && (current_ptr != start_ptr))
            {
                /* move the current pointer to the left */
                current_ptr--;
            }
            else if (ch == HOME)
            {
                /* move the current pointer to the start of the text */
                current_ptr = start_ptr;
            }
            else if (ch == END)
            {
                /* move the current pointer to the end of the text */
                current_ptr = end_ptr;
            }
        }
        /* check if alphabetical character is pressed */
        else if (isalphab(ch) == True)
        {
            /* check if the current pointer at the end of the text */
            if (current_ptr == end_ptr)
            {
                /* put the character at the address of current pointer (the end of the text) */
                *(current_ptr) = ch;
                /* move the current pointer to the right */
                current_ptr++;
                /* move the end pointer to the right */
                end_ptr++;
            }
            else
            {
                /* shift characters from the current pointer location to the end of text to the right one character space */
                shiftText(current_ptr, end_ptr);
                /* put the character at the address of current pointer */
                *(current_ptr) = ch;
                /* move the end pointer to the right */
                end_ptr++;
            }
        }
        /* display the line editor to the console */
        displayLineEditor(start_ptr, current_ptr, end_ptr);
    }
    /* put null character at the end of the text */
    *(end_ptr) = '\0';
    printf("\n%s\n", text);

    return 0;
}

/* check if char. is alphabetical character */
boolean_t isalphab(char c)
{
    if (((c >= 'A') && (c <= 'Z'))
      ||((c >= 'a') && (c <= 'z')))
    {
        return True;
    }
    return False;
}

/*
 * shift text starting from current pointer address to the end pointer.
 */
void shiftText(char * currPtr, char * endPtr)
{
    for (int i = (endPtr - currPtr); i >= 0; i--)
    {
        *(currPtr + i + 1) = *(currPtr + i);
    }
}

/* Display current text to the console */
void displayLineEditor(char * startPtr, char * currPtr, char * endPtr)
{
    int textLength = endPtr - startPtr;
    system("cls");
    for (int i = 0; i <= textLength; i++)
    {
        if ((startPtr + i) != currPtr)
        {
            printf("%c", *(startPtr + i));
        }
        else
        {
            printf("_");
        }
    }
    printf("\n");
}
