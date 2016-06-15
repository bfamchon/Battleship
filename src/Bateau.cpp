#include "Bateau.hpp"

Bateau::Bateau(int taille) : _taille(taille),
			     _coule(false)
{ determinerNom(taille); }

void Bateau::determinerNom(int taille)
{
  switch( taille )
    {
    case 1:
      _nom="Annexe";
      break;
    case 2:
      _nom="Torpilleur";
      break;
    case 3:
      _nom="Sous-marin";
      break;
    case 4:
      _nom="Croiseur";
      break;
    case 5:
      _nom="Porte-avions";
      break;
    }
}
std::string Bateau::getNom() const { return _nom; }
int Bateau::getTaille() const { return _taille; }

/*
 * La position p se trouve sur le bateau ?
 */
bool Bateau::foundInBateau(Position p) const
{
  for (unsigned int i=0 ; i < _etatPos.size() ; ++i )
    {
      if ( _etatPos[i].second._x == p._x && _etatPos[i].second._y == p._y )
	return true;
    }
  return false;
}

void Bateau::setDir(int dir) { _direction=dir; }

/*
 * Affecter un état et position en fonction
 * de la direction et de la taille.
 */
void Bateau::setEtatPos(bool etat,Position pos)
{ 
  for ( int i=0; i < _taille ; ++i )
    {
      _etatPos.push_back(std::make_pair(etat,pos));
      if ( _direction == 1 ) { pos._y--; continue; }
      if ( _direction == 2 ) { pos._y++; continue; }
      if ( _direction == 3 ) { pos._x--; continue; }
      if ( _direction == 4 ) { pos._x++; continue; }
    }
}

void Bateau::setCoule(bool etatBateau) { _coule = etatBateau; }

/*
 * Cette fonction change un bateau existant de position
 * dans une direction souhaitée.
 * Utilisable lors de la position des navires.
 */
void Bateau::changeBoatPosition(int dir)
{
  // récupérer la première position du bateau
  Position basePos = _etatPos[0].second;
  // attribuer la nouvelle direction
  setDir(dir);
  // effacer le vecteur etatPos existant
  _etatPos.erase(_etatPos.begin(),_etatPos.end());
  // le recréer avec la nouvelle direction affecté
  setEtatPos(0,basePos);
}

std::ostream& operator <<(std::ostream& os, const Bateau& b) {
  os << b._direction << ';' << b._coule << ';';

  for ( unsigned int i=0 ; i < b._etatPos.size() ; ++i )
    os << b._etatPos[i].first 
       << '_' << b._etatPos[i].second._x 
       << '_' << b._etatPos[i].second._y << ';';
  return os;
}
