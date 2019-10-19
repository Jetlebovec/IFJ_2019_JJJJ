/**
 *      Project: IFJ – Implementace překladače imperativního jazyka IFJ19
 *      Team 65, variant 1
 *
 *      Authors:
 *          Diviš Jan	    xdivis12
 *          Kopáček Jiří	xkopac06
 *          Pojsl Jakub	    xpojsl00
 *          Sasín Jonáš	    xsasin05
 *
 *      File: scanner.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "stack.h"

// Reserved keywords that must not be used as a variable name
const char* keywords[7] =
{
    "def", "else", "if", "none", "pass", "return", "while"
};

// If the last token was EOL, indentation will not be ignored
int last_token_eol = 0;

int isCharAlpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 1;
    }
    return 0;
}

int isCharDigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}

int finalize(Token *token)
{
    if (token->type == TOKEN_EOL)
    {
        last_token_eol = 1;
    } else
    {
        last_token_eol = 0;
    }
    return 0;
}

// TODO ERASE FILE INPUT
int get_token(Token *token, FILE *file)
{
    // Initializes all required variables
    char c;
    tState state = stSTART;
    token->type = TOKEN_UNDEFINED;
    string_clear(token->attribute);
    int indentation_counter = 0;
    int hex_char_counter = 0;

    //  TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN TODO REWRITE FOR STDIN
    // Reads the input
    while (file)
    {
        c = getc(file);
        switch(state)
        {
            // State: start
            case stSTART:
                if (isCharAlpha(c) || c == '_') // a...Z
                {
                    state = stID_KEYWORD;
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                }
                else if (c >= '1' && c <= '9') // 1...9
                {
                    state = stNUM;
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                }
                else if (c == '\'') // '
                {
                    state = stSTRING_UNFINISHED;
                }
                else if (c == '\"') // "
                {
                    state = stDOC_STRING_A;
                }
                else if (c == '#')
                {
                    state = stCOMMENT;
                }
                else if (c == ' ') // space
                {
                    // If the last token was end of line, starts counting the current indentation
                    if (last_token_eol == 1)
                    {
                        state = stINDENTATION_COUNT;
                        indentation_counter++;
                    } else
                    {
                        state = stSTART;
                    }
                }
                else if (c == '\t' || c == '\n') // tab or eol
                {
                    if (c == '\n')
                    {
                        token->type = TOKEN_EOL;
                        return finalize(token);
                    }
                    state = stSTART;
                }
                else if (c == ':')
                {
                    token->type = TOKEN_COLON;
                    return finalize(token);
                }
                else if (c == ',')
                {
                    token->type = TOKEN_COMMA;
                    return finalize(token);
                }
                else if (c == '(')
                {
                    token->type = TOKEN_LBRACKET;
                    return finalize(token);
                }
                else if (c == ')')
                {
                    token->type = TOKEN_RBRACKET;
                    return finalize(token);
                }
                else if (c == '+')
                {
                    token->type = TOKEN_PLUS;
                    return finalize(token);
                }
                else if (c == '-')
                {
                    token->type = TOKEN_MINUS;
                    return finalize(token);
                }
                else if (c == '*')
                {
                    token->type = TOKEN_MULTI;
                    return finalize(token);
                }
                else if (c == '/')
                {
                    state = stINT_DIV;
                }
                else if (c == '>')
                {
                    state = stGREATER;
                }
                else if (c == '<')
                {
                    state = stLESSER;
                }
                else if (c == '=')
                {
                    state = stASSIGN;
                }
                else if (c == '!')
                {
                    state = stEXCL;
                }
                else if (c == EOF)
                {
                    token->type = TOKEN_EOF;
                    return finalize(token);
                }
                else
                {
                    // Lexical error
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stStart
            // stID_KEYWORD
            case stID_KEYWORD:
                if (isCharAlpha(c) || isCharDigit(c) || c == '_') // Alphanum, _
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stID_KEYWORD;
                } else // ASCII - Alphanum, _
                {
                    ungetc(c, file);
                    // TODO
                    // TODO
                    // TODO If (token->attribute) is keyword...
                    token->type = TOKEN_IDENTIFIER;
                    return finalize(token);
                }
                break;
            // End of stID_KEYWORD
            //
            // NUMBER SECTION
            //
            // stNUM
            case stNUM:
                if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM;
                } else if (c == '.')
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_POINT;
                } else if (c == 'E' || c == 'e')
                {
                    if (string_append_char(token->attribute, 'e') != 0)
                    {
                        return 99;
                    }
                    state = stNUM_E;
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_NUM;
                    return finalize(token);
                }
                break;
            // End of stNUM
            // stNUM_POINT
            case stNUM_POINT:
                if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_DEC;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stNUM_POINT
            // stNUM_DEC
            case stNUM_DEC:
                if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_DEC;
                } else if (c == 'E' || c == 'e')
                {
                    if (string_append_char(token->attribute, 'e') != 0)
                    {
                        return 99;
                    }
                    state = stNUM_E;
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_NUM_DEC;
                    return finalize(token);
                }
                break;
            // End of stNUM_DEC
            // stNUM_E
            case stNUM_E:
                if (c == '+')
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_SIGN;
                } else if (c == '-')
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_SIGN;
                } else if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_EXP;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stNUM_E
            // stNUM_SIGN
            case stNUM_SIGN:
                if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_EXP;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stNUM_SIGN
            // stNUM_EXP
            case stNUM_EXP:
                if (isCharDigit(c))
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stNUM_EXP;
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_NUM_EXP;
                    return finalize(token);
                }
                break;
            // End of stNUM_EXP
            //
            // STRING SECTION
            //
            // stSTRING_UNFINISHED
            case stSTRING_UNFINISHED:
                if (c == '\'')
                {
                    token->type = TOKEN_STRING;
                    return finalize(token);
                } else if (c == '\\')
                {
                    state = stSTRING_ESCAPE;
                } else if (c > 31)
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stSTRING_UNFINISHED
            // stString_ESCAPE
            case stSTRING_ESCAPE:
                if (c == 'x')
                {
                    state = stSTRING_ESCAPE_HEX;
                } else if (c == '\"')
                {
                    if (string_append_char(token->attribute, '\"') != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else if (c == '\'')
                {
                    if (string_append_char(token->attribute, '\'') != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else if (c == 'n')
                {
                    if (string_append_char(token->attribute, '\n') != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else if (c == 't')
                {
                    if (string_append_char(token->attribute, '\t') != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else if (c == '\\')
                {
                    if (string_append_char(token->attribute, '\\') != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else if (c > 31) // Undefined escape sequence
                {
                    if (string_append_char(token->attribute, '\\') != 0)
                    {
                        return 99;
                    }
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stSTRING_UNFINISHED;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stSTRING_ESCAPE
            // stSTRING_ESCAPE_HEX
            case stSTRING_ESCAPE_HEX:
                if (isCharDigit(c))
                {
                    hex_char_counter = (16 * (c - 48)); // Reduces the value of c to the range 0...9
                    state = stSTRING_ESCAPE_HEX_HALF;
                } else if (c >= 'a' && c <= 'f')
                {
                    hex_char_counter = (16 * (c - 87)); // Reduces the value of c to the range 10...15
                    state = stSTRING_ESCAPE_HEX_HALF;
                } else if (c >= 'A' && c <= 'F')
                {
                    hex_char_counter = (16 * (c - 55)); // Reduces the value of c to the range 10...15
                    state = stSTRING_ESCAPE_HEX_HALF;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stSTRING_ESCAPE_HEX
            // stSTRING_ESCAPE_HEX_HALF
            case stSTRING_ESCAPE_HEX_HALF:
                if (isCharDigit(c))
                {
                    hex_char_counter += (c - 48); // Reduces the value of c to the range 0...9
                    state = stSTRING_UNFINISHED;
                } else if (c >= 'a' && c <= 'f')
                {
                    hex_char_counter += (c - 87); // Reduces the value of c to the range 10...15
                    state = stSTRING_UNFINISHED;
                } else if (c >= 'A' && c <= 'F')
                {
                    hex_char_counter += (c - 55); // Reduces the value of c to the range 10...15
                    state = stSTRING_UNFINISHED;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                // Appends the character represented by hexadecimal number and resets the counter
                if (string_append_char(token->attribute, hex_char_counter) != 0)
                {
                    return 99;
                }
                hex_char_counter = 0;
                break;
            // End of stSTRING_ESCAPE_HEX_HALF
            //
            // DOC_STRING SECTION
            //
            // stDOC_STRING_A
            case stDOC_STRING_A:
                if (c == '\"')
                {
                    state = stDOC_STRING_B;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stDOC_STRING_A
            // stDOC_STRING_B
            case stDOC_STRING_B:
                if (c == '\"')
                {
                    state = stDOC_STRING_UNFINISHED;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stDOC_STRING_B
            // stDOC_STRING_UNFINISHED
            case stDOC_STRING_UNFINISHED:
                if (c == '\"')
                {
                    state = stDOC_STRING_UNFINISHED_A;
                } else if (c > 31 || c == '\n')
                {
                    if (string_append_char(token->attribute, c) != 0)
                    {
                        return 99;
                    }
                    state = stDOC_STRING_UNFINISHED;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stDOC_STRING_UNFINISHED
            // stDOC_STRING_UNFINISHED_A
            case stDOC_STRING_UNFINISHED_A:
                if (c == '\"')
                {
                    state = stDOC_STRING_UNFINISHED_B;
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stDOC_STRING_UNFINISHED_A
            // stDOC_STRING_UNFINISHED_B
            case stDOC_STRING_UNFINISHED_B:
                if (c == '\"')
                {
                    token->type = TOKEN_DOC_STRING;
                    return finalize(token);
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
                break;
            // End of stDOC_STRING_UNFINISHED_B
            //
            // COMMENT SECTION
            //
            // stCOMMENT
            case stCOMMENT:
                if (c != EOF && c != '\n')
                {
                    state = stCOMMENT;
                } else
                {
                    ungetc(c, file);
                    state = stSTART;
                }
                break;
            // End of stCOMMENT
            //
            // INDENTATION SECTION
            //
            // stINDENTATION_COUNT
            case stINDENTATION_COUNT:
                if (c == ' ')
                {
                    indentation_counter++;
                    state = stINDENTATION_COUNT;
                } else
                {
                    ungetc(c, file);
                    // TODO
                    // TODO
                    // TODO use stack for indent and dedent check
                    // TODO
                    // TODO
                    // TODO check the next character if the indentation should be ignored
                    state = stSTART;
                }
                break;
            // End of stINDENTATION_COUNT
            //
            // MISCELLANEOUS  SECTION
            //
            // stINT_DIV
            case stINT_DIV:
                if (c == '\\')
                {
                    token->type = TOKEN_FLOAT_DIV;
                    return finalize(token);
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_INT_DIV;
                    return finalize(token);
                }
                break;
            // End of stINT_DIV
            // stGREATER
            case stGREATER:
                if (c == '=')
                {
                    token->type = TOKEN_GREATER_EQUAL;
                    return finalize(token);
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_GREATER;
                    return finalize(token);
                }
                break;
            // End of stGREATER
            // stLESSER
            case stLESSER:
                if (c == '=')
                {
                    token->type = TOKEN_LESSER_EQUAL;
                    return finalize(token);
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_LESSER;
                    return finalize(token);
                }
                break;
            // End of stLESSER
            // stASSIGN
            case stASSIGN:
                if (c == '=')
                {
                    token->type = TOKEN_EQUAL;
                    return finalize(token);
                } else
                {
                    ungetc(c, file);
                    token->type = TOKEN_ASSIGN;
                    return finalize(token);
                }
                break;
            // End of stASSIGN
            // stEXCL
            case stEXCL:
                if (c == '=')
                {
                    token->type = TOKEN_NOT_EQUAL;
                    return finalize(token);
                } else
                {
                    token->type = TOKEN_UNDEFINED;
                    return 1;
                }
        } // End of switch
    }

    return 0;
}
