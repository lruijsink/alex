#pragma once

#include <string>
#include <string_view>
#include <type_traits>
#include <memory>
#include "defines.h"
#include "tag.h"
#include "reader.h"
#include "grammar.h"
#include "grammar_abstract.h"
#include "symbol_tree.h"

namespace ALEX_NAMESPACE_NAME {


class reader_abstract
{
public:
  using traits_type = std::char_traits<char>;
  using char_type   = typename traits_type::char_type;
  using int_type    = typename traits_type::int_type;

  virtual ~reader_abstract()
  {
  }

  virtual int_type get() = 0;
  virtual bool eof() const = 0;
  virtual bool parse(const grammar<tag::poly>&) = 0;
  virtual size_t pos() const = 0;
  virtual std::string_view view(size_t, size_t) const = 0;
  virtual symbol_tree& begin_symbol(std::string) = 0;
  virtual void commit_symbol() = 0;
  virtual void discard_symbol() = 0;
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

  bool eof() const override
  {
    return reader_.eof();
  }

  size_t pos() const override
  {
    return reader_.pos();
  }

  std::string_view view(size_t begin, size_t end) const override
  {
    return reader_.view(begin, end);
  }

  bool parse(const grammar<tag::poly>& g) override
  {
    return reader_.parse(g);
  }

  symbol_tree& begin_symbol(std::string name) override
  {
    return reader_.begin_symbol(name);
  }

  void commit_symbol() override
  {
    reader_.commit_symbol();
  }

  void discard_symbol() override
  {
    reader_.discard_symbol();
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

  bool eof() const
  {
    return ptr_->eof();
  }

  size_t pos() const
  {
    return ptr_->pos();
  }

  std::string_view view(size_t begin, size_t end) const
  {
    return ptr_->view(begin, end);
  }

  symbol_tree& begin_symbol(std::string name)
  {
    return ptr_->begin_symbol(name);
  }

  void commit_symbol()
  {
    ptr_->commit_symbol();
  }

  void discard_symbol()
  {
    ptr_->discard_symbol();
  }

  template<class... TS>
  bool parse(grammar<TS...> g)
  {
    return ptr_->parse(grammar<tag::poly>(g));
  }

private:
  std::unique_ptr<reader_abstract> ptr_;
};


}
