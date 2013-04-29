#include "ElementNode.h"
#include "Attribute.h"

namespace tinyXMLpp {

  /**
   *Function to create an empty ElementNode.
   *
   *@return Returns an object of ElementNode without a name.
   */
  ElementNode* ElementNode::createElementNode()
  {
    return new ElementNode();
  }

  /**
   *Function to create an empty ElementNode with the name passed to the function.
   *
   *@param name The name of the ElementNode.
   *@return Returns an object of ElementNode with the name passed as an argument.
   */
  ElementNode* ElementNode::createElementNode(const std::string& name)
  {
    return new ElementNode(name);
  }

  /**
   *Destructor
   */
  ElementNode::~ElementNode()
  {
    for(int i=0;i<this->attributes.size();++i){
      delete this->attributes[i];
    }
  }

  /**
   *Function to add an attribute to the ElementNode
   *
   *@param key The key or name in the name-value pair of the Attribute to be added to the attributes list of the ElementNode
   *@param value The value in the name-value pair of the Attribute to be added to the attributes list of the ElementNode.
   */
  void ElementNode::addAttribute (const std::string& key, const std::string& value) {		
    attributes.push_back(new Attribute(key, value));
    ++numberOfAttributes;
  }

  /**
   *Function to add an attribute to the ElementNode
   *
   *@param attrib The Attribute object to be added to the attributes list of the ElementNode.
   */
  void ElementNode::addAttribute (Attribute* attrib) {
    attributes.push_back(attrib);
    ++numberOfAttributes;
    return;
  }

  /**
   *Function to find the number of attributes present in the ElementNode.
   *
   *@return The number of attributes present in the ElementNode.
   */
  int ElementNode::getNumberOfAttributes() const{
    return this->numberOfAttributes;
  }

  /**
   *Function to find the name of the ElementNode.
   *
   *@return The name of the ElementNode.
   */
  std::string ElementNode::getName () const {
    return this->name;
  }

  /**
   *Function which returns an attribute with the given name, if it is present in the ElementNode
   *
   *@param name The name of the attribute.
   *@return The attribute with the name passed as argument, if present in the node. Otherwise, return nullptr.
   */
  Attribute* ElementNode::getAttribute (const std::string& name) {
    std::vector<Attribute*>::iterator it = this->attributes.begin();
    Attribute* temp;
    while (it != this->attributes.end()) {
      temp = *it;
      if (temp->getName() == name) {
	return temp;
      }
    }
    return nullptr;
  }

  /**
   *Function which removes an attribute with the given name, if it is present in the ElementNode. Otherwise, throw XMLException.
   *
   *@param name The name of the attribute to be removed from the attribute list of the ElementNode.
   */
  void ElementNode::removeAttribute (const std::string& name) {
    std::vector<Attribute*>::iterator it = this->attributes.begin();
    Attribute* temp;
    while (it != this->attributes.end()) {
      temp = *it;
      if (temp->getName() == name) {
	this->attributes.erase(it);
	delete temp;
	return;
      }
    }
    throw XMLException ("The attribute you tried to delete, does not exist");
  }

  /**
   *Function which returns the attributes of the current ElementNode.
   *
   *@return vector of Attribute* 
   */
  const std::vector<Attribute*>& ElementNode::getAttributes() const {
    return this->attributes;
  }

  /**
   *Function to write the ElementNode as an XML element into the output stream. It also calls the write function on the child nodes.
   *
   *@param os The output stream to which the XML element should be written.
   */
  void ElementNode::write(std::ostream& os) const{

    os << "<" + this->getName();	

    auto attributes = this->getAttributes();
    for (int i = 0; i < attributes.size() ; ++i){   
      os << " " + attributes[i]->getName();
      os << "=\"" + attributes[i]->getValue() + "\"";
    }
    os << ">";

    auto children = this->getChildren();
    for(auto it = children.begin(); it != children.end(); ++it){		
      (*it)->write(os);
    }

    os << "</" +  this->getName() + ">";
  }

}
