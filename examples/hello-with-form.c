/*
 * balde: A microframework for C based on GLib and bad intentions.
 * Copyright (C) 2013-2017 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 *
 * This program can be distributed under the terms of the LGPL-2 License.
 * See the file COPYING.
 */

/**
 * \example hello-with-form.c
 *
 * An example with HTTP forms. It depends on more files. Take a look at
 * it on the balde source code.
 */

#include <balde.h>
#include "templates/hello.h"
#include "templates/form.h"

balde_response_t*
hello(balde_app_t *app, balde_request_t *request)
{
    balde_response_t *response = balde_make_response("");
    if (request->method == BALDE_HTTP_POST) {
        const gchar *name = balde_request_get_form(request, "name");
        balde_response_set_tmpl_var(response, "name",
            name != NULL && name[0] != '\0' ? name : "World");
        balde_template_hello(app, request, response);
    }
    else
        balde_template_form(app, request, response);
    return response;
}


int
main(int argc, char **argv)
{
    balde_app_t *app = balde_app_init();
    balde_app_add_url_rule(app, "hello", "/", BALDE_HTTP_GET | BALDE_HTTP_POST,
        hello);
    balde_app_run(app, argc, argv);
    balde_app_free(app);
    return 0;
}
