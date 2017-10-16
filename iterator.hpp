/* START OF "iterator.hpp" FILE */

#pragma once
#ifndef _ITERATOR_HPP
#define _ITERATOR_HPP


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::dsHASH_MAP_CONST_ITERATOR (void) :
   pTable(NULL), p(NULL), index(0)
{
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::dsHASH_MAP_CONST_ITERATOR (const TABLE * table) :
   pTable(table), index(0)
{
   if (table == NULL || table->table == NULL) {
      p = NULL;
   } else if (table->size == 0) {
      p = NULL;
   } else {
      for (size_t i = 0; i < table->capacity; i++) {
         if (table->table[i] != NULL) {
            index = i;
            p = table->table[i];
            return;
         }
      }
   }
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::dsHASH_MAP_CONST_ITERATOR (const TABLE * table, const ELEM * p, size_t index) :
   p(p), pTable(table), index(index)
{
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::dsHASH_MAP_CONST_ITERATOR (const dsHASH_MAP_CONST_ITERATOR & it) :
   pTable(it.pTable), p(it.p), index(it.index)
{
}


template <typename VALUE_TYPE>
const VALUE_TYPE & dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}


template <typename VALUE_TYPE>
const VALUE_TYPE * dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator!= (const dsHASH_MAP_CONST_ITERATOR & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator== (const dsHASH_MAP_CONST_ITERATOR & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator!= (const dsHASH_MAP_ITERATOR<VALUE_TYPE> & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator== (const dsHASH_MAP_ITERATOR<VALUE_TYPE> & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> & dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator=
   (const dsHASH_MAP_CONST_ITERATOR & it)
{
   p = it.p;
   pTable = it.pTable;
   index = it.index;

   return *this;
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> & dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator++ (void)
{
   if (pTable == NULL) {
      return *this;
   } else if (p != NULL) {
      p = p->next;
   }

   while (p == NULL && index < pTable->capacity) {
      p = pTable->table[index++];
   }

   if (index >= pTable->capacity) {
      p = NULL;
      return *this;
   }

   return *this;
}


template <typename VALUE_TYPE>
dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> & dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE>::dsHASH_MAP_ITERATOR (void) :
   pTable(NULL), p(NULL), index(0)
{
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE>::dsHASH_MAP_ITERATOR (TABLE * table) :
   pTable(table), index(0)
{
   if (table == NULL || table->table == NULL) {
      p = NULL;
   } else if (table->size == 0) {
      p = NULL;
   } else {
      for (size_t i = 0; i < table->capacity; i++) {
         if (table->table[i] != NULL) {
            index = i;
            p = table->table[i];
            return;
         }
      }
   }
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE>::dsHASH_MAP_ITERATOR (TABLE * table, ELEM * p, size_t index) :
   p(p), pTable(table), index(index)
{
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE>::dsHASH_MAP_ITERATOR (const dsHASH_MAP_CONST_ITERATOR<VALUE_TYPE> & it) :
   pTable(it.pTable), p(it.p), index(it.index)
{
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE>::dsHASH_MAP_ITERATOR(const dsHASH_MAP_ITERATOR & it) :
   pTable(it.pTable), p(it.p), index(it.index)
{
}


template <typename VALUE_TYPE>
VALUE_TYPE & dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator* (void) const
{
   return p->data;
}


template <typename VALUE_TYPE>
VALUE_TYPE * dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator-> (void) const
{
   return &p->data;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator!= (const dsHASH_MAP_ITERATOR & it) const
{
   return p != it.p;
}


template <typename VALUE_TYPE>
bool dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator== (const dsHASH_MAP_ITERATOR & it) const
{
   return p == it.p;
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE> & dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator=
   (const dsHASH_MAP_ITERATOR & it)
{
   p = it.p;
   pTable = it.pTable;
   index = it.index;

   return *this;
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE> & dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator++ (void)
{
   if (pTable == NULL) {
      return *this;
   } else if (p != NULL) {
      p = p->next;
   }
   
   while (p == NULL && index < pTable->capacity) {
      p = pTable->table[++index];
   }
   
   if (index >= pTable->capacity) {
      p = NULL;
      return *this;
   }
   
   return *this;
}


template <typename VALUE_TYPE>
dsHASH_MAP_ITERATOR<VALUE_TYPE> & dsHASH_MAP_ITERATOR<VALUE_TYPE>::operator++ (int i)
{
   dsHASH_MAP_ITERATOR<VALUE_TYPE> * it = this;
   ++(*this);

   return *it;
}


#endif // _ITERATOR_H

/* END OF "iterator.hpp" FILE */
