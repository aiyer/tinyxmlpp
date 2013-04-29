#include "CDATANode.h"
#include "XMLException.h"

namespace tinyXMLpp {
  /**
   *Constructor that takes the cdata section as its argument.
   *
   *@param cdata An entire 'cdata' section from the XML input, passed as text.
   */
  CDATANode::CDATANode(const std::string &cdata) 
  {
    this->cdata = cdata;
  }

  /**
   *Function to create a CDATANode.
   *
   *@param cdata An entire 'cdata' section from the XML input, passed as text.
   */
  CDATANode* CDATANode::createCDATANode(const std::string& cdata)
  {
    return new CDATANode(cdata);
  }

  /**
   *Destructor
   */
  CDATANode::~CDATANode() 
  {
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a CDATANode.
   *
   *@param child Node that is trying to be added as a child of the CDATA node.
   */
  void CDATANode::addChildNode (Node* child)
  {
    throw XMLException("\nError! Trying to add a child to a CDATA node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a CDATANode.
   *
   *@param child Node that is trying to be added as a child of the CDATA node.
   *@param index The index at which the node is trying to be added to the child nodes list.
   */
  void CDATANode::addChildNode (Node* child, int index) 
  {
    throw XMLException("\nError! Trying to add a child to a CDATA node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from CDATANode
   *as it does not have any children.
   *
   *@param child Node that is trying to be removed from the child list of the CDATA node.
   */
  void CDATANode::removeChildNode (Node* child)
  {
    throw XMLException("\nError! Trying to remove a child from a CDATA node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from CDATANode
   *as it does not have any children.
   *
   *@param index The index from which you are trying to remove a child of the CDATA node from.
   */
  void CDATANode::removeChildNode (int index) 
  {
    throw XMLException("\nError! Trying to remove a child from a CDATA node\n");
  }

  /**
   *Function returns the value of CDATA within the node.
   *
   */
  std::string CDATANode::getcdata() const
  {
    return this->cdata;
  }

  /**
   *Function to write the CDATANode as an XML CDATA section into the output stream.
   *
   *@param os The output stream to which the CDATA should be written.
   */
  void CDATANode::write(std::ostream& os) const
  {
    os<< "<![CDATA[" + this->getcdata() + "]]>\n";
  }

}
