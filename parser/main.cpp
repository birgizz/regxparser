#include <iostream>
#include <vector>
#include <string>
#include "header/op.h"
#include "header/lexer.h"
#include "header/single_expr.h"
#include "header/or.h"
#include "header/expr.h"
#include "header/concat.h"
#include "header/group.h"
#include "header/more.h"
#include "header/string.h"
#include "header/digit.h"
#include "header/counter.h"
#include "header/any.h"
#include "header/ignore.h"
#include "header/out.h"
#include "header/program.h"
#include "header/char.h"
/*
<PROGRAM> -> <EXPR> | <OUT>
<EXPR>  -> <CONCAT>| <SINGLE_EXPR>
<CONCAT> -> <SINGLE_EXPR><CONCAT>
<SINGLE_EXPR> -> <OR> | <MORE> | <IGNORE> | <COUNT> | <GROUP>| <ANY>|<STRING>
<COUNTER> -> <SINGLE_EXPR>{<DIGIT>}
<OR> -> <STRING> + <STRING>
<MORE> -> <string>*|<ANY>* 
<OUT> ->  <EXPR>\{<DIGIT>}
<IGNORE> ->  <STRING>\I|<GROUP>\I
<GROUP> -> (<EXPR>)
<DIGIT> -> 1|2|3|4|5|6|7|8|9
<STRING> -> allt utom  .  * (  )  \I   \O
<ANY> -> .
*/
using it = std::string::iterator;
std::vector<std::string> captures;
std::string capture;
bool tolow; 
it begin_of_match;
op* program_parse(it& first, it& last);
void print_ast_tree(op*& o, int i);
op* get_out(it& first, it& last);
op* get_string(it& first, it& last);
op* get_expr(it& first, it& last);
op* get_single_expr(it& first, it& last);
op* concat(it& first, it& last);
op* get_group(it& first, it& last);
op* get_count(it& first, it& last);
op* get_ignore(it& first, it& last);
op* get_more(it& first, it& last);
op* get_or(it& first, it& last);
op* get_any(it& first, it& last);  

int main(int argc, char** argv)
{  
    std::string input = argv[1];
    std::string source = "Waterloo I was defeated, you won the war Waterloo promise to love you for ever more Waterloo couldn't escape if I wanted to Waterloo knowing my fate is to be with you Waterloo finally facing my Waterloo";
    it begin = input.begin();    
    it end = input.end();
    it sourceBegin = source.begin();    
    it sourceEnd = source.end();     
    op* result = program_parse(begin, end);
    print_ast_tree(result,0);    
    result->eval(sourceBegin,sourceEnd);
    return 0;
}     
op* program_parse(it &first, it &last)
{
    if(first == last) return nullptr;
    op* expr_or_out = get_out(first, last);
    if(!expr_or_out) expr_or_out = get_expr(first, last);  
    program* prog = new program; 
    prog->operands.push_back(expr_or_out);
    return prog; 
}
op* get_expr(it& first, it& last)
{
    if(first == last) return nullptr;
    op* concat_or_single = concat(first, last);
    if(!concat_or_single) concat_or_single = get_single_expr(first, last);
    op* ex = new expr;
    ex->operands.push_back(concat_or_single);
    return ex;
}
op* get_single_expr(it& first, it& last)
{
    if(first == last) return nullptr;
    std::vector<std::function<op*(it &first, it &last)>> func_calls = {get_or,get_more,get_ignore,get_count,get_group,get_any,get_string};
    it start = first;
    op* get_expr;
    for(auto function: func_calls)
    {
       get_expr = function(first, last);
       if(get_expr) break;
    }
    if(!get_expr){first = start; return nullptr;}
    single_expr* ex = new single_expr;
    ex->operands.push_back(get_expr);
    return ex;
}
op* get_out(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    op* special = get_expr(first, last);
    if(!special){first = start; return nullptr;}
    lexer tk = next_token(first, last);
    if(tk.id != lexer::OUT){first = start; return nullptr;}
    digit* dig = new digit;
    dig->_id = tk.text;
    first+4;
    counter * count= new counter;
    out * Out = new out;
    Out->rhs = tk.text;
    count->operands.push_back(dig);
    Out->operands.push_back(special);
    Out->operands.push_back(count);
    return Out;
}
op* get_ignore(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    op* special = get_string(first, last);
    if(!special) 
    {
        special = get_group(first, last);
        if(!special) 
        {
        first = start;
        return nullptr;
        }
    }
    lexer tk = next_token(first, last);
    if(tk.id != lexer::IGNORE_UPPERCASE) 
    {
        first = start;
        return nullptr;
    }
    first = first + 2;
    
    
    ignore* ignore_expr = new ignore;
    tolow = true;
    ignore_expr->operands.push_back(special);
    return ignore_expr; 
}
op* get_count(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    op* special = get_string(first, last);
    
    if(!special)
    {
        first = start;
        return nullptr;
    }

    lexer tk = next_token(first, last);
    if(tk.id != lexer::COUNTER) 
    {
        first = start;
        return nullptr;
    }
    digit* dig = new digit;
    dig->_id = tk.text;

   
    first++;
    counter * count= new counter;
    count->operands.push_back(special);
    count->operands.push_back(dig);
   
    return count;
}
op* get_any(it& first, it& last)
{    
    it start = first;
    if(first == last) return nullptr;
    lexer tk = next_token(first, last);
    if(tk.id != lexer::ANY)
    {
        first = start;
        return nullptr;
    }
    first++;
    any* expr = new any;
    return expr;
}
op* get_string(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    string* String = new string;
    lexer tk = next_token(first, last);

    while(tk.id == lexer::ID) 
    {
        String->_id += tk.text;
        tk = next_token(++first, last);
    }
    if(start == first) return nullptr;
    return String;
}
op* get_group(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    lexer tk = next_token(first, last);
    if(tk.id != lexer::LEFT_PAR) 
    {
        return nullptr;
    }
    first++;
    op* final_expr = get_expr(first, last);
    if(!final_expr) 
    {
        first = start;
        return nullptr;
    }
    tk = next_token(first, last);
    if(tk.id != tk.RIGHT_PAR) 
    {
        first = start;
        return nullptr;
    }
    first++;
    group* group_expr = new group;
    group_expr->operands.push_back(final_expr);
    return group_expr;
}
op* get_more(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first;
    op* special = get_string(first, last);
    if(!special) 
    {
        special = get_any(first, last);
        if(!special) 
        {
        first = start;
        return nullptr;
        }
    }
    lexer tk = next_token(first, last);
    if(tk.id != lexer::STAR)
    {
        first = start;
        return nullptr;
    }
    first++;
    more* star_expr = new more;
    char_expr* Char_expr = new char_expr; 
    if (special->id() == ".")
    {
        Char_expr->_id = "*";
    }else
    {
        Char_expr->_id = *(special->id().end()-1);
    }
    star_expr->operands.push_back(special);
    star_expr->operands.push_back(Char_expr);
    return star_expr;
}
op* get_or(it& first, it& last)
{
    if(first == last) return nullptr;
    it start = first; 
    op* Or_expr = get_string(first, last);
    if(!Or_expr) 
    {
        first = start;
        return nullptr;
    }
    lexer tk = next_token(first, last);
    if(tk.id != lexer::OR) 
    {
        first = start;
        return nullptr;
    }
    first ++;
    op* final_expr = get_string(first, last);
    if(!final_expr) 
    {
        first = start;
        return nullptr;
    }
    or_expr* sub_expr = new or_expr;
    sub_expr->lhs = Or_expr->id();
    sub_expr->rhs = final_expr->id();
    sub_expr->operands.push_back(Or_expr);
    sub_expr->operands.push_back(final_expr);
    return sub_expr;
}

void print_ast_tree(op*& o, int i)
{
    i++;
    for(int j = 0; j < i; j++) 
    { 
            std::cout<<" |"; 
    }
    std::cout<<o->id()<<std::endl; 
    for(auto e : o->operands) 
    {
        print_ast_tree(e, i);
    }
}

op* concat(it& first, it& last)
{
    if(first == last) return nullptr;
    concat_expr* concat = new concat_expr;
    op* single_expr = get_single_expr(first, last);
    while(single_expr != nullptr)
    {
        concat->operands.push_back(single_expr);
        single_expr = get_single_expr(first, last);
    }
    return concat;
}