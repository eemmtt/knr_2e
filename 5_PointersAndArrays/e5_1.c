#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
static char buf[BUFSIZE];  // buffer for ungetch
static int bufp = 0;       // next free position in buf

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        fprintf(stderr, "ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int getint(int *pn){
    /* getint: get next integer from input into *pn */
    
    int c, sign;

    /* skip white spaces */
    while (isspace(c = getch())); 

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        /* c is not a number or +/- op */
        ungetch(c);
        fprintf(stderr, "getint: input '%c' not a number or op\n", c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-'){
        c = getch();
    }
    for (*pn = 0; isdigit(c); c = getch()){
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF){
        ungetch(c);
    }
    return c;
}

int main(){
    int n = 0;
    int *pn = &n;
    getint(pn);
    printf("%d\n", n);
}