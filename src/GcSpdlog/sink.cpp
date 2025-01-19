#include "./GcSpdlog/sink.h"
namespace gcspdlog{
Sink::Sink(Level level, const Formatter::ptr Formatter):m_level(level), m_formatter(Formatter){

}
Sink::~Sink(){}

void Sink::log(Level level, const std::string & msg){
    //std::cout << "sink"
}


}