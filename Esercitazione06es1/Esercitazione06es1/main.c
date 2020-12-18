#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef struct nodo* lk;//ho dovuto rinominare link come lk perche il compilatore lo prendeva come un errore

struct nodo {//la rappresentazione scelta utilizza due puntatori sapendo che l albero è binario
    char val[MAXS];//chiave
    lk left;//figli
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
int contaCompleti(lk n, int L1, int L2, int *d);
int distanzaRad(lk n, char *k);//conta la distanza dalla radice di un nodo
lk cercaParente(lk n, char *k1, char *k2);
int main(int argc, char **argv) {
    lk root;
    int liv1,liv2,d=0;
    char k1[4],k2[4];
    root = leggi_albero(argv[1]);
    display_albero(root);
    
    // invocazione delle funzioni richieste
    printf("Tra quali livelli dell albero vuoi controllare il numero di nodi completi?\nLivello1: ");
    scanf("%d",&liv1);
    printf("Livello2: ");
    scanf("%d",&liv2);
    printf("Completi: %d\n",contaCompleti(root, liv1, liv2,&d));
    printf("Inserisci le chiavi di due nodi:\nNodo1: ");
    scanf("%s",k1);
    printf("Nodo2: ");
    scanf("%s",k2);
    printf("\nI due nodi distano: %d\n",distanza(root, k1, k2));
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

// Implementazione delle funzioni da aggiungere

lk cercaParente(lk n, char *k1, char *k2){
    lk p=NULL;
    
    if(strcmp(n->val, k1)==0 || strcmp(n->val, k2)==0){//se sono io k1 o k2 sono anche il parente piu profondo
        p=n;
    }
    else{
        if(strcmp(k1,n->val)>0 && strcmp(k2, n->val)>0){//devo cercare a destra
            p=cercaParente(n->right, k1, k2);
        }
        else{
            if(strcmp(k1,n->val)<0 && strcmp(k2, n->val)<0){//devo cercare a sinistra
              p=cercaParente(n->left, k1, k2);
            }
            else{//in questo caso il parente piu profondo è il nodo stesso
                p=n;
            }
        }
    }
    return p;
}

int distanza(lk n, char *k1, char *k2) {
    int dist=0,tmp1=0,tmp2=0;
    lk parente=NULL;
    /*if(n==NULL){//terminazione della ricorsione
        return 0;
    }
    else{
        if(strcmp(n->val, k2)==0){//nella fase di risalita conto gli archi fino a tornare su k1
            return 1;
        }
        tmp1+=distanza(n->right, k1, k2);
        tmp2+=distanza(n->left, k1, k2);
        if(tmp1>0||tmp2>0){
            dist=tmp1+tmp2;
            dist++;
        }
        
        return dist;
        
        
        
    }*/
    //prima di fare questo identifico il parente di entrambi piu profondo
    parente=cercaParente(n,k1,k2);
    if(strcmp(parente->val, k1)!=0){
        tmp1=distanzaRad(parente, k1);
    }
    if(strcmp(parente->val, k2)!=0){
        tmp2=distanzaRad(parente, k2);
    }
    
    dist=tmp2+tmp1;//sommo le due distanze ed ottengo il numero di archi
return dist;
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
        }
        
        return dist;
        
        
        
    }
    
    return dist;
}

int contaCompleti(lk n, int L1, int L2,int *d) {
    int cont=0;*d=L2-L1;
    if(n==NULL){//se sono arrivato ad un puntatore nullo il nodo precedente era una foglia
        return 0;//terminazione ricorsione
    }
    else{
        if(L1==0){
            if(*d>=0){//l intervallo che considero è del tipo[L1,L2]
            if(n->left!=NULL && n->right!=NULL){//controllo che incrementa il conteggio
                cont++;
            }
                if(*d>0){
                    *d=*d-1;
                    cont+=contaCompleti(n->right, L1, L2,d);
                    cont+=contaCompleti(n->left, L1, L2,d);
                }
            }
            }
        else{
            cont+=contaCompleti(n->right, --L1, --L2,d);
            /*cambio l intervallo e mi sposto su un sotto albero piu profondo senza variare la distanza*/
            cont+=contaCompleti(n->left, --L1, --L2,d);
        }
        }
    return cont;
}