#pragma once
#include <memory>
#include <vector>
#include <functional>
#include <string_view>
#include <map>
#include "log_base.h"
namespace gcspdlog
{
    class Formatter
    { 
    private:
        //use chars mapping to functions, the functions include formatter function and a raw transmitting function.
        static const std::map<char, std::function<std::string(const std::string_view &)>> fmt_mat;

        //store the function and its parameter.
        std::vector<std::pair<char, std::string_view>> pattern;

        //temporarily store the message as a global parameter.
        LogMsg::ptr temp_msg;
    public:
        using ptr = std::shared_ptr<Formatter>;
        Formatter() = default;
        Formatter(const std::string & fmt);
        ~Formatter();

        void setPattern(const std::string & fmt);
        void format(LogMsg::ptr msg);
    private:
#define XX(func) std::string func(const std::string_view & _){return func();}
        XX(getMonth);
#undef XX


        std::string getMonth(){ return "month";};
    };
} // namespace gcspdlog
