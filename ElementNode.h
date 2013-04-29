#ifndef __ELEMENTNODE_H__
#define __ELEMENTNODE_H__

#include "Node.h"
#include "CommentNode.h"
#include "TextNode.h"

namespace tinyXMLpp{

  class ElementNode : public Node {
    std::vector<Attribute*> attributes;
    int numberOfAttributes;
    bool isRoot;
    std::string name;
    ElementNode(){}
    ElementNode(std::string name):numberOfAttributes(0), name(name) {  }
    public:		
    ~ElementNode();		

    /*Used to Construct the Element Node*/
    static ElementNode* createElementNode();
    static ElementNode* createElementNode(const std::string& name);

    /*Returns the name of the Element Tag*/
    std::string getName() const;

    /*Methods to add and remove attributes*/
    void addAttribute (Attribute* attrib);		
    void addAttribute(const std::string& key, const std::string& value);		
    void removeAttribute(const std::string& name);		

    /*Methods to retrieve the attributes*/
    int getNumberOfAttributes() const;
    Attribute* getAttribute(const std::string& name);
    const std::vector<Attribute*>& getAttributes() const;		

    /*Method to write the Node to an output stream*/
    void write(std::ostream& os) const;
  };

}
#endif
