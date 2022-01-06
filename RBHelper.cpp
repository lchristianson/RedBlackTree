#include "RBHelper.h"
#include "RBTreeNode.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p)
{
	if (p->getright() && p->getright() != n)
		return p->getright();
	if (p->getleft() && p->getleft() != n)
		return p->getleft();
	return NULL;
}

void DelProcess(RBTreeNode* x, RBTreeNode* p)
{
	if (!getcolor(x)) {
		x->setblack(true);
		return;
	}
	if (p == NULL) {
		x->getRBTree()->setroot(x);
		return;
	}
	RBTreeNode* w = getsibling(x, p);
	if (!getcolor(w)) {
		w->rotate();
		DelProcess(x, p);
		return;
	}
	if (getcolor(w->getleft()) && getcolor(w->getright())) {
		w->setblack(false);
		x = p;
		p = p->getparent();
		DelProcess(x, p);
		return;
	}
	if (!getcolor(w->getdirect())) {
		w->getdirect()->setblack(true);
		w->rotate();
		return;
	}
	if (w->getleft() && w->getleft() != w->getdirect()) {
		RBTreeNode* z = w->getleft();
		z->rotate();
		z->rotate();
		z->setblack(true);
		return;
	}
	if (w->getright() && w->getright() != w->getdirect()) {
		RBTreeNode* z = w->getright();
		z->rotate();
		z->rotate();
		z->setblack(true);
		return;
	}
	return;
}

bool getcolor(RBTreeNode* n)
{
	if (n == NULL)
		return true;
	return (n->isblack());
}
