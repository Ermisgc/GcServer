#include <memory>

namespace gcnetwork{
    class TcpConnection;

    class Callback{
    public:
        virtual ~Callback();
        virtual void call(std::shared_ptr<TcpConnection> conn) = 0;
    };

    typedef Callback ConnectionCallback;
    typedef Callback ReadCallback;
    typedef Callback WriteCallback;
}