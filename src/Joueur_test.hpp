#include "Joueur.hpp"
#include "Flotte.hpp"
#include "Position.hpp"
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

BOOST_AUTO_TEST_CASE(TestJoueur_4) {
  Joueur j("Pseudo");
  Flotte f;
  f.genererFlotte();
  j.setRandFlotte();
  
  j.setFlotte(f);

  BOOST_CHECK_EQUAL(f==j.getFlotte(),true);
}
