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

#include <cstdint>
#include <iostream>

using std::cout;

using features = std::uint64_t;

enum : features
{
  ABSTRACT               = 0x00000001,
  CUSTOM_FIELD           = 0x00000002,
  DETECT_TYPE            = 0x00000004,
  EXCEPTIONS             = 0x00000008,
  LOCK                   = 0x00000010,
  MUTABLE                = 0x00000020,
  NOT_CONSTEXPR          = 0x00000040,
  NO_COPYING             = 0x00000080,
  NO_FIELD               = 0x00000100,
  NO_SETTERS             = 0x00000200,
  OVERRIDE               = 0x00000400,
  PASS_BY_VALUE          = 0x00000800,
  PRIVATE                = 0x00001000,
  PRIV_SET               = 0x00002000,
  READ_ONLY              = 0x00004000,
  REFERENCE              = 0x00008000,
  RWLOCK                 = 0x00010000,
  VOLATILE               = 0x00020000,
  VIRTUAL                = 0x00040000,
  FEATURES_MAX           = 0x0007FFFF,
};

namespace
{
  constexpr inline bool
  features_valid (features f)
    noexcept
  {
    if (f & ABSTRACT
        && f & (CUSTOM_FIELD | DETECT_TYPE | LOCK | NOT_CONSTEXPR
                | NO_FIELD | OVERRIDE | RWLOCK | VOLATILE | VIRTUAL))
      return false;

    if (f & CUSTOM_FIELD
        && f & (NO_FIELD | VOLATILE))
      return false;

    if (f & DETECT_TYPE
        && !(f & (CUSTOM_FIELD | NO_FIELD)))
      return false;

    if ((!!(f & LOCK) + !!(f & RWLOCK) + !!(f & VOLATILE)) > 1)
      return false;

    if (f & MUTABLE
        && f & (PRIV_SET | REFERENCE))
      return false;

    if (f & NOT_CONSTEXPR
        && f & OVERRIDE)
      return false;

    if (f & NO_COPYING
        && f & (NO_SETTERS | PASS_BY_VALUE | READ_ONLY))
      return false;

    if (f & NO_FIELD
        && f & VOLATILE)
      return false;

    if (f & OVERRIDE
        && f & (LOCK | RWLOCK | VIRTUAL))
      return false;

    if (f & PASS_BY_VALUE
        && f & REFERENCE)
      return false;

    if (f & PRIVATE
        && f & PRIV_SET)
      return false;

    if (f & PRIV_SET
        && f & (NO_SETTERS | REFERENCE))
      return false;

    if (f & READ_ONLY
        && f & (LOCK | MUTABLE | NO_SETTERS | PRIV_SET | REFERENCE | RWLOCK
                | VOLATILE))
      return false;

    if (f & VIRTUAL
        && f & VOLATILE)
      return false;

    return true;
  }

  inline void
  write_macro_comment (features f)
  {
    cout << R"123(/**
 * Declares a property.
 *
)123";

    // Name
    cout << " * The property name is taken from the parameter Name.\n";

    // Type
    if (f & DETECT_TYPE)
      cout << " * The type is automatically detected.\n";
    else
      cout << " * The type is taken from the parameter Type.\n";

    if (f & NO_COPYING)
      cout << " * The property type is not copied, there is no copy setter.\n";
    else if (f & PASS_BY_VALUE)
      cout << " * The property type is passed by value.\n";
    else if (f & REFERENCE)
      cout << " * The property type should be a reference type.\n";

    if (f & NO_SETTERS)
      cout << " * No setters are generated.\n";

    // Field
    if (f & ABSTRACT)
      {
      }
    if (f & CUSTOM_FIELD)
      cout << " * The property is using a custom field, specified using the "
        "Field parameter.\n";
    else if (f & NO_FIELD)
      cout << " * The property is using the field whose name is <<Name>>_.\n";
    else
      cout << " * The property declares its field whose name is <<Name>>_.\n";

    // Mutability
    if (f & MUTABLE)
      cout << " * The property is mutable (its value can be changed even "
        "through const references.\n";
    else if (f & READ_ONLY)
      cout << " * The property is read-only.\n";
    else
      cout << " * The property is read-write.\n";

    // Access
    if (f & PRIVATE)
      cout << " * The property is private.\n";
    else if (f & PRIV_SET)
      cout << " * The property is public, but any writable access is "
        "private.\n";
    else
      cout << " * The property is public.\n";

    // Parameterless features
    if (f & ABSTRACT)
      cout << " * The property accessors are abstract.\n";
    else if (f & OVERRIDE)
      cout << " * The property accessors override accessors from a "
        "superclass.\n";
    else if (f & VIRTUAL)
      cout << " * The property accessors are virtual.\n";

    if (f & EXCEPTIONS)
      cout << " * The property accessors may throw.\n";
    else
      cout << " * The property accessors are noexcept.\n";

    if (!(f & (ABSTRACT | OVERRIDE | NOT_CONSTEXPR)))
      cout << " * The property accessors are constexpr.\n";

    if (f & LOCK)
      cout << " * The property has an associated lock, accessible using the "
        "<<Name>>_lock method.\n";
    else if (f & RWLOCK)
      cout << " * The property has an associated shared lock, accessible "
        "using the <<Name>>_lock method.\n";
    else if (f & VOLATILE)
      cout << " * The property is volatile, but does not have an associated "
        "lock.\n";

    cout << " */\n";
  }

  inline void
  write_macro_name (features f)
  {
    cout << "FASTER_PROPERTY";

    if (f & ABSTRACT)
      cout << "_AB";
    if (f & CUSTOM_FIELD)
      cout << "_CF";
    if (f & DETECT_TYPE)
      cout << "_DT";
    if (f & EXCEPTIONS)
      cout << "_EX";
    if (f & LOCK)
      cout << "_LOCK";
    if (f & MUTABLE)
      cout << "_MUTABLE";
    if (f & NOT_CONSTEXPR)
      cout << "_NC";
    if (f & NO_COPYING)
      cout << "_NCP";
    if (f & NO_FIELD)
      cout << "_NF";
    if (f & NO_SETTERS)
      cout << "_NS";
    if (f & OVERRIDE)
      cout << "_OV";
    if (f & PASS_BY_VALUE)
      cout << "_PBV";
    if (f & PRIVATE)
      cout << "_PRIV";
    if (f & PRIV_SET)
      cout << "_PRIVSET";
    if (f & READ_ONLY)
      cout << "_RO";
    if (f & REFERENCE)
      cout << "_REF";
    if (f & RWLOCK)
      cout << "_RWLOCK";
    if (f & VOLATILE)
      cout << "_VOLATILE";
    if (f & VIRTUAL)
      cout << "_VT";
  }

  inline void
  write_macro_args (features f)
  {
    cout << "(Name";

    if (!(f & DETECT_TYPE))
      cout << ", Type";
    if (f & CUSTOM_FIELD)
      cout << ", Field";

    cout << ")";
  }

  inline void
  write_field (features f)
  {
    if (f & CUSTOM_FIELD)
      cout << "Field";
    else
      cout << "Name##_";
  }

  inline void
  write_type (features f)
  {
    if (f & DETECT_TYPE)
      {
        cout << "decltype (";
        write_field (f);
        cout << ")";
      }
    else
      cout << "Type";
  }

  inline void
  begin_item (bool &first_item)
  {
    cout << " \\\n";
    if (first_item)
      first_item = false;
    else
      cout << "  \\\n";
  }

  inline void
  declare_field (features f,
                 bool &first_item)
  {
    if (f & (ABSTRACT | CUSTOM_FIELD | NO_FIELD))
      return;

    begin_item (first_item);

    cout << "  private: \\\n"
      << "  ";

    if (f & MUTABLE)
      cout << "mutable ";

    if (f & DETECT_TYPE)
      cout << "decltype (Name##_) ";
    else
      cout << "Type ";

    if (f & VOLATILE)
      cout << "volatile ";
    if (f & READ_ONLY)
      cout << "const ";

    cout << "Name##_;";
  }

  inline void
  declare_const_getter (features f,
                        bool &first_item)
  {
    if (f & MUTABLE)
      return;

    begin_item (first_item);

    if (f & PRIVATE)
      cout << "  private: \\\n";
    else
      cout << "  public: \\\n";

    cout << "  ";

    if (!(f & (ABSTRACT | NOT_CONSTEXPR | OVERRIDE)))
      cout << "constexpr ";

    if (f & (ABSTRACT | VIRTUAL))
      cout << "virtual ";

    write_type (f);

    if (!(f & (PASS_BY_VALUE | REFERENCE)))
      {
        cout << " const";

        if (f & VOLATILE)
          cout << " volatile";

        cout << " &";
      }

    cout << " \\\n";

    cout << "  Name () const";

    if (!(f & (ABSTRACT | OVERRIDE | VIRTUAL)
          && f & EXCEPTIONS))
      cout << " noexcept";

    if (f & OVERRIDE)
      cout << " override";

    if (f & ABSTRACT)
      cout << " = 0;";
    else
      {
        cout << " \\\n";
        cout << "  { \\\n";
        cout << "    return ";
        write_field (f);
        cout << "; \\\n";
        cout << "  }";
      }
  }

  inline void
  declare_nonconst_getter (features f,
                           bool &first_item)
  {
    if (f & (READ_ONLY | REFERENCE))
      return;

    begin_item (first_item);

    if (f & (PRIVATE | PRIV_SET))
      cout << "  private: \\\n";
    else
      cout << "  public: \\\n";

    cout << "  ";

    if (!(f & (ABSTRACT | NOT_CONSTEXPR | OVERRIDE)))
      cout << "constexpr ";

    if (f & (ABSTRACT | VIRTUAL))
      cout << "virtual ";

    write_type (f);

    if (f & VOLATILE)
      cout << " volatile";

    cout << " &";

    cout << " \\\n";

    cout << "  Name ()";

    if (f & MUTABLE)
      cout << " const";

    if (!(f & (ABSTRACT | OVERRIDE | VIRTUAL)
          && f & EXCEPTIONS))
      cout << " noexcept";

    if (f & OVERRIDE)
      cout << " override";

    if (f & ABSTRACT)
      cout << " = 0;";
    else
      {
        cout << " \\\n";
        cout << "  { \\\n";
        cout << "    return ";
        write_field (f);
        cout << "; \\\n";
        cout << "  }";
      }
  }

  inline void
  declare_setter (features f,
                  bool &first_item)
  {
    if (f & (NO_COPYING | NO_SETTERS | READ_ONLY | REFERENCE))
      return;

    begin_item (first_item);

    if (f & (PRIVATE | PRIV_SET))
      cout << "  private: \\\n";
    else
      cout << "  public: \\\n";

    cout << "  void \\\n";
    cout << "  Name (";

    write_type (f);

    if (!(f & PASS_BY_VALUE))
      cout << " const";

    cout << " ";

    if (!(f & PASS_BY_VALUE))
      cout << "&";

    cout << "Name##_new_value)";

    if (f & MUTABLE)
      cout << " const";

    if (!(f & EXCEPTIONS))
      cout << " noexcept";

    cout << " \\\n";
    cout << "  { \\\n";
    cout << "    Name () = Name##_new_value; \\\n";
    cout << "  }";
  }

  inline void
  declare_move_setter (features f,
                       bool &first_item)
  {
    if (f & (NO_SETTERS | PASS_BY_VALUE | READ_ONLY | REFERENCE))
      return;

    begin_item (first_item);

    if (f & (PRIVATE | PRIV_SET))
      cout << "  private: \\\n";
    else
      cout << "  public: \\\n";

    cout << "  void \\\n";
    cout << "  Name (";

    write_type (f);

    cout << " &&Name##_new_value)";

    if (f & MUTABLE)
      cout << " const";

    if (!(f & EXCEPTIONS))
      cout << " noexcept";

    cout << " \\\n";
    cout << "  { \\\n";
    cout << "    Name () = std::move (Name##_new_value); \\\n";
    cout << "  }";
  }

  inline constexpr const char *
  lock_class (features f)
  {
    return f & LOCK ? "std::mutex" : "std::shared_mutex";
  }

  inline void
  declare_lock (features f,
                bool &first_item)
  {
    if (!(f & (LOCK | RWLOCK)))
      return;

    begin_item (first_item);

    cout << "  private: \\\n";
    cout << "  mutable " << lock_class (f)
      << " Name##_lock_; \\\n";

    if (f & PRIVATE)
      cout << "  private: \\\n";
    else
      cout << "  public: \\\n";

    cout << "  ";

    if (!(f & NOT_CONSTEXPR))
      cout << "constexpr ";

    cout << lock_class (f) << " & \\\n";
    cout << "  Name##_lock () const noexcept \\\n";
    cout << "  { \\\n";
    cout << "    return Name##_lock_; \\\n";
    cout << "  }";
  }

  inline void
  declare_macro (features f)
  {
    write_macro_comment (f);

    cout << "#define ";
    write_macro_name (f);
    write_macro_args (f);

    bool first_item = true;

    declare_field (f, first_item);
    declare_const_getter (f, first_item);
    declare_nonconst_getter (f, first_item);
    declare_setter (f, first_item);
    declare_move_setter (f, first_item);
    declare_lock (f, first_item);

    cout << '\n';
  }

  inline void
  generate (features f)
  {
    if (!features_valid (f))
      return;

    declare_macro (f);
    cout << '\n';
  }
}

int
main ()
{
  cout << "// Generated definitions for <faster/core/property.hh>.\n";
  cout << "// Do not edit this file! Edit gen_property.cc instead.\n";

  cout << R"123(#ifndef __FASTER_CORE_PROPERTY_HH__
# error Do not include <faster/core/property.tcc> alone! Use <faster/core/property.hh> instead.
#endif

)123";

  for (features f = 0; f <= FEATURES_MAX; f ++)
    generate (f);

  return 0;
}
