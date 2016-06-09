#include "Bateau.hpp"
#include "Position.hpp"

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
