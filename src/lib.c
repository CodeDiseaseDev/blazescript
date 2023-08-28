/*
 * Created by rakinar2 on 8/26/23.
 */

#include "lib.h"
#include "eval.h"
#include "http.h"

#include <stdio.h>
#include <string.h>

/* FIXME: this is for testing/debugging */
BUILTIN_FN(test) {
    for (unsigned i = 0; i < 10; i++)
        printf("%u\n", i);
    return scope->null;
}

BUILTIN_FN(httpget)
{
    if (argc != 1 || args[0]->type != VAL_STRING)
    {
        eval_fn_error = strdup("function http_get() requires 1 string argument");
        return NULL;
    }

    struct http_response response = http_make_request(
        "https://discord.com/robots.txt");

    if (!http_is_successful(response)) {
        sprintf(eval_fn_error, "function http_get() failed: Server responded with unsuccessful status code (%u)", response.status);
        return NULL;
    }

    val_t *val = val_create(VAL_STRING);
    val->strval->value = strdup(response.body);

    return val;
}

BUILTIN_FN(println)
{
    if (argc == 0)
    {
        eval_fn_error = strdup("function println() requires at least 1 argument to be passed");
        return NULL;
    }

    for (size_t i = 0; i < argc; i++)
    {
        if (args[i]->type == VAL_STRING)
            printf("%s", args[i]->strval->value);
        else
            print_val_internal(args[i], false);

        if (i != (argc - 1))
            printf(" ");
    }

    printf("\n");

    return scope->null;
}
