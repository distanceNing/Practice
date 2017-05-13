#pragma once
#include "Csocket.h"
#include <fstream>
#include <iostream>
const int BUF_SIZE=2048;
int receive_file( const char * const filename,Csocket& sock);


