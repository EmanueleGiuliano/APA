//
//  BST.c
//  RaccoltaADTIClasse
//
//  Created by apple on 04/01/17.
//  Copyright © 2017 emag. All rights reserved.
//

#include "BST.h"


typedef struct BSTnode* bstLink;



struct BSTnode{
    Item val;
    bstLink p;
    bstLink left;
    bstLink right;
    int N;//numero nodi del BST radice compresa
};
struct binarysearchtree{
    bstLink root;
    int N;//numero nodi totali del bst
};




//.............................FUNZIONI DI UTILITA' ALL INTERNO DEL BST STESSO...............................


//FUNZIONI DI ROTAZIONE
bstLink rotR(bstLink root) {
    int rNtmp=0,lNtmp=0;
    bstLink x = root->left;
    root->left = x->right;
    if(x->right!=NULL){
        x->right->p = root;
        rNtmp=root->right->N;
    }
    x->right = root;
    if(root->left!=NULL){
        lNtmp=root->left->N;
    }
    x->p = root->p;
    root->p = x;
    x->N = root->N;
    root->N =  rNtmp+ lNtmp +1;
    return x;
}

bstLink rotL(bstLink root) {
    int rNtmp=0,lNtmp=0;
    bstLink x = root->right;
    root->right = x->left;
    if(x->left!=NULL){
        x->left->p = root;
        lNtmp=root->left->N;
    }
    x->left = root;
    if(root->right!=NULL){
        rNtmp=root->right->N;
    }
    x->p = root->p;
    root->p = x;
    x->N = root->N;
    root->N = lNtmp+rNtmp +1;
    return x;
}


//FUNZIONE DI PARTITION
bstLink partR(bstLink root, int k) {
    int t=0;
    if(root->left!=NULL){
        t=root->left->N;
    }
    if ( t > k) {
        root->left = partR(root->left, k);
        root = rotR(root); }
    if ( t < k) {
        root->right = partR(root->right, k-t-1);
        root = rotL(root);
    }
    return root;
}

//JOIN
bstLink joinLR(bstLink a, bstLink b) {
    int rNtmp=0;
    if (b == NULL){
        return a;
    }
    b = partR(b, 0);//fa una partition cercando il nodo successivo a b nel sottoalbero radicato in b(k=0)
    b->left = a;
    a->p = b;
    if(b->right!=NULL){
        rNtmp=b->right->N;
    }
    b->N = a->N + rNtmp +1;
    return b;
}


//CREAZIONE E DISTRUZIONE NODI

bstLink BSTnew_node(Item item, bstLink p, bstLink l, bstLink r, int N){
    bstLink x = malloc(sizeof *x);
    x->val = ITEMinit();
    ITEMdup(item,&(x->val));
    x->p = p;
    x->left = l;
    x->right = r;
    x->N = N;//numero nodi albero radicato in questo nodo
    return x;
}



void BSTnode_free(bstLink x){
    ITEMfree(x->val);
    free(x);
}


//.........................................................................................................










//...........................FUNZIONI CHE SI INTERFACCIANO COL CLIENT.....................................
//....(NB molte sono realizzate come wrapper sotto e funzione ricorsiva sopra)


BST BSTinit(){
    Item tmp=ITEMinit();
    BST x=malloc(sizeof(struct binarysearchtree));
    x->N=0;
    x->root=BSTnew_node(tmp,NULL,NULL,NULL,1);
    ITEMfree(tmp);
    return x;
}







int BSTcount(BST t){
    return t->N;
}







int BSTempty(BST t){
    if(BSTcount(t)==0){return 1;}
    return 0;
}








void minR(bstLink root, Item *x) {
    if (ITEMcheckvoid(root->val)){
        return;
    }
    if(root->left==NULL){
        ITEMdup(root->val,x);
        return;
    }
     minR(root->left, x);
}
void BSTmin(BST t,Item *x){
    minR(t->root,x);
}









void maxR(bstLink root, Item *x){
    if (ITEMcheckvoid(root->val)){
        return;
    }
    if(root->right==NULL){
        ITEMdup(root->val,x);
        return;
    }
    maxR(root->right, x);
}
void BSTmax(BST t,Item *x){
    maxR(t->root,x);
}








bstLink insertR(bstLink root,bstLink p, Item x) {
    if(root==NULL){
        return BSTnew_node(x, p, NULL, NULL, 1);
    }
    if (ITEMcheckvoid(root->val)){
         ITEMdup(x,&(root->val));
        return root;
    }
    root->N++;//prima di scendere incremento il numero di nodi sottostanti
    if(KEYcompare(KEYget(root->val), KEYget(x))<=0){
        root->right=insertR(root->right,root, x);
    }
    else{
        root->left=insertR(root->left,root,x);
    }
    return root;
}
void BSTinsert_leaf(BST t,Item x){
    insertR(t->root,NULL,x);
    t->N++;
}














bstLink insertT(bstLink root,bstLink p,Item x){
    if(root==NULL){
        return BSTnew_node(x, p, NULL, NULL, 0);
    }
    if(ITEMcheckvoid(root->val)){
        ITEMdup(x,&(root->val));
        return root;
    }
    if(KEYcompare(KEYget(root->val), KEYget(x))>0){
        root->left=insertT(root->left,root,x);
        root=rotR(root);
    }
    else{
        root->right=insertT(root->right,root,x);
        root=rotL(root);
    }
    root->N++;
    return root;
}
void BSTinsert_root(BST t,Item x){
    t->root=insertT(t->root,NULL,x);
    t->N++;
}








void searchR(bstLink root,Key kx, Item *cpy){
    if(root==NULL){
        (*cpy)=ITEMsetvoid(*cpy);
        return;
    }
    if(KEYcompare(KEYget(root->val), kx)==0){
        ITEMdup(root->val, cpy);
        return;
    }
    if(KEYcompare(KEYget(root->val), kx)>0){
        searchR(root->left, kx, cpy);
    }
    else{
        searchR(root->right, kx, cpy);
    }
}
void BSTsearch(BST t,Key kx, Item *cpy){
    searchR(t->root,kx,cpy);
}

















bstLink deleteR(bstLink root,bstLink p,Key kx,char ramo){
    bstLink ptmp=NULL,y=NULL;
    if(root==NULL){
        return NULL;
    }
    
    if(KEYcompare(KEYget(root->val), kx)==0){
        y=root;
        ptmp=root->p;
        //se il nodo ha almeno un figlio chiamo la join
        if(root->right!=NULL || root->left!=NULL){
            root=joinLR(root->left, root->right);
        
        //bypass
        root->p=ptmp;
        if(ramo=='l'){
            ptmp->left=root;
        }
        if(ramo=='r'){
            ptmp->right=root;
        }
        }
        else{//sto cancellando una foglia
            if(ramo=='l'){
                ptmp->left=NULL;
            }
            if(ramo=='r'){
                ptmp->right=NULL;
            }
            root=ptmp;
        }
        //liberazione nodo
        BSTnode_free(y);
        return root;
    }
    root->N--;
    if(KEYcompare(KEYget(root->val), kx)>0){
        if(deleteR(root->left,p, kx,'l')==NULL){
            root->N++;
        }
       return root;
    }
    
    
    if(deleteR(root->right,p, kx,'r')==NULL){
        root->N++;
    }
    return root;
}
int BSTdelete(BST t,Key kx){
    bstLink newRoot=NULL;
    newRoot=deleteR(t->root,NULL,kx,'z');
    if(newRoot!=NULL){
        t->root=newRoot;
        return 1;
    }
    return 0;
}











void selectR(bstLink root,int i, Item *x){
    int t;
    t=(root->left==NULL)?0:root->left->N;
    if(t>i){
        selectR(root->left,i,x);
        return;
    }
    if(t<i){
        selectR(root->right,i-t-1,x);
    }
    
    ITEMdup(root->val,x);
    return;
}
void BSTselect(BST t,int i, Item *x){
    selectR(t->root,i,x);
}









void BSTsortInOrderR(bstLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //discesa a sinistra
    BSTsortInOrderR(root->left,v,indice,dim);
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    //discesa a destra
    BSTsortInOrderR(root->right,v,indice,dim);
    return;
}
void BSTsortinorder(BST t,Item v[],int dimVett){
    int indice=0;
    BSTsortInOrderR(t->root,v,&indice,&dimVett);
}



void BSTsortPreOrderR(bstLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    //discesa a sinistra
    BSTsortPreOrderR(root->left,v,indice,dim);
    //discesa a destra
    BSTsortPreOrderR(root->right,v,indice,dim);
    return;
}
void BSTsortpreorder(BST t,Item v[],int dimVett){
    int indice=0;
    BSTsortPreOrderR(t->root,v,&indice,&dimVett);
}




void BSTsortPostOrderR(bstLink root,Item v[],int *indice,int *dim){
    if(root==NULL || (*indice)>=(*dim)){
        return;
    }
    //discesa a sinistra
    BSTsortPostOrderR(root->left,v,indice,dim);
    //discesa a destra
    BSTsortPostOrderR(root->right,v,indice,dim);
    //nodo attuale
    ITEMdup(root->val,&v[(*indice)]);
    (*indice)++;
    return;
}
void BSTsortpostorder(BST t,Item v[],int dimVett){
    int indice=0;
    BSTsortPostOrderR(t->root,v,&indice,&dimVett);
}















void searchSucc(bstLink root, Key kx, Item *x){
    bstLink p=NULL;
    if(root == NULL){
        *x=ITEMsetvoid(*x);
        return;
    }
    if(KEYcompare(kx, KEYget(root->val))==0) {
        if (root->right != NULL){
            minR(root->right, x);
            return;
        }
        else {
            p = root->p;
            while (p != NULL && root == p->right) {
                root = p;
                p = p->p;
            }
            ITEMdup(p->val,x);
            return;
        }
    }
    if(KEYcompare(kx, KEYget(root->val))<0){
        searchSucc(root->left, kx, x);
        return ;
    }
    else{
        searchSucc(root->right, kx, x);
        return ;
    }
}
void BSTsucc(BST t,Key kx,Item *x){
    searchSucc(t->root,kx,x);
}















void searchPred(bstLink root, Key kx, Item *x){
    bstLink p=NULL;
    if (root == NULL){
        *x=ITEMsetvoid(*x);
     return;
    }
    if (KEYcompare(kx, KEYget(root->val))==0) {
        if (root->left != NULL){
            return maxR(root->left, x);
        }
        else {
            p = root->p;
            while (p != NULL && root == p->left) {
                root = p;
                p = p->p;
            }
            ITEMdup(p->val,x);
            return;
        }
    }
    if (KEYcompare(kx, KEYget(root->val))<0){
        searchPred(root->left, kx, x);
        return ;
    }
     searchPred(root->right, kx, x);
    return;
}
void BSTpred(BST t,Key kx,Item *x){
    searchPred(t->root,kx, x);
}



void BSTreadFR(FILE *fp,BST *t, Item *lettura){
    ITEMread(fp, lettura);
    if(ITEMcheckvoid(*lettura)){
        return;
    }
    BSTinsert_leaf(*t,*lettura);
    BSTreadFR(fp,t,lettura);
}
void BSTreadF(FILE *fp,BST *t){
    Item lettura=ITEMinit();//e un buffer per il file
    BSTreadFR(fp,t,&lettura);
    ITEMfree(lettura);
}//legge un file e costruisce un bst



void BSTprintfR(bstLink root, FILE *fp,int tabulazione, Item filler){
    if(root==NULL){
        return;
    }
    if(root->left==NULL && root->right==NULL){
        ITEMsetfoglia(&(root->val));
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
    BSTprintfR(root->left,fp,tabulazione+1,filler);
    BSTprintfR(root->right,fp,tabulazione+1,filler);
    return;
}
void BSTprintF(FILE *fp,BST t){
    Item riempitore=ITEMinit();
    //NB inoltre il filler essendo un item void non verra caricato in memoria al momento della read
    riempitore=ITEMsetvoid(riempitore);
    bstLink r=t->root;
    ITEMprint(r->val, fp);
    BSTprintfR(r->left,fp,1,riempitore);
    BSTprintfR(r->right,fp,1,riempitore);
    ITEMfree(riempitore);
}



void BSTdisplayR(bstLink root, int tabulazione){
    if(root==NULL){
        return;
    }
    BSTdisplayR(root->left,tabulazione+1);
    for(int i=0;i<tabulazione;i++){
        printf("\t");
    }
    printf("_");
    ITEMshow(root->val);
    BSTdisplayR(root->right,tabulazione+1);
    return;
}
void BSTdisplay(BST t){
    BSTdisplayR(t->root,0);
}