/*
 * Created by rakinar2 on 8/22/23.
 */

#ifndef BLAZESCRIPT_AST_H
#define BLAZESCRIPT_AST_H

#include <stdbool.h>
#include <stddef.h>

typedef enum ast_node_type {
    NODE_ROOT,
    NODE_INT_LIT,
    NODE_BINARY_EXPR,
    NODE_IDENTIFIER,
    NODE_STRING,
    NODE_VAR_DECL,
    NODE_ASSIGNMENT,
    NODE_EXPR_CALL,
    NODE_FN_DECL
} ast_type_t;

typedef enum ast_bin_operator {
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_DIVIDE = '/',
    OP_TIMES = '*',
    OP_MODULUS = '%'
} ast_bin_operator_t;

typedef struct ast_int_lit {
    long long int intval;
} ast_intlit_t;

typedef struct ast_str_lit {
    char *strval;
} ast_string_t;

typedef struct ast_binexpr {
    struct ast_node *left;
    struct ast_node *right;
    ast_bin_operator_t operator;
} ast_binexpr_t;

typedef struct ast_identifier {
    char *symbol;
} ast_identifier_t;

typedef struct ast_assignment_expr {
    struct ast_node *assignee;
    struct ast_node *value;
} ast_assignment_expr_t;

typedef struct ast_var_decl {
    char *name;
    bool is_const;
    struct ast_node *value;
} ast_var_decl_t;

typedef struct ast_root {
    size_t size;
    struct ast_node **nodes;
} ast_root_t;

typedef struct ast_fn_call {
    size_t argc;
    struct ast_node **args;
    ast_identifier_t *identifier;
} ast_call_t;

typedef struct ast_fn_decl {
    size_t param_count;
    char **param_names;
    ast_identifier_t *identifier;
    struct ast_node **body;
    size_t size;
} ast_fn_decl_t;

typedef struct ast_node
{
    ast_type_t type;
    size_t line_start, line_end;
    size_t column_start, column_end;

    union {
        ast_intlit_t *integer;
        ast_binexpr_t *binexpr;
        ast_identifier_t *identifier;
        ast_root_t *root;
        ast_string_t *string;
        ast_var_decl_t *var_decl;
        ast_assignment_expr_t *assignment_expr;
        ast_call_t *fn_call;
        ast_fn_decl_t *fn_decl;
    };
} ast_node_t;

#endif /* BLAZESCRIPT_AST_H */
