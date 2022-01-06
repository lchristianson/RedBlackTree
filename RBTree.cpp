#include "RBTree.h"

using namespace std;

RBTree::RBTree() { root = NULL; }

RBTree::~RBTree() { delete root; }

void RBTree::setroot(RBTreeNode* r) { root = r; }

RBTreeNode* RBTree::getroot() { return root; }

DRT* RBTree::add(string key, string data) { //very similar to sample code

    if (!root) {
        root = new RBTreeNode(key, data, NULL, NULL, NULL, this);
        root->setblack(true);
        return new DRT("", "", "");
    }
    return root->add(key, data, "", "");
}

DRT* RBTree::searchnode(string key) { //searches the tree for the given key

    if (key == "")
        return new DRT("", "", "");
    if (root->getd() == key) {
        if (root->getleft() && root->getright())
            return new DRT(root->getd(), root->getright()->getk(), root->getleft()->getk());
        if (root->getleft() && !root->getright())
            return new DRT(root->getd(), "", root->getleft()->getk());
        if (!root->getleft() && root->getright())
            return new DRT(root->getd(), root->getright()->getk(), "");
        return new DRT(root->getd(), "", "");
    }
    return root->searchnode(key, "", "");



}

string RBTree::first() {
    if (!root)
        return "";
    RBTreeNode* temp(root);
    while (temp->getleft() != nullptr)
        temp = temp->getleft();
    return temp->getk();

}

string RBTree::last() { //last key in the tree (right all the way down)
    if (!root)
        return "";
    RBTreeNode* temp(root);
    while (temp->getright() != nullptr)
        temp = temp->getright();
    return temp->getk();

}

DRT* RBTree::remove(string key) { //removes an item from the list
    if (key == "")
        return new DRT("", first(), last());
    return root->remove(key, "", "");
}

DRT* RBTree::search(string key) { //Database search method
    if (!root) return new DRT("", "", "");
    if (key == "")
        return new DRT("", first(), last());
    return root->searchnode(key, "", "");
}
//checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode



DRT* RBTree::modify(string key, string data) { //Database modify method

    if (key == "") return new DRT("", first(), last());
    if (data == "") {
        DRT* a = remove(key);
        assert(Valid() >= 0);
        return a;
    }
    DRT* a = add(key, data);
    assert(Valid() >= 0);
    return a;
}

int RBTree::Valid() {

	int r;

	if (!root) {
		r = 1;
	}
	else {
		if (!root->isblack() || root->getparent()) {
			r = 0;
		}
		else {
			r = root->ValidNode() != -1;
		}
	}
	return r;
}