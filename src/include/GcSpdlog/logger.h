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
        using ptr = std::shared_ptr<Logger>;
        Logger(const std::string & name, gcspdlog::Level level);
        void addSink(Sink::ptr);
        void removeSink(Sink::ptr);
        void log(LogMsg::ptr msg);
        ~Logger();
    };
    
} // namespace gcspdlog
