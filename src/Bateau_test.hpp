#include "Bateau.hpp"
#include "Position.hpp"
#include <sstream>
#include <iostream>

BOOST_AUTO_TEST_CASE(TestBateau_1) {
  Bateau b(5);
  Position pos{9,9},test{0,0},test2{9,5},test3{9,4};
  b.setDir(1);
  b.setEtatPos(false,pos);
  
  BOOST_CHECK_EQUAL(b.getNom(), "Porte-avions");
  BOOST_CHECK_EQUAL(b.getTaille(), 5);
  BOOST_CHECK_EQUAL(b.foundInBateau(test), false);
  BOOST_CHECK_EQUAL(b.foundInBateau(pos), true);
  BOOST_CHECK_EQUAL(b.foundInBateau(test2), true);
  BOOST_CHECK_EQUAL(b.foundInBateau(test3), false);
}

BOOST_AUTO_TEST_CASE(TestBateau_2) {
  Bateau b(3);
  Position pos{9,9};
  std::ostringstream oss;

  b.setDir(1);
  b.setEtatPos(false,pos);
  
  oss << b;

  BOOST_CHECK_EQUAL(b.getNom(), "Sous-marin");
  BOOST_CHECK_EQUAL(b.getTaille(), 3);
  BOOST_CHECK_EQUAL(oss.str(),"1;0;0_9_9;0_9_8;0_9_7;");
}

BOOST_AUTO_TEST_CASE(TestBateau_3) {
  Bateau b(1);
  Position pos{9,9};
  std::ostringstream oss;

  b.setDir(1);
  b.setEtatPos(false,pos);
  
  oss << b;
  BOOST_CHECK_EQUAL(oss.str(),"1;0;0_9_9;");
}

BOOST_AUTO_TEST_CASE(TestBateau_4) {
  Bateau b(3);
  Position pos{9,9};
  std::ostringstream oss;

  b.setDir(1);
  b.setEtatPos(false,pos);
  b.changeBoatPosition(3);

  oss << b;
  BOOST_CHECK_EQUAL(oss.str(),"3;0;0_9_9;0_8_9;0_7_9;");
}
