#pragma once
#include "formatter.h"

namespace gcspdlog{
    // Sink corresponds to Appender in Log4J, which depends the logging method in different destination.
    // this could be used directly(as a stdoutSink), or used by deriving a new class for custom.
    class Sink{
        Formatter::ptr m_formatter;
        Level m_level;
    public:
        using ptr = std::shared_ptr<Sink>;
        Sink(Level level, const Formatter::ptr formatter);
        void setFormatter(const Formatter::ptr formatter);
        virtual ~Sink();

        virtual void log(LogMsg::ptr msg);
    };

    class FileSink: Sink{
        std::string file_name;
    public:
        using ptr = std::shared_ptr<FileSink>;
        FileSink(Level Level, const Formatter::ptr formatter,const std::string & file);
        ~FileSink();

        void log(LogMsg::ptr msg) override;
    }
}