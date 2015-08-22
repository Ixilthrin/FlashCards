#ifndef __cardreader_h__
#define __cardreader_h__

#include <string>
using namespace std;

class FlashCardApp;

class CardReader
{
public:
    CardReader(string aFile) : fileName(aFile)
    {}
    string getFileContents();
    void sendStringsToApp(FlashCardApp *app);
private:
    string fileName;
};


#endif
