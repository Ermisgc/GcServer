#include "./GcSpdlog/sink.h"
namespace gcspdlog{
Sink::Sink(Level level, const Formatter::ptr Formatter):m_level(level), m_formatter(Formatter){}

Sink::~Sink(){}

void Sink::log(LogMsg::ptr msg){
    if(msg->level < this->m_level) return;
    std::cout << m_formatter->format(msg) << std::endl;
}

void Sink::setFormatter(const Formatter::ptr formatter){
    if(formatter != nullptr) this->m_formatter = formatter;
}

FileSink::FileSink(Level Level, const Formatter::ptr formatter,const std::string & file):file_name(file), Sink(Level, formatter){

}

FileSink::~FileSink(){

}
        
void FileSink::log(LogMsg::ptr msg) {

}

}