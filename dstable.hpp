/* START OF "dstable.hpp" FILE */

#pragma once
#ifndef _DSTABLE_HPP
#define _DSTABLE_HPP


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE_ELEM::dsTABLE_ELEM (const VALUE_TYPE & data) :
   next(NULL), prev(NULL), data(data)
{
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE_ELEM::dsTABLE_ELEM (void) :
   next(NULL), prev(NULL)
{
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::dsTABLE_ELEM & dsTABLE<VALUE_TYPE>::dsTABLE_ELEM::operator= (const dsTABLE_ELEM & elem)
{
   dsTABLE_ELEM * pElem = this;
   dsTABLE_ELEM * pPrev = pElem;
   const dsTABLE_ELEM * pCopy = &elem;

   while (pElem != NULL && pCopy != NULL) {
      pElem->data = pCopy->data;

      pPrev = pElem;
      pElem = pElem->next;
      pCopy = pCopy->next;
   }

   while (pCopy != NULL) {
      pElem = new dsTABLE_ELEM(pCopy->data);

      pElem->prev = pPrev;
      pElem->next = NULL;
      pPrev = pElem;
      pElem = pElem->next;
      pCopy = pCopy->next;
   }

   if (pElem != NULL) {
      delete pElem->next;
   }

   return *this;
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR dsTABLE<VALUE_TYPE>::End (void)
{
   return ITERATOR(this, NULL);
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR dsTABLE<VALUE_TYPE>::Begin (void)
{
   if (size == 0) {
      return End();
   }
   return ITERATOR(this);
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::CONST_ITERATOR dsTABLE<VALUE_TYPE>::End (void) const
{
   return CONST_ITERATOR(this, NULL);
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::CONST_ITERATOR dsTABLE<VALUE_TYPE>::Begin (void) const
{
   if (size == 0) {
      return End();
   }
   return CONST_ITERATOR(this);
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE_ELEM::dsTABLE_ELEM (const dsTABLE_ELEM & elem)
{
   data = elem.data;
   prev = NULL;

   if (elem.next == NULL) {
      next = NULL;
   } else {
      dsTABLE_ELEM * pElem = elem.next;
      dsTABLE_ELEM * pNext;

      next = new dsTABLE_ELEM(pElem->data);
      next->prev = this;
      pElem = pElem->next;
      pNext = next;

      while (pElem != NULL) {
         next->next = new dsTABLE_ELEM(pElem->data);
         next->next->prev = next;

         pElem = pElem->next;
         next = next->next;
      }
      next = pNext;
   }
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE_ELEM::~dsTABLE_ELEM (void)
{
   dsTABLE_ELEM * pElem = this;

   while (pElem->next != NULL) {
      pElem = pElem->next;
   }

   while (pElem != this) {
      pElem = pElem->prev;
      free(pElem->next);
   }
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE (void) :
   dsTABLE(8)
{
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE (const dsTABLE & constrTable)
{
   table = new ELEM * [constrTable.capacity];
   size = constrTable.size;
   capacity = constrTable.capacity;

   for (size_t i = 0; i < capaciti; i++) {
      if (constrTable[i] == NULL) {
         table[i] = NULL;
      }
      else {
         table[i] = new ELEM(constructable[i]);
      }
   }
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE (size_t capacity) :
   capacity(capacity), size(0)
{
   table = new ELEM * [capacity];

   for (size_t i = 0; i < capacity; i++) {
      table[i] = NULL;
   }
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::dsTABLE (dsTABLE && constrTable)
{
   size = constrTable.size;
   capacity = constrTable.capacity;
   table = constrTable.table;
   constrTable.table = NULL;
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE>::~dsTABLE (void)
{
   if (table == NULL) {
      return;
   }

   for (size_t i = 0; i < capacity; i++) {
      if (table[i] != NULL) {
         delete table[i];
      }
   }

   delete [] table;
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR 
   dsTABLE<VALUE_TYPE>::Insert (const VALUE_TYPE & data, const int & index)
{
   if (index >= capacity) {
      return End();
   }

   size++;
   if (table[index] == NULL) {
      table[index] = new ELEM(data);
      return ITERATOR(this, table[index]);
   } else {
      ELEM * pElem = table[index];

      while (pElem->next != NULL) {
         pElem = pElem->next;
      }

      pElem->next = new ELEM(data);
      pElem->next->next = NULL;
      pElem->next->prev = pElem;

      return ITERATOR(this, pElem->next);
   }
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR
   dsTABLE<VALUE_TYPE>::Find (const VALUE_TYPE & data)
{
   for (size_t i = 0; i < capacity; i++) {
      ELEM * pElem = table[i];

      while (pElem != NULL) {
         if (pElem->data == data) {
            return ITERATOR(this, pElem);
         }

         pElem = pElem->next;
      }
   }

   return End();
}



template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR
dsTABLE<VALUE_TYPE>::Get (const int & index)
{
   if ((size_t)index >= capacity) {
      return End();
   }
   return ITERATOR(this, table[index]);
}



template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::CONST_ITERATOR
dsTABLE<VALUE_TYPE>::Get (const int & index) const
{
   if ((size_t)index >= capacity) {
      return End();
   }
   return CONST_ITERATOR(this, table[index]);
}


/* Function returns ITERATOR of the last element in table[index] row */
template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::ITERATOR
   dsTABLE<VALUE_TYPE>::GetLast (const int & index)
{
   if ((size_t)index >= capacity || table[index] == NULL) {
      return End();
   }

   ELEM * p = table[index];

   while (p->next != NULL) {
      p = p->next;
   }
   return ITERATOR(this, p);
}



/* Function returns CONST_ITERATOR of the last element in table[index] row */
template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::CONST_ITERATOR
   dsTABLE<VALUE_TYPE>::GetLast (const int & index) const
{
   if ((size_t)index >= capacity || table[index] == NULL) {
      return End();
   }

   ELEM * p = table[index];

   while (p->next != NULL) {
      p = p->next;
   }
   return CONST_ITERATOR(this, p);
}


template <typename VALUE_TYPE>
typename dsTABLE<VALUE_TYPE>::CONST_ITERATOR
   dsTABLE<VALUE_TYPE>::Find (const VALUE_TYPE & data) const
{
   for (size_t i = 0; i < capacity; i++) {
      ELEM * pElem = table[i];

      while (pElem != NULL) {
         if (pElem->data == data) {
            return CONST_ITERATOR(this, pElem);
         }

         pElem = pElem->next;
      }
   }

   return End();
}


template <typename VALUE_TYPE>
void dsTABLE<VALUE_TYPE>::Clear (void)
{
   for (size_t i = 0; i < capacity; i++) {
      if (table[i] != NULL) {
         delete table[i];
         table[i] = NULL;
      }
   }

   size = 0;
}


template <typename VALUE_TYPE>
void dsTABLE<VALUE_TYPE>::Delete (ITERATOR & it)
{
   if (it == End()) {
      return;
   }

   size--;

   ELEM * p = it.p;
   if (p->next != NULL) {
      p->next->prev = p->prev;
   }

   if (p->prev != NULL) {
      p->prev->next = p->next;
   } else {
      table[it.index] = NULL;
   }

   free(p);
}


template <typename VALUE_TYPE>
void dsTABLE<VALUE_TYPE>::Delete (const VALUE_TYPE & data)
{
   ITERATOR it = Find(data);
   Delete(it);
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE> &dsTABLE<VALUE_TYPE>::operator= (dsTABLE && copyTable)
{
   if (copyTable.table == table) {
      return *this;
   }

   for (size_t i = 0; i < capacity; i++) {
      delete table[i];
   }
   delete table;

   size = copyTable.size;
   capacity = copyTable.capacity;
   table = copyTable.table;
   copyTable.table = NULL;

   return *this;
}


template <typename VALUE_TYPE>
dsTABLE<VALUE_TYPE> & dsTABLE<VALUE_TYPE>::operator= (const dsTABLE & copyTable)
{
   size = copyTable.size;

   if (capacity != copyTable.capacity) {
      // Delete previous table
      for (size_t i = 0; i < capacity; i++) {
         if (table[i] != NULL) {
            delete table[i];
         }
      }
      delete[] table;

      // Init new table
      capacity = copyTable.capacity;
      table = new ELEM * [capacity];

      // Copy data
      for (size_t i = 0; i < capacity; i++) {
         if (copyTable.table[i] == NULL) {
            table[i] = NULL;
         } else {
            table[i] = new ELEM(*copyTable.table[i]);
         }
      }
   } else {
      for (size_t i = 0; i < capacity; i++) {
         if (table[i] == NULL && copyTable.table[i] != NULL) {
            table[i] = new ELEM(*copyTable.table[i]);
         } else if (table[i] != NULL && copyTable.table[i] == NULL) {
            delete table[i];
            table[i] = NULL;
         } else {
            *table[i] = *copyTable.table[i];
         }
      }
   }

   return *this;
}


#endif // _DSTABLE_HPP

/* END OF "dstable.hpp" FILE */
