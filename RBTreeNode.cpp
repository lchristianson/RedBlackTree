#include "RBTreeNode.h"
#include "RBHelper.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "DRT.h"
#include "RBHelper.h"

using namespace std;

RBTreeNode::RBTreeNode(string key, string data, RBTreeNode* l, RBTreeNode* r, RBTreeNode* p, RBTree* T) {

	k = key; d = data; left = l; right = r; parent = p; t = T; black = false;
}

RBTreeNode::~RBTreeNode() {
	delete left;
	delete right;
}

DRT* RBTreeNode::add(string key, string data, string n, string p) {
	if (key < k) {
		if (left == nullptr) {
			RBTreeNode* s = new RBTreeNode(key, data, nullptr, nullptr, this, t);
			left = s;
			left->AddProcess();
			return new DRT("", n, p);
		}
		else
			return left->add(key, data, k, p);
	}
	if (key > k) {
		if (right == nullptr) {
			RBTreeNode* s = new RBTreeNode(key, data, nullptr, nullptr, this, t);
			right = s;
			right->AddProcess();
			return new DRT("", n, p);
		}
		else
			return right->add(key, data, n, k);
	}
	string temp = d;
	d = data;
	return new DRT(d, n, p);

}

DRT* RBTreeNode::searchnode(string key, string n, string p) {

	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev);
	}
	if (k < key) {
		if (right) return right->searchnode(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p);
	return new DRT("", k, p);

}

RBTreeNode* RBTreeNode::first() {//left all the down
	if (left == nullptr)
		return this;
	RBTreeNode* temp = left->first();
	return temp;
}

RBTreeNode* RBTreeNode::last() { //right all the way down
	if (right == nullptr)
		return this;
	RBTreeNode* temp = right->last();
	return temp;

}

DRT* RBTreeNode::remove(string key, string n, string p) {
	if (k == key) {
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		this->remove();
		return new DRT("", next, prev);
	}
	if (k < key) {
		if (right) return right->remove(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->remove(key, k, p);
	return new DRT("", k, p);
}

void RBTreeNode::remove() {
	RBTreeNode* p = parent;
	RBTreeNode* x = NULL;
	if (left) x = left;
	if (right) x = right;
	if (black) {
		DelProcess(x, p);
	}
	delete this;
}

bool RBTreeNode::isblack() {
	return black;
}

void RBTreeNode::setblack(bool b) {
	black = b;
}

RBTreeNode* RBTreeNode::getdirect() {
	if (left && parent->getleft() == this)
		return left;
	if (right && parent->getright() == this)
		return right;
	return NULL;
}

bool RBTreeNode::isdirect() {
	if (parent != nullptr) {
		if (parent->getleft() != nullptr && parent->getleft() == this && parent->getparent()->getleft() == parent)
			return true;
		if (parent->getright() != nullptr && parent->getright() == this && parent->getparent()->getright() == parent)
			return true;
	}
	return false;
}

void RBTreeNode::AddProcess() {
	if (parent == NULL) {
		black = true;
		return;
	}
	if (parent->isblack())
		return;
	if (!getcolor(getsibling(this, parent))) {
		parent->setblack(true);
		getsibling(this, parent)->setblack(true);
		parent->getparent()->setblack(false);
		return parent->getparent()->AddProcess();
	}
	if (isdirect()) {
		parent->rotate();
		return;
	}
	rotate();
	rotate();
	return;

}

void RBTreeNode::rotate() {
	RBTreeNode* gp = NULL;
	RBTreeNode* z = NULL;
	RBTreeNode* p = parent;
	if (parent->getparent() != NULL)
		gp = parent->getparent();
	if (left && left != getdirect())
		z = left;
	if (right && right != getdirect())
		z = right;
	if (gp) {
		parent = gp;
		if (gp->getright() == p)
			gp->setright(this);
		else
			gp->setleft(this);
	}
	else {
		t->setroot(this);
	}
	p->setparent(this);
	if (p->getright() == this) {
		left = p;
		p->setright(z);
	}
	else {
		right = p;
		p->setleft(z);
	}
	if (z)
		z->setparent(p);

}

int RBTreeNode::ValidNode() 
{
	int lc, rc, r;

	if (!black && parent && !parent->isblack()) {
		r = -1;
	}
	else {
		if (left && left->getparent() != this) {
			r = -1;
		}
		else {
			if (left && left->getk() >= k) {
				r = -1;
			}
			else {
				if (right && right->getparent() != this) {
					r = -1;
				}
				else {
					if (right && right->getk() <= k) {
						r = -1;
					}
					else {
						if (left) {
							lc = left->ValidNode();
						}
						else {
							lc = 0;
						}
						if (lc == -1) {
							r = -1;
						}
						else {
							if (right) {
								rc = right->ValidNode();
							}
							else {
								rc = 0;
							}
							if (rc == -1) {
								r = -1;
							}
							else {
								if (lc != rc) {
									r = -1;
								}
								else {
									if (black) {
										r = lc + 1;
									}
									else {
										r = lc;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return r;
}


void RBTreeNode::setparent(RBTreeNode* p) { parent = p; }
void RBTreeNode::setleft(RBTreeNode* l) { left = l; }
void RBTreeNode::setright(RBTreeNode* r) { right = r; }
RBTree* RBTreeNode::getRBTree() { return t; }
RBTreeNode* RBTreeNode::getparent() { return parent; }
string RBTreeNode::getk() { return k; }
string RBTreeNode::getd() { return d; }
RBTreeNode* RBTreeNode::getright() { return right; }
RBTreeNode* RBTreeNode::getleft() { return left; }
string RBTreeNode::next() { return right->first()->getk(); }
string RBTreeNode::prev() { return left->last()->getk(); }

