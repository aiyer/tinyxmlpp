#include "Node.h"
#include "XMLException.h"

namespace tinyXMLpp{

  /**
   *Constructor
   */
  Node::Node() {
    this->numberOfChildren = 0;
    this->parentNode = nullptr;
    this->nextSibling = this->previousSibling = nullptr;
  }

  /**
   *Destructor
   */
  Node::~Node() {
    int i;
    for (i = 0; i < this->childNodes.size(); ++i) {
      delete this->childNodes[i];
    }
  }

  /**
   * Function which returns the list of child nodes of the current Node
   *
   *@return A vector of Node* containing pointers to all the child nodes of the current Node.
   */
  const std::vector<Node*>& Node::getChildren() const{
    return childNodes;
  }

  /**
   * Function which returns a pointer to the next sibling of the current node
   *
   *@return A pointer to the Node that is the next sibling of the current node.
   */
  Node* Node::getNextSibling() const{
    //Code to return the next sibling of the node.		
    return this->nextSibling;
  }

  /**
   * Function which returns a pointer to the previous sibling of the current node
   *
   *@return A pointer to the Node that is the previous sibling of the current node.
   */
  Node* Node::getPreviousSibling() const{
    //Code to return the previous sibling of the node.
    return this->previousSibling;
  }

  /**
   * Function which adds a child node to the current node's child list.
   *
   *@param child The node to be added as a child of the current node.
   */
  void Node::addChildNode (Node* child){
    if (this->childNodes.size() > 0) {
      child->previousSibling = this->childNodes.back();
      this->childNodes.back()->nextSibling = child;
    }
    this->childNodes.push_back(child);
    child->parentNode = this;
    ++numberOfChildren;
  }

  /**
   * Function which adds a child node to the current node's child list at the given index.
   *
   *@param child The node to be added as a child of the current node.
   *@param index The index at which the child should be added to the list of children.
   */
  void Node::addChildNode (Node* child, int index){
    if (index >= numberOfChildren || index < 0) {
      throw XMLException("\nError! Trying to add a child node at an index that doesn't exist");
    }

    auto it = childNodes.begin();
    Node* prev_it = nullptr;
    int temp = 0;
    while (it != childNodes.end()) { 
      if (temp == index) {
	if (index == 0) {
	  child->nextSibling = *it;
	  (*it)->previousSibling = child;
	}
	else {
	  prev_it->nextSibling = child;
	  (*it)->previousSibling = child;
	  child->previousSibling = prev_it;
	  child->nextSibling = *it;
	}
	childNodes.insert(it, child);
	child->parentNode = this;
	++numberOfChildren;
	return;
      }
      prev_it = *it;
      ++temp;
      ++it;
    }
    if (temp == index) {
      childNodes.insert(it, child);
      child->parentNode = this;
      ++numberOfChildren;
      return;
    }
    throw XMLException("\nError! Trying to add a child node at an index that doesn't exist");
  }

  /**
   * Function which removes a child node from the current node's child list.
   *
   *@param child The node to be removed from the child list of the current node.
   */
  void Node::removeChildNode (Node* child){
    auto it = childNodes.begin();
    while (it != childNodes.end()){ 

      if (*it == child) {
	if (child->previousSibling != nullptr)
	  child->previousSibling->nextSibling = child->nextSibling;
	if (child->nextSibling != nullptr)
	  child->nextSibling->previousSibling = child->previousSibling;

	childNodes.erase(it);
	--numberOfChildren;
	delete child;
	return;
      }

      ++it;
    }

    throw XMLException("\nError! Trying to remove a child node from an index that doesn't exist");
  }

  /**
   * Function which removes a child node from the current node's child list, at the given index.
   *
   *@param index The index from which a node is to be from the child list of the current node.
   */
  void Node::removeChildNode (int index){
    if (index >= numberOfChildren){
      throw XMLException("\nError! Trying to remove a child node from an index that doesn't exist");
    }
    auto it = childNodes.begin() + index;
    Node* child = *it;

    if (child->previousSibling != nullptr)
      child->previousSibling->nextSibling = child->nextSibling;
    if (child->nextSibling != nullptr)
      child->nextSibling->previousSibling = child->previousSibling;

    childNodes.erase(childNodes.begin() + index);
    delete child;
    --numberOfChildren;
  }	

  /**
   * Function which returns the parent node of the current node.
   *
   *@return A pointer to the parent node of this particular node.
   */
  Node* Node::getParentNode () const {
    return this->parentNode;
  }

}
