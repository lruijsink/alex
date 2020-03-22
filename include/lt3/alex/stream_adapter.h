#pragma once

#include <type_traits>
#include "defines.h"
#include "adapter_traits.h"

LT3_ALEX_NAMESPACE_BEGIN


template<class AdapterTraitsT>
class basic_stream_adapter
{
public:
  using adapter_traits = AdapterTraitsT;
  using char_type      = typename adapter_traits::char_type;
  using traits_type    = std::char_traits<char_type>;
  using int_type       = typename traits_type::int_type;

  virtual int_type get()   = 0;
  virtual bool     eof()   = 0;
  virtual void     fork()  = 0;
  virtual void     join()  = 0;
  virtual void     reset() = 0;
};

template<class AdapterTraitsT, class StreamT>
class basic_stream_adapter_impl : public basic_stream_adapter<AdapterTraitsT>
{
public:
  using adapter_traits = AdapterTraitsT;
  using char_type      = typename adapter_traits::char_type;
  using traits_type    = std::char_traits<char_type>;
  using int_type       = typename traits_type::int_type;

  basic_stream_adapter_impl(StreamT& stream)
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

using stream_adapter = basic_stream_adapter<default_adapter_traits>;

template<class StreamT>
using stream_adapter_impl = basic_stream_adapter_impl<default_adapter_traits, StreamT>;


LT3_ALEX_NAMESPACE_END
