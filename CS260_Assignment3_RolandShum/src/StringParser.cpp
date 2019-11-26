//
// Created by roland on 11/25/19.
//
#include "stdafx.h"
#include "StringParser.h"

// Given a string, splits it up into host name and local path
std::tuple<std::string_view, std::string_view> StringParser::ParseURL(std::string_view url)
{
    // Host name is everything between second and third slashes (if there is one)
    std::size_t host_start_pos = url.find("//") + 2;
    std::size_t host_end_pos = url.find("/", host_start_pos);

    // If there is no trailing '/', use the length of the string
    if(host_end_pos == std::string::npos)
    {
        std::string_view host_name = url.substr(host_start_pos, url.length() - host_start_pos);
        return std::make_tuple(host_name, "");
    }
    std::string_view host_name = url.substr(host_start_pos, host_end_pos - host_start_pos);

    // Get the rest of the local path
    std::string_view localPath = url.substr(host_end_pos, url.length());

    return std::make_tuple(host_name, localPath);
}

std::string StringParser::ComposeHTMLMessage(std::string RequestMethod, const std::string &host,
                                          const std::string &localPath)
{
    std::string result = std::move(RequestMethod);
    result.append(" ");
    if(localPath.empty())
        result.append("/");
    else
        result.append(localPath);
    result.append(" ");
    result.append("HTTP/1.1\r\nHost: ");
    result.append(host);
    result.append("\r\n\r\n");
    return result;
}

std::string StringParser::ReceiveHTML(TCPSocketPtr socket)
{
    // An PIv6 theoretically can hold 64kb
    constexpr int BUFFER_SIZE = 16000;
    // Store the message we are about to send.
    char buffer[BUFFER_SIZE] = {};


    // Read the first message.
    std::size_t num = socket->Receive(buffer, sizeof(buffer));
    buffer[num] = 0;
    std::string contentLength = buffer;

    // If the content of 400 is found...
    if(contentLength.find("Bad Request") != std::string::npos)
    {
        std::cout << "Error: 400 bad request" << std::endl;
        exit(1);
    }

    // std::cout << contentLength  << std::endl;

    // Find the Content-Length
    std::size_t start_content = contentLength.find("Content-Length: ") + 16;
    std::size_t end_length = contentLength.find("\r\n", start_content) - 1u;
    std::string number_in_string_form = contentLength.substr(start_content, end_length - start_content);
    long content_length = std::atoi(number_in_string_form.data());

    // We have found the length. Now we need to find the body.
    std::size_t body_start = contentLength.find("\r\n\r\n") + 4;

    // Calc the number of stuff we have received.
    long currentSize = contentLength.size() - body_start;

    long totalReadCount = currentSize;
    long currentReadCount = 0;
    std::string message;
    message.reserve(content_length);
    message = contentLength.substr(body_start, std::string::npos);

    // While we don't have the amount required, we keep reading
    while (content_length > totalReadCount)
    {
        currentReadCount = socket->Receive(buffer, sizeof(buffer));
        buffer[currentReadCount] = 0;
        message += buffer;
        totalReadCount += currentReadCount;
    }
    return message;
}
