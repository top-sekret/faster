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

core_property_tcc = custom_target (
  'property.tcc',

  capture: true,
  command: [
    executable (
      'gen_property',
      'gen_property.cc',
      native: true
    )
  ],
  install: true,
  install_dir: 'include/faster/core',
  output: 'property.tcc'
)

install_headers (
  'property.hh',

  subdir: 'faster/core'
)
