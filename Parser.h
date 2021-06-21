#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include <ctype.h>
#include "errors.h"
#include "typedefs.h"


struct Token
{
    const char opcode;
    std::string value;
    std::string name;
};


struct Symbol
{
    std::string value; // see Token
    std::string name;
};


class Parser
{
    enum Flag : u8
    {
        newl = 1 << 0,
        col  = 1 << 1,
        tbl  = 1 << 2,
        decl = 1 << 3,
        def  = 1 << 4
    };

    Flag flags;
    long index;
    short column;
    int line;
    std::ifstream file;
    std::string code;
    std::string filename;
    std::vector<std::string> lines;

    const std::unordered_map<char, std::string> TOKENS =
    {
        {'{' , "L_BRACE"      }, {'}' , "R_BRACE"      },
        {'[' , "L_BRACKET"    }, {']' , "R_BRACKET"    },
        {'(' , "L_PAREN"      }, {')' , "R_PAREN"      },
        {'<' , "L_ANGLE"      }, {'>' , "R_ANGLE"      },
        {';' , "SEMI_COLON"   }, {'&' , "AMPERSAND"    },
        {'@' , "AT_SIGN"      }, {'*' , "STAR"         },
        {'!' , "EXCLAMATION"  }, {' ' , "WHITESPACE"   },
        {'\n', "NEW_LINE"     }, {'|' , "PIPE"         },
        {'#' , "HASH"         }, {'`' , "GRAVE_ACCENT" },
        {'=' , "EQUALS"       }, {'_' , "UNDERSCORE"   },
        {'%' , "MOD"          }, {'~' , "TILDE"        },
        {'-' , "DASH"         }, {'$' , "DOLLAR"       },
        {'.' , "IDENTIFIER"   }, {'/' , "NUMBER"       }
    };

    const std::unordered_map<std::string, std::string> SYMBOLS =
    {
        { "$", "COMMENT"     }, { "<.>", "TYPE"         },
        { "%", "DEFAULT"     }, { "{"  , "L_BRACE"      },
        { "}", "R_BRACE"     }, { "["  , "L_BRACKET"    },
        { "]", "R_BRACKET"   }, { "("  , "L_PAREN"      },
        { ")", "R_PAREN"     }, { "->" , "DEFINE"       },
        { ";", "END"         }, { "&"  , "UNIQUE"       },
        { "*", "COL_DECLAR"  }, { "#"  , "TABLE_DECLAR" },
        { "!", "PKEY_DECLAR" }, { "`"  , "STRING_LIT"   },
        { "_", "NULLABLE"    }, { "~"  , "NULL"         },
        { "/", "NUMBER"      }, { "."  , "IDENTIFIER"   }
    };

    char get_c();
    std::string make_value();
    std::string make_number();
    std::string calculate_name(const char&);
    Token create_token(const char&);
    Token create_token(const std::string&);
    ParserError error(std::string);
    char advance();

    public:
    explicit Parser(std::string fname) : filename(fname) {}
    std::string& read(bool = false);
    std::vector<Symbol> parse(const bool& = false);
};
