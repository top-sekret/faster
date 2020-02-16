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

#ifndef __FASTER_CORE_PROPERTY_HH__
#define __FASTER_CORE_PROPERTY_HH__

/*
 * Properties
 *
 * SUMMARY
 *
 * Macros in this file all correspond more or less to a common pattern in C++
 * code for object properties:
 *
 *
 * class example
 * {
 *   ...
 *
 *   type &
 *   property ()
 *   {
 *     return property_;
 *   }
 *
 *   type property_;
 *
 *   ...
 * };
 *
 * While the version presented above is abbreviated for clearness, the macros
 * provide a full, complex property pattern, which allows for maximal
 * efficiency and usage comfort.
 *
 * PBV TYPES
 *
 * In some places we distinguish "PBV types".  These are types like primitives,
 * which exhibit the following properties:
 *
 *   * They are small.  Preferably up to the size of a pointer or not much
 *     larger (not larger than 10 bytes/long double).
 *   * They have trivial constructor, copy constructor and destructor.
 *
 * The *_PBV function variants are optimized for PBV types, especially on weak
 * optimizing compilers or with optimization disabled.  They also should be
 * much easier to debug.
 *
 * PROPERTY FEATURES
 *
 *   * Some of the macros declare the actual field.  Its name is the name of
 *     the property with an underscore appended.  Its type is just the type of
 *     the property, both in normal and in PBV properties.
 *
 *   * A const getter, which returns a const reference (or passes by value for
 *     PBV types). It is constexpr and noexcept.
 *
 *   * A nonconst getter, which returns a reference.  It is constexpr and
 *     noexcept.
 *
 *   * A copy setter, which takes a const reference (a value for PBV types).
 *     It is noexcept iff the copy assignment operator of the type is noexcept.
 *     For non-copy assignable types, this overload does not exist.
 *
 *   * A move setter, which takes a rvalue reference (nonexistent for PBV
 *     types).  It is noexcept iff the move assignment operator of the type is.
 *     For non-move assignable types, this overload does not exist.
 *
 * MACRO DOCUMENTATION
 *
 * FASTER_PROPERTY       - declares a read-write, non-PBV property and the
 *                         corresponding field
 * *_AB                  - declares an abstract property
 * *_CF                  - does not declare a field, accepts the field name
 *                         (may refer to fields of members or even to global
 *                         variables, this is flexible)
 * *_DT                  - (only for _CF or _NF) detects type using declype()
 * *_EX                  - allow the functions to throw
 * *_LOCK                - A mutex is generated for the property.
 * *_MUTABLE             - declares a mutable property, there is no const
 *                         getter, all methods are const. The field, if
 *                         generated, is mutable.
 * *_NC                  - not constexpr
 * *_NCP                 - not copiable (no copy setter)
 * *_NF                  - does not declare a field
 * *_OV                  - mark the functions as override
 * *_PBV                 - declares a PBV property
 * *_PRIV                - declares a private property
 * *_PRIVSET             - declares a property with private nonconst functions
 * *_REF                 - declares a property whose value is a reference
 * *_RO                  - declares a read-only property, there is no nonconst
 *                         getter and there are no setters. The field, if
 *                         generated, is const.
 * *_RWLOCK              - A shared mutex is generated for the property.
 * *_VOLATILE            - The field, if generated, is volatile.
 * *_VT                  - declares a virtual property
 *
 * Please note that you have to include <mutex> or <shared_mutex> yourself.
 *
 * Not all feature combinations are supported. Use common sense and/or view
 * the generated definitions.
 *
 * SOURCE CODE
 *
 * The source of this file is generated using a helper C++ program, which
 * allows for so many variants.  This may have slight influence on compilation
 * time, but absolutely no influence at all on link or runtime time.
 */

// Load the generated macros
#include <faster/core/property.tcc>

#endif /* __FASTER_CORE_PROPERTY_HH__ */
