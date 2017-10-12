#include "logger.h"

Logger::Logger(const char *name)
{
    log_file.open(name);
}

Logger::~Logger()
{
    closeLogFile();
}

void Logger::closeLogFile()
{
    if (log_file.is_open())
    {
        log_file.close();
    }
}

void Logger::openLogFile(const char *name)
{
    closeLogFile();
    log_file.open(name);

    if (!log_file.is_open())
    {
        throw FileOpeningErr("\nLogger::openLogFile(const char *name) in logger.cpp");
    }
}

bool Logger::isOpened()
{
    return log_file.is_open();
}
