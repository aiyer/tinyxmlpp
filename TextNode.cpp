#include "TextNode.h"

namespace tinyXMLpp {
  /**
   * Constructor which takes as input the text for the TextNode
   *
   *@param text The value to be used to create a TextNode object.
   */
  TextNode::TextNode(std::string text) 
  {	
    this->text = text;
  }

  /**
   * Destructor
   */
  TextNode::~TextNode() 
  {
  }

  /**
   * Function to create a TextNode.
   *
   *@param text The input text used for creating a TextNode
   *@return An object of type TextNode*
   */
  TextNode* TextNode::createTextNode(const std::string& text)
  {
    return new TextNode(text);
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a TextNode.
   *
   *@param child Node that is trying to be added as a child of the TextNode.
   */
  void TextNode::addChildNode (Node* child) 
  {
    throw XMLException("\nError! Trying to add a child to a TEXT node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot add child node to a TextNode.
   *
   *@param child Node that is trying to be added as a child of the TextNode.
   *@param index Index at which the new child is trying to be added to, in the TextNode's child node list.
   */
  void TextNode::addChildNode (Node* child, int index) 
  {
    throw XMLException("\nError! Trying to add a child to a TEXT node\n");
  }

  /**
   * Function which returns the text within the TextNode
   *
   *@return A string which contains the text within the TextNode
   */
  std::string TextNode::getText() const
  {
    return this->text;
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from TextNode
   *as it does not have any children.
   *
   *@param child Node that is trying to be removed from the child list of the TextNode.
   */
  void TextNode::removeChildNode (Node* node) 
  {
    throw XMLException ("nError! Trying to remove a child from a TEXT node\n");
  }

  /**
   *Overrided function from Node.h. Overrided to make it throw an exception if used. Cannot remove child node from TextNode
   *as it does not have any children.
   *
   *@param index Index from which a child is trying to be removed from the child list of the TextNode.
   */
  void TextNode::removeChildNode (int index) 
  {
    throw XMLException ("nError! Trying to remove a child from a TEXT node\n");
  }

  /**
   *Function to write the TextNode as a text string into the output stream.
   *
   *@param os The output stream to which the text should be written.
   */
  void TextNode::write(std::ostream& os) const
  {
    os << this->getText();
  }
}
