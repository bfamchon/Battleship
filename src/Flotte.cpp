#include "Flotte.hpp"
#include "Position.hpp"
#include "RandomInRange.hpp"
#include <sstream>

// Les 6 bateaux sont initialisés
Flotte::Flotte() : _nbBateaux(6) 
{
  initFlotte();
}

void Flotte::initFlotte()
{
  // Effacer l'ancienne flotte
  _bateaux.erase(_bateaux.begin(),_bateaux.end());
  for ( int taille=1 ; taille <= 3 ; ++taille )
    _bateaux.push_back(Bateau(taille));
  _bateaux.push_back(3);
  for ( int taille=4 ; taille < 6 ; ++taille )
    _bateaux.push_back(Bateau(taille));
}

/*
 * Generer une nouvelle flotte avec des positions aleatoires
 */
void Flotte::genererFlotte()
{
  int brdSize=10;
  RandomInRange randomIn;
  int directionOk;
  Position randPos;
  // Réinitialiser la flotte
  initFlotte();
  
  for ( int i=0 ; i < 6 ; ++i )
    {
      do 
	{
	  // Positions aléatoires
	  randPos._x = randomIn(0,brdSize-1);
	  randPos._y = randomIn(0,brdSize-1);
	  
	  // Position valide pour cette taille de bateau ?
	  directionOk = estValide(randPos,_bateaux[i].getTaille());
	  
	} while ( directionOk == 0 );
      _bateaux[i].setDir(directionOk);
      _bateaux[i].setEtatPos(false,randPos);
    }
  
}

int Flotte::estValide(Position p,int taille)
{
  int brdSize=10;
  if ( estValideHaut(p,taille) )
    return 1;
  if ( estValideBas(p,taille,brdSize) )
    return 2;
  if ( estValideGauche(p,taille) )
    return 3;
  if ( estValideDroite(p,taille,brdSize) )
    return 4;

  return 0;
}

bool Flotte::estValideHaut(Position p,int taille)
{
  // valide si on ne trouve pas de position égale dans _bateaux vers le haut
  if ( p._y-taille+1 < 0 )
    return false;
  while ( taille > 0 )
    {
      if ( foundInFlotte(p) )
	return false;
      p._y--;
      taille--;
    }
  return true;
}

bool Flotte::estValideBas(Position p,int taille,int brdSize)
{
  if ( p._y+taille-1 > brdSize )
    return false;
  while ( taille > 0 )
    {
      if ( foundInFlotte(p) )
	return false;
      p._y++;
      taille--;
    }
  return true;
}

bool Flotte::estValideGauche(Position p,int taille)
{
  if ( p._x-taille+1 < 0 )
    return false;
  while ( taille > 0 )
    {
      if ( foundInFlotte(p) )
	return false;
      p._x--;
      taille--;
    }
  return true;
}
bool Flotte::estValideDroite(Position p,int taille,int brdSize)
{
  if ( p._x+taille-1 > brdSize )
    return false;
  while ( taille > 0 )
    {
      if ( foundInFlotte(p) )
	return false;
      p._x++;
      taille--;
    }
  return true;
}

bool Flotte::foundInFlotte(Position p) const
{
  // Pour chaque bateau de la flotte, regarder si une position correspond
  for ( unsigned int i=0 ; i < _bateaux.size() ; ++i )
    {
      for ( int j=0 ; j < _bateaux[i].getTaille() ; j++ )
	{
	  if ( _bateaux[i].foundInBateau(p) )
	    return true; 
	}
    }
  return false;
}


std::ostream& operator <<(std::ostream& os,const Flotte& f) {
  for ( std::vector<Bateau>::const_iterator iter = f._bateaux.begin(); 
	iter != f._bateaux.end(); 
	iter++ )
    os << *iter << '\n';
  return os;
}

std::istream & operator>>(std::istream & is, Flotte & f) {
  std::string buffer;
  
  for ( unsigned int i = 0 ; i < 6 ; ++i )
    {
      int etat;
      Position p;
      if ( std::getline(is, buffer, ';') )
	f._bateaux[i].setDir(std::stoi(buffer));

      if ( std::getline(is,buffer, ';') )
	f._bateaux[i].setCoule(std::stoi(buffer));
      
      if ( std::getline(is,buffer, '_') )
	etat = std::stoi(buffer);
      if ( std::getline(is,buffer, '_') )
	p._x = std::stoi(buffer);
      if ( std::getline(is,buffer, ';') )
	p._y = std::stoi(buffer);
      if ( std::getline(is, buffer, '\n') ) { /* pass */ }
      f._bateaux[i].setEtatPos(etat,p);
    }
  return is;
}


bool operator==(const Flotte & f1,const Flotte & f2)
{
  std::ostringstream oss1,oss2;
  oss1 << f1;
  oss2 << f2;
  return oss1.str() == oss2.str(); 
}
