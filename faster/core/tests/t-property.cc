/*
 * Faster - a C++ miscellaneous utility library
 * Copyright 2020  Jakub Kaszycki
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <mutex>
#include <shared_mutex>
#include <string>

#include <gtest/gtest.h>
#include <faster/core/property.hh>

// Here, we only test some variants.

TEST (property, simple)
{
  class test_class
  {
  public:
    test_class ()
      noexcept
      : str_ {"123"}
    {
    }

    FASTER_PROPERTY (str, std::string)
  };

  test_class x;
  ASSERT_EQ (x.str (), "123");
  x.str ("456");
  ASSERT_EQ (x.str (), "456");
  x.str () = "789";
  ASSERT_EQ (x.str (), "789");
}

TEST (property, lock)
{
  class test_class
  {
  public:
    test_class ()
      noexcept
      : str_ {"123"}
    {
    }

    FASTER_PROPERTY_LOCK (str, std::string)
  };

  test_class x;

  {
    std::unique_lock lock {x.str_lock ()};

    ASSERT_EQ (x.str (), "123");
    x.str ("456");
  }

  ASSERT_EQ (x.str (), "456");
}

TEST (property, rwlock)
{
  class test_class
  {
  public:
    test_class ()
      noexcept
      : str_ {"123"}
    {
    }

    FASTER_PROPERTY_RWLOCK (str, std::string)
  };

  test_class x;

  {
    std::shared_lock lock {x.str_lock ()};

    ASSERT_EQ (x.str (), "123");
    x.str ("456");
  }

  ASSERT_EQ (x.str (), "456");
}

TEST (property, abstract)
{
  class test_class
  {
  public:
    test_class ()
      noexcept
    {
    }

    virtual
    ~test_class ()
      noexcept
    {
    }

    FASTER_PROPERTY_AB (str, std::string)
  };

  class test_subclass final : public test_class
  {
  public:
    test_subclass ()
      noexcept
      : test_class {}, str_ {"123"}
    {
    }

    FASTER_PROPERTY_OV (str, std::string)
  };

  test_subclass sc;
  test_class &cref = sc;

  ASSERT_EQ (cref.str (), "123");
  cref.str ("456");
  ASSERT_EQ (sc.str (), "456");
}

TEST (property, pbv)
{
  class test_class
  {
  public:
    test_class ()
      noexcept
      : num_ {123}
    {
    }

    FASTER_PROPERTY_PBV (num, int)
  };

  test_class x;
  ASSERT_EQ (x.num (), 123);
  x.num (456);
  ASSERT_EQ (x.num (), 456);
  x.num (789);
  ASSERT_EQ (x.num (), 789);
}
