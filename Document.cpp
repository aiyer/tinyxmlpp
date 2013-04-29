#include "Document.h"
#include "ElementNode.h"
#include <regex>

namespace tinyXMLpp{

  /**
   * Function which returns the root element of the document.
   *
   *@return The root element of type ElementNode*.
   */
  ElementNode* Document::getRootElement() const 
  {	
    return this->rootElement;
  }

  /**
   * Destructor.
   */
  Document::~Document()
  {		
    int i;
    for (i = 0; i < this->childNodes.size(); ++i) {
      delete this->childNodes[i];
    }	
  }

  /**
   * Function which checks whether an input string contains only a combination of spaces, newlines and tabs. It uses regex to
   * do this checking.
   *
   *@param input The input string
   *@return A bool value which is true if the input string contains only spaces, newlines and tabs
   */
  bool Document::isEmptyText (const std::string& input) const {
    regex rx("[\\r\\n\\t\\s]*");
    return regex_match(input.begin(), input.end(), rx);
  }

  /**
   * Function to validate that a given Node is not of types CDATANode and Document types. It also makes sure that if the given node
   * is of type TextNode, its contents are empty. This is used whenever a child is being added to the document object. Only ElementNode,
   * CommentNode or TextNodes with empty strings can be added as a child of a Document node.
   *
   * @param child The node object to be validated.
   */
  void Document::validate(Node* child)
  {

    if (dynamic_cast<TextNode*>(child) != NULL) {
      if (!isEmptyText(static_cast<TextNode*>(child)->getText())) {
	throw XMLException ("Cannot add or remove a Text node directly to the XML Document");
      }
    }

    if (dynamic_cast<CDATANode*>(child) != NULL || dynamic_cast<Document*>(child) != NULL) {
      throw XMLException ("Cannot add or remove a CDATA Node or an XML Document directly to the XML Document");
    }		

  }

  /**
   * Function which sets the root element of the Document object.
   *
   * @param child The node to be set as the root element of the Document object.
   */
  void Document::setRootElement (Node* child)
  {
    ElementNode* temp = dynamic_cast<ElementNode*>(child);
    if (this->isRootSet == false || temp == NULL) {

      if ( temp != NULL) {
	this->rootElement = temp;
	this->isRootSet = true;
      }

    }
    else
      throw XMLException("Error! Root Element already exists for the document. A document cannot have more than one root.");
  }

  /**
   * Function to add a child node to the Document object.
   *
   * @param child The node to be added as a child of the Document object.
   */
  void Document::addChildNode (Node* child)  
  {
    validate(child);		
    setRootElement(child);
    this->childNodes.push_back(child);
  }

  /**
   * Function to add a child node to the Document object, at a given index.
   * 
   * @param child The node to be added as a child of the Document object.
   * @param index The index at which 'child' should be added as a child of the Document object.
   */
  void Document::addChildNode (Node* child, int index) 
  {
    validate(child);		
    setRootElement(child);
    if(index >= childNodes.size() || index < 0 )
      throw XMLException("\nError! Trying to add a child node at an index that doesn't exist");

    childNodes.insert(childNodes.begin() + index, child);
  }

  /**
   * Function to remove a node from the child nodes list of the Document object.
   *
   * @param child The node to be removed from the list of child nodes of the Document object.
   */
  void Document::removeChildNode (Node* child) 
  {
    validate(child);

    if (dynamic_cast<ElementNode*>(child) != NULL){
      this->isRootSet = false;
      this->rootElement = nullptr;
    }

    auto it = childNodes.begin();
    while (it != childNodes.end()){ 
      if (*it == child) {
	childNodes.erase(it);
	delete child;
	return;
      }
      ++it;
    }

    throw XMLException("\nError! Trying to remove a child node that doesn't exist");
  }

  /**
   * Function to remove a child at the given index from the list of child nodes of the Document object.
   *
   * @param index The index from which a child node should be removed from the list of children of the Document object.
   */
  void Document::removeChildNode (int index)
  {
    if(index >= this->childNodes.size())
      throw XMLException("\nError! Trying to remove a child node from an index that doesn't exist");

    Node* child = this->childNodes[index];
    if (dynamic_cast<ElementNode*>(child) != NULL){
      this->isRootSet = false;
      this->rootElement = nullptr;
    }

    childNodes.erase(childNodes.begin() + index);
    delete child;
  }

  /**
   * Function to write the Document node as an XML node into the given output stream.
   *
   * @param os The output stream to which the Document node should be written as an XML node.
   */
  void Document::write(std::ostream& os) const
  {
    if(!this->isRootSet)
      throw XMLException("XML Document does not have a root");

    for(int i=0; i < childNodes.size(); ++i){
      childNodes[i]->write( os );
    }
  }

  /**
   * Function to write the Document node as an XML node into a file at the given path.
   *
   * @param path The path to the file to which the Document object should be written as an XML node.
   */
  void Document::write(const std::string& path) const
  {
    if(!this->isRootSet)
      throw XMLException("XML Document does not have a root");

    std::ofstream file(path.c_str());		
    write(file);
    file.close();
  }

  /**
   * Recursive function called by the actual getElementById, that is exposed to the user.
   *
   * @param node A pointer to the current node in the recursion
   * @param id The string being searched for in the attribute values.
   * @return A pointer to the Node which has an attribute value that matches id
   */
  Node* Document::getElementById (Node* node, const std::string& id) {
    if (node != nullptr) {

      vector<Attribute*> attributes = static_cast<ElementNode*>(node)->getAttributes();
      for (int i = 0; i < attributes.size(); ++i) {
	Attribute* attrib = attributes[i];
	if (attrib->getValue() == id) {
	  return node;
	}
      }

      vector<Node*> children = node->getChildren();
      for (int i = 0; i < children.size(); ++i) {
	if (dynamic_cast<ElementNode*>(children[i]) == NULL)
	  continue;
	Node* temp = getElementById(children[i], id);
	if(!temp)
	  return temp;
      }

    }
    return nullptr;	
  }

  /**
   * Function to find the first node in the XML DOM object that has an attribute with the value provided as 'id'. This function
   * in turn calls the private getElementById function that takes in a Node* and std::string as arguments.
   *
   * @param id The string being searched for inside attribute values.
   * @return A pointer to an ElementNode which contains an attribute that has the value = id
   */
  ElementNode* Document::getElementById (const std::string& id) {
    return static_cast<ElementNode*>(getElementById(this->rootElement, id));
  }

  /**
   * Private, recursive function that gets called by the getElementsByTagName function that is exposed to users. It does a DFS
   * 
   * @param node The current node at this level of recursion.
   * @param tagName The tag name being searched for.
   * @param nodes A vector to hold the list of ElementNode that has a name matching 'tagName'
   */
  void Document::getElementsByTagName (Node* node, const std::string& tagName, vector<ElementNode*>& nodes) {
    if (node != nullptr) {
      if (static_cast<ElementNode*>(node)->getName() == tagName) {
	nodes.push_back(static_cast<ElementNode*>(node));
      }
      vector<Node*> children = node->getChildren();
      for (int i = 0; i < children.size(); ++i) {
	if (dynamic_cast<ElementNode*>(children[i]) == NULL)
	  continue;
	getElementsByTagName(static_cast<ElementNode*>(children[i]), tagName, nodes);
      }
    }
    return;
  }

  /**
   * Function exposed to the user, used to get a vector of ElementNode whose name is same as the value passed to the function
   * 
   * @param tagName The name being searched for, in all the element nodes.
   * @return A vector of ElementNode* which points to all the element nodes that have a name equal to the value passed to the function
   */
  vector<ElementNode*> Document::getElementsByTagName (const std::string& tagName) {
    vector<ElementNode*> outputNodes;
    getElementsByTagName (this->rootElement, tagName, outputNodes);
    return outputNodes;
  }

}
