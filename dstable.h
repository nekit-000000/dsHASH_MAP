/* START OF "dstable.h" FILE */

#pragma once
#ifndef _DSTABLE_H
#define _DSTABLE_H


#include "iterator.h"


template <typename VALUE_TYPE>
class dsTABLE {
   friend class dsHASH_MAP_ITERATOR<VALUE_TYPE>;
   friend class dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>;

public:
   struct dsTABLE_ELEM {
   public:
      dsTABLE_ELEM (void);
      dsTABLE_ELEM (const VALUE_TYPE & data);
      dsTABLE_ELEM (const dsTABLE_ELEM & elem);

      ~dsTABLE_ELEM(void);

      dsTABLE_ELEM & operator= (const dsTABLE_ELEM & elem);

   public:
      dsTABLE_ELEM * next;
      dsTABLE_ELEM * prev;
      VALUE_TYPE data;
   };

public:
   typedef dsTABLE_ELEM ELEM;
   typedef dsHASH_MAP_ITERATOR<VALUE_TYPE> ITERATOR;
   typedef dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> CONST_ITERATOR;

   dsTABLE (void);
   dsTABLE (size_t capacity);
   dsTABLE (const dsTABLE & constrTable);
   dsTABLE (dsTABLE && constrTable);

   ~dsTABLE (void);

   dsTABLE & operator= (dsTABLE && copyTable);
   dsTABLE & operator= (const dsTABLE & copyTable);

   ITERATOR Begin       (void);
   ITERATOR End         (void);

   CONST_ITERATOR Begin (void) const;
   CONST_ITERATOR End   (void) const;

   ITERATOR Insert        (const VALUE_TYPE & data, const int & index);
   ITERATOR Get           (const int & index);
   CONST_ITERATOR Get     (const int & index) const;
   ITERATOR GetLast       (const int & index);
   CONST_ITERATOR GetLast (const int & index) const;
   ITERATOR Find          (const VALUE_TYPE & data);
   CONST_ITERATOR Find    (const VALUE_TYPE & data) const;
   void Clear             (void);
   void Delete            (ITERATOR & it);
   void Delete            (const VALUE_TYPE & data);

   size_t Capacity        (void) const { return capacity; }
   size_t Size            (void) const { return size; }

private:
   ELEM ** table;
   size_t capacity;
   size_t size;
};


#include "dstable.hpp"


#endif // _DSTABLE_H

/* END OF "dstable.h" FILE */
