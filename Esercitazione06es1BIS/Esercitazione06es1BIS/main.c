#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef struct nodo* lk;

struct nodo {
    char val[MAXS];
    lk left;
    lk right;
};

// Prototipi delle funzioni di utilità
lk new_nodo(char *val);
lk leggi_nodo(FILE *in);
lk leggi_albero(char *filename);
void libera_albero(lk root);
void display_albero(lk root);

// Prototipi delle funzioni da implementare
int distanza(lk n, char *k1, char *k2);
int contaCompleti(lk n, int L1, int L2);

int distanzaRad(lk n, char *k);
int cercaPadre(lk n, char *k1, char *k2);//cerca il padre più profondo dei due nodi
int accumulaArchi(lk n, char *k1, char *k2);//fa la somma degli archi tra due nodi
int main(int argc, char **argv) {
    lk root;
    root = leggi_albero(argv[1]);
    display_albero(root);
    
    // invocazione delle funzioni richieste
    
    libera_albero(root);
    return 0;
}

// Implementazione delle funzioni di utilità

lk new_nodo(char *val) {
    lk n = malloc(1*sizeof(*n));
    strcpy (n->val,val);
    n->left = NULL;
    n->right = NULL;
    return n;
};


void display_albero(lk root) {
    if (root == NULL) return;
    printf("nodo %s\n", root->val);
    display_albero(root->left);
    display_albero(root->right);
}

void libera_albero(lk root) {
    if (root == NULL) return;
    libera_albero(root->left);
    libera_albero(root->right);
    free(root);
}

lk leggi_nodo(FILE *in) {
    char val[MAXS];
    int l, r;
    if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
    lk n = new_nodo(val);
    if (l!=0) n->left = leggi_nodo(in);
    if (r!=0) n->right = leggi_nodo(in);
    return n;
}

lk leggi_albero(char *filename) {
    FILE *in;
    in = fopen(filename, "r");
    lk root = leggi_nodo(in);
    fclose(in);
    return root;
}
int distanzaRad(lk n, char *k){
    int dist=0,tmp1=0,tmp2=0;
    if(n==NULL){//terminazione della ricorsione
        return 0;
    }
    else{
        if(strcmp(n->val, k)==0){//nella fase di risalita conto gli archi fino a tornare alla radice
            return 1;
        }
        tmp1+=distanzaRad(n->right, k);
        tmp2+=distanzaRad(n->left, k);
        if(tmp1>0||tmp2>0){
            dist=tmp1+tmp2;
            dist++;
        }
        
        return dist;
        
        
        
    }
    
    return dist;
}
// Implementazione delle funzioni da aggiungere
int distanza(lk n, char *k1, char *k2) {
    int nodo1,nodo2;
    nodo1=cerca(n->left,k1,k2);
    nodo2=cerca(n->right,k1,k2);
    //a seconda del valore restituito(0 1 2 o 3) so che i due nodi sono o entrambi a sinistra o uno da una parte e uno dall altra o entrambi a destra
    if((nodo1==1 && nodo2==2)||(nodo1==2 && nodo2==1)){
       return accumulaArchi(n->left, k1, k2)+accumulaArchi(n->right, k1, k2);
    }
    else{
        if(strcmp(n->val,k1)==0){//io sono k1 e quindi anche il padre piu profondo
            return accumulaArchi(n->left, k1, k2)+accumulaArchi(n->right, k1, k2);
        }
        if(strcmp(n->val, k2)==0){//io sono k2 e anche il padre piu profondo
            return accumulaArchi(n->left, k1, k2)+accumulaArchi(n->right, k1, k2);
        }
        
    }
    
    return distanza(n->left, k1, k2)+distanza(n->right, k1, k2);
}

int cerca(lk n, char *k1, char *k2){
    if(n==NULL){
        return 0;//sono arrivato a una foglia e non ho trovato i due valori
    }
        if(strcmp(n->val,k1)==0 || strcmp(n->val, k2)==0){
            if(strcmp(n->val,k1)==0){
                return 1;
            }
            else{
                return 2;
            }
        }
    return cerca(n->left, k1, k2)+cerca(n->right, k1, k2);
}

int contaCompleti(lk n, int L1, int L2) {
    return 0;
}


