/* START OF "dshashmap.hpp" FILE */

#pragma once
#ifndef _DSHASH_MAP_HPP
#define _DSHASH_MAP_HPP


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::ITERATOR
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::End (void)
{
   return mapTable.End();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::ITERATOR 
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Begin (void)
{
   return mapTable.Begin();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::CONST_ITERATOR
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::End (void) const
{
   return mapTable.End();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::CONST_ITERATOR 
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Begin (void) const
{
   return mapTable.Begin();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::dsHASH_MAP (size_t capacity) :
   mapTable(capacity), maxLoadFactor(1.0)
{
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::dsHASH_MAP (const dsHASH_MAP & constrTable) :
   mapTable(constrTable.mapTable), hash(constrTable.hash), maxLoadFactor(constrTable.maxLoadFactor)
{
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::dsHASH_MAP (dsHASH_MAP && constrTable)
{
   hash = copyTable.hash;
   maxLoadFactor = copyTable.maxLoadFactor;
   mapTable = std::move(copyTable.mapTable);
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::dsHASH_MAP (void) :
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>(8)
{
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::~dsHASH_MAP (void)
{
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
void dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::SetMaxLoadFactor (float z)
{
   maxLoadFactor = z;
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
bool dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Empty (void) const
{
   return Size() == 0;
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::CONST_ITERATOR
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Find (const KEY_TYPE & key) const
{
   size_t index = GetIndex(key);
   CONST_ITERATOR it = mapTable.Get(index);

   if (it == End() || it->first == key) {
      return it;
   }

   while (!mapTable.NextIsNull(it)) {
      it++;
   }

   if (mapTable.NextIsNull(it) && it->first != key) {
      return End();
   }
   return it;
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::ITERATOR
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Find (const KEY_TYPE & key)
{
   size_t index = GetIndex(key);
   ITERATOR it = mapTable.Get(index);

   if (it == End() || it->first == key) {
      return it;
   }

   while (!mapTable.NextIsNull(it)) {
      it++;
   }

   if (mapTable.NextIsNull(it) && it->first != key) {
      return End();
   }
   return it;
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
void dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Clear (void)
{
   mapTable.Clear();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
void dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Erase (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);
   mapTable.Delete(it);
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
void dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Rehash (void)
{
   size_t newCapacity = mapTable.Capacity() << 1;

   while ((mapTable.Size() / newCapacity) >= maxLoadFactor) {
      newCapacity <<= 1;
   }

   // creating new table
   dsTABLE<ELEM_TYPE> newTable(newCapacity);

   // copying elements
   for (size_t i = 0; i < mapTable.Capacity(); i++) {
      ITERATOR it = mapTable.Get(i);

      if (it != End()) {
         newTable.Insert(*it, hash(it->first) % newCapacity);
         if (it != mapTable.GetLast(i)) {
            while (it != mapTable.GetLast(i)) {
               it++;
               newTable.Insert(*it, hash(it->first) % newCapacity);
            }
         }
      }
   }

   mapTable = std::move(newTable);
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
std::pair<typename dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::ITERATOR, bool> 
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::Insert (const ELEM_TYPE & data)
{
   // check if we need to incrase the capacity
   if (GetLoadFactor() >= maxLoadFactor) {
      Rehash();
   }

   ITERATOR it = Find(data.first);

   if (it == End()) {
      it = mapTable.Insert(data, GetIndex(data.first));
      return std::make_pair(it, true);
   } else {
      it->second = data.second;
      return std::make_pair(it, false);
   }
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
VALUE_TYPE & dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::operator[] (const KEY_TYPE & key)
{
   ITERATOR it = Find(key);

   if (it == End()) {
      ELEM_TYPE insertPair;
      insertPair.first = key;

      // check if we need to incrase the capacity
      if (GetLoadFactor() >= maxLoadFactor) {
         Rehash();
      }

      return mapTable.Insert(insertPair, GetIndex(key))->second;
   } else {
      return it->second;
   }
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
float dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::GetLoadFactor(void) const
{ 
   return (float)(mapTable.Size() / mapTable.Capacity());
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
size_t dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::GetIndex (const KEY_TYPE & key) const 
{
   return hash(key) % mapTable.Capacity();
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH> & 
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::operator= (dsHASH_MAP && copyTable)
{
   hash = copyTable.hash;
   maxLoadFactor = copyTable.maxLoadFactor;
   mapTable = std::move(copyTable.mapTable);

   return *this;
}


template <typename KEY_TYPE, typename VALUE_TYPE, typename HASH>
dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH> & 
   dsHASH_MAP<KEY_TYPE, VALUE_TYPE, HASH>::operator= (const dsHASH_MAP & copyTable)
{
   mapTable = copyTable.mapTable;
   hash = copyTable.hash;
   maxLoadFactor = copyTable.maxLoadFactor;

   return *this;
}


#endif // _DSHASHMAP_HPP

/* END OF "dshashmap.hpp" FILE */
