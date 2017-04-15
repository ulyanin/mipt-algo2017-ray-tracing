//
// Created by ulyanin on 15.04.17.
//

#include "ParserRT.h"


ParserRT::ParserRT(const std::string &path) :
        path_(path)
{

}

std::vector<IGraphObject *> ParserRT::getObjects()
{
    return objects_;
}

void ParserRT::parseAll()
{

}
