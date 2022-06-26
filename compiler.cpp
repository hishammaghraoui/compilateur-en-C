#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analiser_syntax();
struct Node
{
    char data[255];
    int line;
    struct Node* next;
};
typedef struct Node Node;
Node* head = NULL;
struct variables {
    char name;
    char* type;
    int* valueint;
    char* valuechar;
    float* valuefloat;
};
typedef struct variables var;
static var* vars= (var*)malloc(sizeof(var) * 1);
static int cmp =0;
void freeList(Node* first)
{
    Node* tmp;

    while (first != NULL)
    {
        tmp = first;
        first = first->next;
        free(tmp);
    }

}
void display()
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = head;
    if (head == NULL) return;
    while (temp->next != NULL)
    {
        printf("-> %s  ", temp->data);
        temp = temp->next;
    }

    printf("%s\n", temp->data);
}
void append(char* value , int line)
{
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));

    strcpy(newNode->data, value);
    newNode->line = line;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
bool findvar(char *v,var *v1) {
    int len,i=0;
    char *c;
    c = (char*)malloc(sizeof(char) * 2);
    bool b = false ;
    while((vars+i)->name!=NULL && (vars + i)->type != NULL) {
        if(i<=cmp) {
        *c = (vars + i)->name;
        *(c + 1) = '\0';
        if(!strcmp(c , v)){
           * v1 =*( vars + i);
            b = true;
            break;
        }
        else {
            b = false;
        }
        }i++;
    }

    return b;
}

void* alloaction(char *type ) {
    if (!strcmp(type, "entier")) {
        int* i;
        i = (int*)malloc(sizeof(int) * 1);
        return i;
    }
    else if (!strcmp(type, "reel")) {
        float *f;
        f = (float*)malloc(sizeof(float) * 1);
        return f;
    }
    else if (!strcmp(type, "charcter")) {
        char* c;
        c = (char*)malloc(sizeof(char) * 1);
        return c;
    }
    else {
        printf("\nthe type of variable cant be allocated \n");
        return NULL;
    }
}
char* getswords(FILE* fp,int* line) {
    char c;
    char* word;
    int i = 0;
    bool k = false;

    if (fp == NULL) {
        printf("erreur fopen\n");
        return NULL;
    }
    word = (char*)malloc(sizeof(char));
    do {
        c = fgetc(fp);
        if (c == '\n') {
            *line = (*line) + 1;
        }
        if ((c == ' ' || c == '\n') && k) {
            break;
        }
        else if (c != ' ' && c != '\n') {
            word = (char*)realloc(word, sizeof(char) * (strlen(word) + 1));
            *(word + i) = c;
            i++;
            k = true;
        }


    } while (c != EOF);
    if (c == EOF) {
        *line = (*line) + 1;
        *(word + i-1) = '\0';
    }
    else{
    *(word + i) = '\0';}
    return word;

}

bool isitint(char* word) {
    int lenght;
    bool b = false;
    if (strlen(word) == 1) {
        if (*(word) >= 48 && *(word) <= 57) {
            b = true;
            return true;
        }
    }
    else {
        lenght = strlen(word);
        for (int i = 0; i < lenght; i++) {
            if (*(word + i) >= 48 && *(word + i) <= 57) {
                b = true;

            }
            else
            {
                b = false;

                break;
            }
        }

    }
    return b;
}
bool isitchar(char* word) {
    if (strlen(word) > 1) {
        return false;
    }
    else if (strlen(word) == 1) {
        char c;
        c = *(word);
        if (c >= 97 && c <= 122) {
            return true;
        }
        else {
            return false;
        }
    }
}
bool isitfloat(char* word) {
    int lenght;
    bool b = false;
    if (strlen(word) == 1) {
        if (*(word) >= 48 && *(word) <= 57) {
            b = true;
            return true;
        }
    }
    else {
        lenght = strlen(word);
        for (int i = 0; i < lenght; i++) {
            if ((*(word + i) >= 48 && *(word + i) <= 57) || *(word + i) == 46) {
                b = true;

            }
            else
            {
                b = false;

                break;
            }
        }

    }
    return b;
}
bool isittxt(char *word) {
    if (*(word+0) == '"' && *(word + strlen(word)-1) == '"') {
        return true;
    }
    else {
        return false; 
    }
}
bool findvarput(char* v, char* v1) {
    int len, i = 0;
    char* c;
    c = (char*)malloc(sizeof(char) * 2);
    bool b = false;
    while ((vars + i)->name != NULL && (vars + i)->type != NULL) {
        if (i <= cmp) {
            *c = (vars + i)->name;
            *(c + 1) = '\0';
            if (!strcmp(c, v1)) {
                if(!strcmp((vars+i)->type , "entier")) {
                    (vars + i)->valueint = (int * ) alloaction((vars + i)->type);
                    sscanf(v, "%d",(vars + i)->valueint);
                    b = true;
                    break;
                }
                else if (!strcmp((vars + i)->type, "charcter")) {
                    (vars + i)->valuechar = (char*) alloaction((vars + i)->type);
                   * (vars + i)->valuechar = * v;
                    b = true;
                    break;
                }
                if (!strcmp((vars + i)->type, "reel")) {
                    (vars + i)->valuefloat = (float*)alloaction((vars + i)->type);
                    sscanf(v, "%f", (vars + i)->valuefloat);
                    b = true;
                    break;
                }
               
            }
            else {
                b = false;
            }
            i++;
        }
    }

    return b;
}
int findinlix(char* word, FILE* lix) {
    char* mot;
    int line=0;
    int test, i = 0;
    while (!feof(lix)) {
        mot = getswords(lix,&line);
        if(strlen(word) !=0){
        test = strcmp(word, mot);
        if (test == 0 ) {
            i = 1;
            rewind(lix);
            break;
        }

        else {
            i = 0;
        }
        }
        else if (strlen(word) == 0) {
            i = 1;
        }
    }
    
    return i;
}
void addvartovars(var *vr1) {
    int len, i = 0;
    char c;
    bool b = false;
    while ((vars + i)->name != NULL && (vars + i)->type != NULL) {
        if (i <= cmp) {
            c = (vars + i)->name;
           
            if (c==vr1->name) {
                if (!strcmp((vars + i)->type, "entier")) {
    
                    (vars + i)->valueint == vr1->valueint;
                    b = true;
                    break;
                }
                else if (!strcmp((vars + i)->type, "charcter")) {
                    (vars + i)->valuechar == vr1->valuechar;
                    b = true;
                    break;
                }
                if (!strcmp((vars + i)->type, "reel")) {
                    (vars + i)->valuefloat == vr1->valuefloat;
                    b = true;
                    break;
                }

            }
            else {
                b = false;
            }
            i++;
        }
    }


}
void analiser_lix() {
    int line = 0, test = 2;
    bool is = false,isint=false;

    char* word;
    FILE* lix;
    lix = fopen("lix.txt", "r");
     if (lix == NULL)
      {
        printf("LIX : File could not be opened for writing\n");
      }
    FILE* prog;
    prog = fopen("prog.txt", "r");
    if (prog == NULL)
      {
        printf("prog : File could not be opened for writing\n");
      }
    while (!feof(prog)) {
        word = getswords(prog, &line );
        is = isittxt(word);
        isint = isitint(word);
        if (is == false && isint == false) {
            test = findinlix(word, lix);
        }
        if (test == 0 ) {
            if (line == 0) {
                line = 1;
                printf("error lexique:  \"%s\" in line %d \n", word, line);

            }
            else {
                
                printf("error lexique:  \"%s\" in line %d \n", word, line);
            }
        }
        else
        {
                if (line == 0) {
                    append(word, 1);
                }
                else {
                    append(word, line);
                }
        }
        free(word);
        rewind(lix);
    }
}
void  analiser_syntax() {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = head;
    if (head == NULL) { printf("this node is empty "); }
    while (temp!= NULL)
    {
    if (!strcmp(temp->data , "lire"))
    {
        temp = temp->next;
        if (!strcmp(temp->data, "(")) {
            temp = temp->next;
            if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                temp = temp->next;
                if (!strcmp(temp->data, ")")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                    }
                    else {
                        printf("error syntaxique missed \';\' in line %d \n",temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed \')\' in line %d \n", temp->line);
                }
            }
            else {
                printf("error syntaxique problem at variable in line %d \n", temp->line);
            }
        }

        else {
            printf("error syntaxique missed \'(\'  at line %d \n",temp->line+1);
        }
    }
    else if (!strcmp(temp->data, "ecrire")) {
        temp = temp->next;
        if (!strcmp(temp->data, "(")) {
            temp = temp->next;
            if (isittxt(temp->data) == true) {
                temp = temp->next;
                if (!strcmp(temp->data, ")")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                    }
                    else {
                        printf("error syntaxique missed \';\' in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed \')\' in line %d \n", temp->line);
                }
            }
            else if (isitchar(temp->data) == true) {
                temp = temp->next;
                if (!strcmp(temp->data, ")")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                    }
                    else {
                        printf("error syntaxique missed \';\' in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed \')\' in line %d \n", temp->line);
                }
            }
            else {
                printf("error syntaxique problem at variable   in line %d \n", temp->line);
            }
        }
        else {
            printf("error syntaxique missed \')\'  ;.;;;;llin line %d \n", temp->line);
        }
    }
    else if (!strcmp(temp->data, "declaration")) {
        temp = temp->next;
        if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
            temp = temp->next;
            if (strlen(temp->data) == 1 || strcmp(temp->data, ":") == 0) {
                temp = temp->next;
                if (!strcmp(temp->data, "entier")) {
                    temp = temp->next;
                 
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                   
                    }
                    else {
                        printf("error syntaxique missed \';\'in line %d \n", temp->line);
                    }
                }
                else if (!strcmp(temp->data, "reel")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;

                    }
                    else {
                        printf("error syntaxique missed \';\'in line %d \n", temp->line);
                    }
                }
                else if (!strcmp(temp->data, "charcter")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;

                    }
                    else {
                       printf("error syntaxique missed \';\'in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed type of variable in line %d \n", temp->line);
                }
            }
            else {
                printf("error syntaxique missed \':\'  in line %d \n", temp->line);
            }
        }
        else {
            printf("error syntaxique missed varibale  in line %d \n", temp->line);
        }
    } //si ( a > 7 ) alors a := 7 sinon a := 5 finsi ;
    else if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
    temp = temp->next;

    if (strlen(temp->data) == 2 && strcmp(temp->data, ":=") == 0)
    {
        temp = temp->next;
        if (isitint(temp->data) == true)
        {

            temp = temp->next;
            if (!strcmp(temp->data, ";")) {
                temp = temp->next;
            }
            else {
                printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
            }

        }
        else if (isitchar(temp->data) == true)
        {

            temp = temp->next;
            if (!strcmp(temp->data, ";")) {
                temp = temp->next;
            }
            else {
                printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
            }


        }
        else if (isitfloat(temp->data) == true)
        {
            temp = temp->next;
            if (!strcmp(temp->data, ";")) {
                temp = temp->next;
            }
            else {
                printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
            }

        }
        else
        { 
            printf(" erreur SYNTAXE : missed value  in line %d \n", temp->line);
        }
    }
    else {
        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
    }
    }//si ( a > 7 ) alors a := 7 sinon a := 5 finsi ;
    else if (!strcmp(temp->data,"si")) {
        temp = temp->next;
        if (!strcmp(temp->data,"(")) {
            temp = temp->next; 
            if (strlen(temp->data) == 1 && isitchar(temp->data) == true)
            {
                temp = temp->next;
                if (strlen(temp->data) == 1 && strcmp(temp->data, "=") == 0)
                {
                    temp = temp->next;
                    if (isitint(temp->data) == true)
                    {
                        temp = temp->next;
                        if (!strcmp(temp->data, ")"))
                        {
                            temp = temp->next;
                            if (!strcmp(temp->data, "alors")) {
                                temp = temp->next;
                                if (strlen(temp->data) == 1 && isitchar(temp->data) == true)
                                {
                                    temp = temp->next;
                                    if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0)
                                    {
                                        temp = temp->next;
                                        if (isitint(temp->data) == true)
                                        {
                                            temp = temp->next;
                                            if (!strcmp(temp->data, ")"))
                                            {
                                                temp = temp->next;
                                                if (!strcmp(temp->data, "alors")) {
                                                    temp = temp->next;
                                                    if (strlen(temp->data) == 1 && isitchar(temp->data) == true)
                                                    {
                                                        temp = temp->next;
                                                        if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0)
                                                        {
                                                            temp = temp->next;
                                                            if (isitint(temp->data) == true) {
                                                                temp = temp->next;
                                                                if (!strcmp(temp->data, "sinon")) {
                                                                    temp = temp->next;
                                                                    if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                                                                        temp = temp->next;
                                                                        if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0) {
                                                                            temp = temp->next;
                                                                            if (isitint(temp->data) == true) {
                                                                                temp = temp->next;
                                                                                if (!strcmp(temp->data, "finsi")) {
                                                                                    temp = temp->next;
                                                                                    if (!strcmp(temp->data, ";")) {
                                                                                        temp = temp->next;
                                                                                    }
                                                                                    else {
                                                                                        printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                                                                }
                                                                            }
                                                                            else {
                                                                                printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                                                            }
                                                                        }
                                                                        else {
                                                                            printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                                                        }
                                                                    }
                                                                    else {
                                                                        printf(" erreur SYNTAXE : missed variable in line %d \n", temp->line);
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                                                }
                                                            }
                                                            else {
                                                                printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                                            }
                                                        }
                                                        else {
                                                            printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                                        }
                                                    }
                                                    else
                                                    {
                                                        printf(" erreur SYNTAXE : variable not founded in line %d \n", temp->line);
                                                    }
                                                }
                                                else {
                                                    printf(" erreur SYNTAXE : missed \'alors\' in line %d \n", temp->line);
                                                }

                                            }
                                            else {
                                                printf(" erreur SYNTAXE : missed \')\' in line %d \n", temp->line);
                                            }
                                        }
                                        else {
                                            printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                        }
                                    }
                                    else {
                                        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                    }
                                }
                                else
                                {
                                    printf(" erreur SYNTAXE : variable not founded in line %d \n", temp->line);
                                }
                            }
                            else {
                                printf(" erreur SYNTAXE : missed \'alors\' in line %d \n", temp->line);
                            }

                        }
                        else {
                            printf(" erreur SYNTAXE : missed \')\' in line %d \n", temp->line);
                        }
                    }
                    else {
                        printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                    }
                    
                }
                else if (strlen(temp->data) == 1 && strcmp(temp->data, ">") == 0) {

                    temp = temp->next;
                    if (isitint(temp->data) == true)
                    {
                        temp = temp->next;
                        if (!strcmp(temp->data, ")"))
                        {
                            temp = temp->next;
                            if (!strcmp(temp->data, "alors")) {
                                temp = temp->next;
                                if (strlen(temp->data) == 1 && isitchar(temp->data) == true)
                                {
                                    temp = temp->next;
                                    if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0)
                                    {
                                        temp = temp->next;
                                        if (isitint(temp->data) == true) {
                                            temp = temp->next;
                                            if (!strcmp(temp->data, "sinon")) {
                                                temp = temp->next;
                                                if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                                                    temp = temp->next;
                                                    if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0) {
                                                        temp = temp->next;
                                                        if (isitint(temp->data) == true) {
                                                            temp = temp->next;
                                                            if (!strcmp(temp->data, "finsi")) {
                                                                temp = temp->next;
                                                                if (!strcmp(temp->data, ";")) {
                                                                    temp = temp->next;
                                                                }
                                                                else {
                                                                    printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                                            }
                                                        }
                                                        else {
                                                            printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                                        }
                                                    }
                                                    else {
                                                        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                                    }
                                                }
                                                else {
                                                    printf(" erreur SYNTAXE : missed variable in line %d \n", temp->line);
                                                }
                                            }
                                            else
                                            {
                                                printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                            }
                                        }
                                        else {
                                            printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                        }
                                    }
                                    else {
                                        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                    }
                                }
                                else
                                {
                                    printf(" erreur SYNTAXE : variable not founded in line %d \n", temp->line);
                                }
                            }
                            else {
                                printf(" erreur SYNTAXE : missed \'alors\' in line %d \n", temp->line);
                            }

                        }
                        else {
                            printf(" erreur SYNTAXE : missed \')\' in line %d \n", temp->line);
                        }
                    }
                    else {
                        printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                    }
                   

                }
                else if (strlen(temp->data) == 1 && strcmp(temp->data, "<") == 0)
                {
                    temp = temp->next;
                    if (isitint(temp->data) == true)
                    {
                        temp = temp->next;
                        if (!strcmp(temp->data, ")"))
                        {
                            temp = temp->next;
                            if (!strcmp(temp->data, "alors")) {
                                temp = temp->next;
                                if (strlen(temp->data) == 1 && isitchar(temp->data) == true)
                                {
                                    temp = temp->next;
                                    if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0)
                                    {
                                        temp = temp->next;
                                        if (isitint(temp->data) == true) {
                                            temp = temp->next;
                                            if (!strcmp(temp->data, "sinon")) {
                                                temp = temp->next;
                                                if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                                                    temp = temp->next;
                                                    if (strlen(temp->data) == 2 || strcmp(temp->data, ":=") == 0) {
                                                        temp = temp->next;
                                                        if (isitint(temp->data) == true) {
                                                            temp = temp->next;
                                                            if (!strcmp(temp->data, "finsi")) {
                                                                temp = temp->next;
                                                                if (!strcmp(temp->data, ";")) {
                                                                    temp = temp->next;
                                                                }
                                                                else {
                                                                    printf(" erreur SYNTAXE : missed \';\' in line %d \n", temp->line);
                                                                }
                                                            }
                                                            else
                                                            {
                                                                printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                                            }
                                                        }
                                                        else {
                                                            printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                                        }
                                                    }
                                                    else {
                                                        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                                    }
                                                }
                                                else {
                                                    printf(" erreur SYNTAXE : missed variable in line %d \n", temp->line);
                                                }
                                            }
                                            else
                                            {
                                                printf(" erreur SYNTAXE : missed \'finsi\' in line %d \n", temp->line);
                                            }
                                        }
                                        else {
                                            printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                                        }
                                    }
                                    else {
                                        printf(" erreur SYNTAXE : missed \':=\' in line %d \n", temp->line);
                                    }
                                }
                                else
                                {
                                    printf(" erreur SYNTAXE : variable not founded in line %d \n", temp->line);
                                }
                            }
                            else {
                                printf(" erreur SYNTAXE : missed \'alors\' in line %d \n", temp->line);
                            }

                        }
                        else {
                            printf(" erreur SYNTAXE : missed \')\' in line %d \n", temp->line);
                        }
                    }
                    else {
                        printf(" erreur SYNTAXE : missed value in line %d \n", temp->line);
                    }
                }
                else {
                    printf(" erreur SYNTAXE : opperater not founded in line %d \n", temp->line);
                }
            }
            else {
                printf(" erreur SYNTAXE : variable not founded in line %d \n", temp->line);
            }
        }
        else {
            printf(" erreur SYNTAXE : missed \'(\' in line %d \n", temp->line);
        }

    }  
    else {
    temp = temp->next;
    printf(" \n");
    }
   
    }
  //  printf("syntexiqur the process done \n");
    
}
void analyse_symontique() {
    var *v1;
    v1 = (var*)malloc(sizeof(var) * 1);
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = head;
    char c;
    char kart[9] = "charcter";
    char ent[7] = "entier";
    char reel[5] = "reel";
    if (head == NULL) { printf("this node is empty "); }
    while (temp != NULL)
    {
     if (!strcmp(temp->data, "declaration")) {
        temp = temp->next;
        if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
            c = temp->data[0];
            (vars + cmp)->name = c;
            temp = temp->next;
            if (strlen(temp->data) == 1 || strcmp(temp->data, ":") == 0) {
                temp = temp->next;
                if (!strcmp(temp->data, "entier")) {
                    temp = temp->next;
                    (vars + cmp)->type = ent;
                    cmp++;
                
                }
                else if (!strcmp(temp->data, "reel")) {
                    temp = temp->next;
                    (vars + cmp)->type = reel;
                    cmp++;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;

                    }
                    else {
                        printf("error syntaxique missed \';\'in line %d \n", temp->line);
                    }
                }
                else if (!strcmp(temp->data, "charcter")) {
                    temp = temp->next;
                    (vars + cmp)->type = kart;
                    cmp++;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;

                    }
                    else {
                        printf("error syntaxique missed \';\'in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed type of variable in line %d \n", temp->line);
                }
            }
            else {
                printf("error syntaxique missed \':\'  in line %d \n", temp->line);
            }
        }
        else {
            printf("error syntaxique missed varibale  in line %d \n", temp->line);
        }
    } //si ( a > 7 ) alors a := 7 sinon a := 5 finsi ;
    else if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
        if (findvar(temp->data,v1)==true) {
            temp = temp->next;

            if (strlen(temp->data) == 2 && strcmp(temp->data, ":=") == 0)
            {
                temp = temp->next;
                if (isitint(temp->data) == true)
                {
                    
                    if(!strcmp(v1->type, "entier")){
                            temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                   
                    }
                    else {
                  
                    }
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line+1);
                    }
                }
                else if (isitchar(temp->data) == true)
                {
                   

                    if (!strcmp(v1->type, "charcter")) {
                        temp = temp->next;
                        if (!strcmp(temp->data, ";")) {
                        }
                        else {
                        }
                    }
                    else {
                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n",v1->name, temp->line+1);
                    }
                }
                else if (isitfloat(temp->data) == true)
                {
                    
                    
                    if (!strcmp(v1->type, "reel")) {

                    
                        temp = temp->next;
                        if (!strcmp(temp->data, ";")) {
                     
                        }
                        else {
                           
                        }
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else {
                   
                }
            }
            else if (strlen(temp->data) == 1 || strcmp(temp->data, "=") == 0)
            {
                temp = temp->next;
                if (isitint(temp->data) == true)
                {

                    if (!strcmp(v1->type, "entier")) {
                       
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else if (isitchar(temp->data) == true)
                {


                    if (!strcmp(v1->type, "charcter")) {
                 
                    }
                    else {
                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else if (isitfloat(temp->data) == true)
                {


                    if (!strcmp(v1->type, "reel")) {

                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else {
                    
                }
            }
            else if (strlen(temp->data) == 1 || strcmp(temp->data, ">") == 0)
            {
                temp = temp->next;
                if (isitint(temp->data) == true)
                {

                    if (!strcmp(v1->type, "entier")) {
                        //  strcpy(v1->value, temp->data);
                        temp = temp->next;
                       
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else if (isitchar(temp->data) == true)
                {


                    if (!strcmp(v1->type, "charcter")) {
                        //strcpy(v1->value, temp->data);
                        temp = temp->next;
                        
                    }
                    else {
                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                        // printf(" erreur symontique  : type char of variable \'%s\' is not exact in line %d \n", (char*)v1->name, temp->line);
                    }
                }
                else if (isitfloat(temp->data) == true)
                {


                    if (!strcmp(v1->type, "reel")) {

                        // strcpy(v1->value, temp->data);
                        temp = temp->next;
                        
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else {
                    // printf(" erreur SYNTAXE : probleme in value   in line %d \n", temp->line);
                }
            }
            else if (strlen(temp->data) == 1 || strcmp(temp->data, "<") == 0)
            {
                temp = temp->next;
                if (isitint(temp->data) == true)
                {

                    if (!strcmp(v1->type, "entier")) {
                        //  strcpy(v1->value, temp->data);
                        temp = temp->next;
                       
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else if (isitchar(temp->data) == true)
                {


                    if (!strcmp(v1->type, "charcter")) {
                        //strcpy(v1->value, temp->data);
                        temp = temp->next;
                        
                    }
                    else {
                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                        // printf(" erreur symontique  : type char of variable \'%s\' is not exact in line %d \n", (char*)v1->name, temp->line);
                    }
                }
                else if (isitfloat(temp->data) == true)
                {


                    if (!strcmp(v1->type, "reel")) {

                        // strcpy(v1->value, temp->data);
                        temp = temp->next;
                       
                    }
                    else {

                        printf(" erreur symontique  : type char of variable \'%c\' is not exact in line %d \n", v1->name, temp->line);
                    }
                }
                else {
                    // printf(" erreur SYNTAXE : probleme in value   in line %d \n", temp->line);
                }
            }
            else {
            }
        }
        else {
            printf(" erreur symontique  : variable \'%s\' not declared in line %d \n", temp->data, temp->line);
        }
    }//si ( a > 7 ) alors a := 7 sinon a := 5 finsi ;
    else if (!strcmp(temp->data, "lire"))
    {
        temp = temp->next;
        if (!strcmp(temp->data, "(")) {
            temp = temp->next;
            if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                if (findvar(temp->data, v1) == true) {
                temp = temp->next;
                if (!strcmp(temp->data, ")")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                    }
                    else {
                        printf("error syntaxique missed \';\' in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed \')\' in line %d \n", temp->line);
                }
            }
                else {
                    printf(" erreur symontique  : variable \'%s\' not declared in line %d \n", temp->data, temp->line);
                }
            }
            else {
                printf("error syntaxique problem at variable in line %d \n", temp->line);
            }

        }

        else {
            printf("error syntaxique missed \'(\'  at line %d \n", temp->line + 1);
        }
    }
    else if (!strcmp(temp->data, "ecrire"))
    {
    temp = temp->next;
    if (!strcmp(temp->data, "(")) {
        temp = temp->next;
        if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
            if (findvar(temp->data, v1) == true) {
                temp = temp->next;
                if (!strcmp(temp->data, ")")) {
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        temp = temp->next;
                    }
                    else {
                        printf("error syntaxique missed \';\' in line %d \n", temp->line);
                    }
                }
                else {
                    printf("error syntaxique missed \')\' in line %d \n", temp->line);
                }
            }
            else {
                printf(" erreur symontique  : variable \'%s\' not declared in line %d \n", temp->data, temp->line);
            }
        }
        else {
            printf("error syntaxique problem at variable in line %d \n", temp->line);
        }

    }

    else {
        printf("error syntaxique missed \'(\'  at line %d \n", temp->line + 1);  
    }
    }
    if(temp != NULL){
    temp = temp->next;}
}
//printf("the symontique done");
}

void interprt() {
    var* v1;
    v1 = (var*)malloc(sizeof(var) * 1);
    Node* temp = (Node*)malloc(sizeof(Node));
    temp = head;
    char *c;

    c = (char*)malloc(sizeof(char) *1);

    int ine;
    char inc;
    float inf;
    char name;
    char kart[9] = "charcter";
    char ent[7] = "entier";
    char reel[5] = "reel";
    if (head == NULL) { printf("this node is empty "); }
    while (temp != NULL)
    {
        if (!strcmp(temp->data, "ecrire")) {
             temp = temp->next;
            if (!strcmp(temp->data, "(")) {
                temp = temp->next;
                if (isittxt(temp->data)==true) {
                    c = (char*)realloc(c,sizeof(char) * strlen(temp->data));
                    strcpy(c, temp->data);
                    printf("%s \n", c);
                    temp = temp->next;

                }
                else if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                    if (findvar(temp->data, v1) == true) {
                        temp = temp->next;
                        if (!strcmp(v1->type, "entier")) {
                            printf("%d \n", v1->valueint[0]);
                            temp = temp->next;
                        }
                        else if (!strcmp(v1->type, "reel")) {
                            printf("%f \n", v1->valuefloat[0]);
                            temp = temp->next;
                        }
                        else if (!strcmp(v1->type, "charcter")) {
                             printf("%s \n", v1->valuechar);
                            temp = temp->next;
                        }
                    }
                }
            }
            else {

            }
        }
        else if (!strcmp(temp->data, "lire")) {
            temp = temp->next;
            if (!strcmp(temp->data, "(")) {
                temp = temp->next;
                if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
                  
                    if (findvar(temp->data, v1) == true) {
                        if (!strcmp(v1->type, "entier")) {
                            scanf("%d", &ine);
                            sprintf(c, "%d", ine);
                            findvarput(temp->data, c);
                            temp = temp->next;
                        }
                        else if (!strcmp(v1->type, "reel")) {
                            scanf("%f", &inf);
                            sprintf(c, "%f", inf);
                            findvarput(temp->data, c);
                            temp = temp->next;
                        }
                        else if (!strcmp(v1->type, "charcter")) {
                            scanf("%c", &inc);
                            sprintf(c, "%c", inc);
                            findvarput(temp->data, c);
                            temp = temp->next;
                            
                        }
                    }
                   
                }
            }
            else {

            }
        }
        else if (!strcmp(temp->data,"declaration")) {
            temp = temp->next;
            if (isitchar(temp->data) == true && strlen(temp->data) == 1)  {
                if (findvar(temp->data, v1) == true) {
                    name = temp->data[0];
                    temp = temp->next;
                    if (!strcmp(temp->data, ":")) {
                        temp = temp->next;
                     // to do change tbe struct var to take 3 types innt * and char *  and float *so i can allcoate a value without change the type of variables 
                        if (!strcmp(temp->data, "entier")) {
                            strcpy(v1->type, "entier");
                           v1->valueint = (int*)alloaction(temp->data);
                           v1->name = name;
                          *( vars + cmp) = *v1;
                           cmp++;
                        }
                        else if (!strcmp(temp->data, "charcter")) {
                            v1->valuechar = (char*)alloaction(temp->data);
                            strcpy(v1->type, "charcter");
                            v1->name = name;
                            *(vars + cmp) = *v1; cmp++;
                        }
                        if (!strcmp(temp->data, "reel")) {
                            v1->valuefloat = (float*)alloaction(temp->data);
                            strcpy(v1->type, "reel");
                            v1->name = name;
                            *(vars + cmp) = *v1; cmp++;
                          
                        }
                    }
                }
            }
        }
        else if (strlen(temp->data) == 1 && isitchar(temp->data) == true) {
            char* smia;
            smia = (char*)malloc(sizeof(char) * 1);
            *smia = temp->data[0];
            *(smia + 1) = '\0';
            temp = temp->next;
            if (!strcmp(temp->data, ":=")) {
                temp = temp->next;
                if (isitint(temp->data) == true) {
                    char* value;
                    value = (char*)malloc(sizeof(char)*1);
                    strcpy(value, temp->data);
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        findvarput(value, smia);
                    }
                }
                else if( isitchar(temp->data) == true) {
                    char* value;
                    value = (char*)malloc(sizeof(char) * 1);
                    strcpy(value, temp->data);
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        findvarput(value, smia);
                    }
                }
                else if (isitfloat(temp->data) == true) {
                    char* value;
                    value = (char*)malloc(sizeof(char) * 1);
                    strcpy(value, temp->data);
                    temp = temp->next;
                    if (!strcmp(temp->data, ";")) {
                        findvarput(value, smia);
                    }
                }

           }
        }
        temp = temp->next;
    }
}



int main() {
    analiser_lix();
   analiser_syntax();
   analyse_symontique();
   interprt();
}
