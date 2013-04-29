#ifndef __TEXTNODE_H__
#define __TEXTNODE_H__

#include <iostream>
#include "Node.h"
#include "XMLException.h"

namespace tinyXMLpp{

  class TextNode : public Node {
    std::string text;
    TextNode(std::string text);
    public:
    ~TextNode();

    static TextNode* createTextNode(const std::string& text);

    void addChildNode (Node* child);

    void addChildNode (Node* child, int index) ;

    std::string getText() const;

    void removeChildNode (Node* child);

    void removeChildNode (int index);

    void write(std::ostream& os) const;
  };

}

#endif
