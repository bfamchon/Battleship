#include "Joueur.hpp"
#include "Position.hpp"
#include <sstream>
#include <iostream>

BOOST_AUTO_TEST_CASE(TestJoueur_1) {
  Joueur j("Eric");
  BOOST_CHECK_EQUAL(j.getPseudo(),"Eric");
}

BOOST_AUTO_TEST_CASE(TestJoueur_2) {
  Joueur j("Eric");
  j.setPseudo("Baptiste");
  BOOST_CHECK_EQUAL(j.getPseudo(),"Baptiste");
}

BOOST_AUTO_TEST_CASE(TestJoueur_3) {
  Joueur j("Pseudo");
  j.setRandFlotte();
  std::cout << j.getFlotte();

  BOOST_CHECK_EQUAL(true,true);
}
