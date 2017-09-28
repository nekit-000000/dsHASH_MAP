/* START OF "dshashmap.h" FILE */

#pragma once
#ifndef _DSHASH_MAP_H
#define _DSHASH_MAP_H

#include "dstable.h"


template <typename KEY_TYPE, 
   typename VALUE_TYPE, 
   typename HASH = std::hash<KEY_TYPE>>
class dsHASH_MAP {
public:
   typedef std::pair<KEY_TYPE, VALUE_TYPE> ELEM_TYPE;
   typedef dsHASH_MAP_ITERATOR<ELEM_TYPE> ITERATOR;
   typedef dsHASH_MAP_CONST_ITERATOR<ELEM_TYPE> CONST_ITERATOR;

   dsHASH_MAP (void);
   dsHASH_MAP (size_t capacity);
   dsHASH_MAP (const dsHASH_MAP & constrTable);
   dsHASH_MAP (dsHASH_MAP && constrTable);

   ~dsHASH_MAP (void);

   VALUE_TYPE & operator[] (const KEY_TYPE & key);
   dsHASH_MAP & operator=  (dsHASH_MAP && copyTable);
   dsHASH_MAP & operator=  (const dsHASH_MAP & copyTable);

   ITERATOR Begin (void);
   ITERATOR End   (void);

   CONST_ITERATOR Begin (void) const;
   CONST_ITERATOR End   (void) const;

   std::pair<ITERATOR, bool> Insert (const ELEM_TYPE & elem);
   ITERATOR Find                    (const KEY_TYPE & key);
   CONST_ITERATOR Find              (const KEY_TYPE & key) const;
   void Clear                       (void);
   void Erase                       (const KEY_TYPE & key);
   bool Empty                       (void) const;
   size_t Size                      (void) const { return mapTable.size; }

   float LoadFactor                 (void) const;
   void MaxLoadFactor               (float z);
   float MaxLoadFactor              (void) const { return maxLoadFactor; }

private:
   void Rehash     (void);
   size_t GetIndex (const KEY_TYPE & key) const;

private:
   dsTABLE<ELEM_TYPE> mapTable;
   HASH hash;
   float maxLoadFactor;
};


#include "dshashmap.hpp"


#endif // _DSHASH_MAP_H

/* END OF "dshashmap.h" FILE */