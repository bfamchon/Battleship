#include "Flotte.hpp"
#include "Position.hpp"
#include <sstream>
#include <iostream>
BOOST_AUTO_TEST_CASE(TestFlotte_1) {
  Flotte f;
  f.genererFlotte();

  std::ostringstream oss;
  oss << f;
  std::cout << f;
  f.genererFlotte();
  oss << f;
  std::cout << f;
  
  BOOST_CHECK_EQUAL(true,true);
}
