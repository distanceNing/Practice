#pragma once
#include <stdio.h>
#include "Csocket.h"
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>
int is_text_file(const char* filename);


int send_file( const char * const filename,Csocket& sock);


