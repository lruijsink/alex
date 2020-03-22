#pragma once

#include <type_traits>
#include "defines.h"
#include "adapter_traits.h"

LT3_ALEX_NAMESPACE_BEGIN


class stream_adapter
{
public:
  using char_type      = typename adapter_traits::char_type;
  using traits_type    = std::char_traits<char_type>;
  using int_type       = typename traits_type::int_type;

  virtual int_type get()   = 0;
  virtual bool     eof()   = 0;
  virtual void     fork()  = 0;
  virtual void     join()  = 0;
  virtual void     reset() = 0;
};

template<class StreamT>
class stream_adapter_impl : public stream_adapter
{
public:
  using char_type   = typename adapter_traits::char_type;
  using traits_type = std::char_traits<char_type>;
  using int_type    = typename traits_type::int_type;

  stream_adapter_impl(StreamT& stream)
    : stream_(stream)
  {
  }

  virtual int_type get() override
  {
    return stream_.get();
  }

  virtual bool eof() override
  {
    return stream_.eof();
  }

  virtual void fork() override
  {
    stream_.fork();
  }

  virtual void join() override
  {
    stream_.join();
  }

  virtual void reset() override
  {
    stream_.reset();
  }

private:
  StreamT& stream_;
};


LT3_ALEX_NAMESPACE_END
