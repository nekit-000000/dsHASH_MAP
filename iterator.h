/* START OF "iterator.h" FILE */

#pragma once
#ifndef _ITERATOR_H
#define _ITERATOR_H


// forward declaration
template <typename VALUE_TYPE>
class dsHASH_MAP_ITERATOR;

// forward declaration
template <typename VALUE_TYPE>
class dsTABLE;


template <typename VALUE_TYPE>
class dsHASH_MAP_CONST_ITERATOR {
   friend class dsHASH_MAP_ITERATOR<VALUE_TYPE>;
   friend class dsTABLE<VALUE_TYPE>;

public:
   typedef dsTABLE<VALUE_TYPE> TABLE;
   typedef typename dsTABLE<VALUE_TYPE>::dsTABLE_ELEM ELEM;

   dsHASH_MAP_CONST_ITERATOR (void);
   dsHASH_MAP_CONST_ITERATOR (const TABLE * table);
   dsHASH_MAP_CONST_ITERATOR (const TABLE * table, const ELEM * p);
   dsHASH_MAP_CONST_ITERATOR (const dsHASH_MAP_CONST_ITERATOR & it);

   ~dsHASH_MAP_CONST_ITERATOR (void) {}

   const VALUE_TYPE & operator*           (void) const;
   const VALUE_TYPE * operator->          (void) const;
   bool operator!=                        (const dsHASH_MAP_CONST_ITERATOR & it) const;
   bool operator==                        (const dsHASH_MAP_CONST_ITERATOR & it) const;
   bool operator!=                        (const dsHASH_MAP_ITERATOR<VALUE_TYPE> & it) const;
   bool operator==                        (const dsHASH_MAP_ITERATOR<VALUE_TYPE> & it) const;
   dsHASH_MAP_CONST_ITERATOR & operator=  (const dsHASH_MAP_CONST_ITERATOR & it);
   dsHASH_MAP_CONST_ITERATOR & operator++ (void);
   dsHASH_MAP_CONST_ITERATOR & operator++ (int i);

private:
   size_t index;
   const TABLE * pTable;
   const ELEM * p;
};



template <typename VALUE_TYPE>
class dsHASH_MAP_ITERATOR {
   friend class dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>;
   friend class dsTABLE<VALUE_TYPE>;

public:
   typedef dsTABLE<VALUE_TYPE> TABLE;
   typedef typename dsTABLE<VALUE_TYPE>::dsTABLE_ELEM ELEM;

   dsHASH_MAP_ITERATOR (void);
   dsHASH_MAP_ITERATOR (TABLE * table);
   dsHASH_MAP_ITERATOR (TABLE * table, ELEM * p);
   dsHASH_MAP_ITERATOR (const dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> & it);
   dsHASH_MAP_ITERATOR (const dsHASH_MAP_ITERATOR & it);

   ~dsHASH_MAP_ITERATOR (void) {}

   VALUE_TYPE & operator*           (void) const;
   VALUE_TYPE * operator->          (void) const;
   bool operator!=                  (const dsHASH_MAP_ITERATOR & it) const;
   bool operator==                  (const dsHASH_MAP_ITERATOR & it) const;
   dsHASH_MAP_ITERATOR & operator=  (const dsHASH_MAP_ITERATOR & it);
   dsHASH_MAP_ITERATOR & operator++ (void);
   dsHASH_MAP_ITERATOR & operator++ (int i);

private:
   size_t index;
   TABLE * pTable;
   ELEM * p;
};



#include "iterator.hpp"


#endif // _ITERATOR_H

/* END OF "iterator.h" FILE */
