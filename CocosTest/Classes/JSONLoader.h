//
//  JSONLoader.h
//  CocosTest
//
//  Created by Michael Levesque on 7/7/17.
//
//

#ifndef JSONLoader_h
#define JSONLoader_h

#include "document.h" // for rapidjson::Document

/**
 * JSONLoader loads a given json file and uses Rapid JSON to to parse it.
 */
class JSONLoader {
private:
    // store filename so it can be reloaded whenever
    const char* m_filename;
    
    // this is the Rapid JSON object that the file gets parsed into
    rapidjson::Document m_document;
public:
    // Constructor. This will start loading and parsing the given file.
    JSONLoader (const char* filename);
    
    // will reopen the file and reparse it.
    void Reload (void);
    
    // returns the Rapid JSON parsed object.
    rapidjson::Document* GetDocument (void);
};

#endif /* JSONLoader_h */
