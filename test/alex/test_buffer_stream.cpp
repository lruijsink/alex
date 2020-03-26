#include <string_view>
#include "gtest/gtest.h"
#include "alex/buffer_source.h"
#include "alex/buffer_stream.h"

auto source = alex::buffer_source<char[5]>("1234");

TEST(basic, get_reads_back_then_eof)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');
  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_join)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.join(f1);

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_reset)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.reset(f1);

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_join_fork_join)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.join(f1);

  EXPECT_EQ(stream.get(), '3');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '4');

  stream.join(f2);

  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_reset_fork_reset)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.reset(f1);

  EXPECT_EQ(stream.get(), '2');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset(f2);

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_join_join)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.join(f2);

  EXPECT_EQ(stream.get(), '4');
  
  stream.join(f1);

  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_reset_join)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset(f2);

  EXPECT_EQ(stream.get(), '3');

  stream.join(f1);

  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_join_reset)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.join(f2);

  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());

  stream.reset(f1);

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_reset_reset)
{
  auto stream = alex::buffer_stream(source);

  EXPECT_EQ(stream.get(), '1');

  auto f1 = stream.fork();

  EXPECT_EQ(stream.get(), '2');

  auto f2 = stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset(f2);

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());

  stream.reset(f1);

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}
