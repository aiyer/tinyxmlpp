#ifndef __XML_TOKENIZER_H__
#define __XML_TOKENIZER_H__

#include <string>
#include <vector>
#include <fstream>

namespace tinyXMLpp{

  enum TokenType { BOF, START_TAG, END_TAG, TEXT, CDATA, COMMENT, ENDOFFILE };

  class XMLTokenizer{

    std::istream& inputStream;
    TokenType tokenType;
    std::string tagName;
    std::vector<std::string> attrNames;
    std::vector<std::string> attrVals;
    std::string text;		
    bool hasEndTag;

    void reset();
    int readChar(bool skipWS);
    int peekChar();
    bool tryMatch(const std::string& str);

    void pushBack(int c);
    void parseText();		
    bool parseAttributes();
    void parseStartTag();
    void parseEndTag();		
    void parseCDATA();		
    void parseComment();
    void skipUnimpChars();

    public:
    /*Constructor to initialize the Tokenizer*/
    XMLTokenizer(std::istream& input): 
      inputStream(input), tokenType(BOF) { };

    /*returns the token type of the next token from 
      the input stream*/
    TokenType getToken();

    /*Methods which expose the Tokens based on the Token type*/
    std::string getTagName();
    std::string getAttributeValue(const std::string& attrName);
    int getAttributeCount();
    std::string getAttributeName(int idx);
    std::string getAttributeValue(int idx);
    std::string getText();
    std::string getCDATA();
    std::string getComment();

  };

}

#endif
