#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include "cJSON.h"

char *_host, *_login_path;
int _port;
char *_user, *_password;

char *_server_side_api_param_init(char *host, int _port, char *login_path, char *user, char *password);
char *form_jwt_http_request();
char *form_http_request_for_other_api(char *_method, char *api, char *_token);
char *form_login_json_string();
void get_jwt(char *_token, char *_refreshToken, int read_buffer_size);
void http_request_for_other_api(char *_token, char *api, int read_buffer_size);
int  socket_connect();