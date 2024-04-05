#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mystack.h"

int isCharStackEmpty(void);
int getPresidency(char);
int isNum(char);
int isOperator(char);
int isRightParantheses(char);
int isLeftParantheses(char);
void getExpVal(char);
void calc(char *);
double decimal(int);
int isLeftgreatRight(int, int);
int syntax_error(char *, int);
void vect(void);
void DotProd(void);
void CrossProd(void);
void VectAdd(void);
void VectSub(void);
void complex(void);
void cadd(void);
void csub(void);
void cpro(void);
void conjugate();
void cdivision();
void polar();
void matadd(float *, float *, int, int, int, int);
void matsub(float *, float *, int, int, int, int);
void matpro(float *, float *, int, int, int, int);
void matinv(float *, int, int);
float matdet(float *, int, int);
void getCofactor(float *, float *, int, int, int);

struct stack s;
struct stack_ch c;

struct complex
{
    float real;
    float imag;
} c1, c2;

struct vector
{
    float x;
    float y;
    float z;
} v1, v2;

char syner = 'n';
int leftParantheses = 0;
int rightParantheses = 0;

int main()
{
    float dp, cpx, cpy, cpz, vadx, vady, vadz, vsubx, vsuby, vsubz, mag;
    s.index = -1;
    c.index = -1;
    char str[200], vchoice, cchoice, mchoice;
    char prevchar;
    int mode, cch, mch, loop_break;
    int row1, col1, row2, col2, i, j;
    float *p = NULL;
    float *q = NULL;

    while (1)
    {
        printf("\n\n\tMENU");
        printf("\nEnter 1 for Computational");
        printf("\nEnter 2 for Vectors");
        printf("\nEnter 3 for Complex");
        printf("\nEnter 4 for Matrices");
        printf("\nEnter 5 to EXIT");
        printf("\n\nEnter your Choice : ");
        fflush(0);
        scanf(" %d", &mode);
        switch (mode)
        {
        case 1:
            printf("Enter expression : ");
            fflush(0);
            scanf(" %s", str);
            rightParantheses = 0;
            leftParantheses = 0;
            s.index = -1;
            c.index = -1;
            calc(str);
            if (rightParantheses != leftParantheses || syner == 'y')
            {
                printf("\t--SYNTAX ERROR--\n");
                break;
            }
            else
            {
                do
                {
                    if (isCharStackEmpty())
                    {
                        printf("\n\n%s = %lf", str, pop_val(&s));
                        break;
                    }
                    else
                    {
                        prevchar = pop_char(&c);
                        getExpVal(prevchar);
                    }
                } while (1);
            }
            break;
        case 2:
            printf("\n Enter x,y,z components of 1st vector:");
            scanf(" %f %f %f", &v1.x, &v1.y, &v1.z);
            while (1)
            {
                loop_break = 1;
                printf("Do you want to enter the 2nd vector(Y/N)\n");
                scanf(" %c", &vchoice);
                switch (vchoice)
                {
                case 'y':
                case 'Y':
                    vect();
                    break;
                case 'n':
                case 'N':
                    mag = sqrt(((v1.x) * (v1.x)) + ((v1.y) * (v1.y)) + ((v1.z) * (v1.z)));
                    printf("\n The magnitude is: %f", mag);
                    break;
                default:
                    loop_break = 0;
                    printf("Enter a Valid input\n");
                }
                if (loop_break == 1)
                    break;
            }
            break;
        case 3:
            printf("\n Enter real and imaginary parts of 1st complex number:");
            scanf(" %f %f", &c1.real, &c1.imag);
            while (1)
            {
                loop_break = 1;
                printf("\n Do you want to enter the 2nd Complex number?(Y/N)\n");
                scanf(" %c", &cchoice);
                switch (cchoice)
                {
                case 'y':
                case 'Y':
                    complex();
                    break;
                case 'n':
                case 'N':
                    printf("\n The conjugate is:");
                    conjugate(c1);
                    polar(c1);
                    break;
                default:
                    loop_break = 0;
                    printf("\n Enter valid input");
                }
                if (loop_break == 1)
                    break;
            }
            break;
        case 4:
            printf("\n Enter dimensions of 1st matrix(row col):");
            scanf(" %d %d", &row1, &col1);
            p = (float *)malloc((row1) * (col1) * (sizeof(float)));
            for (i = 0; i < row1; i++)
            {
                for (j = 0; j < col1; j++)
                {
                    printf("\np[%d][%d] = ", i + 1, j + 1);
                    scanf(" %f", (p + i * col1) + j);
                }
            }
            for (i = 0; i < row1; i++)
            {
                for (j = 0; j < col1; j++)
                {
                    printf(" %f", *((p + i * col1) + j));
                }
                printf("\n");
            }
            printf("\n Do you want to continue?(Y/N)\n");
            scanf(" %c", &mchoice);
            switch (mchoice)
            {
            case 'y':
            case 'Y':
                printf("\n Enter dimensions of 2nd matrix(row col):");
                scanf(" %d %d", &row2, &col2);
                q = (float *)malloc((row2) * (col2) * (sizeof(float)));
                for (i = 0; i < row1; i++)
                {
                    for (j = 0; j < col2; j++)
                    {
                        printf("\nq[%d][%d] = ", i + 1, j + 1);
                        scanf(" %f", (q + i * col2) + j);
                    }
                }
                for (i = 0; i < row2; i++)
                {
                    for (j = 0; j < col2; j++)
                    {
                        printf(" %f", *((q + i * col2) + j));
                    }
                    printf("\n");
                }
                printf("\n Enter 1 for addition");
                printf("\n Enter 2 for subtraction");
                printf("\n Enter 3 for multiplication");
                printf("\n Enter your choice:");
                scanf(" %d", &mch);
                switch (mch)
                {
                case 1:
                    matadd((float *)p, (float *)q, row1, col1, row2, col2);
                    break;
                case 2:
                    matsub((float *)p, (float *)q, row1, col1, row2, col2);
                    break;
                case 3:
                    matpro((float *)p, (float *)q, row1, col1, row2, col2);
                    break;
                }
                free(q);
                q = NULL;
                break;
            case 'n':
            case 'N':
                printf("\n Inverse of the matrix is:");
                matinv((float *)p, row1, col1);
                printf("\n Determinant of the matrix is: %f", matdet((float *)p, row1, col1));
                break;
            }
            free(p);
            p = NULL;
            break;
        case 5:
            return 0;
        }
    }
}

void calc(char *str)
{
    int j = 0;
    int k = 0;
    int t = 0;
    char temp[10];
    char prevchar;
    if (str[0] == '-')
    {
        push_val(0, &s);
    }
    for (; str[j] != '\0'; j++)
    {
        if (isNum(str[j]))
        {
            if (isNum(str[j + 1]))
            {
                for (k = j, t = 0; isNum(str[k]); k++, t++)
                {
                    temp[t] = str[k];
                }
                temp[t] = '\0';
                j = k - 1;
                push_val((double)atoi(temp), &s);
            }
            else
            {
                push_val((double)(str[j] - 48), &s);
            }
        }
        else if (str[j] == '.')
        {
            j++;
            if (syntax_error(str, j))
                return;
            if (isNum(str[j]))
            {
                if (isNum(str[j + 1]))
                {
                    for (k = j, t = 0; isNum(str[k]); k++, t++)
                    {
                        temp[t] = str[k];
                    }
                    temp[t] = '\0';
                    j = k - 1;
                    push_val(pop_val(&s) + decimal(atoi(temp)), &s);
                }
                else
                {
                    push_val(pop_val(&s) + (double)(str[j] - 48) / 10.000000, &s);
                }
            }
        }
        else
        {
            if (syntax_error(str, j))
                return;
            if (str[j] == '(')
                leftParantheses++;
            if (str[j] == ')')
                rightParantheses++;
            if (isCharStackEmpty())
            {
                push_char(str[j], &c);
            }
            else
            {
                prevchar = pop_char(&c);
                if (getPresidency(str[j]) == 4)
                {
                    push_char(prevchar, &c);
                    if (str[j] == '(')
                    {
                        if (str[j + 1] == '-')
                            push_val(0, &s);
                        push_char('(', &c);
                    }
                    else
                    {
                        if (leftParantheses >= rightParantheses)
                        {
                            do
                            {
                                prevchar = pop_char(&c);
                                if (prevchar == '(')
                                    break;
                                getExpVal(prevchar);
                            } while (1);
                        }
                        else
                        {
                            syner = 'y';
                            return;
                        }
                    }
                }
                else if (getPresidency(str[j]) < getPresidency(prevchar))
                {
                    push_char(prevchar, &c);
                    push_char(str[j], &c);
                }
                else
                {
                    getExpVal(prevchar);
                    push_char(str[j], &c);
                }
            }
        }
    }
    j = 0, k = 0;
}

int getPresidency(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 3;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 4;
    }
}

int isNum(char ch)
{
    if (ch >= '0' && ch <= '9')
        return 1;
    else
        return 0;
}

int isCharStackEmpty()
{
    if (c.index == -1)
        return 1;
    else
        return 0;
}

void getExpVal(char ch)
{
    double x = pop_val(&s);
    double y = pop_val(&s);
    double ret = 0;
    switch (ch)
    {
    case '+':
        ret = y + x;
        break;
    case '-':
        ret = y - x;
        break;
    case '*':
        ret = y * x;
        break;
    case '/':
        ret = y / x;
        break;
    }
    push_val(ret, &s);
    return;
}

double decimal(int temp)
{
    double dec;
    for (dec = (double)temp / 10; temp /= 10;)
        dec = dec / 10;
    return dec;
}

int isOperator(char p)
{
    if (p == '+' || p == '-' || p == '*' || p == '/')
        return 1;
    else
        return 0;
}

int isRightParantheses(char ch)
{
    if (ch == ')')
        return 1;
    else
        return 0;
}

int isLeftParantheses(char ch)
{
    if (ch == '(')
        return 1;
    else
        return 0;
}

int isLeftgreatRight(int LP, int RP)
{
    if (LP >= RP)
        return 1;
    else
        return 0;
}

int syntax_error(char *str, int j)
{
    if (!isLeftgreatRight || (str[0] == ')' || str[0] == '+' || str[0] == '/' || str[0] == '*') || !(isOperator(str[j]) || isRightParantheses(str[j]) || isLeftParantheses(str[j]) || str[j] != '.'))
    {
        syner = 'y';
        return 1;
    }
    else if (isLeftParantheses(str[j]) && (isNum(str[j - 1]) || str[j + 1] == '+' || str[j + 1] == '*' || str[j + 1] == '/'))
    {
        syner = 'y';
        return 1;
    }
    else if (isOperator(str[j]) && (isOperator(str[j + 1]) || isRightParantheses(str[j + 1])))
    {
        syner = 'y';
        return 1;
    }
    else if (str[j] == '.' && ((!isNum(str[j + 1])) || (!isNum(str[j - 1]))))
    {
        syner = 'y';
        return 1;
    }
    else
        syner = 'n';
    return 0;
}

void vect()
{
    int vch, brk;
    while (1)
    {
        printf("\n Enter x,y,z components of 2nd vector:");
        scanf(" %f %f %f", &v2.x, &v2.y, &v2.z);
        printf("\n\tVectors MENU");
        printf("\n Enter 1 for Dot Product");
        printf("\n Enter 2 for Cross Product");
        printf("\n Enter 3 for Addition");
        printf("\n Enter 4 for Subtraction");
        printf("\n Enter 5 to EXIT MODE");
        printf("\n Enter your choice:");
        scanf(" %d", &vch);
        switch (vch)
        {
        case 1:
            printf("\n V1 . V2 =");
            DotProd();
            break;
        case 2:
            printf("\n V1 x V2 =");
            CrossProd();
            break;
        case 3:
            printf("\n V1 + V2 =");
            VectAdd();
            break;
        case 4:
            printf("\n V1 - V2 =");
            VectSub();
            break;
        case 5:
            return;
        default:
            brk = 0;
            printf(" Invalid Input , Try again\n");
        }
        if (brk == 1)
            break;
    }
}

void DotProd()
{
    float dp;
    dp = ((v1.x) * (v2.x)) + ((v1.y) * (v2.y)) + ((v1.z) * (v2.z));
    printf(" %f", dp);
}

void CrossProd()
{
    float cpx, cpy, cpz;
    cpx = ((v1.y) * (v2.z)) - ((v2.y) * (v1.z));
    cpy = ((v1.z) * (v2.x)) - ((v2.z) * (v1.x));
    cpz = ((v1.x) * (v2.y)) - ((v1.y) * (v2.x));
    printf(" (%f)i+(%f)j+(%f)k", cpx, cpy, cpz);
}

void VectAdd()
{
    float vadx, vady, vadz;
    vadx = (v1.x) + (v2.x);
    vady = (v1.y) + (v2.y);
    vadz = (v1.z) + (v2.z);
    printf(" (%f)i+(%f)j+(%f)k", vadx, vady, vadz);
}

void VectSub()
{
    float vsubx, vsuby, vsubz;
    vsubx = (v1.x) - (v2.x);
    vsuby = (v1.y) - (v2.y);
    vsubz = (v1.z) - (v2.z);
    printf(" (%f)i+(%f)j+(%f)k", vsubx, vsuby, vsubz);
}

void complex(void)
{
    int cch, brk;
    while (1)
    {
        printf("\n Enter real and imaginary parts of 2nd complex number:");
        scanf(" %f %f", &c2.real, &c2.imag);
        printf("\n\tComplex MENU");
        printf("\n Enter 1 for addition");
        printf("\n Enter 2 for subtraction");
        printf("\n Enter 3 for multiplication");
        printf("\n Enter 4 for division");
        printf("\n Enter 5 to EXIT MODE");
        printf("\n Enter your choice:");
        scanf(" %d", &cch);
        switch (cch)
        {
        case 1:
            cadd();
            break;
        case 2:
            csub();
            break;
        case 3:
            cpro();
            break;
        case 4:
            cdivision();
            break;
        case 5:
            return;
        default:
            brk = 0;
            printf(" Invalid Input , Try again\n");
        }
        if (brk == 1)
            break;
    }
}

void cadd()
{
    float cadr, cadi;
    cadr = (c1.real) + (c2.real);
    cadi = (c1.imag) + (c2.imag);
    printf("\n Real and imaginary parts are %f %f:", cadr, cadi);
}
void csub()
{
    float csubr, csubi;
    csubr = (c1.real) - (c2.real);
    csubi = (c1.imag) - (c2.imag);
    printf("\n The real and imaginary parts are %f %f ", csubr, csubi);
}
void cpro()
{
    float cpror, cproi;
    cpror = ((c1.real) * (c2.real)) - ((c1.imag) * (c2.imag));
    cproi = ((c1.imag) * (c2.real)) + ((c1.real) * (c2.imag));
    printf("\n The real and imaginary parts are %f %f", cpror, cproi);
}
void conjugate()
{
    printf(" The real and imaginary parts are %f %f", (c1.real), ((-1) * (c1.imag)));
}
void cdivision()
{
    float cdivr, cdivi, magi;
    magi = ((c2.real) * (c2.real)) + ((c2.imag) * (c2.imag));
    cdivr = (((c1.real) * (c2.real)) + ((c1.imag) * (c2.imag))) / magi;
    cdivi = (((c1.imag) * (c2.real)) - ((c1.real) * (c2.imag)));
    printf("\n The real and imaginary parts are %f %f", cdivr, cdivi);
}
void polar()
{
    float r, angle, mgn;
    mgn = ((c1.real) * (c1.real)) + ((c1.imag) * (c1.imag));
    r = sqrt(mgn);
    angle = atan((c1.imag) / (c1.real));
    printf("\n The Polar form is: %f<%f", r, angle);
}
void matadd(float *o, float *u, int p1, int q1, int p2, int q2)
{
    int x, y;
    if ((p1 == p2) && (q1 == q2))
    {
        for (x = 0; x < p1; x++)
        {
            for (y = 0; y < q1; y++)
            {
                printf(" %f", (*((o + x * q1) + y)) + (*((u + x * q1) + y)));
            }
            printf("\n");
        }
    }
    else
        printf("\n Matrices CANNOT be added");
    o = NULL;
    u = NULL;
}

void matsub(float *o, float *u, int r1, int c1, int r2, int c2)
{
    int x, y;
    if ((r1 == r2) && (c1 == c2))
    {
        for (x = 0; x < r1; x++)
        {
            for (y = 0; y < c1; y++)
            {
                printf(" %f", (*((o + x * c1) + y)) - (*((u + x * c1) + y)));
            }
            printf("\n");
        }
    }
    else
        printf("\n Matrices CANNOT be subtracted");
    o = NULL;
    u = NULL;
}

void matpro(float *o, float *u, int r1, int c1, int r2, int c2)
{
    int i, j, k;
    float temp = 0;
    if (c1 == r2)
    {
        for (i = 0; i < r1; i++)
        {
            for (j = 0; j < c2; j++)
            {
                temp = 0;
                for (k = 0; k < c1; k++)
                {
                    temp += (*((o + i * c1) + k)) * (*((u + k * c1) + j));
                }
                printf(" %0.3f", temp);
            }
            printf("\n");
        }
    }
    else
        printf("\n Matrices CANNOT be multiplied");
    o = NULL;
    u = NULL;
}

void matinv(float *mat, int r, int c)
{
    int i, j, k, n;
    float *a, ratio;
    if (r == c)
    {
        n = r;
        a = (float *)malloc(2 * r * c * sizeof(float));
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                *((a + i * 2 * n) + j) = *((mat + i * n) + j);
            }
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i == j)
                {
                    *((a + i * 2 * n) + j + n) = 1;
                }
                else
                {
                    *((a + i * 2 * n) + j + n) = 0;
                }
            }
        }
        for (i = 0; i < n; i++)
        {
            if ((*((a + i * 2 * n) + i)) == 0.0)
            {
                printf(" Mathematical Error!");
                return;
            }
            for (j = 0; j < n; j++)
            {
                if (i != j)
                {
                    ratio = (*((a + j * 2 * n) + i)) / (*((a + i * 2 * n) + i));
                    for (k = 0; k < 2 * n; k++)
                    {
                        (*((a + j * 2 * n) + k)) = (*((a + j * 2 * n) + k)) - ratio * (*((a + i * 2 * n) + k));
                    }
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = n; j < 2 * n; j++)
        {
            *((a + i * 2 * n) + j) = *((a + i * 2 * n) + j) / (*((a + i * 2 * n) + i));
        }
    }
    printf("\n Inverse Matrix is:\n");
    for (i = 0; i < n; i++)
    {
        for (j = n; j < 2 * n; j++)
        {
            printf(" %0.3f", *((a + i * 2 * n) + j));
        }
        printf("\n");
    }
    free(a);
    a = NULL;
    mat = NULL;
}

void getCofactor(float *mat, float *temp, int p, int q, int n)
{
    int i = 0, j = 0;
    int row, col;
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                (*((temp + i * (n - 1)) + j)) = (*((mat + row * (n)) + col));
                j++;
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
    for (row = 0; row < i; row++)
    {
        for (col = 0; col < j; col++)
        {
            printf("%0.2f ", *((temp + row * n) + col));
        }
    }
    mat = NULL;
    temp = NULL;
}

float matdet(float *a, int r, int c)
{
    float D = 0;
    int i, j, n, f = 0;
    float *temp;
    float sign = 1;
    if (r != c)
    {
        printf(" Determinant cannot be found");
        return 0;
    }
    n = r;
    if (n == 2)
        return (*(a)) * (*(a + 3)) - (*(a + 1)) * (*(a + 2));
    temp = (float *)malloc((n - 1) * (n - 1) * sizeof(float));
    for (f = 0; f < n; f++)
    {
        getCofactor((float *)a, (float *)temp, 0, f, n);
        D = D + sign * ((*((a + 0 * n) + f)) * matdet((float *)temp, n - 1, n - 1));
        sign = -sign;
    }
    free(temp);
    temp = NULL;
    a = NULL;
    return D;
}