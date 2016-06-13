#include "Flotte.hpp"
#include "Position.hpp"
#include "RandomInRange.hpp"

// Les 6 bateaux sont initialisés
Flotte::Flotte() : _nbBateaux(6) 
{
  initFlotte();
}

void Flotte::initFlotte()
{
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
  // Effacer l'ancienne flotte
  _bateaux.erase(_bateaux.begin(),_bateaux.end());
  // L'initialiser à nouveau
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
