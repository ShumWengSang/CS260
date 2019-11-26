//
// Created by roland on 11/25/19.
//

#ifndef CS260_ASSIGNMENT3_ROLANDSHUM_STRINGPARSER_H
#define CS260_ASSIGNMENT3_ROLANDSHUM_STRINGPARSER_H

#include "TCPSocket.h"

class StringParser
{
public:
    static std::tuple<std::string_view, std::string_view> ParseURL(std::string_view url);
    static std::string ComposeHTMLMessage(std::string RequestMethod, const std::string &host,
                                          const std::string &localPath);
    static std::string ReceiveHTML(TCPSocketPtr socketptr);
};


#endif //CS260_ASSIGNMENT3_ROLANDSHUM_STRINGPARSER_H
