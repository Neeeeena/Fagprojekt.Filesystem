/*
 * ExternFunctions.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: nina
 */
#include <errno.h>
#include <string.h>
#include "ExternFunctions.h"
#include <libssh/libssh.h>
#include <stdio.h>
#include <stdlib.h>

ExternFunctions::ExternFunctions() {
	// TODO Auto-generated constructor stub

}

ExternFunctions::~ExternFunctions() {
	// TODO Auto-generated destructor stub
}

int ExternFunctions::verify_knownhost(ssh_session session)
{
  int state, hlen;
  unsigned char *hash = NULL;
  char *hexa;
  char buf[10];
  state = ssh_is_server_known(session);
  hlen = ssh_get_pubkey_hash(session, &hash);
  if (hlen < 0)
    return -1;
  switch (state)
  {
    case SSH_SERVER_KNOWN_OK:
      break; /* ok */
    case SSH_SERVER_KNOWN_CHANGED:
      fprintf(stderr, "Host key for server changed: it is now:\n");
      ssh_print_hexa("Public key hash", hash, hlen);
      fprintf(stderr, "For security reasons, connection will be stopped\n");
      free(hash);
      return -1;
    case SSH_SERVER_FOUND_OTHER:
      fprintf(stderr, "The host key for this server was not found but an other"
        "type of key exists.\n");
      fprintf(stderr, "An attacker might change the default server key to"
        "confuse your client into thinking the key does not exist\n");
      free(hash);
      return -1;
    case SSH_SERVER_FILE_NOT_FOUND:
      fprintf(stderr, "Could not find known host file.\n");
      fprintf(stderr, "If you accept the host key here, the file will be"
       "automatically created.\n");
      /* fallback to SSH_SERVER_NOT_KNOWN behavior */
    case SSH_SERVER_NOT_KNOWN:
      hexa = ssh_get_hexa(hash, hlen);
      fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
      fprintf(stderr, "Public key hash: %s\n", hexa);
      free(hexa);
      if (fgets(buf, sizeof(buf), stdin) == NULL)
      {
        free(hash);
        return -1;
      }
      if (strncasecmp(buf, "yes", 3) != 0)
      {
        free(hash);
        return -1;
      }
      if (ssh_write_knownhost(session) < 0)
      {
        fprintf(stderr, "Error %s\n", strerror(errno));
        free(hash);
        return -1;
      }
      break;
    case SSH_SERVER_ERROR:
      fprintf(stderr, "Error %s", ssh_get_error(session));
      free(hash);
      return -1;
  }
  free(hash);
  return 0;
}

int ExternFunctions::show_remote_files(ssh_session session)
{
  ssh_channel channel;
  int rc;
  channel = ssh_channel_new(session);
  if (channel == NULL) return SSH_ERROR;
  rc = ssh_channel_open_session(channel);
  if (rc != SSH_OK)
  {
    ssh_channel_free(channel);
    return rc;
  }
  rc = ssh_channel_request_exec(channel, "ls -l");
  if (rc != SSH_OK)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return rc;
  }
  char buffer[256];
  int nbytes;
  nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  while (nbytes > 0)
  {
    if (fwrite(buffer, 1, nbytes, stdout) != nbytes)
    {
      ssh_channel_close(channel);
      ssh_channel_free(channel);
      return SSH_ERROR;
    }
    nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
  }
  if (nbytes < 0)
  {
    ssh_channel_close(channel);
    ssh_channel_free(channel);
    return SSH_ERROR;
  }
  ssh_channel_send_eof(channel);
  ssh_channel_close(channel);
  ssh_channel_free(channel);
  return SSH_OK;
}
