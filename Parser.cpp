#include "Parser.h"


// Time: O(1)
// Space: O(1)
ParserError Parser::error(std::string msg)
{ return ParserError(msg, filename, lines[line], line, column); }


// Time: O(1)
// Space: O(1)
char Parser::advance()
{
    if (get_c() == '\n')
        flags = static_cast<Flag>(flags | newl);
    line += ((flags & newl) == newl);
    column += ((flags & newl) != newl);
    column *= ((flags & newl) == newl);
    index++;
    return get_c();
}


// Time: O()
// Space: O()
// where 
std::string Parser::make_value()
{
    bool num = false;
    bool id = false;
    bool dec = false;
    std::string value;
    char c = get_c();
    while (std::isalnum(c) || c == '.')
    {
        value += c;
        if (c == '.' && (id || dec || !num))
            throw error("Too many decimal points");
        else if (std::isalpha(c) && (dec || num))
            throw error("Letter in number literal");
        else if (std::isdigit(c) && id)
            throw error("Number in Identifier");
        if (std::isdigit(c)) num = true;
        else if (std::isalpha(c)) id = true;
        else dec = (c == '.');
        c = advance();
    }
    return value;
}


// Time: O()
// Space: O()
// where 
std::string Parser::make_number()
{
    bool dec = false;
    std::string value;
    char c = get_c();
    while (std::isdigit(c) || c == '.')
    {
        value += c;
        if (c == '.' && dec)
            throw error("Too many decimal points");
        else dec = (c == '.');
        c = advance();
    }
    return value;
}


// Time: O(1)
// Space: O(1)
Token Parser::create_token(const char& c)
{
    char opcode;
    if (TOKENS.count(c) == 1) opcode = c;
    else if (std::isalpha(c)) opcode = '.';
    else if (std::isdigit(c)) opcode = '/';
    else throw error(&opcode);
    std::string name = TOKENS.at(opcode);
    std::string value = &c;
    Token token { opcode, name, value };
    return token;
}


// Time: O(1) - O(1)
// Space: O(1)
Token Parser::create_token(const std::string& chars)
{
    if (chars.size() == 1) return create_token(chars[0]);
    char opcode;
    if (std::isalpha(chars[0])) opcode = '.';
    else if (std::isdigit(chars[0])) opcode = '/';
    else throw error(&opcode);
    std::string name = calculate_name(opcode);
    return Token { opcode, chars, name };
}


// Time: O(1)
// Space: O(1)
char Parser::get_c()
{
    if (index < code.size()) return code[index];
    else throw error("End of file");
}


// Time: O(1)
// Space: O(1)
std::string Parser::calculate_name(const char& c)
{
    if (TOKENS.count(c) == 1) return TOKENS.at(c);
    else throw error(&c);
}


// Time: O(s)
// Space: O(s)
// where s = size of file
std::string& Parser::read(bool close)
{
    code.erase(0, code.size());
    if (!file.is_open()) file.open(filename, file.in);
    std::string buffer;
    while (std::getline(file, buffer))
    {
        code += buffer + '\n';
        lines.push_back(buffer);
    }
    delete &buffer;
    if (close) file.close();
    return code;
}


// Time: O(s + t - i)
// Space: O()
// where s = file size, t = # of tokens found, and i = number of tokens which are whitespace
std::vector<Symbol> Parser::parse(const bool& verbose)
{
    read();
    std::vector<Token> tokens;
    long code_size = code.size();
    index = 0;
    char c = get_c();
    for (;index < code_size; c = advance())
    {
        if (std::isalnum(c)) tokens.push_back(create_token(make_value()));
        else if (TOKENS.count(c) == 1) tokens.push_back(create_token(c));
        else throw error("Invalid token");
    }

    if (verbose)
    {
        std::cout << "Uncleaned Tokens:" << std::endl;
        for (Token token : tokens)
        {
            char opcode = token.opcode;
            std::string value;
            if (opcode == '\n') value = "\\n";
            else if (opcode == '\t' || opcode == ' ') value = "\\t";
            else value = &opcode;
            std::string name = token.value;
            std::cout << '\t' << value << ':' << name << std::endl;
        }
        std::cout << std::endl;
    }

    std::vector<Token> cleaned;
    for (Token token : tokens)
        if (token.opcode != '\n' && token.opcode != ' ' && token.opcode != '\t')
            cleaned.push_back(token);

    delete &tokens;

    bool ignore = false;
    std::vector<Symbol> symbols;
    std::string key, current, next, two_ahead;
    for (int i = 0; i < cleaned.size(); i++)
    {
        current = cleaned[i].opcode;
        next = cleaned[(i+1) % cleaned.size()].opcode;
        two_ahead = cleaned[(i-1) % cleaned.size()].opcode;
        next = current + next;
        two_ahead = next + two_ahead;
        ignore = (current == "$");
        if (!ignore)
        {
            if (SYMBOLS.count(two_ahead) == 1) key = two_ahead;
            else if (SYMBOLS.count(next) == 1) key = next;
            else if (SYMBOLS.count(current) == 1) key = current;
            else key = '.';

            Symbol symbol { key, SYMBOLS.at(key) };
            symbols.push_back(symbol);
        }
    }

    if (verbose)
    {
        std::cout << "Symbols:" << std::endl;
        for (Symbol symbol : symbols) std::cout << '\t' << symbol.value << ':' << symbol.name << std::endl;
        std::cout << std::endl;
    }

    return symbols;
}
