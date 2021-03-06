/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include <gtest/gtest.h>

#include "../linker_utils.h"

TEST(linker_utils, normalize_path_smoke) {
  std::string output;
  ASSERT_TRUE(normalize_path("/../root///dir/.///dir2/somedir/../zipfile!/dir/dir9//..///afile", &output));
  ASSERT_EQ("/root/dir/dir2/zipfile!/dir/afile", output);

  ASSERT_TRUE(normalize_path("/../root///dir/.///dir2/somedir/.../zipfile!/.dir/dir9//..///afile", &output));
  ASSERT_EQ("/root/dir/dir2/somedir/.../zipfile!/.dir/afile", output);

  ASSERT_TRUE(normalize_path("/root/..", &output));
  ASSERT_EQ("/", output);

  ASSERT_TRUE(normalize_path("/root/notroot/..", &output));
  ASSERT_EQ("/root/", output);

  ASSERT_TRUE(normalize_path("/a/../../b", &output));
  ASSERT_EQ("/b", output);

  output = "unchanged";
  ASSERT_FALSE(normalize_path("root///dir/.///dir2/somedir/../zipfile!/dir/dir9//..///afile", &output));
  ASSERT_EQ("unchanged", output);
}
