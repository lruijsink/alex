#include <string_view>
#include "gtest/gtest.h"
#include "alex/stream_range.h"

TEST(basic, get_reads_back_then_eof)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');
  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_join)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.join();

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_reset)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.reset();

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_join_fork_join)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.join();

  EXPECT_EQ(stream.get(), '3');

  stream.fork();

  EXPECT_EQ(stream.get(), '4');

  stream.join();

  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_reset_fork_reset)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.reset();

  EXPECT_EQ(stream.get(), '2');

  stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset();

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_join_join)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.join();

  EXPECT_EQ(stream.get(), '4');

  stream.join();

  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_reset_join)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset();

  EXPECT_EQ(stream.get(), '3');

  stream.join();

  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_join_reset)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.join();

  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());

  stream.reset();

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}

TEST(combos, fork_fork_reset_reset)
{
  auto source_range = std::string_view("1234");
  auto stream = alex::stream_range(source_range);

  EXPECT_EQ(stream.get(), '1');

  stream.fork();

  EXPECT_EQ(stream.get(), '2');

  stream.fork();

  EXPECT_EQ(stream.get(), '3');

  stream.reset();

  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());

  stream.reset();

  EXPECT_EQ(stream.get(), '2');
  EXPECT_EQ(stream.get(), '3');
  EXPECT_EQ(stream.get(), '4');
  EXPECT_TRUE(stream.eof());
}
