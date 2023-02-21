//-----------------------------------------------------------------------------------------
//--------------  Map  ---------------------------------------------------------------------
//------------------------------------------------------------------------------------------
//Class value_compare (indispensable ?)
//	Operator()
// --- Constructeurs/ destructeurs
Constructeurs (1/3)
operator=
get_allocator 

// --- Element access
at?
operator[]

// --- Iterators
begin / end
+ en const
rbegin / rend

// --- Capacity
//insert
empty
size
max_size

// --- Modifiers
clear
insert ***
erase ***
swap

// --- Operations / look up
Count
find  ***
equal_range
//lower_bound
//upper_bound

// --- observers
key_comp
value_compare

// --- Nom members fct
Surcharge operator comparaison < > <=.....


//-----------------------------------------------------------------------------------------------------
//--------------  Red_black_tree  ---------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
Constructeurs
operator=
Destructeur
Rotations
//Insert node
//fix insertion
fix deletion

begin / end
+ en const
rbegin / rend

empty
size
max_size
clear

insert
erase
swap

Count
//find
//lower_bound**
//upper_bound**
equal_range
key_comp

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




