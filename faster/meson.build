# Faster - a C++ miscellaneous utility library
# Copyright 2020  Jakub Kaszycki
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

includes = include_directories ('..')

subdir ('core')

# This library is used to ensure all generated files are generated and to
# provide compile_commands.json for code assistance.
library (
  'faster',

  'faster.cc',

  'core/property.hh',
  core_property_tcc,

  include_directories: includes,
  install: false
)

pkg.generate (
  description: 'A library complementary to Boost',
  install_dir: 'lib/pkgconfig',
  filebase: 'faster',
  name: 'Faster'
)

subdir ('core/tests')
