#pragma once
#include "formatter.h"
#include "log_base.h"

namespace gcspdlog{
    class Sink{
        Formatter::ptr m_formatter;
        Level m_level;
    public:
        using ptr = std::shared_ptr<Sink>;
        Sink(Level level, const Formatter::ptr Formatter);
        virtual ~Sink();

        void log(Level level, const std::string & msg);
        
    };
}