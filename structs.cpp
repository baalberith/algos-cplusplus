#include <iostream>
using namespace std;

struct lnode {
  int key;
  lnode *next;
  lnode(int k, lnode *n = 0) 
    : key(k), next(n) {}
};

enum col { red, black };

struct tnode {
  int key;
  col color;
  tnode *left, *right, *parent;
  tnode(int k, tnode *l = 0, tnode *r = 0, tnode *p = 0, col c = red) 
    : key(k), left(l), right(r), parent(p), color(c)  {}
};

lnode ** list_search(lnode **pphead, int value) {
  lnode **pp = pphead;
  while (*pp != 0 && (*pp)->key < value)
    pp = &(*pp)->next;
  return pp;
}

void list_insert(lnode **pp, int value) {
  *pp = new lnode(value, *pp);
}

void list_erase(lnode **pp) {
  lnode *p = *pp;
  *pp = (*pp)->next;
  delete p;
}

void list_print(lnode **pphead) {
  lnode **pp = pphead;
  while (*pp != 0) {
    cout << (*pp)->key << " ";
    pp = &(*pp)->next;
  }
}

void list_manipulation() {
  lnode *phead = 0;
  lnode **pphead = &phead;
  char c;
  int n;
  while (cin >> c >> n) {
    switch (c) {
      case 'i' :
        list_insert(list_search(pphead, n), n);
        break;
      case 'e' :
        lnode **pp = list_search(pphead, n);
        if (*pp != 0 && (*pp)->key == n)
          list_erase(pp);
        break;
    }
    cout << "list: ";
    list_print(pphead);
    cout << endl;
  }
}

tnode ** tree_insert_search(tnode **pproot, int value) {
  tnode **pp = pproot;
  while (*pp != 0)
    if (value < (*pp)->key)
      pp = &(*pp)->left;
    else
      pp = &(*pp)->right;
  return pp;
}

tnode ** tree_erase_search(tnode **pproot, int value) {
  tnode **pp = pproot;
  while (*pp != 0 && (*pp)->key != value)
    if (value < (*pp)->key)
      pp = &(*pp)->left;
    else
      pp = &(*pp)->right;
  return pp;
}

tnode ** tree_max(tnode **pp) {
  while ((*pp)->right)
    pp = &(*pp)->right;
  return pp;
}

tnode ** tree_min(tnode **pp) {
  while ((*pp)->left)
    pp = &(*pp)->left;
  return pp;
}

void tree_insert(tnode **pp, int value) {
  *pp = new tnode(value);
}

void tree_insert_2(tnode *&proot, tnode *pnew) {
  tnode *pprev = 0,
  *pcurr = proot;
  while (pcurr != 0) {
    pprev = pcurr;
    if (pnew->key < pcurr->key)
      pcurr = pcurr->left;
    else
      pcurr = pcurr->right;
  }
  pnew->parent = pprev;
  if (pprev == 0)
    proot = pnew;
  else if (pnew->key < pprev->key)
    pprev->left = pnew;
  else
    pprev->right = pnew;
}

void tree_erase(tnode **pp) {
  tnode *p = 0;
  if ((*pp)->right && (*pp)->left) {
    tnode ** ppmax = tree_max(&(*pp)->left);
    (*pp)->key = (*ppmax)->key;
    p = *ppmax;
    *ppmax = (*ppmax)->left;
  }
  else {
    p = *pp;
    *pp = (*pp)->left ? (*pp)->left : (*pp)->right;
  }
  delete p;
}

tnode * tree_erase_2(tnode *&proot, tnode *pdel) {
  tnode *ptmp, *p;
  if (pdel->left == 0 || pdel->right == 0)
    ptmp = pdel;
  else
    ptmp = *tree_min(&pdel->right);
  if (ptmp->left != 0)
    p = ptmp->left;
  else
    p = ptmp->right;
  if (p != 0)
    p->parent = ptmp->parent;
  if (ptmp->parent == 0)
    proot = p;
  else if (ptmp == ptmp->parent->left)
    ptmp->parent->left = p;
  else 
    ptmp->parent->right = p;
  if (ptmp != pdel)
    pdel->key = ptmp->key;
  return ptmp;
}

void tree_build(tnode **ppcurr, tnode *pprev = 0) {
  if (*ppcurr != 0) {
    (*ppcurr)->parent = pprev;
    tree_build(&(*ppcurr)->left, *ppcurr);
    tree_build(&(*ppcurr)->right, *ppcurr);
  }
}

tnode ** tree_successor(tnode **pp) {
  if ((*pp)->right != 0)
    return tree_min(&(*pp)->right);
  tnode **pppar = &(*pp)->parent;
  while (*pppar != 0 && *pp == (*pppar)->right) {
    pp = pppar;
    pppar = &(*pp)->parent;
  }
  return pppar;
}

tnode ** tree_predecessor(tnode **pp) {
  if ((*pp)->left != 0)
    return tree_max(&(*pp)->left);
  tnode **pppar = &(*pp)->parent;
  while (*pppar != 0 && *pp == (*pppar)->left) {
    pp = pppar;
    pppar = &(*pp)->parent;
  }
  return pppar;
}

void tree_print(tnode **pp) {
  if (*pp != 0) {
    tree_print(&(*pp)->left);
    cout << (*pp)->key << " ";
    tree_print(&(*pp)->right);
  }
}

void tree_manipulation() {
  tnode *proot = 0,
  **pproot = &proot, 
  **pp, **pppred, **ppsucc;
  char c;
  int n;
  while (cin >> c >> n) {
    switch (c) {
      case 'i' :
        tree_insert(tree_insert_search(pproot, n), n);
        //tree_insert_2(proot, new tnode(n));
        break;
      case 'e' : 
        pp = tree_erase_search(pproot, n);
        if (*pp != 0)
          tree_erase(pp);
          //delete tree_erase_2(proot, *pp); 
        break;
      case 'm' :
        if (*pproot != 0)
          cout << "min: " << (*tree_min(pproot))->key << " "
          << "max: " << (*tree_max(pproot))->key << endl;
        break;
      case 'f' :
        if (*pproot != 0) {
          tree_build(pproot);
          pp = tree_erase_search(pproot, n);
          if (*pp != 0) {
            pppred = tree_predecessor(pp);
            if (*pppred != 0)
              cout << "pred: " << (*pppred)->key << " ";
            ppsucc = tree_successor(pp);
            if (*ppsucc != 0)
              cout << "succ: " << (*ppsucc)->key << " ";
            cout << endl;
          }
        }
        break; 
      default : return;
    }
    cout << "tree: ";
    tree_print(pproot);
    cout << endl;
  }
}

void left_rotate(tnode *&proot, tnode *p) {
  tnode *r = p->right;
  p->right = r->left;
  if (r->left != 0)
    r->left->parent = p;
  r->parent = p->parent;
  if (p->parent == 0)
    proot = r;
  else if (p == p->parent->left)
    p->parent->left = r;
  else
    p->parent->right = r;
  r->left = p;
  p->parent = r;
}

void right_rotate(tnode *&proot, tnode *p) {
  tnode *l = p->left;
  p->left = l->right;
  if (l->right != 0)
    l->right->parent = p;
  l->parent = p->parent;
  if (p->parent == 0)
    proot = l;
  else if (p == p->parent->left)
    p->parent->left = l;
  else
    p->parent->right = l;
  l->right = p;
  p->parent = l;
}

void red_black_insert(tnode *&proot, tnode *p) {
  tree_insert_2(proot, p);
  p->color = red;
  while (p != proot && p->parent->color == red) {
    if (p->parent == p->parent->parent->left) {
      tnode *q = p->parent->parent->right;
      if (q->color == red) {
        p->parent->color = black;
        q->color = black;
        p->parent->parent->color = red;
        p = p->parent->parent;
      }
      else {
        if (p == p->parent->right) {
          p = p->parent;
          left_rotate(proot, p);
        }
        p->parent->color = black;
        p->parent->parent->color = red;
        right_rotate(proot, p->parent->parent);
      }
    }
    else {
    }
  }
  proot->color = black;
}

int main() {
  //list_manipulation();
  //tree_manipulation();
}
