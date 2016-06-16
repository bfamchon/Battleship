#include "Flotte.hpp"
#include "Position.hpp"
#include <sstream>
#include <iostream>
BOOST_AUTO_TEST_CASE(TestFlotte_1) {
  Flotte f;
  f.genererFlotte();
  std::cout << "Run TestFlotte_1" << std::endl;
  std::ostringstream oss;
  oss << f;
  std::cout << f;
  f.genererFlotte();
  oss << f;
  std::cout << f;
  
  BOOST_CHECK_EQUAL(true,true);
}

BOOST_AUTO_TEST_CASE(TestFlotte_2) {
  Flotte f;
  std::cout << "Run TestFlotte_2" << std::endl;
  std::istringstream iss("1;0;0_0_4;\n1;0;0_1_5;0_1_4;\n2;0;0_3_1;0_3_2;0_3_3;\n1;0;0_7_2;0_7_1;0_7_0;\n1;0;0_2_4;0_2_3;0_2_2;0_2_1;\n2;0;0_4_2;0_4_3;0_4_4;0_4_5;0_4_6;\n");
  iss >> f;
  std::cout << f;
  BOOST_CHECK_EQUAL(true,true);
}

/*
  1;0;0_0_4;\n
  1;0;0_1_5;0_1_4;\n
  2;0;0_3_1;0_3_2;0_3_3;\n
  1;0;0_7_2;0_7_1;0_7_0;\n
  1;0;0_2_4;0_2_3;0_2_2;0_2_1;\n
  2;0;0_4_2;0_4_3;0_4_4;0_4_5;0_4_6;\n
*/

BOOST_AUTO_TEST_CASE(TestFlotte_3) {
  Flotte f,f2;
  f.genererFlotte();
  std::cout << "Run TestFlotte_3" << std::endl;
  std::ostringstream oss;
  oss << f;
  std::cout << f;
  std::istringstream iss(oss.str());
  iss >> f2;
  std::cout << f2;

  BOOST_CHECK_EQUAL(true,true);
}
