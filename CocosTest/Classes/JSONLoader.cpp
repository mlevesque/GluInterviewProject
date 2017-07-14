//
//  JSONLoader.cpp
//  CocosTest
//
//  Created by Michael Levesque on 7/7/17.
//
//

#include "JSONLoader.h"
#include <fstream>
#include <string>

/**
 * Constructor. We will try to load the file and parse it into the document object.
 */
JSONLoader::JSONLoader (const char* filename)
: m_filename(filename) {
    Reload();
}

/**
 * Reloads the file and re-parses it.
 */
void JSONLoader::Reload (void) {
    // Note that we should add error checking for file loading issues and JSON parsing issues.
    
    // load file and put into a string
    std::ifstream infile(m_filename);
    std::string file_contents {std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
    infile.close();
    
    // parse json
    m_document.Parse(file_contents.c_str());
}

/**
 * Returns a reference to the document object. This object contains the parsed JSON data.
 */
rapidjson::Document* JSONLoader::GetDocument (void) {
    return &m_document;
}
