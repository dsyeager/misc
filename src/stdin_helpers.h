#pragma once

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

bool stdin_has_data(uint32_t tries = 10, uint32_t us_sleep = 100000)
{
    for (uint32_t i = 0; i < tries; i++)
    {
        struct pollfd fds;
        int ret;
        fds.fd = 0; // this is STDIN
        fds.events = POLLIN;
        ret = poll(&fds, 1, 0);
        if(ret == 1)
            return true;
        usleep(us_sleep);
    }
    return false;
}


void read_stdin(std::string *buffer)
{
    char *line = nullptr;
    size_t len = 0;

    while (std::cin)
    {
        //getline(cin, buff);
        ssize_t res = getline(&line, &len, stdin);
        if (res <= 0)
            break;
        buffer->append(line, res);
    }
    free(line);
}

void read_stdin(std::string &buffer)
{
    read_stdin(&buffer);
}
