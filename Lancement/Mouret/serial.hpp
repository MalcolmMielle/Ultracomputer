#ifndef SERIAL_HPP_
#define SERIAL_HPP_

#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <vector>

namespace serial
{  
  typedef unsigned char byte_t;

  inline double get_time()
  {    
    static struct timeval tv;
    gettimeofday(&tv, 0x0);
    return tv.tv_sec + tv.tv_usec * 1e-6;
  }


  // exception
  class Error
  {
  public:
    Error() {}
    Error(const char* msg) : _msg(msg) {}
    Error(const std::string& msg) : _msg(msg) {}
    const std::string& msg() const { return _msg; }
  private:
    std::string _msg;
  };

  class Serial
  {
  public:   
    Serial(const std::string& name, int baudrate=B115200);
    // general send
    void send(const std::string& str) const
    {
      //std::cout<<"sending :"<<str<<std::endl;
      write(_fd, (byte_t*)str.c_str(), str.size());
    }
    void capture_image() const
    {
      write(_fd, (char*)("\xb7\x0"), 2);
    }
    // general receive
    bool recv(std::string& str, int size=100, float timeout = 10);
    byte_t* recv_buffer() {return _recv_buffer;}
  private:
    int _fd;
    static const size_t _recv_buffer_size = 256;
    byte_t _recv_buffer[_recv_buffer_size];
  };
}

#endif
