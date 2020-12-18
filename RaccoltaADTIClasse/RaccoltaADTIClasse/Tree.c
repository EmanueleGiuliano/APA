//
//  Tree.c
//  RaccoltaADTIClasse
//
//  Created by apple on 31/12/16.
//  Copyright © 2016 emag. All rights reserved.
//

#include "Tree.h"
//#include "Queue.h"



typedef struct treenode *treeLink,treenode_t;//definisce i tipi puntatore a nodo e nodo della lista
//Attenzione ai confilitti con la struct node presente invece in LIST QUEUE STACK e PQ




struct tree{//wrapper che contiene solamente il puntatore alla radice
    treeLink root;
};




struct treenode{//albero binario, spesso sara necessario modificare la struttura del nodo aggiungendo dei figli(e magari il padre)
    Item val;
    treeLink left;
    treeLink right;
};




treeLink TREEnew_node(Item x) {
    treeLink n = malloc(sizeof(struct treenode));
    n->val=ITEMinit();
    ITEMdup(x, &(n->val));
    n->left = NULL;
    n->right = NULL;
    return n;
};




void TREEfree_node(treeLink n){
    ITEMfree(n->val);
    free(n);
}





Tree TREEinit(){
    Tree x=malloc(sizeof(struct tree));
    x->root=malloc(sizeof(struct treenode));
    x->root->val=ITEMinit();
    x->root->left=NULL;
    x->root->right=NULL;
    return x;
}



void TREEinsertR(treeLink root, Item x){
    if(root->left==NULL){
        if(ITEMcheckfoglia(root->val)){//se era una foglia non lo sarà piu e lo memorizza nell item
            ITEMsetNotfoglia(&(root->val));
        }
        root->left=TREEnew_node(x);
        ITEMsetfoglia(&(root->left->val));//il figlio sinsitro appena creato diventa una foglia
        return;
    }
    if(root->right==NULL){
        if(ITEMcheckfoglia(root->val)){//se era una foglia non lo sarà piu e lo memorizza nell item
            ITEMsetNotfoglia(&(root->val));
        }
        root->right=TREEnew_node(x);
        ITEMsetfoglia(&(root->right->val));//il figlio destro appena creato diventa una foglia
        return;
    }
    if(root->left->left ==NULL || root->left->right==NULL){
        TREEinsertR(root->left,x);
    }
    else{
        TREEinsertR(root->right,x);
    }
}
void TREEinsert(Tree t,Item x){
    if(ITEMcheckvoid(t->root->val)){//primo inserimento(nella radice)
        ITEMdup(x, &(t->root->val));
        return;
    }
    else{
        TREEinsertR(t->root,x);
    }
}

/*void sortChiaviCrescenti(Tree t){//visita in order e ordina il vettore risultante per chiavi crescenti, poi ricompone l albero
    int numNodi=countNodes(t);
    Item tree[numNodi];
    for(int i=0;i<numNodi;i++){
        tree[i]=ITEMinit();
    }
    TREEsortinpreorder(t,tree);
    TREEfree(t);
    KEYquicksort(tree);
    t=TREEinit();
    //reinserisco prendendo dal vettore ordinato
}*/













/*
 |.............................................................................|
 |funzione che necessita di un albero le cui chiavi siano ordinate da sinistra |
 |in ordine crescente                                                          |
 |.............................................................................|
 */
treeLink cercaParente(treeLink root, Key k1,Key k2){
    //sortChiaviCrescenti(root);
    if(KEYcompare(KEYget(root->val),k1)>0 && KEYcompare(KEYget(root->val),k2)>0){
        cercaParente(root->right, k1, k2);
    }
    if(KEYcompare(KEYget(root->val),k1)<0 && KEYcompare(KEYget(root->val),k2)<0){
        cercaParente(root->left, k1, k2);
    }
    return root;
}



int distanzaRad(treeLink p,Key k){
    int tro=0,accumulatore=0;
    if(p==NULL){
        return 0;
    }
    if(KEYcompare(KEYget(p->val), k)==0){
        return 1;
    }
    tro=distanzaRad(p->right, k);
    if(tro>0){
        accumulatore++;
    }
    tro=distanzaRad(p->left, k);
    if(tro>0){
        accumulatore++;
    }
    return accumulatore;
}

int TREEdistNodes(Tree t,Key k1, Key k2){//calcola la lunghezza del cammino tra due nodi
    treeLink p=NULL;
    int distanza=0;
    p=cercaParente(t->root,k1,k2);//identifico il parente comune piu profondo(estrae un sottoalbero)
    distanza+=distanzaRad(p,k1);
    distanza+=distanzaRad(p,k2);
    return distanza;
}





















void TREEgetR(treeLink root, Key kx, Item *x){
    if(KEYcompare(KEYget(root->val),kx)){
        ITEMdup(root->val, x);
        return;
    }
    TREEgetR(root->left,kx,x);
    TREEgetR(root->right,kx,x);
}



void TREEgetItem(Tree t, Key kx, Item *x){//wrapper
    if(KEYcompare(KEYget(t->root->val),kx)){
        ITEMdup(t->root->val, x);
        return;
    }
    else{
        TREEgetR(t->root->left, kx,x);
        TREEgetR(t->root->right, kx,x);
    }
    return;
}

















int contaCompleti(treeLink root, int L1, int L2, int *depth){
    int completi=0;
    (*depth)++;
    if(root==NULL || (*depth)>=L2){
        return 0;
    }
    if((*depth)>=L1 && root->left!=NULL && root->right!=NULL){
        completi++;
    }
    completi+=contaCompleti(root->left, L1, L2, depth);
    completi+=contaCompleti(root->right, L1, L2, depth);
    return completi;
}

int  TREEcontaCompleti(Tree t, int L1, int L2){
    int depth=-1;
    return contaCompleti(t->root,L1,L2,&depth);
}














int countNodes(treeLink root){
    if(root==NULL){
        return 0;
    }
    return countNodes(root->left)+countNodes(root->right)+1;
}

int  TREEcountNodes(Tree t){
    int numNodi=0;
    numNodi=countNodes(t->root);
    return numNodi;
}
















int height(treeLink root){
    int hr=0,hl=0;
    if(root==NULL){
        return -1;
    }
    hl=height(root->left);
    hr=height(root->right);
    if(hr>hl){
        return hr+1;
    }
    else{
        return hl+1;
    }
}
int  TREEheight(Tree t){
    return height(t->root);
}

















void sortInOrder(treeLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //discesa a sinistra
    sortInOrder(root->left,v,indice,dim);
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    //discesa a destra
    sortInOrder(root->right,v,indice,dim);
    return;
}
void TREEsortinorder(Tree t, Item v[],int dimVett){//bisogna passargli un vettore di countnodes elementi
    int indice=0;
    sortInOrder(t->root,v,&indice,&dimVett);
}




















void sortPreOrder(treeLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    //discesa a sinistra
    sortPreOrder(root->left,v,indice,dim);
    //discesa a destra
    sortPreOrder(root->right,v,indice,dim);
    return;
}
void TREEsortpreorder(Tree t, Item v[],int dimVett){
    int indice=0;
    sortPreOrder(t->root,v,&indice,&dimVett);
}






















void sortPostOrder(treeLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //discesa a sinistra
    sortPostOrder(root->left,v,indice,dim);
    //discesa a destra
    sortPostOrder(root->right,v,indice,dim);
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    return;
}
void TREEsortpostorder(Tree t, Item v[],int dimVett){
    int indice=0;
    sortPostOrder(t->root,v,&indice,&dimVett);
}





 
 //Richiede la gestione dei nodi nell albero tramite coda esplicita(non esiste una coda di sistema), la ricorsione usa uno stack
/*
void sortLevelOrder(treeLink root,Item v[],int *indice,int *dim){
    Queue coda=QUEUEinit();
    QUEUEenqueue(root->val, coda);
    while(!QUEUEempty(coda)){
        QUEUEdequeue(coda, &v[(*indice)]);
        if(root->left !=NULL){
            QUEUEenqueue(root->left->val, coda);
        }
        if(root->right !=NULL){
            QUEUEenqueue(root->right->val, coda);
        }
    }
}
void TREEsortlevelorder(Tree t, Item v[],int dimVett){
    sortLevelOrder(t->root,v,0,&dimVett);
}*/
void display(treeLink root, int tabulazione){
    if(root==NULL){
        return;
    }
    display(root->left,tabulazione+1);
    for(int i=0;i<tabulazione;i++){
        printf("\t");
    }
    printf("_");
    ITEMshow(root->val);
    display(root->right,tabulazione+1);
    return;
}
void TREEdisplay(Tree t){
    display(t->root,0);
}




















void TREEfreeR(treeLink root){
    if(root==NULL){
        return;
    }
    TREEfreeR(root->left);
    TREEfreeR(root->right);
    TREEfree_node(root);
    return;
}
void TREEfree(Tree t){
    TREEfreeR(t->root);
    printf("Albero deallocato\n");
}















treeLink TREEreadNode(FILE *fp, treeLink root, Item *lettura){
    ITEMread(fp, lettura);
    if(ITEMcheckvoid(*lettura)){
        return NULL;
    }
    ITEMdup(*lettura, &(root->val));
    if(ITEMcheckfoglia(*lettura)){
        return root;
    }
    root->left=TREEnew_node(ITEMsetvoid(*lettura));
    root->right=TREEnew_node(ITEMsetvoid(*lettura));
    root->left=TREEreadNode(fp,root->left,lettura);
    root->right=TREEreadNode(fp,root->right,lettura);
    return root;
}
void TREEreadF(FILE *fp,Tree *t){
    Item lettura=ITEMinit();
    TREEreadNode(fp,(*t)->root,&lettura);
    ITEMfree(lettura);
    return;
}
















void TREEprintfR(treeLink root, FILE *fp,int tabulazione, Item filler){
    if(root==NULL){
        return;
    }
    for(int i=0;i<tabulazione;i++){
        fprintf(fp,"\t");
    }
    ITEMprint(root->val, fp);
    //se un nodo non e completo, stampo il riempitore per non spezzare la gerarchia nell albero
    if((root->left!=NULL && root->right==NULL) ||(root->left==NULL && root->right!=NULL)){
        for(int i=0;i<tabulazione+1;i++){
            fprintf(fp,"\t");
        }
        ITEMprint(filler,fp);
    }
    TREEprintfR(root->left,fp,tabulazione+1,filler);
    TREEprintfR(root->right,fp,tabulazione+1,filler);
    return;
}
void TREEprintF(FILE *fp,Tree t){
    Item riempitore=ITEMinit();
    //NB inoltre il filler essendo un item void non verra caricato in memoria al momento della read
    riempitore=ITEMsetvoid(riempitore);
    treeLink r=t->root;
    ITEMprint(r->val, fp);
    TREEprintfR(r->left,fp,1,riempitore);
    TREEprintfR(r->right,fp,1,riempitore);
    ITEMfree(riempitore);
}





/*
 Funzione utilizzata coi grafi ma utilizzabile in qualunque contesto
 l' array deve essere fatto nel seguente modo: gli indici delle celle rappresentano il nodo(numericamente, andra convertito con la symboltable) mentre i contenuti della cella
 rappresentano il padre del nodo
 i figli interni da ora in poi saranno numerati con A,B,C
 e gli estremi saranno left e right
 */
void genFromArrayR(treeLink root,int treeVett[],int dimTreeVett,int radice,ST symboltable){
    Item buffer=ITEMinit();
    for(int i=0;i<dimTreeVett;i++){
        if(treeVett[i]==radice){
            STretrieve(symboltable, i, &buffer);
            //se ci fossero piu nodi aggiungi if e new node fino a quella quantita, nota bene; se inserisco a destra non devo farlo a sinistra e se inserisco nel nodo A non devo farlo negli altri e cosi via
            if(root->left==NULL){
                root->left=TREEnew_node(buffer);
                genFromArrayR(root->left,treeVett, dimTreeVett, i, symboltable);
            }
            else{
                root->right=TREEnew_node(buffer);
                genFromArrayR(root->right,treeVett, dimTreeVett, i, symboltable);
            }
            
        }
    }
    //se scorrendo treeVett non ho trovato niente ero arrivato in una foglia
    return;
}
Tree* TREEgenFromArray(int treeVett[],int dimTreeVett,ST st,int numMaxAlberi){
    Tree *elenco=malloc(numMaxAlberi*sizeof(struct tree));
    Item buffer = ITEMinit();
    int num=0,radice=0;
    for(int i=0;i<dimTreeVett && num<numMaxAlberi;i++){
        if(treeVett[i]==i){//nuova radice
            STretrieve(st, treeVett[i], &buffer);
            radice=treeVett[i];
            genFromArrayR(elenco[num]->root,treeVett, dimTreeVett, radice, st);
            num++;
        }
    }
    return elenco;
}