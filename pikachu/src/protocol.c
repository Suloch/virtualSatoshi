
#if !defined (LWS_PLUGIN_STATIC)
#define LWS_DLL
#define LWS_INTERNAL
#include <libwebsockets.h>
#endif
#include <string.h>
#include "machine.h"


static int callback_machine_state_server(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{

  switch (reason)
  {
    case LWS_CALLBACK_PROTOCOL_INIT:    break;
    case LWS_CALLBACK_ESTABLISHED:      lwsl_warn("LWS_CALLBACK_ESTABLISHED\n");
                                        break;
    case LWS_CALLBACK_SERVER_WRITEABLE: lwsl_user("LWS_CALLBACK_SERVER_WRITEABLE\n");
                                        break;
    case LWS_CALLBACK_RECEIVE:          lwsl_user("LWS_CALLBACK_SERVER_RECIEVE\n");
                                        char *msg = NULL;
                                        do{
                                          char * msg = get_machine_state(NULL, 2);
                                        }while(msg == NULL);
                                        lws_write(wsi, msg, strlen(msg), lws_write_ws_flags(LWS_WRITE_TEXT, '1', '1'));
                                        lws_callback_on_writable(wsi);
                                        break;
    case LWS_CALLBACK_CLOSED:           lwsl_user("LWS_CALLBACK_CLOSED\n");
                                        break;
    default:                            break;

  }
  return 0;
}

#define LWS_PLUGIN_PROTOCOL_MACHINE_STATE_SERVER \
        { \
                "machine-state-server", \
                callback_machine_state_server, \
                NULL, \
                1024, \
                0, NULL, 0 \
        }

#if !defined (LWS_PLUGIN_STATIC)

static const struct lws_protocols protocols[] = {
        LWS_PLUGIN_PROTOCOL_MACHINE_STATE_SERVER
};

int init_protocol_machine_state_server(struct lws_context *context,
                               struct lws_plugin_capability *c)
{
        if (c->api_magic != LWS_PLUGIN_API_MAGIC) {
                lwsl_err("Plugin API %d, library API %d", LWS_PLUGIN_API_MAGIC,
                         c->api_magic);
                return 1;
        }

        c->protocols = protocols;
        c->count_protocols = LWS_ARRAY_SIZE(protocols);
        c->extensions = NULL;
        c->count_extensions = 0;

        return 0;
}

int
destroy_protocol_machine_state_server(struct lws_context *context)
{
        return 0;
}
#endif
