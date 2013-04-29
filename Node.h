#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <list>
#include <vector>
#include <memory>

namespace tinyXMLpp{

  class Attribute;

  class Node {

    int numberOfChildren;            		
    Node* parentNode;               
    std::vector<Node*> childNodes;  
    Node* nextSibling, *previousSibling;

    public:
    Node();
    virtual ~Node();

    /*retrieve parent-child-siblings*/
    const std::vector<Node*>& getChildren() const;
    Node* getParentNode () const;
    Node* getNextSibling() const;        
    Node* getPreviousSibling() const;		

    /*Methods which allow addition and 
      removal of children*/
    virtual void addChildNode (Node* child);
    virtual void addChildNode (Node* child, int index);		
    virtual void removeChildNode (Node* child);
    virtual void removeChildNode (int index);

    /*write contents of the node to ostream*/
    virtual void write(std::ostream& os) const = 0 ;
  };

}

#endif
