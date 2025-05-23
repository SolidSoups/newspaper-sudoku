#pragma once
#include <cstdint>

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"

namespace olc
{
namespace net
{
// Forward declare
template<typename T>
class server_interface;

template <typename T>
class connection : public std::enable_shared_from_this<connection<T>>
{
public:
  enum class owner
  {
    server,
    client
  };

  connection(owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket,
      tsqueue<owned_message<T>>& qIn)
      : m_asioContext(asioContext), m_socket(std::move(socket)), m_qMessagesIn(qIn)
  {
    m_nOwnerType = parent;

    // Construct validation check data
    if (m_nOwnerType == owner::server)
    {
      // Connection is Server -> Client, construct random data for the client
      // to transform and send back for validation
      m_nHandshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

      // Pre-calculate the result for checking when the client responds
      m_nHandshakeCheck = scramble(m_nHandshakeOut);
    }
    else
    {
      // Connection is Client -> Server, so we have nothing to define,
      m_nHandshakeOut = 0;
      m_nHandshakeCheck = 0;
    }
  }

  virtual ~connection()
  {
  }

  uint32_t GetID() const
  {
    return id;
  }

public:
  void ConnectToClient(olc::net::server_interface<T>* server, uint32_t uid = 0)
  {
    if (m_nOwnerType == owner::server)
    {
      if (m_socket.is_open())
      {
        id = uid;
        // Was: ReadHeader();

        // A client has attempted to connect to the sever, but we wish
        // the client to first validate itself, so first write out the
        // handskahe data to be validated
        WriteValidation();

        // Next, issue a task to sit and wait asynchronously for precisely
        // the validation data sent back from the client
        ReadValidation(server);
      }
    }
  }
  bool ConnectToServer(const asio::ip::tcp::resolver::results_type& endpoints)
  {
    // Only clients can connect to servers
    if (m_nOwnerType == owner::client)
    {
      // Request asio attempts to connect to an endpoint
      asio::async_connect(m_socket,
          endpoints,
          [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
          {
            if (!ec)
            {
              // was: ReadHeader();

              // First thing server will do is send packet to be validated
              // so wait for that to happend
              ReadValidation();
            }
          });
      return true;
    }
    return false;
  }
  bool Disconnect()
  {
    if (IsConnected())
    {
      asio::post(m_asioContext,
          [this]()
          {
            m_socket.close();
          });
      return true;
    }
    return false;
  }
  bool IsConnected() const
  {
    return m_socket.is_open();
  }

public:
  bool Send(const message<T>& msg)
  {
    asio::post(m_asioContext,
        [this, msg]()
        {
          bool bWritingMessage = !m_qMessagesOut.empty();
          m_qMessagesOut.push_back(msg);
          if (!bWritingMessage)
          {
            WriteHeader();
          }
        });
    return true;
  }

private:
  // ASYNC - Prime context to read a message header
  void ReadHeader()
  {
    asio::async_read(m_socket,
        asio::buffer(&m_msgTemporaryIn.header, sizeof(message_header<T>)),
        [this](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if (m_msgTemporaryIn.header.size > 0)
            {
              m_msgTemporaryIn.body.resize(m_msgTemporaryIn.header.size);
              ReadBody();
            }
            else
            {
              AddToIncomingMessageQueue();
            }
          }
          else
          {
            std::cout << "[" << id << "] Read Header Fail.\n";
            m_socket.close();
          }
        });
  }

  // ASYNC - Prime context to read a message body
  void ReadBody()
  {
    asio::async_read(m_socket,
        asio::buffer(m_msgTemporaryIn.body.data(), m_msgTemporaryIn.body.size()),
        [this](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            AddToIncomingMessageQueue();
          }
          else
          {
            std::cout << "[" << id << "] Read Body Fail.\n";
            m_socket.close();
          }
        });
  }

  // ASYNC - Prime context to write a message header
  void WriteHeader()
  {
    asio::async_write(m_socket,
        asio::buffer(&m_qMessagesOut.front().header, sizeof(message_header<T>)),
        [this](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if (m_qMessagesOut.front().body.size() > 0)
            {
              WriteBody();
            }
            else
            {
              m_qMessagesOut.pop_front();

              if (!m_qMessagesOut.empty())
              {
                WriteHeader();
              }
            }
          }
          else
          {
            std::cout << "[" << id << "] Write Header Fail.\n";
            m_socket.close();
          }
        });
  }

  // ASYNC - Prime context to write a message body
  void WriteBody()
  {
    auto& msg = m_qMessagesOut.front();
    auto* data = msg.body.data();
    auto size = msg.body.size();

    asio::async_write(m_socket,
        asio::buffer(data, size),
        [this](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            m_qMessagesOut.pop_front();

            if (!m_qMessagesOut.empty())
            {
              WriteHeader();
            }
          }
          else
          {
            std::cout << "[" << id << "] Write Body Fail.\n";
            m_socket.close();
          }
        });
  }

  void AddToIncomingMessageQueue()
  {
    if (m_nOwnerType == owner::server)
      m_qMessagesIn.push_back({this->shared_from_this(), m_msgTemporaryIn});
    else
      m_qMessagesIn.push_back({nullptr, m_msgTemporaryIn});

    ReadHeader();
  }

  // "Encrypt" data
  uint64_t scramble(uint64_t nInput)
  {
    uint64_t out = nInput ^ 0xDEADBEEFC0DECAFE;
    out = (out & 0xF0F0F0F0F0F0F0) >> 4 | (out & 0xF0F0F0F0F0F0F0) << 4;
    return out ^ 0xC0DEFACE12345678;  // this could have something to do with
    // version number, that way we can stop old clients from talking to new clients
  }

  // ASYNC - Used by both client and server to write validation packet
  void WriteValidation()
  {
    asio::async_write(m_socket,
        asio::buffer(&m_nHandshakeOut, sizeof(uint64_t)),
        [this](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            // Validation data send, clients should sit and wait
            //  for a response (or a closure)
            if (m_nOwnerType == owner::client)
            {
              ReadHeader();
            }
          }
          else
          {
            m_socket.close();
          }
        });
  }

  void ReadValidation(olc::net::server_interface<T>* server = nullptr)
  {
    asio::async_read(m_socket,
        asio::buffer(&m_nHandshakeIn, sizeof(uint64_t)),
        [this, server](std::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            if (m_nOwnerType == owner::server)
            {
              if (m_nHandshakeIn == m_nHandshakeCheck)
              {
                // Client has provided a valid solution, so allow it
                // to connect properly
                std::cout << "Client validated\n";
                server->OnClientValidated(this->shared_from_this());

                // Sit waiting to recieve data now
                ReadHeader();
              }
              else
              {
                // Client gave incorrect data, so disconnect
                std::cout << "Client Disconnected (Fail Validation)\n";
                m_socket.close();
              }
            }
            else
            {
              // Connection is a client, so solve puzzle
              m_nHandshakeOut = scramble(m_nHandshakeIn);

              // Write the result
              WriteValidation();
            }
          }
          else
          {
            // Some biggerfailure occured
            // std::cout << "Client Disconnected (ReadValidation)\n";
            m_socket.close();
          }
        });
  }

protected:
  // Each connection has a unique socket to a remote
  asio::ip::tcp::socket m_socket;

  // This context is shared with the whole asio instance
  asio::io_context& m_asioContext;

  // This queue holds all messages to be sent to the remote side
  // of this connection
  tsqueue<message<T>> m_qMessagesOut;

  // This queue holds all messages that have been recieved from
  // the remote side of this connection. Note that it is a reference
  // as the "owner" of this connection is expected to provide a queue
  tsqueue<owned_message<T>>& m_qMessagesIn;
  message<T> m_msgTemporaryIn;

  // The "owner" decides how some of the connection behaves
  owner m_nOwnerType = owner::server;
  uint32_t id = 0;

  // Handshake validation
  uint64_t m_nHandshakeOut = 0;
  uint64_t m_nHandshakeIn = 0;
  uint64_t m_nHandshakeCheck = 0;
};
}  // namespace net
}  // namespace olc
