#include <zmq.h>
#include <string.h>
#include "telive-zmq.h"

static void *context;
static void *push;

void telive_zmq_init() {
    context = zmq_init (1);
    push    = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (push, "tcp://127.0.0.1:8898");
}

void telive_zmq_msg(char *s, int ssi) {
    zmq_msg_t envelope;
    zmq_msg_t body;

    zmq_msg_init_size (&envelope, strlen(s) + 1);
    strcpy (zmq_msg_data (&envelope), s);

    char str[10];
    sprintf(str, "%d", ssi);

    zmq_msg_init_size (&body, strlen(str) + 1);
    strcpy (zmq_msg_data (&body), str);

    zmq_msg_send (&envelope, push, ZMQ_DONTWAIT | ZMQ_SNDMORE);
    zmq_msg_send (&body, push, ZMQ_DONTWAIT);
    zmq_msg_close (&envelope);
    zmq_msg_close (&body);
}
