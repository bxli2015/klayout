
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2017 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include "utHead.h"
#include "bdCommon.h"
#include "dbReader.h"
#include "tlLog.h"

#include <sstream>

BD_PUBLIC int strmxor (int argc, char *argv[]);

TEST(0)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in1.gds";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", input_a.c_str (), input_b.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 0);

  EXPECT_EQ (cap.captured_text (),
    "No differences found\n"
  );
}

TEST(1A)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au1.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
    "Result summary (layers without differences are not shown):\n"
    "\n"
    "  Layer      Output       Differences (shape count)\n"
    "  -------------------------------------------------------\n"
    "  3/0        3/0          30\n"
    "  6/0        6/0          41\n"
    "  8/1        8/1          1\n"
    "  10/0       -            (no such layer in first layout)\n"
    "\n"
  );
}

TEST(1B)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", input_a.c_str (), input_b.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
    "Result summary (layers without differences are not shown):\n"
    "\n"
    "  Layer      Output       Differences (shape count)\n"
    "  -------------------------------------------------------\n"
    "  3/0        -            30\n"
    "  6/0        -            41\n"
    "  8/1        -            1\n"
    "  10/0       -            (no such layer in first layout)\n"
    "\n"
  );
}

TEST(1C)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", input_a.c_str (), input_b.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
  );
}

TEST(1D)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "-s", input_a.c_str (), input_b.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);
  EXPECT_EQ (cap.captured_text (), "");
}

TEST(2)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au2.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", "-l", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    ""
  );
}

TEST(3)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au3.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", "-p=1.0", "-n=4", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
  );
}

TEST(4)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au4.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", "-p=1.0", "-n=4", "-t=0.0,0.005,0.01,0.02,0.09,0.1", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
  );
}

TEST(5)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au5.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", "-b=1000", "-t=0.0,0.005,0.01,0.02,0.09,0.1", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
  );
}

TEST(6)
{
  ut::CaptureChannel cap;

  std::string input_a = ut::testsrc ();
  input_a += "/testdata/bd/strmxor_in1.gds";

  std::string input_b = ut::testsrc ();
  input_b += "/testdata/bd/strmxor_in2.gds";

  std::string au = ut::testsrc ();
  au += "/testdata/bd/strmxor_au6.oas";

  std::string output = this->tmp_file ("tmp.oas");

  const char *argv[] = { "x", "--no-summary", "-ta=INV2", "-tb=2VNI", input_a.c_str (), input_b.c_str (), output.c_str () };

  EXPECT_EQ (strmxor (sizeof (argv) / sizeof (argv[0]), (char **) argv), 1);

  db::Layout layout;

  {
    tl::InputStream stream (output);
    db::Reader reader (stream);
    reader.read (layout);
  }

  this->compare_layouts (layout, au, ut::NoNormalization);
  EXPECT_EQ (cap.captured_text (),
    "Layer 10/0 is not present in first layout, but in second\n"
  );
}