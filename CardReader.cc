#include "CardReader.h"
#include "FlashCardApp.h"

#include <rapidjson/document.h>

#include <string.h>

#include <stdio.h>
#include <stdlib.h>


#include <fstream>
#include <streambuf>
#include <string>
#include <iostream>

using namespace std;

string CardReader::getFileContents()
{
    ifstream t(fileName.c_str());
    string str((istreambuf_iterator<char>(t)),
                 istreambuf_iterator<char>());
    return str;
}

void CardReader::sendStringsToApp(FlashCardApp *app)
{
    rapidjson::Document d;

    string contents = getFileContents();

    d.Parse<0>(contents.c_str());

cout << "parsed\n";

    const rapidjson::Value& strings = d["strings"];

cout << "got strings\n";

    for (rapidjson::SizeType i = 0; i < strings.Size(); i++) 
    {
        string nextString = strings[i].GetString();
        app->addCardValue(nextString);
    }

}

