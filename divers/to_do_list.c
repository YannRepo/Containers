To do list
Vector / random acces it
	//check list des typedef
	//check list fonction c++
	//TBD flag
	//suppression commentaires
	//Titres fichier
	main de test perso pour correction
		faire test
		check leaks

Map / red_black_tree / red_black_tree iterator
	//check list des typedef
	//check list fonction c++
	//TBD flag
	//suppression commentaires
	//Titres fichier
	main de test perso pour correction
		faire test
		check leaks

Stack
	//check list des typedef
	//check list fonction c++
	//TBD flag
	//suppression commentaires
	//Titres fichier na
	main de test perso pour correction
		faire test
		check leaks

Set / red_black_tree_set
	//check list des typedef
	//check list fonction c++
	//TBD flag
	//suppression commentaires
	//Titres fichier
	main de test perso pour correction
		faire test
		check leaks
Autre
	leaks sur main sujet
	Makefile avec flags
	ajout i++ apres end pointe sur debut arbre ?
	revoir methode inert/delete RBT
	changer set Julia coheremt mes fichiers
	relire sujet
	set modif value_compare
	set ajout get allocatoor



modif faites:
maj end() dans map et rbt et set et rbt_set
fonction get_allocator
private public sur rbt
suppression get tree head (RBT)
changement right de l'element fantome











//-----------------------------------------------------------------------------------------
//--------------  Map  ---------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//Class value_compare (indispensable ?)
//	Operator()
// --- Constructeurs/ destructeurs
Constructeurs (1/3)
operator=***
get_allocator 

// --- Element access
at?
operator[]

// --- Iterators
//begin / end
//+ en const
rbegin / rend

// --- Capacity
//insert
empty
//size
//max_size

// --- Modifiers
clear***
insert **
erase **
swap

// --- Operations / look up
Count
find  ***
//equal_range
//lower_bound
//upper_bound

// --- observers
key_comp*
value_compare

// --- Nom members fct
Surcharge operator comparaison < > <=.....


//-----------------------------------------------------------------------------------------------------
//--------------  Red_black_tree  ---------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
Constructeurs
operator=***
Destructeur
Rotations
//Insert node
//fix insertion
fix deletion

//begin / end
//+ en const
rbegin / rend

empty
size
max_size
clear***

insert
erase
swap

Count
find
//lower_bound
//upper_bound
//equal_range
key_comp*

Surcharge operator comparaison < > <=.....

//--------------------------------------------------------------------------------------------------------------
//--------------  Red_black_tree_iterator  ---------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
Destructeur / Constructeurs
operator RBT_iterator<const T, node, Compare>() const
operator++
++ operator
operator--
--operator
operator*
operator->
get_node
operator==
operator!=

increase (a faire ?)
decrease (a faire ?)

fonctions en const


//----------------------------------------------------------------------------------------------------------------------
//--------------  Red_black_tree_reverse_iterator  ---------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
TBD utiliser meme que vector ?




