Chaque insertion se fait dans une zone 2^k -1
Une recherche dans une zone 2^k - 1 vaut au max k

Par exemple 2^3 - 1 = 7 -> 3 comparaisons

Pour FordJhonson le calcul d insertions max se fait log2((3*k)/4) pour chaque valeur k

donc pour 5 valeurs 

C(5) =
ceil(log2(3 * 1 / 4)) +
ceil(log2(3 * 2 / 4)) +
ceil(log2(3 * 3 / 4)) +
ceil(log2(3 * 4 / 4)) +
ceil(log2(3 * 5 / 4))

= 0 + 1 + 2 + 2 + 2
= 7

C(11) = 0 + 1 + 2 + 2 + 2 + 3 + 3 + 3 + 3 + 3 + 4
      = 26