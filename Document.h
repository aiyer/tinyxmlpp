#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__

#include <string>
#include <fstream>
#include "Node.h"
#include "Parser.h"
#include "Attribute.h"
#include "ElementNode.h"
#include "CDATANode.h"
#include <regex>

using namespace std;

namespace tinyXMLpp {

  class Document
  {	
    ElementNode* rootElement;

    vector<Node*> childNodes;

    bool isRootSet;		//Keeps track of whether the root element was set or not. Root element should be set only once.	

    bool isEmptyText (const std::string& input) const;

    void validate(Node* child);

    void setRootElement (Node* child);

    Node* getElementById (Node* node, const std::string& id);

    void getElementsByTagName (Node* node, const std::string& tagName, vector<ElementNode*>& nodes);


    public:		
    Document() : isRootSet(false), rootElement(nullptr) {}

    ~Document();

    /*Returns the XML document element(node)*/
    ElementNode* getRootElement() const;		

    /*call the function to commit the XML DOM to a file.*/
    void write(const std::string& path) const;
    void write(std::ostream& os) const;		

    /*Overloads for adding a node to the Document*/
    void addChildNode (Node* child);
    void addChildNode (Node* child,int index);

    /*Overloads for removing a node to the Document*/
    void removeChildNode (Node* child);
    void removeChildNode (int index);

    ElementNode* getElementById(const std::string& id);		
    vector<ElementNode*> getElementsByTagName(const std::string& tagName);

  };

}

#endif
