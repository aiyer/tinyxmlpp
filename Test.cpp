#include "tinyXMLpp.h"
#include "Acceptance.h"

#include <iostream>
#include <cassert>

using namespace tinyXMLpp;

int main(int argc, char** argv)
{	   
  /*
     std::ifstream f("t.xml");
     XMLTokenizer xt(f);
     TokenType tt;
     while(true){
     std::cout<<"\n";
     tt = xt.getToken();
     if( tt == START_TAG){
     std::cout<<"START_TAG:"<<xt.getTagName()<< "\nAttributes: \n";
     for(int i =0; i< xt.getAttributeCount(); ++i)
     std::cout<<xt.getAttributeName(i)<<":"<<xt.getAttributeValue(i)<<"\n";
     }

     if(tt == COMMENT)
     std::cout<<"COMMENT:"<<xt.getComment()<<"\n";

     if(tt == CDATA)
     std::cout<<"CDATA:"<<xt.getCDATA()<<"\n";

     if(tt == END_TAG)
     std::cout<<"END_TAG:"<<xt.getTagName()<<"\n";

     if(tt == TEXT)
     std::cout<<"TEXT_NODE:"<<xt.getText()<<"\n";

     if(tt == ENDOFFILE){
     std::cout<<"END_OF_FILE\n";
     break;
     }

     }

     return 1;*/

  //Create blank XML Document.
  std::unique_ptr<Document> doc(new Document());	

  //Creating child nodes
  ElementNode* root = ElementNode::createElementNode("Note");
  root->addAttribute("Id","1");	//Adding Attribute
  root->addChildNode(TextNode::createTextNode("Hello World"));

  ElementNode* elem = ElementNode::createElementNode("InnerNote");
  elem->addAttribute("Name","Pen");
  elem->addAttribute("Color", "Blue");
  elem->addChildNode(TextNode::createTextNode("Inner Text Node"));

  //Adding child nodes
  doc->addChildNode(CommentNode::createCommentNode("Topmost Comment."));
  doc->addChildNode(root);
  root->addChildNode(elem);

  //Writing the DOM to an XML file
  doc->write("output.xml");

/*
  std::string file_in = "t.xml", file_out = "tout.xml";	
  Parser p;

  //Invoking the function to parse the XML file
  std::unique_ptr<Document> d = p.parse(file_in);

  //DOM Navigation
  ElementNode *r = d->getRootElement();
  Node* t1 = r->getChildren()[2];
  Node* t2 = t1->getNextSibling();
  Node* t3 = t1->getPreviousSibling();

  //DOM Manipulation
  r->removeChildNode(t1);
  t3->addChildNode (TextNode::createTextNode("test node"));

  //More DOM Navigation
  auto node = d->getElementById ("test");
  auto nodes = d->getElementsByTagName ("tag_name");

  //Writing the DOM to an XML file.
  d->write( file_out );

  //Testing whether the two given XML files are the same.
  tinyXMLtest::accept_files(file_in,file_out);
*/
  return 0;
}
