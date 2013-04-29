#include "CommentNode.h"
#include "XMLException.h"

namespace tinyXMLpp {

  /**
   *Function to create a CommentNode.
   *
   *@return a new CommentNode object.
   */
  CommentNode* CommentNode::createCommentNode()
  {
    return new CommentNode();
  }

  /**
   *Function to create a CommentNode.
   *
   *@param content The value for the comment node's conent.
   *@return a new CommentNode object.
   */
  CommentNode* CommentNode::createCommentNode(const std::string& content)
  {
    return new CommentNode(content);
  }

  /**
   *Default Constructor
   */
  CommentNode::CommentNode() 
  {
  }

  /**
   *Constructor
   *
   *@param comment The value for the comment node's content.
   */
  CommentNode::CommentNode(const std::string& comment) 
  {
    this->content = comment;
  }

  /**
   *Destructor
   */
  CommentNode::~CommentNode() 
  {
  }

  /**
   *Function to set the content of the CommentNode
   *
   *@param content The value for the comment node's conent.
   */
  void CommentNode::setContent(const std::string& content) 
  {
    this->content = content;
  }

  /**
   *Function to get the conent of the CommentNode
   *
   *@return The comment node's content.
   */
  std::string CommentNode::getContent() const 
  {
    return this->content;
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a CommentNode.
   *
   *@param child Node that is trying to be added as a child of the CommentNode.
   */
  void CommentNode::addChildNode (Node* child) 
  {
    throw XMLException("\nError! Trying to add a child to a COMMENT node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a CommentNode.
   *
   *@param child Node that is trying to be added as a child of the CommentNode.
   *@param index Index at which the new child is trying to be added to, in the CommentNode's child node list.
   */
  void CommentNode::addChildNode (Node* child, int index) 
  {
    throw XMLException("\nError! Trying to add a child to a COMMENT node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from CommentNode
   *as it does not have any children.
   *
   *@param child Node that is trying to be removed from the child list of the CommentNode.
   */
  void CommentNode::removeChildNode (Node* child) 
  {
    throw XMLException("\nError! Trying to remove a child from a COMMENT node\n");
  }


  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from CommentNode
   *as it does not have any children.
   *
   *@param index Index from which a child is trying to be removed from the child list of the CommentNode.
   */
  void CommentNode::removeChildNode (int index) 
  {
    throw XMLException("\nError! Trying to remove a child from a COMMENT node\n");
  }

  /**
   *Function to write the CommentNode as an XML comment into the output stream.
   *
   *@param os The output stream to which the comment should be written.
   */
  void CommentNode::write(std::ostream& os) const
  {
    os << "<!--" + this->getContent() + "-->";
  }

}
