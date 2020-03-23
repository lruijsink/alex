#pragma once

#include <string>
#include <type_traits>
#include <memory>
#include "defines.h"
#include "tag.h"
#include "reader.h"
#include "grammar.h"
#include "grammar_abstract.h"

LT3_ALEX_NAMESPACE_BEGIN


class reader_abstract
{
public:
  using traits_type = std::char_traits<char>;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  virtual int_type get() = 0;
  virtual bool eof() = 0;
  virtual bool parse(grammar<tag::poly>& g) = 0;
  virtual std::unique_ptr<reader_abstract> clone() const = 0;
};

template<class... TS>
class reader_impl : public reader_abstract
{
public:
  using reader_abstract::traits_type;
  using reader_abstract::char_type;
  using reader_abstract::int_type;

  reader_impl(reader<TS...> reader) : reader_(reader) {}

  int_type get() override
  {
    return reader_.get();
  }

  bool eof() override
  {
    return reader_.eof();
  }

  bool parse(grammar<tag::poly> g)
  {
    return reader_.parse(g);
  }

  std::unique_ptr<reader_abstract> clone() const override
  {
    return std::make_unique<reader_impl>(reader_);
  }

private:
  reader<TS...> reader_;
};

template<>
class reader<tag::poly>
{
public:
  using traits_type = std::char_traits<char>;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  reader(const reader<tag::poly>& reader)
    : ptr_(reader.ptr_->clone()) {}

  template<class... TS>
  reader(reader<TS...> reader)
    : ptr_(new reader_impl<TS...>(reader)) {}

  template<class... TS>
  reader(TS... vs)
    : reader(reader<TS...>(vs...)) {}

  int_type get()
  {
    return ptr_->get();
  }

  bool eof()
  {
    return ptr_->eof();
  }

  bool parse(grammar<tag::poly> g)
  {
    return ptr_->parse(g);
  }

private:
  std::unique_ptr<reader_abstract> ptr_;
};


LT3_ALEX_NAMESPACE_END
