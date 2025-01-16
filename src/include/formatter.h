#pragma once
#include <memory>
namespace gcspdlog
{
    class Formatter
    { 
    private:
        
    public:
        using ptr = std::shared_ptr<Formatter>;
        Formatter(const std::string & fmt);
        ~Formatter();

        void format(const std::string & msg);
    };
} // namespace gcspdlog
