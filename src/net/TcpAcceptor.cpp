#include "TcpAcceptor.h"
#include <boost/bind.hpp>

TcpAcceptor::TcpAcceptor(TcpAcceptorCallback &callback) :
    NetworkAcceptor(),
    m_callback(callback)
{
}

void TcpAcceptor::start_accept()
{
    m_acceptor->on<uvw::ListenEvent>([this](const uvw::ListenEvent &, uvw::TcpHandle &srv) {
        std::shared_ptr<uvw::TcpHandle> client = srv.loop().resource<uvw::TcpHandle>();
        srv.accept(*client);
        handle_accept(client);
    });
}

void TcpAcceptor::handle_accept(const std::shared_ptr<uvw::TcpHandle>& socket)
{
    if(!m_started) {
        // We were turned off sometime before this operation completed; ignore.
        socket->close();
        return;
    }

    uvw::Addr remote = socket->peer();
    uvw::Addr local = socket->sock();
    handle_endpoints(socket, remote, local);
}

void TcpAcceptor::handle_endpoints(const std::shared_ptr<uvw::TcpHandle>& socket, const uvw::Addr& remote, const uvw::Addr& local)
{
    // Inform the callback:
    m_callback(socket, remote, local);
}
