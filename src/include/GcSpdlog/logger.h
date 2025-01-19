#pragma once
#include <string>
#include <list>
#include "sink.h"
namespace gcspdlog
{
    class Logger
    {
    private:
        std::string m_name;
        Level m_level;
        std::list<Sink::ptr> m_sinks;
    public:
        Logger(const std::string & name, gcspdlog::Level level);
        void addSink(Sink::ptr);
        void removeSink(Sink::ptr);
        void log(Level level, const std::string & message);
        ~Logger();
    };
    
} // namespace gcspdlog
