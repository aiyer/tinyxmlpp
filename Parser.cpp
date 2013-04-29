#include "Parser.h"
#include "XMLTokenizer.h"
#include "Node.h"
#include "Attribute.h"
#include "TextNode.h"
#include "CDATANode.h"
#include "ElementNode.h"
#include "CommentNode.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "Document.h"
#include "XMLException.h"

namespace tinyXMLpp {

  /**
   * Function that parses an XML file, given the path to the file.
   *
   *@param filePath The path to the input XML file
   *@return A unique_ptr to a Document object which holds the XML file as a tree.
   */
  std::unique_ptr<Document> Parser::parse(const std::string& filePath){
    std::ifstream ifs(filePath);
    return parse(ifs);
  }

  /**
   * Function which checks whether an input string is only made of spaces, newlines or tabs.
   *
   *@param input The input string.
   *@return A bool value set to true if the input string is made up only of spaces, newlines or tabs.
   */
  bool Parser::isEmptyText (const std::string& input) {
    regex rx("[\\r\\n\\t\\s]*");
    return regex_match(input.begin(), input.end(), rx);
  }

  /**
   * Function which checks whether an input string has any characters that are invalid when used within an XML document.
   * The characters >, < and &, are invalid, expect when used to delimit tags and such other special uses.
   *
   *@param input The input string.
   *@return A bool value set to true if the input string is invalid within an XML document.
   */
  bool Parser::isInvalidText (const std::string& input) {
    regex rx("[><&]");
    return regex_search(input.begin(), input.end(), rx);
  }

  /**
   * Function that parses an XML file, given an input stream.
   *
   *@param is An input stream which contains an XML file
   *@return A unique_ptr to a Document object which holds the XML file as a tree.
   */
  std::unique_ptr<Document> Parser::parse(std::istream& is) {		

    try{		

      XMLTokenizer t(is);			
      Document *documentNode = new Document();			
      Node *temp, *newNode;
      std::string currentNodeName = "";
      bool rootElementNotFound = true;
      std::string rootElementName = "";

      std::unique_ptr<Document> doc(documentNode);
      /*if (t.getToken() == TEXT) {
	if (!isEmptyText(t.getText())) 
	throw XMLException("The first TextNode is not empty");
	else if(t.getText() != "")
	documentNode->addChildNode( TextNode::createTextNode(t.getText()) );
	}*/

      while (true){

	switch (t.getToken()) {

	  case START_TAG:
	    currentNodeName = t.getTagName();
	    newNode = ElementNode::createElementNode(currentNodeName);

	    if (rootElementNotFound) {
	      rootElementNotFound = false;
	      rootElementName = t.getTagName();
	      documentNode->addChildNode(newNode);

	    }else{

	      temp->addChildNode(newNode);					
	    }

	    for (int i = 0; i < t.getAttributeCount(); ++i) {
	      static_cast<ElementNode*>(newNode)->addAttribute(t.getAttributeName(i), t.getAttributeValue(i));
	    }
	    temp = newNode;
	    break;

	  case END_TAG:
	    if (currentNodeName == t.getTagName()) {
	      if (temp->getParentNode() == nullptr) {
		if (currentNodeName == rootElementName) {
		  rootElementNotFound = true;
		  currentNodeName = "";
		  temp = nullptr;
		  break;
		}
	      }
	      else {
		temp = temp->getParentNode();

		if(dynamic_cast<ElementNode*>(temp) != NULL)
		  currentNodeName =  static_cast<ElementNode*>(temp)->getName();
	      }

	    }else{
	      throw XMLException("Mismatched Tags! Error.. ");						
	    }
	    break;

	  case TEXT:
	    if (isInvalidText (t.getText())) {
	      throw XMLException ("Invalid XML detected..");
	    }
	    std::cout << "*" << t.getText() << "*";
	    if (t.getText() == "") {
	      break;
	    }

	    newNode = TextNode::createTextNode(t.getText());
	    if (rootElementNotFound) {
	      documentNode->addChildNode(newNode);
	    }else{						
	      temp->addChildNode(newNode);
	    }

	    break;

	  case ENDOFFILE:
	    if (temp != nullptr) {
	      throw XMLException ("Mismatched tags");
	    }

	    return doc;

	  case BOF:
	    break;

	  case CDATA:
	    newNode = CDATANode::createCDATANode(t.getCDATA());

	    if (rootElementNotFound)
	      documentNode->addChildNode(newNode);												
	    else
	      temp->addChildNode(newNode);

	    break;

	  case COMMENT:
	    newNode =  CommentNode::createCommentNode(t.getComment());

	    if (rootElementNotFound)					
	      documentNode->addChildNode(newNode);						
	    else				
	      temp->addChildNode(newNode);

	    break;

	  default:
	    std::cout << "Default \n ";
	    return doc;

	}
      }

      return doc;

    }
    catch (bad_alloc&)
    {
      std::cerr<<"Out of Memory!\n";
      throw;
    }
    catch(XMLException&)
    {	
      throw;
    }
    catch(exception&)
    {
      throw;
    }

  }

}
