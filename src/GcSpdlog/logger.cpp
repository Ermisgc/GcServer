#include "logger.h"
namespace gcspdlog{
Logger::Logger(const std::string & name, gcspdlog::Level level):m_name(name), m_level(level){

}
void Logger::addSink(Sink::ptr sink){
    m_sinks.push_back(sink);
}
void Logger::removeSink(Sink::ptr sink){
    m_sinks.push_back(sink);
}
void Logger::log(Level level, const std::string & message){
    //if the level is small than the logger_level, the logger will not handle it.
    if(level < m_level) return;
    for(auto & sink:m_sinks){
        sink->log(level, message);
    }
}
Logger::~Logger(){

}
}