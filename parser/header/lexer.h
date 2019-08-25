#include <string>
#include <cctype>
#include <algorithm>
struct lexer {

    enum id {
        ID,
        ANY,
        PLUS, 
        STAR,
        OR,
        SLASH, 
        LEFT_PAR,
        RIGHT_PAR,
        LEFT_BRA,
        RIGHT_BRA, 
        END_PROGRAM,
        OUT,
        IGNORE_UPPERCASE,
        COUNTER
    };
    id id;
    std::string text;
};


using it = std::string::iterator;

lexer next_token(it& first, it& last) {
    if( first == last) {
        return { lexer::END_PROGRAM, ""};
    }
    lexer tk;
    switch(*first) {
        case '*':
            tk = {lexer::STAR, "*"};
            break;
        case '.':
            if (std::string(first+2, first + 3) <= "9" and std::string(first+2, first + 3) >= "0" and std::string(first+3, first + 4) == "}") {
                        tk = {lexer::COUNTER, std::string(first+2, first + 3)};
                    }
                    else
                    {
                        tk = {lexer::ANY, std::string(first, first + 1)};
                    }
            break;
        case '+':
            tk = {lexer::OR, "|"};
            break;
        case '(':
            tk = {lexer::LEFT_PAR, "("};
            break;
        case ')':
            tk = {lexer::RIGHT_PAR, ")"};
            break;
        case '{':
            tk = {lexer::LEFT_BRA, "{"};
            break;
        case '}':
            tk = {lexer::RIGHT_BRA, "}"};
            break;
        case '\\':
            if (std::string(first, first + 1) == "\\") {
                if(std::string(first+1, first + 2)  == "I"  ) {
                    tk = {lexer::IGNORE_UPPERCASE, "\\I"}; 
                }else if (std::string(first+1, first + 2) == "O" and std::string(first+3, first + 4) <= "9" and std::string(first+3, first + 4) >= "0"  and std::string(first + 2 , first + 3)  == "{" and std::string(first+4, first + 5)  == "}") {
                    tk = {lexer::OUT, std::string(first+3, first + 4)};
                }   
            }
            break;
        default: 
                tk = {lexer::ID, std::string(first, first+1)};
            
    };
    return tk;
}