#include "base.h"

inline internal bool is_whitespace(char c)
{
	return ((c == ' ') || (c == '\t') || (c == '\n') || (c == ' ') || (c == '\r') || (c == '\v') || (c == '\f'));
}

inline internal bool is_alphabet(char c)
{
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

inline internal bool is_digit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

enum TokenType
{
    TokenType_INVALID,
    TokenType_SEMICOLON,
    TokenType_OPEN_PARENTHESIS,
    TokenType_CLOSE_PARENTHESIS,
    TokenType_OPEN_BRACES,
    TokenType_CLOSE_BRACES,
    TokenType_COMMA,
    TokenType_ASSIGN,
    TokenType_MULTIPLY,
    TokenType_DIVIDE,
    TokenType_PLUS,
    TokenType_MINUS,
    TokenType_NOT,
    TokenType_EQUALS,
    TokenType_NOT_EQUALS,
    TokenType_LESS_THAN,
    TokenType_GREATER_THAN,
    TokenType_LESS_THAN_EQUALS_TO,
    TokenType_GREATER_THAN_EQUALS_TO,
	TokenType_INT_LITERAL,
	TokenType_STRING_LITERAL,
	TokenType_KEYWORD,
	TokenType_IDENT,
	TokenType_EOF,
	TokenType_KEYWORDS_BEGIN,
	TokenType_LET,
	TokenType_RETURN,
	TokenType_FUNC,
	TokenType_IF,
	TokenType_ELSE,
	TokenType_FOR,
	TokenType_TRUE,
	TokenType_FALSE,
	TokenType_KEYWORDS_END,
};

struct Token
{
    TokenType type;
	u64 start_index;
	u64 len;
};

// NOTE(karan): This can be a hash map so that token can be matched quickly to a keyword
char* g_keywords[] =
{
	"let",
	"return",
	"fn",
	"if",
	"else",
	"for",
	"true",
	"false"
};

char* g_token_type_strings[] =
{
    "INVALID",
    "SEMICOLON",
    "OPEN_PARENTHESIS",
    "CLOSE_PARENTHESIS",
    "OPEN_BRACES",
    "CLOSE_BRACES",
    "COMMA",
    "ASSIGN",
    "MULTIPLY",
    "DIVIDE",
    "PLUS",
    "MINUS",
    "NOT",
    "EQUALS",
    "NOT_EQUALS",
    "LESS_THAN",
    "GREATER_THAN",
    "LESS_THAN_EQUALS_TO",
    "GREATER_THAN_EQUALS_TO",
	"INT_LITERAL",
	"STRING_LITERAL",
	"KEYWORD",
	"IDENT",
	"EOF",
	"KEYWORDS_BEGIN",
	"LET",
	"RETURN",
	"FUNC",
	"IF",
	"ELSE",
	"FOR",
	"TRUE",
	"FALSE",
	"KEYWORDS_END",
};


s32 get_index_of(char **arr, u32 arr_len, char* str, u32 str_len)
{
	s32 result = -1;
	for(u32 i = 0; i < arr_len; i++)
	{
		bool equal = true;
		for(u32 j = 0; j < str_len; j++)
		{
			if(str[j] != arr[i][j]){ equal = false; break;}
		}
		
		if(equal && arr[i][str_len] == 0){ result = i; break;}
	}
	
	return result;
}


internal void get_token(char *source, u64* index, Token *result)
{
    u64 i = *index;
    while(is_whitespace(source[i])) i++;
    
    if(is_alphabet(source[i]) || source[i] == '_')
    {
		result->type = TokenType_IDENT;
		result->start_index = i++;
        while(is_alphabet(source[i]) || is_digit(source[i]) || source[i] == '_') ++i;
		result->len = i - result->start_index;
		s32 keyword_index = get_index_of(g_keywords, LEN(g_keywords), source + result->start_index, result->len);
		if(keyword_index != -1)
		{
			result->start_index = 0;
			result->len = 0;
			result->type = (TokenType)((s32)TokenType_KEYWORDS_BEGIN + keyword_index + 1);
		}
	}
    else if(is_digit(source[i]))
    {
		result->type = TokenType_INT_LITERAL;
		result->start_index = i;
		while(is_digit(source[++i]));
		result->len = i - result->start_index;
    }
    else
    {
        switch(source[i])
        {
			case 0:
			{
				result->type = TokenType_EOF;
				++i;
			}break;
            case ';':
            {
                result->type = TokenType_SEMICOLON;
				++i;
            }break;
            case '(':
            {
                result->type = TokenType_OPEN_PARENTHESIS;
				++i;
            }break;
            case ')':
            {
                result->type = TokenType_CLOSE_PARENTHESIS;
				++i;
            }break;
            case '{':
            {
                result->type = TokenType_OPEN_BRACES;
				++i;
            }break;
            case '}':
            {
                result->type = TokenType_CLOSE_BRACES;
				++i;
            }break;
            case ',':
            {
                result->type = TokenType_COMMA;
				++i;
            }break;
            case '=':
            {
				if(source[i+1] == '=')
				{
					result->type = TokenType_EQUALS;
					i+=2;
				}
				else
				{
					result->type = TokenType_ASSIGN;
					++i;
				}
            }break;
			case '!':
            {
                if(source[i+1] == '=')
				{
					result->type = TokenType_NOT_EQUALS;
					i+=2;
				}
				else
				{
					result->type = TokenType_NOT;
					++i;
				}
            }break;
            case '+':
            {
                result->type = TokenType_PLUS;
				++i;
            }break;
            case '-':
            {
                result->type = TokenType_MINUS;
				++i;
            }break;
            case '/':
            {
                result->type = TokenType_DIVIDE;
				++i;
            }break;
            case '*':
            {
                result->type = TokenType_MULTIPLY;
				++i;
            }break;
			case '<':
            {
				if(source[i+1]='=')
				{
					result->type = TokenType_LESS_THAN_EQUALS_TO;
					i+=2;
				}
				else
				{
					result->type = TokenType_LESS_THAN;
					++i;
				}
            }break;
			case '>':
            {
				if(source[i+1]='=')
				{
					result->type = TokenType_GREATER_THAN_EQUALS_TO;
					++i;
				}
				else
				{
					result->type = TokenType_GREATER_THAN;
					++i;
				}
            }break;
			case '"':
			{
				result->start_index = i++;
				while(source[i] != 0 && source[i] != '"') ++i;
				if(source[i] == 0) {result->type = TokenType_INVALID;}
				else {++i; result->type = TokenType_STRING_LITERAL;}
				result->len = i - result->start_index;
			}break;
			default: { ++i;}
        }
    }
	
	*index = i;
}


int main()
{
	u32 num_keyword_tokens = (u32)TokenType_KEYWORDS_END - (u32)TokenType_KEYWORDS_BEGIN - 1;
	u32 num_tokens = (u32)TokenType_KEYWORDS_END - (u32)TokenType_INVALID + 1;
	ASSERT(num_keyword_tokens == LEN(g_keywords), "There are %d keyword tokens, but only %llu string representations of those tokens are defined", num_keyword_tokens, LEN(g_keywords));
	ASSERT(num_tokens == LEN(g_token_type_strings), "There are %d tokens, but only %llu string representations of those tokens are defined", num_tokens, LEN(g_token_type_strings));
	
	char *test = R"FOO(
            let five = 5;
            let ten = 10;
            let add = fn(x, y) {
            x + y;
            };
            let result = add(five, ten);
            )FOO";
	
	u64 index = 0;
	Token result = {};
	Token clear = {};
	do{
		result = clear;
		get_token(test, &index, &result);
		LOG("Token Type: %s", g_token_type_strings[result.type]);
		if(result.len > 0) LOG(" = %.*s", (s32)result.len, test + result.start_index);
		LOG("\n");
	} while(result.type != TokenType_EOF);
	
	return 0;
}